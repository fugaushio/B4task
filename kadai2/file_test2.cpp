#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>



int main()
{
    int i,j,k;

    std::ifstream ifs("./data.csv");
    std::ofstream ofs("./TwiceData.csv");

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
           // csvファイルに書き込む
           int num = stoi(str);
           num +=2;
           ofs << num << ',';

           a[k].push_back(num);
        }
        // 改行する
        ofs << std::endl;
        k++;

        

      }

       for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    } 


}