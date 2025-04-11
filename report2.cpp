#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// CSV読み込み関数
vector<vector<double>> readCSV(const string& filename) {
    ifstream file(filename);
    vector<vector<double>> data;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<double> row;
        while (getline(ss, value, ',')) {
            row.push_back(stod(value));
        }
        data.push_back(row);
    }
    return data;
}

// ベクトルCSV読み込み（1列だけ）
vector<double> readVectorCSV(const string& filename) {
    ifstream file(filename);
    vector<double> vec;
    string line;
    while (getline(file, line)) {
        vec.push_back(stod(line));
    }
    return vec;
}

// 解のCSV出力
void writeVectorCSV(const string& filename, const vector<double>& vec) {
    ofstream file(filename);
    for (double val : vec) {
        file << val << "\n";
    }
}

// ガウス消去法でAx = bを解く
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
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    return x;
}

int main() {
    // 読み込み
    auto A1 = readCSV("matrix1.csv");
    auto b1 = readVectorCSV("vector1.csv");
    auto A2 = readCSV("matrix2.csv");
    auto b2 = readVectorCSV("vector2.csv");

    // 解く
    auto x1 = gaussianElimination(A1, b1);
    auto x2 = gaussianElimination(A2, b2);

    // 書き出し
    writeVectorCSV("solution1.csv", x1);
    writeVectorCSV("solution2.csv", x2);

    cout << "連立方程式を解きました。solution1.csv と solution2.csv に出力しました。\n";

    return 0;
}

