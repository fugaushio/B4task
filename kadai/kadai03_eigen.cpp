#include <iostream>                      // 標準入出力を使うため
#include <fstream>                       // ファイルの読み書きに使う
#include <sstream>                       // 文字列ストリームでCSVをパースするため
#include <vector>                        // ベクトル型（動的配列）を使う
#include <eigen3/Eigen/Dense>                  // Eigenライブラリのメイン機能を使うため


using namespace std;
using namespace Eigen;

// CSVファイルから行列を読み込む関数（行×列指定あり）
MatrixXd readCSVtoMatrix(const string& filename, int rows, int cols) {
    MatrixXd mat(rows, cols);           // 空の行列を定義
    ifstream file(filename);            // ファイルを開く
    string line;

    int row = 0;
    while (getline(file, line) && row < rows) {
        stringstream ss(line);
        string cell;
        int col = 0;

        while (getline(ss, cell, ',') && col < cols) {
            mat(row, col) = stod(cell); // 文字列をdoubleに変換して格納
            col++;
        }
        row++;
    }

    return mat;                         // 完成した行列を返す
}

// ベクトルをCSVに書き出す関数（1列ずつ書く）
void writeVectorToCSV(const string& filename, const VectorXd& vec) {
    ofstream file(filename);
    for (int i = 0; i < vec.size(); ++i) {
        file << vec(i) << "\n";         // 各要素を1行で書く
    }
}

int main() {
    // CSVファイルから係数行列（100×100）を読み込む
    MatrixXd A = readCSVtoMatrix("matrix1.csv", 100, 100);

    // CSVファイルから定数ベクトル（100×1）を読み込む
    MatrixXd B = readCSVtoMatrix("vector1.csv", 100, 1);

    // Ax = B を解く（数値安定性の高い方法）
    VectorXd x = A.colPivHouseholderQr().solve(B);

    // 結果をoutput.csvに保存
    writeVectorToCSV("output.csv", x);

    cout << "連立方程式を解きました！結果は output.csv に保存されています。" << endl;

    return 0;
}
