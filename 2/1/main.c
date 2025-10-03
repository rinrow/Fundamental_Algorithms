#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "include/Operate.h"

void test_operate() {
    struct TestCase {
        const char* name;
        int base;
        int n;
        double fractions[5];
        bool expected[5];
        Status expected_status;
    };
    
    struct TestCase tests[] = {
        // Базовые корректные случаи
        {"Binary common fractions", 2, 3, {0.5, 0.25, 0.1}, {true, true, false}, Ok},
        {"Decimal fractions", 10, 2, {0.2, 0.333}, {true, true}, Ok},
        {"Single fraction", 8, 1, {0.125}, {true}, Ok},
        {"Octal fractions", 8, 3, {0.5, 0.25, 0.1}, {true, true, false}, Ok},
        
        // Тесты с некорректными основаниями
        {"Invalid base 1", 1, 1, {0.5}, {false}, InvalidBase},
        {"Invalid base 0", 0, 1, {0.5}, {false}, InvalidBase},
        {"Invalid base negative", -2, 1, {0.5}, {false}, InvalidBase},
        {"Invalid base -1", -1, 1, {0.5}, {false}, InvalidBase},
        
        // Тесты с разным количеством аргументов
        {"Zero fractions", 2, 0, {}, {}, Ok},
        {"One fraction true", 2, 1, {0.5}, {true}, Ok},
        {"One fraction false", 2, 1, {0.1}, {false}, Ok},
        {"Multiple fractions", 2, 4, {0.5, 0.25, 0.125, 0.1}, {true, true, true, false}, Ok},
        {"Five fractions", 10, 5, {0.5, 0.2, 0.1, 0.25, 0.333}, {true, true, true, true, true}, Ok},
        
        // Тесты с граничными значениями дробей
        {"Fractions near zero", 2, 3, {0.001, 0.0001, 0.00001}, {false, false, false}, Ok},
        {"Fractions near one", 2, 2, {0.999, 0.9999}, {false, false}, Ok},
        {"Exactly half", 2, 1, {0.5}, {true}, Ok},
        {"Exactly quarter", 4, 1, {0.25}, {true}, Ok},
        
        // Тесты с разными основаниями
        {"Base 3 fractions", 3, 3, {0.333, 0.666, 0.5}, {false, false, false}, Ok},
        {"Base 4 fractions", 4, 2, {0.25, 0.5}, {true, true}, Ok},
        {"Base 5 fractions", 5, 2, {0.2, 0.4}, {true, true}, Ok},
        {"Base 6 fractions", 6, 3, {0.5, 0.333, 0.2}, {true, false, false}, Ok},
        {"Base 16 fractions", 16, 2, {0.5, 0.125}, {true, true}, Ok},
        
        // Известные математические случаи
        {"Powers of 2 in binary", 2, 4, {0.5, 0.25, 0.125, 0.0625}, {true, true, true, true}, Ok},
        {"Powers of 5 in decimal", 10, 3, {0.2, 0.04, 0.008}, {true, true, true}, Ok},
        {"Mixed denominators base 10", 10, 4, {0.5, 0.2, 0.1, 0.3}, {true, true, true, true}, Ok},
        
        // Дроби с периодическим представлением
        {"Periodic in decimal", 10, 3, {1.0/3.0, 1.0/7.0, 1.0/9.0}, {false, false, false}, PeriodFrac},
        {"Terminating in decimal", 10, 3, {0.5, 0.25, 0.75}, {true, true, true}, Ok},
        
        // Специфические дроби
        {"0.375 in different bases", 8, 1, {0.375}, {true}, Ok},
        {"0.375 in base 2", 2, 1, {0.375}, {true}, Ok},
        {"0.375 in base 10", 10, 1, {0.375}, {true}, Ok},
        {"0.6 in base 10", 10, 1, {0.6}, {true}, Ok},
        {"0.6 in base 2", 2, 1, {0.6}, {false}, Ok},
        
        // Крайние случаи
        {"Very small fraction", 2, 1, {0.0000001}, {false}, Ok},
        {"Repeating pattern", 3, 1, {0.1}, {false}, Ok}, // 0.1₃ = 1/3₁₀
    };
    
    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < total; i++) {
        printf("Test %d: %s\n", i + 1, tests[i].name);
        
        bool results[5];
        Status status = operate(results, tests[i].base, tests[i].n, 
                               tests[i].fractions[0], tests[i].fractions[1], 
                               tests[i].fractions[2], tests[i].fractions[3], 
                               tests[i].fractions[4]);
        
        bool test_passed = (status == tests[i].expected_status);
        
        // Проверяем результаты если статус Ok
        if (test_passed && status == Ok) {
            for (int j = 0; j < tests[i].n; j++) {
                if (results[j] != tests[i].expected[j]) {
                    test_passed = false;
                    break;
                }
            }
        }
        
        if (test_passed) {
            printf("  PASS\n");
            passed++;
        } else {
            printf("  FAIL - Status: %d, Expected: %d\n", status, tests[i].expected_status);
        }
    }
    
    printf("\nResults: %d/%d tests passed\n", passed, total);
}

int main() {
    // test_operate();
    int n = 2;
    bool *out = malloc(n * sizeof(bool));
    if(out == NULL) {
        printf("Ошибка выделения памяти\n");
        return 0;
    }
    operate(out, 3, n, 0.3, 0.5);
    for(int i = 0; i < n; ++i) {
        printf("число по номеру %d, %s имеет конеч предс\n", i + 1, out[i] ? "": "не");
    }
    return 0;
}