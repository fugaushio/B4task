#include <fstream>
#include <sstream>  
#include <string>
#include <vector>
#include <iostream>

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

void cout_mat(std::vector<std::vector<float>> data){
    for (std::vector<float> line : data){
        for (float x : line){
            std::cout << x << ", ";
        }
        std::cout  << std::endl;
    }
}

void write_csv_vec(std::vector<float> vec, std::string path){
    std::ofstream ofs(path);
    if (ofs.fail()){
        std::cerr << "failed\n";
		exit(1);
    }
    for (float x : vec){
        ofs << x << std::endl;
    } 
}

std::vector<std::vector<float>> augment(std::vector<std::vector<float>> mat, std::vector<float> vec){
    for (int i=0; i < vec.size(); i++){
        mat[i].push_back(vec[i]);
    }
    return mat;
}


std::vector<float> gauss(std::vector<std::vector<float>> mat){
    for (int i=0; i < mat.size(); i++){
        float p = mat[i][i];
        // std::cout << i << std::endl;
        for (int j=i; j < mat[0].size(); j++){
            mat[i][j] = mat[i][j] / p; 
        }
        for (int k=0; k < mat.size(); k++){
            // std::cout << k << std::endl;
            if(!(k==i)){
                float d = mat[k][i];
                for (int j=i; j < mat[0].size(); j++){
                    mat[k][j] -= d * mat[i][j]; 
                }
            }
        }
    }
    std::vector<float> ans;
    for(std::vector<float> line : mat){
        ans.push_back(line.back());
    }
    return ans;
}



// int main(){
//     std::vector<std::vector<float>> mat1, mat2;
//     mat1 = read_csv_mat("Input/matrix1.csv");
//     mat2 = read_csv_mat("Input/matrix2.csv");
//     std::vector<float> vec1, vec2, result1, result2;
//     vec1 = read_csv_vec("Input/vector1.csv");
//     vec2 = read_csv_vec("Input/vector2.csv");
//     result1 = gauss(augment(mat1, vec1));
//     result2 = gauss(augment(mat2, vec2));
//     write_csv_vec(result1, "result1.csv");
//     write_csv_vec(result2, "result2.csv");
//     return 0;
// }

int main(){
    std::vector<std::vector<float>> mat1, mat2;
    mat1 = read_csv_mat("te.csv");
    std::vector<float> vec1, vec2, result1, result2;
    vec1 = read_csv_vec("te2.csv");
    result1 = gauss(augment(mat1, vec1));
    // result2 = gauss(augment(mat2, vec2));
    write_csv_vec(result1, "restes.csv");
    // write_csv_vec(result2, "result2.csv");
    return 0;
}