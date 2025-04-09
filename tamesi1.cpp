#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// CSVから行列を読み込む
vector<vector<double>> readMatrixCSV(const string& filename) {
    vector<vector<double>> matrix;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(stod(cell));
        }
        matrix.push_back(row);
    }
    return matrix;
}

// CSVからベクトルを読み込む
vector<double> readVectorCSV(const string& filename) {
    vector<double> vec;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vec.push_back(stod(line));
    }
    return vec;
}

// 結果を書き出す
void writeVectorCSV(const string& filename, const vector<double>& vec) {
    ofstream file(filename);
    for (double val : vec) {
        file << val << endl;
    }
}

// ガウス消去法で Ax = b を解く
vector<double> gaussianElimination(vector<vector<double>> A, vector<double> b) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        // ピボット選択
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        // 前進消去
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // 後退代入
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = b[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }

    return x;
}

int main() {
    // 1つ目の連立方程式
    auto A1 = readMatrixCSV("matrix1.csv");
    auto b1 = readVectorCSV("vector1.csv");
    auto x1 = gaussianElimination(A1, b1);
    writeVectorCSV("solution1.csv", x1);

    // 2つ目の連立方程式
    auto A2 = readMatrixCSV("matrix2.csv");
    auto b2 = readVectorCSV("vector2.csv");
    auto x2 = gaussianElimination(A2, b2);
    writeVectorCSV("solution2.csv", x2);

    cout << "両方の連立方程式の解を solution1.csv および solution2.csv に出力しました。" << endl;
    return 0;
}
