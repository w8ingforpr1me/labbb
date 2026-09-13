#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        std::cerr << "Ошибка: Передайте путь к файлу в качестве аргумента.\n";
        std::cerr << "Использование: " << argv[0] << " <input_file.txt>\n";
        return 1;
    }

    std::string filePath = argv[1];
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filePath << "\n";
        return 1;
    }

    std::vector<int> nums;
    int number;

    while (file >> number) {
        nums.push_back(number);
    }
    file.close();

    if (nums.empty()) {
        std::cout << "0\n";
        return 0;
    }

    std::sort(nums.begin(), nums.end());

    int median = nums[nums.size() / 2];
    int totalMoves = 0;

    for (int num : nums) {
        totalMoves += std::abs(num - median);
    }

    if (totalMoves > 20) {
        std::cout << "20 ходов недостаточно для приведения всех элементов массива к одному числу\n";
    }
    else {
        std::cout << totalMoves << "\n";
    }

    return 0;
}
