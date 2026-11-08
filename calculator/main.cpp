#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

// Функция вывода справки
void print_usage() {
    cout << "Usage: calculator -o <operation> [operands]\n";
    cout << "Operations (Variant 13 - Logarithmic):\n";
    cout << "  ln       - natural logarithm (1 operand: x)\n";
    cout << "  log      - logarithm to base b (2 operands: base, x)\n";
    cout << "Examples:\n";
    cout << "  calculator -o ln 10\n";
    cout << "  calculator --operation log 2 8\n";
}

int main(int argc, char *argv[]) {
    string operation = "";
    vector<double> operands;

    // 1. Парсинг аргументов командной строки
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        
        if (arg == "-o" || arg == "--operation") {
            if (i + 1 < argc) {
                operation = argv[i + 1];
                i++; // Пропускаем значение флага
            } else {
                cerr << "Error: Missing operation name after flag.\n";
                return 1;
            }
        } else {
            // Это операнд (число). Максимум 2 операнда для нашего варианта.
            if (operands.size() < 2) {
                operands.push_back(atof(argv[i]));
            } else {
                cerr << "Error: Too many operands for this operation.\n";
                return 1;
            }
        }
    }

    // Если операция не задана, выводим справку
    if (operation.empty()) {
        print_usage();
        return 0;
    }

    // 2. Выполнение операций
    if (operation == "ln") {
        if (operands.size() != 1) {
            cerr << "Error: 'ln' requires exactly 1 operand.\n";
            return 1;
        }
        if (operands[0] <= 0) {
            cerr << "Error: Logarithm domain error (x > 0).\n";
            return 1;
        }
        // Функция log() в C++ - это натуральный логарифм
        cout << "ln(" << operands[0] << ") = " << log(operands[0]) << "\n";
    } 
    else if (operation == "log") {
        if (operands.size() != 2) {
            cerr << "Error: 'log' requires exactly 2 operands (base, number).\n";
            return 1;
        }
        double base = operands[0];
        double val = operands[1];

        // Проверка ОДЗ: основание > 0, основание != 1, аргумент > 0
        if (base <= 0 || base == 1 || val <= 0) {
            cerr << "Error: Domain error (base > 0, base != 1, value > 0).\n";
            return 1;
        }
        
        // Формула: log_b(a) = ln(a) / ln(b)
        double result = log(val) / log(base);
        cout << "log_" << base << "(" << val << ") = " << result << "\n";
    } 
    else {
        cerr << "Error: Unknown operation '" << operation << "'.\n";
        print_usage();
        return 1;
    }

    return 0;
}