#include <iostream>
#include <vector>

int main(){

    int n,m;
    int i,j,k;
 
 
    std::vector<double> b{1,2,3};
    std::vector<std::vector<double>> A(3,std::vector<double>(3,0));
    std::vector<std::vector<int>> a;

    a.reserve(1000); 

    A[0].emplace_back(2.0);
    A[0].emplace_back(3.0);
    A[0].emplace_back(4.0);
    A[1].emplace_back(8.0);
    A[2].emplace_back(8.1);
    a.push_back(std::vector<int>());

    A[3].emplace_back(8.1);

/*      for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            std::cout << A[i][j] << "  ";
        }
        std::cout << std::endl;
    }  */

    a[0].push_back(1);//a[0][0]=1に相当する要素を追加
    a[0].push_back(2);//a[0][1]=2に相当する要素を追加
    a[0].push_back(3);//a[0][2]=3に相当する要素を追加


    a.push_back(std::vector<int>());

    a[1].push_back(4);//a[1][0]=4に相当する要素を追加
    a[1].push_back(5);//a[1][1]=5に相当する要素を追加
    a[1].push_back(5);//a[1][1]=5に相当する要素を追加
    int t =a.size();
    std::cout<<  t  << std::endl;

   for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            std::cout << a[i][j] << "  ";
        }
        std::cout << std::endl;
    }  






    return 0;



}