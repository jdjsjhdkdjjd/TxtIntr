#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void print_usage() {
    printf("Usage: calculator -o <operation> [operands]\n");
    printf("Operations:\n");
    printf("  ln       - natural logarithm (1 operand)\n");
    printf("  log      - logarithm to base (2 operands: base, number)\n");
    printf("Example:\n");
    printf("  calculator -o ln 10\n");
    printf("  calculator --operation log 2 8\n");
}

int main(int argc, char *argv[]) {
    char *operation = NULL;
    double operands[2];
    int op_count = 0;

    // 1. Парсинг аргументов
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--operation") == 0) {
            if (i + 1 < argc) {
                operation = argv[i + 1];
                i++; // Пропускаем значение флага
            } else {
                fprintf(stderr, "Error: Missing operation name after flag.\n");
                return 1;
            }
        } else {
            // Это операнд (число)
            if (op_count < 2) {
                operands[op_count] = atof(argv[i]);
                op_count++;
            }
        }
    }

    // Если операция не задана, выводим справку
    if (operation == NULL) {
        print_usage();
        return 0;
    }

    // 2. Выполнение операций
    if (strcmp(operation, "ln") == 0) {
        if (op_count != 1) {
            fprintf(stderr, "Error: 'ln' requires exactly 1 operand.\n");
            return 1;
        }
        if (operands[0] <= 0) {
            fprintf(stderr, "Error: Logarithm domain error (x > 0).\n");
            return 1;
        }
        printf("ln(%.2f) = %.4f\n", operands[0], log(operands[0]));
    } 
    else if (strcmp(operation, "log") == 0) {
        if (op_count != 2) {
            fprintf(stderr, "Error: 'log' requires exactly 2 operands (base and number).\n");
            return 1;
        }
        double base = operands[0];
        double val = operands[1];

        if (base <= 0 || base == 1 || val <= 0) {
            fprintf(stderr, "Error: Domain error (base > 0, base != 1, value > 0).\n");
            return 1;
        }
        // Формула перехода к новому основанию: log_b(a) = ln(a) / ln(b)
        double result = log(val) / log(base);
        printf("log_%.2f(%.2f) = %.4f\n", base, val, result);
    } 
    else {
        fprintf(stderr, "Error: Unknown operation '%s'.\n", operation);
        print_usage();
        return 1;
    }

    return 0;
}