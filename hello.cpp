#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

const int SIZE = 100;  // 行列のサイズ（100元連立方程式）

// ガウス・ジョルダン法で解を求める関数
bool gaussJordan(std::vector<std::vector<double>>& matrix, std::vector<double>& solution) {
    int n = matrix.size();
    std::vector<std::vector<double>> augmented(n, std::vector<double>(n + 1));

    // 拡張行列を作成
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented[i][j] = matrix[i][j];
        }
        augmented[i][n] = solution[i];  // 定数項
    }

    // ガウス・ジョルダン法で解を求める
    for (int i = 0; i < n; ++i) {
        // ピボット選択
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::fabs(augmented[k][i]) > std::fabs(augmented[maxRow][i])) {
                maxRow = k;
            }
        }

        // 行を交換
        if (i != maxRow) {
            std::swap(augmented[i], augmented[maxRow]);
        }

        // ピボットを1にする
        double pivot = augmented[i][i];
        if (pivot == 0) {
            return false;  // 解なし
        }
        for (int j = 0; j < n + 1; ++j) {
            augmented[i][j] /= pivot;
        }

        // 他の行を消去
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double factor = augmented[j][i];
                for (int k = 0; k < n + 1; ++k) {
                    augmented[j][k] -= factor * augmented[i][k];
                }
            }
        }
    }

    // 解を取り出す
    for (int i = 0; i < n; ++i) {
        solution[i] = augmented[i][n];
    }

    return true;
}

// CSVファイルから行列と定数項を読み込む関数
bool readCSV(const std::string& matrixFilename, const std::string& vectorFilename, 
             std::vector<std::vector<double>>& matrix, std::vector<double>& solution) {
    std::ifstream matrixFile(matrixFilename);
    std::ifstream vectorFile(vectorFilename);
    
    if (!matrixFile || !vectorFile) {
        std::cerr << "ファイルを開けません: " << matrixFilename << " または " << vectorFilename << std::endl;
        return false;
    }

    std::string line;
    int row = 0;

    // 行列の読み込み
    while (std::getline(matrixFile, line) && row < SIZE) {
        std::stringstream ss(line);
        std::string cell;
        int col = 0;
        while (std::getline(ss, cell, ',')) {
            matrix[row][col] = std::stod(cell);  // 行列の係数を格納
            col++;
        }
        row++;
    }

    // 定数項ベクトルの読み込み
    row = 0;
    while (std::getline(vectorFile, line) && row < SIZE) {
        solution[row] = std::stod(line);  // 定数項を格納
        row++;
    }

    return true;
}

// 解をCSVファイルに書き出す関数
void writeCSV(const std::string& filename, const std::vector<double>& solution) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "ファイルを書き込めません: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < SIZE; ++i) {
        file << solution[i] << std::endl;
    }
}

int main() {
    // 行列と解を格納するためのベクトル
    std::vector<std::vector<double>> matrix(SIZE, std::vector<double>(SIZE, 0));
    std::vector<double> solution(SIZE, 0);

    // CSVファイルからデータを読み込む
    if (!readCSV("matrix1.csv", "vector1.csv", matrix, solution)) {
        std::cerr << "CSVファイルの読み込みに失敗しました。" << std::endl;
        return 1;
    }

    // ガウス・ジョルダン法で連立方程式を解く
    if (!gaussJordan(matrix, solution)) {
        std::cerr << "解なし: 連立方程式は解けません。" << std::endl;
        return 1;
    }

    // 解をCSVに出力
    writeCSV("solution.csv", solution);

    std::cout << "解が solution.csv に保存されました。" << std::endl;

    return 0;
}
