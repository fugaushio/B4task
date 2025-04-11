#include <iostream>
#include <fstream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// CSV読み込み関数
    Eigen::MatrixXd readCSV(const string& filename) {
    ifstream file(filename);
    vector<vector<double>> data;
    string line;

    // 1行ずつ読み込む
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<double> row;

        // カンマで区切って double に変換
        while (getline(ss, value, ',')) {
            try {
                row.push_back(stod(value));
            } catch (...) {
                row.push_back(0.0); // 値が不正なら0として扱う（適宜変更）
            }
        }

        if (!row.empty()) {
            data.push_back(row);
        }
    }

    file.close();

    // ベクトルから Eigen::MatrixXd に変換
    if (data.empty()) {
        return MatrixXd(0, 0);
    }

    size_t rows = data.size();
    size_t cols = data[0].size();
    MatrixXd mat(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            mat(i, j) = data[i][j];
        }
    }

    return mat;
}

// ベクトルCSV読み込み（1列だけ）
    Eigen::VectorXd readVectorCSV(const string& filename) {
    ifstream file(filename);
    vector<double> vec;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            vec.push_back(stod(line));
        }
    }
    
    file.close();

    if(vec.empty()){
        return VectorXd(0,0);
    }

    VectorXd mat(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        mat(i) = vec[i];
    }

    return mat;
}

// 解のCSV出力
void writeVectorCSV(const string& filename, const Eigen::VectorXd& vec) {
    ofstream file(filename);
    for (double val : vec) {
        file << val << "\n";
    }
}

int main(){
    // 読み込み
    auto A1 = readCSV("matrix1.csv");
    auto b1 = readVectorCSV("vector1.csv");
    auto A2 = readCSV("matrix2.csv");
    auto b2 = readVectorCSV("vector2.csv");

    VectorXd x1 = A1.colPivHouseholderQr().solve(b1);
    VectorXd x2 = A2.colPivHouseholderQr().solve(b2);

    // 書き出し
    writeVectorCSV("result1.csv", x1);
    writeVectorCSV("result2.csv", x2);

    cout << "連立方程式を解きました。result1.csv と result2.csv に出力しました。\n";

    return 0;
}