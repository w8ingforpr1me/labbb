#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 4) {
        std::cerr << "Ошибка: Передайте 3 пути к файлам в качестве аргументов.\n";
        std::cerr << "Использование: " << argv[0] << " <values.json> <tests.json> <report.json>\n";
        return 1;
    }

    std::unordered_map<std::string, std::string> valuesMap;

    std::ifstream valuesFile(argv[1]);
    if (!valuesFile.is_open()) {
        std::cerr << "Не удалось открыть файл значений: " << argv[1] << "\n";
        return 1;
    }

    std::string line;
    std::string currentId = "";
    std::regex idRegex(R"(\"id\"\s*:\s*(\d+))");
    std::regex valueRegex(R"(\"value\"\s*:\s*\"([^\"]*)\")");
    std::smatch match;

    while (std::getline(valuesFile, line)) {
        if (std::regex_search(line, match, idRegex)) {
            currentId = match[1].str();
        }
        if (std::regex_search(line, match, valueRegex)) {
            if (!currentId.empty()) {
                valuesMap[currentId] = match[1].str();
                currentId = "";
            }
        }
    }
    valuesFile.close();

    //чтение tests.json
    std::ifstream testsFile(argv[2]);
    if (!testsFile.is_open()) {
        std::cerr << "Не удалось открыть файл структуры тестов: " << argv[2] << "\n";
        return 1;
    }

    //report
    std::ofstream reportFile(argv[3]);
    if (!reportFile.is_open()) {
        std::cerr << "Не удалось создать файл отчета: " << argv[3] << "\n";
        return 1;
    }

    std::string testLine;
    std::string activeId = "";
    std::regex testIdRegex(R"(\"id\"\s*:\s*(\d+))");

    while (std::getline(testsFile, testLine)) {
        if (std::regex_search(testLine, match, testIdRegex)) {
            activeId = match[1].str();
        }

        if (testLine.find("\"value\"") != std::string::npos && !activeId.empty()) {
            auto it = valuesMap.find(activeId);
            if (it != valuesMap.end()) {
                size_t pos = testLine.find(":");
                if (pos != std::string::npos) {
                    size_t firstQuote = testLine.find("\"", pos);
                    if (firstQuote != std::string::npos) {
                        std::string leading = testLine.substr(0, firstQuote + 1);
                        std::string trailing = testLine.substr(testLine.find("\"", firstQuote + 1));

                        if (testLine.back() == ',' && trailing.back() != ',') {
                            trailing += ",";
                        }
                        testLine = leading + it->second + trailing;
                    }
                }
            }
            activeId = "";
        }
        reportFile << testLine << "\n";
    }

    testsFile.close();
    reportFile.close();

    std::cout << "Отчет успешно сгенерирован и сохранен в: " << argv[3] << "\n";
    return 0;
}
