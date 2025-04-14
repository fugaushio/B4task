#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

const int MAX_N = 100; // 最大サイズ
double A[MAX_N][MAX_N], b[MAX_N], x[MAX_N];
int N; // 実際のサイズ（行数）

// ガウスの消去法（ピボットあり）
void gaussianEliminationWithPivoting() {
    for (int k = 0; k < N; ++k) {
        int maxRow = k;
        for (int i = k + 1; i < N; ++i) {
            if (fabs(A[i][k]) > fabs(A[maxRow][k])) {
                maxRow = i;
            }
        }
        for (int j = 0; j < N; ++j) swap(A[k][j], A[maxRow][j]);
        swap(b[k], b[maxRow]);

        for (int i = k + 1; i < N; ++i) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < N; ++j) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    for (int i = N - 1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i + 1; j < N; ++j) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

void checkResidualError(double originalA[MAX_N][MAX_N], double originalB[MAX_N]) {
    double error = 0.0;
    for (int i = 0; i < N; ++i) {
        double Ax_i = 0.0;
        for (int j = 0; j < N; ++j) {
            Ax_i += originalA[i][j] * x[j];
        }
        double diff = Ax_i - originalB[i];
        error += diff * diff;
    }
    cout << "残差の二乗ノルム（誤差）: " << sqrt(error) << endl;
}

bool readMatrixCSV(const string& filename, double A[MAX_N][MAX_N]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "行列ファイルを開けませんでした: " << filename << endl;
        return false;
    }

    string line;
    N = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        int col = 0;
        while (getline(ss, value, ',')) {
            A[N][col++] = stod(value);
        }
        N++;
    }

    file.close();
    return true;
}

bool readVectorCSV(const string& filename, double b[MAX_N]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ベクトルファイルを開けませんでした: " << filename << endl;
        return false;
    }

    string line;
    int i = 0;
    while (getline(file, line)) {
        b[i++] = stod(line);
    }

    file.close();
    return true;
}

int main() {
    string matrixFile = "/home/suwahikaru/B4task/Input/matrix1.csv";

    string vectorFile = "/home/suwahikaru/B4task/Input/vector1.csv";

    if (!readMatrixCSV(matrixFile, A)) return 1;
    if (!readVectorCSV(vectorFile, b)) return 1;

    double originalA[MAX_N][MAX_N], originalB[MAX_N];
    for (int i = 0; i < N; ++i) {
        originalB[i] = b[i];
        for (int j = 0; j < N; ++j) {
            originalA[i][j] = A[i][j];
        }
    }

    gaussianEliminationWithPivoting();

    cout << "\n解 x:\n";
    for (int i = 0; i < N; ++i) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    checkResidualError(originalA, originalB);

    return 0;
}
