#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

// CSVファイルから行列を読み込む関数
MatrixXd readCSV(const string& filename, int rows, int cols) {
    ifstream file(filename);
    MatrixXd matrix(rows, cols);
    string line;
    int row = 0;
    while (getline(file, line) && row < rows) {
        stringstream lineStream(line);
        string cell;
        int col = 0;
        while (getline(lineStream, cell, ',') && col < cols) {
            matrix(row, col) = stod(cell);
            col++;
        }
        row++;
    }
    return matrix;
}

// 行列をCSVファイルに書き出す関数
void writeCSV(const string& filename, const MatrixXd& matrix) {
    ofstream file(filename);
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            file << matrix(i, j);
            if (j < matrix.cols() - 1) file << ",";
        }
        file << "\n";
    }
}

int main() {
    // 行列のサイズ
    const int N = 100;

    // CSVファイルから係数行列Aと定数ベクトルbを読み込む
    MatrixXd A = readCSV("coefficients.csv", N, N);
    MatrixXd b = readCSV("constants.csv", N, 1);

    // 連立方程式を解く
    VectorXd x = A.colPivHouseholderQr().solve(b);

    // 結果をCSVファイルに書き出す
    writeCSV("solution.csv", x);

    cout << "連立方程式の解がsolution.csvに書き出されました。" << endl;

    return 0;
}
