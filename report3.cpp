#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <Eigen/Dense>


using namespace std;

// CSV読み込み関数
vector<vector<double>> readCSV(const string& filename) {
    ifstream file(filename);
    vector<vector<double>> data;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<double> row;
        while (getline(ss, value, ',')) {
            row.push_back(stod(value));
        }
        data.push_back(row);
    }
    return data;
}

// ベクトルCSV読み込み（1列だけ）
vector<double> readVectorCSV(const string& filename) {
    ifstream file(filename);
    vector<double> vec;
    string line;
    while (getline(file, line)) {
        vec.push_back(stod(line));
    }
    return vec;
}

// 解のCSV出力
void writeVectorCSV(const string& filename, const vector<double>& vec) {
    ofstream file(filename);
    for (double val : vec) {
        file << val << "\n";
    }
}

int main() {
  
}
