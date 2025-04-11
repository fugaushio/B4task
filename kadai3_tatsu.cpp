#include <iostream> //c++において画面表示の入出力を扱うライブラリ(i:input,o:output）
#include <fstream> //ファイル操作用(今回の場合CSVの読み込み）
#include <Eigen/Dense> //Eigen使用時に書く，数列・行列計算ライブラリ
#include <string> //文字列の道具,std::stringを使用するために

using namespace std;
using namespace Eigen; //いちいちstd::とか書かんでええおまじない

// CSVから行列を読み込む
MatrixXd readMatrixCSV(const string& filename, int rows, int cols) {  //CSVから行列を読み込む関数，MatrixXdはEigenの行列データ型，filenameはファイル名取得？，rows,colsは行列大きさの取得（今回は100*100）
   //int:整数型のデータ，const:これは変更しないの意,string&:文字列を「参照」で渡す．→const string&:文字列を参照で渡すけど、関数の中では変更できない．速くて安全
    MatrixXd mat(rows, cols); //空行列をまず作り，後で中身をcsvから詰める
    ifstream file(filename); //ファイルを開く,読み取り専用，ifstreamはファイル内読み込みの際に
    string line;
    int row = 0; //1行ずつ読んでいくための変数用意

    while (getline(file, line) && row < rows) { //上限のrows行までcsvファイルを1行ずつ読み込むループ
        stringstream ss(line); //stringstream:文字列から数値を抜き取る・区切って取り出す
        string cell; //1つずつ取り出した「カンマの間の値（文字列）」を入れる箱(cell:csvの1マス）
        int col = 0; //読み込んだ1行をカンマで分割する準備,ここは今何列目にいるのかカウントする変数

        while (getline(ss, cell, ',') && col < cols) {  //ss からカンマ , で区切って、1個ずつ cell に取り出す.＆＆以降は「列数より多く読まない」ようにしてる
            mat(row, col) = stod(cell);  //Eigenの行列の「row 行 col 列」に値を入れる.stod(cell)は文字列をdouble型に変換
            col++;  //次列へ
        } //カンマで区切られた数字を1つずつ読み込んで行列に詰めていく
        row++; //次の行へ
    }

    return mat; //読み終えた行列を呼び出して元に戻す
}

// CSVからベクトルを読み込む
VectorXd readVectorCSV(const string& filename, int size) { //csvからベクトルを読む関数，VectorXdはEigenの「ベクトル」データ型(一列のやつ）
    VectorXd vec(size); //空のベクトルつくる
    ifstream file(filename);
    string line;
    int i = 0; //ベクトル用の空配列を用意。1行ずつ読んで詰める準備。

    while (getline(file, line) && i < size) {
        vec(i++) = stod(line);
    }  //1行ずつ読んで、ベクトルに数値を詰める。

    return vec; //できたベクトルを返す
}

// ベクトルをCSVに出力
void writeVectorCSV(const string& filename, const VectorXd& vec) { //「ベクトルをファイルに保存」する関数
    ofstream file(filename);
    for (int i = 0; i < vec.size(); ++i) {
        file << vec(i) << endl;
    }  //ベクトルの中身を1つずつファイルに書き出す（1行1数字
}

int main() {
    const int N = 100;  //メイン関数のはじまり！ N=100 は行列のサイズ（100×100

    // matrix1.csv + vector1.csv
    MatrixXd A1 = readMatrixCSV("matrix1.csv", N, N);  
    VectorXd b1 = readVectorCSV("vector1.csv", N);  //1個目の連立方程式の係数行列A₁とベクトルb₁を読み込む
    VectorXd x1 = A1.colPivHouseholderQr().solve(b1);  //A₁x₁ = b₁ を解いて、x₁（解ベクトル）を計算する．.colPivHouseholderQr() はQR分解ってやつ（安全で高速）
    writeVectorCSV("solution3.csv", x1);  //解x₁を solution1.csv に書き出す！

    // matrix2.csv + vector2.csv
    MatrixXd A2 = readMatrixCSV("matrix2.csv", N, N);
    VectorXd b2 = readVectorCSV("vector2.csv", N);
    VectorXd x2 = A2.colPivHouseholderQr().solve(b2);
    writeVectorCSV("solution4.csv", x2);

    cout << "連立方程式を解いて solution3.csv と solution4.csv に出力しました。" << endl;  //処理終わりの画面表示
    return 0;  //おわり
}
