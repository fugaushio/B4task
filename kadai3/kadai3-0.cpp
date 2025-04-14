#include <iostream>
#include <vector>
#include <fstream>
#include <eigen3/Eigen/Dense>


Eigen::MatrixXd readCSV(std::string file) {

    std::ifstream in(file);
    
    std::string line;
    std::string str;
  
    int row = 0;
    int col = 0;

    std::vector<std::vector<int>> data;
  
    
    //std::cout << res << std::endl;

    if (in.is_open()) {
  
        while (getline(in, line)) {
            std::istringstream i_stream(line);
            col = 0;
            std::vector<int> row_data;

            std::string str;
            while (getline(i_stream, str, ',')) {
                row_data.push_back(std::stoi(str));
            }
            data.push_back(row_data);
            row++;
        }
        
      //std::cout << res << std::endl;
      in.close();
    }else {
        std::cerr << "ファイルを開けません!" << std::endl;
    }

    int rows,cols;

    rows = data.size();
    if (rows > 0) {
        cols = data[0].size();
    }

    // Eigenの行列に変換
    Eigen::MatrixXd res = Eigen::MatrixXd(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            res(i, j) = data[i][j];
        }
    }

    return res;
}

int output(Eigen::VectorXd x, std::string path){

    std::ofstream ofs(path);

    ofs << x << std::endl;

    return 0;
}

int main(){

    std::string path_A = "../kadai2/Matrix1.csv";
    std::string path_b = "../kadai2/Matrix2.csv";
    std::string path_x = "./Solution_Eigen.csv";

    Eigen::MatrixXd A = readCSV(path_A);
    Eigen::VectorXd b = readCSV(path_b);

    Eigen::FullPivLU<Eigen::MatrixXd> LU(A);
    Eigen::VectorXd x = LU.solve(b);

    output(x, path_x);
}