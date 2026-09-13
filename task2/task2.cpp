#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
  
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <путь_к_файлу1> <путь_к_файлу2>\n";
        return 1;
    }

    //первый файл
    std::ifstream ellipseFile(argv[1]);
    if (!ellipseFile.is_open()) {
        std::cerr << "Ошибка открытия файла эллипса: " << argv[1] << "\n";
        return 1;
    }

    double x0, y0; //центр эллипса
    double a, b;   //радиусы

    if (!(ellipseFile >> x0 >> y0 >> a >> b)) {
        std::cerr << "Ошибка чтения данных эллипса.\n";
        return 1;
    }
    ellipseFile.close();

    //второй файл
    std::ifstream pointsFile(argv[2]);
    if (!pointsFile.is_open()) {
        std::cerr << "Ошибка открытия файла точек: " << argv[2] << "\n";
        return 1;
    }

    double x, y;
    const double EPSILON = 1e-9;

    while (pointsFile >> x >> y) {
        double result = (std::pow(x - x0, 2) / std::pow(a, 2)) + (std::pow(y - y0, 2) / std::pow(b, 2));

        if (std::abs(result - 1.0) < EPSILON) {
            std::cout << 0 << '\n'; //на эллипсе
        }
        else if (result < 1.0) {
            std::cout << 1 << '\n'; //внутри
        }
        else {
            std::cout << 2 << '\n'; //снаружи
        }
    }
    pointsFile.close();

    return 0;
}
