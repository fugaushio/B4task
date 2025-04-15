#include <iostream>     //標準の入出力ライブラリ。cout や cin を使うために必要
#include <fstream>      //ファイルの読み書きに使うライブラリ。ifstream（読み込み）、ofstream（書き込み）を使うために必要
#include <Eigen/Dense>   //線形代数ライブラリ Eigen のヘッダ。MatrixXd, VectorXd などの型や操作に使い
#include <string>         //std::string 型を使うためのヘッダ

using namespace std;     //std::cout や std::string を std:: なしで使えるよう
using namespace Eigen;   //Eigen::MatrixXd や Eigen::VectorXd を Eigen:: なしで使えるよう

// CSV読み込み関数（行列用）
MatrixXd readCSVMatrix(const string& filename, int rows, int cols) {  //CSVファイルを読み込んで MatrixXd 型の行列として返す関数。 filename: ファイル名 rows: 行数 cols: 列数
    MatrixXd mat(rows, cols);    //行列 mat を rows x cols サイズで初期化します。
    ifstream file(filename);     //ファイルを開くためのストリームを作成（読み込みモード)
    string line;                 //1行ずつ読み込むための文字列変数

    int row = 0;              //行インデックスの初期化。
    while (getline(file, line) && row < rows) { //ファイルから1行ずつ読み込むループ。rowが指定の数に達するまで繰り返す。
        stringstream ss(line);         //読み込んだ1行をカンマで分割するためのストリームに変換。
        string cell;
        int col = 0;                 //セル（カンマで区切られた値）と列インデックスの初期化。
        while (getline(ss, cell, ',') && col < cols) { //カンマで区切られたセルを1つずつ取り出すループ。
            mat(row, col) = stod(cell);     //セルの文字列を double に変換して行列に格納。
            col++;
        }
        row++;   //行と列のインデックスを更新
    }
    return mat;
}

// CSV出力関数（ベクトル用）
void writeCSVVector(const string& filename, const VectorXd& vec) {  //ベクトルをCSVファイルに保存する関数
    ofstream file(filename);                                 //ファイルを開くためのストリーム（書き込みモード）
    for (int i = 0; i < vec.size(); ++i) {                    //ベクトルの各要素にアクセスするループ。
        file << vec(i);                                //i番目の要素をファイルに書き込む
        if (i != vec.size() - 1)                      //最後の要素以外はカンマを追加
    }
    file << endl;                            //最後の要素以外はカンマを追加
}

int main() {
    const int N = 100;             //行列・ベクトルのサイズを定義（100×100 の行列と長さ100のベクトルを想定）

    // CSVファイルから行列とベクトルを読み込む
    MatrixXd A = readCSVMatrix("matrix1.csv", N, N);   //100×100 の行列を読み込む
    VectorXd b = readCSVMatrix("vector1.csv", N, 1);    //長さ100のベクトルを読み込む

    // 解を計算
    VectorXd x = A.colPivHouseholderQr().solve(b);

    // 解をCSV出力
    writeCSVVector("result.csv", x);

    cout << "解を result.csv に出力しました。" << endl;
    return 0;
}