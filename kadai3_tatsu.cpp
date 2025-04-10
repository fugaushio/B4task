#include <iostream> //c++において画面表示の入出力を扱うライブラリ(i:input,o:output
#include <fstream> //ファイル操作用(今回の場合CSVの読み込み）
#include <Eigen/Dense> 
#include <string>

using namespace std;
using namespace Eigen;

// CSVから行列を読み込む
MatrixXd readMatrixCSV(const string& filename, int rows, int cols) {
    MatrixXd mat(rows, cols);
    ifstream file(filename);
    string line;
    int row = 0;

    while (getline(file, line) && row < rows) {
        stringstream ss(line);
        string cell;
        int col = 0;

        while (getline(ss, cell, ',') && col < cols) {
            mat(row, col) = stod(cell);
            col++;
        }
        row++;
    }

    return mat;
}

// CSVからベクトルを読み込む
VectorXd readVectorCSV(const string& filename, int size) {
    VectorXd vec(size);
    ifstream file(filename);
    string line;
    int i = 0;

    while (getline(file, line) && i < size) {
        vec(i++) = stod(line);
    }

    return vec;
}

// ベクトルをCSVに出力
void writeVectorCSV(const string& filename, const VectorXd& vec) {
    ofstream file(filename);
    for (int i = 0; i < vec.size(); ++i) {
        file << vec(i) << endl;
    }
}

int main() {
    const int N = 100;

    // matrix1.csv + vector1.csv
    MatrixXd A1 = readMatrixCSV("matrix1.csv", N, N);
    VectorXd b1 = readVectorCSV("vector1.csv", N);
    VectorXd x1 = A1.colPivHouseholderQr().solve(b1);
    writeVectorCSV("solution3.csv", x1);

    // matrix2.csv + vector2.csv
    MatrixXd A2 = readMatrixCSV("matrix2.csv", N, N);
    VectorXd b2 = readVectorCSV("vector2.csv", N);
    VectorXd x2 = A2.colPivHouseholderQr().solve(b2);
    writeVectorCSV("solution4.csv", x2);

    cout << "連立方程式を解いて solution3.csv と solution4.csv に出力しました。" << endl;
    return 0;
}
