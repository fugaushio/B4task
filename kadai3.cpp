#include <iostream>
#include <fstream>       // ファイルストリーム
#include <string>        // 文字列
#include <vector>        // ベクター
#include <sstream>       // ストリーム
#include <stdio.h>   // for printf()
#include <Eigen/Dense>

# define N 100
using namespace std;
int main()
{   
    // string matrixPath = "B4task/Input/sample.csv";  // 読み込むCSVファイルのパス
    string matrixPath = "B4task/Input/matrix1.csv";  // 読み込むCSVファイルのパス
    
    ifstream matrixfile(matrixPath);  // ファイルストリームを作成
    // ファイルが正常に開けたか確認
    if (!matrixfile.is_open()) {
        cerr << "ファイルを開けませんでした" << endl;
        return 1;  // エラーコードを返す
    }
    Eigen::MatrixXd A; //マトリックスを定義
    A.resize(N,N);
    string line;  // 読み込む行を格納する変数
    int i = 0;
    while (getline(matrixfile, line) && i<N ) {  // 1行ずつ読み込む
        stringstream ss(line);  // 行をストリームに変換
        string item;  // 分割したデータを格納する変数
        int j=0;
        while (getline(ss, item, ',' )&& j<N) {  // カンマで分割
           A(i,j) = stod(item) ;
           j++;}
        i++;
    }
    matrixfile.close();

   // string vectorPath = "B4task/Input/sample2.csv";  // 読み込むCSVファイルのパス
    string vectorPath = "B4task/Input/vector1.csv";  // 読み込むCSVファイルのパス
    
    ifstream vectorfile(vectorPath);  // ファイルストリームを作成
    // ファイルが正常に開けたか確認
    if (!vectorfile.is_open()) {
        cerr << "ファイルを開けませんでした。" << endl;
        return 1;  // エラーコードを返す
    }
    Eigen::VectorXd B(N);
    i=0;
    while (getline(vectorfile, line) && i<N ) {  // 1行ずつ読み込む
        B(i) = stod(line) ;
        i++;
    }
    vectorfile.close();

    
    //std::cout << "Here is the matrix A:\n" << A << std::endl;
    //std::cout << "Here is the vector b:\n" << B << std::endl;

    Eigen::VectorXd x = A.colPivHouseholderQr().solve(B);

    //std::cout << "The solution is:\n" << x << std::endl;

    ofstream outputFile("output_kadai3.csv");  // 出力ファイルを指定
    if (!outputFile) {  // ファイルが開けなかった場合
        std::cerr << "ファイルを開けませんでした。" << std::endl;
        return 1;  // エラーコードを返す
    }

    outputFile << x << std::endl;  // CSV形式で書き込み
    outputFile.close();  // ファイルを閉じる
    std::cerr << "ファイルを生成しました" << std::endl;
    return 0;
}