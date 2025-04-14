#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

const int N = 100; // 100元連立方程式

using namespace std;

// CSV読み込み（1行ずつdoubleで取得）
vector<vector<double>> readCSV(const string& filename, int expected_cols) {
    vector<vector<double>> data;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
            row.push_back(stod(value));
        }
        if (row.size() != expected_cols) {
            cerr << "列数が不正: " << filename << endl;
            exit(1);
        }
        data.push_back(row);
    }

    return data;
}

// ガウス消去法で解く
vector<double> gaussElimination(vector<vector<double>>& A, vector<double>& b) {
    for (int i = 0; i < N; i++) {
        // ピボット選択
        int maxRow = i;
        for (int k = i + 1; k < N; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) maxRow = k;
        }

        // 行を交換
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        // 前進消去
        for (int k = i + 1; k < N; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < N; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // 後退代入
    vector<double> x(N);
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

// 結果をCSVで出力
void writeCSV(const string& filename, const vector<double>& x) {
    ofstream file(filename);
    for (double val : x) {
        file << fixed << setprecision(10) << val << "\n";
    }
    file.close();
}

int main() {
    // 入力ファイル読み込み
    vector<vector<double>> A = readCSV("matrix1.csv", N);
    vector<vector<double>> b_vec = readCSV("matrix2.csv", 1);

    // bの列をベクトルに変換
    vector<double> b;
    for (int i = 0; i < N; i++) {
        b.push_back(b_vec[i][0]);
    }

    // 解を求める
    vector<double> solution = gaussElimination(A, b);

    // 出力
    writeCSV("output.csv", solution);

    cout << "解を output.csv に出力しました。" << endl;
    return 0;
}
