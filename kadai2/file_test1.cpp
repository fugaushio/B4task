#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream file("./file.txt");  // 読み込むファイルのパスを指定
    std::string line;

    while (std::getline(file, line)) {  // 1行ずつ読み込む
        std::cout << line << std::endl;
    }

    return 0;
}