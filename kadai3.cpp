#include <fstream>
#include <sstream>  
#include <string>
#include <vector>
#include <iostream>
#include <eigen3/Eigen/Dense>

std::vector<float> split(std::string line, char delim = ',')
{
    std::vector<float> items;
    std::stringstream ss(line); // std::getline に渡す入力ストリーム
    std::string item;           // std::getline が吐き出す文字列の格納先
    while (std::getline(ss, item, delim))
        items.push_back(std::stof(item));
    return items;
}

std::vector<std::vector<float>> read_csv_mat(std::string path)
{
    std::vector<std::vector<float>> data;
    std::ifstream ifs(path); // std::getline に渡す入力ストリーム
    if (ifs.fail()){
        std::cerr << "failed\n";
		exit(1);
    }
    std::string line;        // std::getline が吐き出す文字列の格納先
    while (std::getline(ifs, line, '\n'))
        data.push_back(split(line, ','));
    return data;
}

std::vector<float> read_csv_vec(std::string path)
{
    std::vector<float> data;
    std::ifstream ifs(path); // std::getline に渡す入力ストリーム
    if (ifs.fail()){
        std::cerr << "failed\n";
		exit(1);
    }
    std::string line;        // std::getline が吐き出す文字列の格納先
    while (std::getline(ifs, line, '\n'))
        data.push_back(std::stof(line));
    return data;
}


void write_csv_vec(Eigen::VectorXd vec, std::string path){
    std::ofstream ofs(path);
    if (ofs.fail()){
        std::cerr << "failed\n";
		exit(1);
    }
    for (float x : vec){
        ofs << x << std::endl;
    } 
}


int main(){
    std::vector<std::vector<float>> mat1, mat2;
    mat1 = read_csv_mat("../Input/matrix1.csv");
    mat2 = read_csv_mat("../Input/matrix2.csv");
    std::vector<float> vec1, vec2, result1, result2;
    vec1 = read_csv_vec("../Input/vector1.csv");
    vec2 = read_csv_vec("../Input/vector2.csv");
    Eigen::MatrixXd A1(100, 100), A2(100, 100);
    Eigen::VectorXd b1(100), b2(100);
    for ( int i=0; i<100; i++){
        b1(i) = vec1[i];
        b2(i) = vec2[i];
        for ( int j=0; j<100; j++){
            A1(i, j) = mat1[i][j];
            A2(i, j) = mat2[i][j];
        }
    }
    
    Eigen::VectorXd ans = A1.inverse() * b1;
    Eigen::VectorXd ans2 = A2.inverse() * b2;
    write_csv_vec(ans, "result3.csv");
    write_csv_vec(ans2, "result4.csv");
    // write_csv_vec(result2, "result2.csv");
    return 0;
}