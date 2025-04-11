#include <iostream>      // 入出力ストリーム
#include <fstream>       // ファイルストリーム
#include <string>        // 文字列
#include <vector>        // ベクター
#include <sstream>       // ストリーム
#include <stdio.h>   // for printf()

#define N 100
using namespace std;

int main(){
    
    string filePath = "B4task/Input/matrix2.csv";  // 読み込むCSVファイルのパス
    
    ifstream file(filePath);  // ファイルストリームを作成
    // ファイルが正常に開けたか確認
    if (!file.is_open()) {
        cerr << "ファイルを開けませんでした。" << endl;
        return 1;  // エラーコードを返す
    }
    vector<vector<double>> data;  // 2次元ベクターを用意
    string line;  // 読み込む行を格納する変数
    while (getline(file, line)) {  // 1行ずつ読み込む
        stringstream ss(line);  // 行をストリームに変換
        string item;  // 分割したデータを格納する変数
        vector<double> row;  // 行のデータを格納するベクター
        // カンマで分割
        while (getline(ss, item, ',')) {  // カンマで分割
            row.push_back(stod(item));  // 分割したデータをベクターに追加
        }
        data.push_back((row));  // 行のデータを全体のベクターに追加
    }
    file.close();

    filePath = "B4task/Input/vector2.csv";  // 読み込むCSVファイルのパス


    ifstream file2(filePath);  // ファイルストリームを作成
    // ファイルが正常に開けたか確認
    if (!file2.is_open()) {
        cerr << "ファイルを開けませんでした。" << endl;
        return 1;  // エラーコードを返す
    }
    vector<vector<double>> DATA;  // 2次元ベクターを用意
    // string line;  // 読み込む行を格納する変数
    while (getline(file2, line)) {  // 1行ずつ読み込む
        stringstream ss(line);  // 行をストリームに変換
        string item;  // 分割したデータを格納する変数
        vector<double> row;  // 行のデータを格納するベクター
        // カンマで分割
        while (getline(ss, item, ',')) {  // カンマで分割
            row.push_back(stod(item));  // 分割したデータをベクターに追加
        }
        DATA.push_back((row));  // 行のデータを全体のベクターに追加
    }
    file2.close();

    int data_row = data.size();
    int data_col = data.at(0).size();

    for (int i = 0; i < data_row; i++){
        data.at(i).push_back(DATA.at(i).at(0));
    }

    
    for (int k = 0; k < N; k++) {
        // ピボット係数
        double p = data[k][k];

        // ピボット行を p で除算
        for (int j = k; j < N + 1; j++){
            
            data[k][j] /= p;
        }
       

        // ピボット列の掃き出し
        for (int i = 0; i < N; i++) {
            if (i != k) {
                double d = data[i][k];
                for (int j = k; j < N + 1; j++){
                    data[i][j] -= d * data[k][j];
                }
               
            }
        }
    }

    // 結果出力
    for (int k = 0; k < N; k++){
        printf("x%d = %f\n", k + 1, data[k][N]);
     }
   
     return 0;
    }