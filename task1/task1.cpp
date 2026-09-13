#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    
    if (argc < 5) {
        std::cerr << "Использование: " << argv[0] << " n1 m1 n2 m2\n";
        return 1;
    }

    
    int n1 = std::stoi(argv[1]);
    int m1 = std::stoi(argv[2]);
    int n2 = std::stoi(argv[3]);
    int m2 = std::stoi(argv[4]);

    std::vector<int> path1;
    std::vector<int> path2;

    bool working1 = true;
    bool working2 = true;

    int temp1 = 0;
    int temp2 = 0;

    while (working1 || working2) {
        path1.push_back(temp1 + 1);
        temp1 = (temp1 + m1 - 1) % n1;
        if (temp1 == 0) {
            working1 = false;
        }

        path2.push_back(temp2 + 1);
        temp2 = (temp2 + m2 - 1) % n2;
        if (temp2 == 0) {
            working2 = false;
        }
    }

    for (const auto& el : path1) {
        std::cout << el;
    }

    for (const auto& el : path2) {
        std::cout << el;
    }

    std::cout << "\n";

    return 0;
}
