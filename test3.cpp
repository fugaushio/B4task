#include <Eigen/Dense>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace Eigen;
using namespace std;

// -----------------------------------------------------------------------------
// CSV ファイルへ Eigen の行列／ベクトルを書き出すユーティリティ
// -----------------------------------------------------------------------------
template <typename Derived>
bool writeCSV(const string &filename, const Eigen::MatrixBase<Derived> &mat)
{
    ofstream file(filename);
    if (!file.is_open()) return false;

    for (Index i = 0; i < mat.rows(); ++i)
    {
        for (Index j = 0; j < mat.cols(); ++j)
        {
            file << mat(i, j);
            if (j != mat.cols() - 1) file << ",";
        }
        file << "\n";
    }
    return true;
}

// -----------------------------------------------------------------------------
// CSV ファイルを読み取り Eigen::MatrixXd へ取り込むユーティリティ
// -----------------------------------------------------------------------------
bool readCSV(const string &filename, MatrixXd &mat)
{
    ifstream file(filename);
    if (!file.is_open()) return false;

    vector<vector<double>> values;
    string line, cell;

    // 1 行ずつ読み取り
    while (getline(file, line))
    {
        stringstream linestream(line);
        vector<double> row;
        // カンマ区切りでセルを抽出
        while (getline(linestream, cell, ','))
        {
            row.push_back(stod(cell));
        }
        if (!row.empty()) values.push_back(row);
    }

    if (values.empty()) return false;

    const size_t rows = values.size();
    const size_t cols = values[0].size();
    mat.resize(rows, cols);

    // 2 次元ベクトル → Eigen 行列へコピー
    for (size_t i = 0; i < rows; ++i)
    {
        if (values[i].size() != cols)
        {
            cerr << "エラー: 列数が不一致です (" << filename << ")" << endl;
            return false;
        }
        for (size_t j = 0; j < cols; ++j)
        {
            mat(i, j) = values[i][j];
        }
    }
    return true;
}

// -----------------------------------------------------------------------------
// メイン処理
// -----------------------------------------------------------------------------
int main()
{
    // 1. 係数行列 A (100×100) と右辺ベクトル b (100×1) を読み込む
    MatrixXd A;
    if (!readCSV("matrix1.csv", A))
    {
        cerr << "matrix1.csv を読み込めません" << endl;
        return EXIT_FAILURE;
    }

    MatrixXd bMat;
    if (!readCSV("matrix2.csv", bMat))
    {
        cerr << "matrix2.csv を読み込めません" << endl;
        return EXIT_FAILURE;
    }

    if (bMat.cols() != 1 || bMat.rows() != A.rows())
    {
        cerr << "matrix2.csv は " << A.rows() << " 行 1 列である必要があります" << endl;
        return EXIT_FAILURE;
    }

    VectorXd b = bMat.col(0);

    // 2. A * x = b を QR 分解で求解
    VectorXd x = A.colPivHouseholderQr().solve(b);

    // 3. 残差ノルムをチェック (必要に応じて閾値を変更)
    double residual = (A * x - b).norm();
    if (residual > 1e-6)
    {
        cerr << "警告: 残差が大きい可能性があります (" << residual << ")" << endl;
    }

    // 4. 解ベクトルを CSV へ書き出し
    if (!writeCSV("solution.csv", x))
    {
        cerr << "solution.csv への書き込みに失敗しました" << endl;
        return EXIT_FAILURE;
    }

    cout << "解を書き出しました (残差 " << residual << ")" << endl;
    return EXIT_SUCCESS;
}
