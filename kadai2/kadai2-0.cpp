#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

#define MAX_ERR 1e-10
#define N 30

std::vector<std::vector<double>> read_Matrix1(std::string path){

    int i,j,k;

    std::ifstream ifs(path);

    std::vector<std::vector<double>> a;

    std::string line;
    std::string str;

    k=0;

    a.reserve(20000);

    while (getline(ifs, line)) {    
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream i_stream(line);

        a.push_back(std::vector<double>());
       
        // 「,」区切りごとにデータを読み込む
        while (getline(i_stream, str, ',')) {
           int num = stoi(str);
           a[k].push_back(num);
        }
        k++;
    
    }



    return a;

}
std::vector<double> read_Matrix2(std::string path){

    std::ifstream ifs(path);

    std::vector<double> b;

    std::string line;
    std::string str;

    b.reserve(200);

    while (getline(ifs, line)) {    
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream i_stream(line);
 
        // 「,」区切りごとにデータを読み込む
        while (getline(i_stream, str, ',')) {
           // csvファイルに書き込む
           int num = stoi(str);
           b.push_back(num);
        }
    
    }



    return b;

}

int output(std::vector<double> x, std::string path){

    int i;
    std::ofstream ofs(path);

    for (i=0; i < x.size(); i++){
        double num = x[i];
        ofs << num << std::endl;
    }

    return 0;
}

void generateCsv( int n, int m, std::string path){

    int i,j;
    std::ofstream ofs(path);

    std::random_device rnd;     // 非決定的な乱数生成器を生成
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> rand100(0, 99); 

    for (i=0; i < n; i++){
        for (j=0; j < m; j++){
            int num = rand100(mt);
            ofs << num << ",";
        }
        ofs << std::endl;
    }
}

int main(){

   int n,m;
   int i,j,k;

   double t;

   std:: string path_A = "./Matrix1.csv";//インプットファイル
   std:: string path_b = "./Matrix2.csv";
   std:: string path_x = "./Solution.csv";

   generateCsv(N,N,path_A);//インプットファイルを生成
   generateCsv(N,1,path_b);

   std::vector<std::vector<double>> a = read_Matrix1(path_A);
   std::vector<double> b = read_Matrix2(path_b);

/*    for(i =0 ; i < b.size(); i++){
    std::cout << b[i] << std::endl;
   } */

   n = a.size();
   m = a[0].size();

   if( b.size() != m ){
    std::cout << "解けません" << std::endl;
    return 0;
   }

   std::vector<std::vector<double>> inv(n,std::vector<double>(m,0));//逆行列
   std::vector<double> x(n,0);//解

    for (i=0;i<n;i++){
        for(j=0;j<m;j++){
            if (i==j){
                inv[i][j]=1;//単位行列を作る
            }
        }
    }


    for(k=0; k<n; k++){//吐き出し法

        double max = fabs(a[k][k]);

        int max_i = k;

        for (i = k + 1; i < n; i++) {
            if (fabs(a[i][k]) > max) {
                max = fabs(a[i][k]);
                max_i = i;
            }
        }
        
        if (fabs(a[max_i][k]) <= MAX_ERR) {
            /* 逆行列は求められない */
            std::cout<<"逆行列なし\n";
            return 0;
        }

        if (k != max_i) {//ピポッド選択
            for (j = 0; j < n; j++) {
                double tmpA = a[max_i][j];
                a[max_i][j] = a[k][j];
                a[k][j] = tmpA;
                double tmpInv = inv[max_i][j];
                inv[max_i][j] = inv[k][j];
                inv[k][j] = tmpInv;
            }
        }

        t = 1/a[k][k];

        for( j=0; j<m; j++){
            a[k][j] *= t;
            inv[k][j] *= t;
        }

        for(i=0; i<n; i++){
            if(i != k){

                t = a[i][k];

                for(j=0; j<n; j++){
                a[i][j] -= a[k][j]*t;
                inv[i][j] -= inv[k][j]*t;
                }
            }
        }
    }

/*     std::cout<<"Inv_A="<<std::endl;

    for (int i = 0; i < inv.size(); i++) {
        for (int j = 0; j < inv[0].size(); j++) {
            std::cout << inv[i][j] << " ";
        }
        std::cout << std::endl;
    } */

    //逆行列を右辺にかける

    for (int i = 0; i < inv.size(); i++) {//解を計算
        for (int j = 0; j < inv[0].size(); j++) {
            x[i] += inv[i][j]*b[j];
        }
        //std::cout << x[i] << std::endl;
    }

    output(x, path_x);

    return 0;
}




