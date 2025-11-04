#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/solve.h"

void print_test_result(const char* test_name, int passed, const char* input, int expected, int actual) {
    printf("%s: %s\n", test_name, passed ? "PASSED" : "FAILED");
    printf("  Input:    \"%s\"\n", input);
    printf("  Expected: %d\n", expected);
    printf("  Actual:   %d\n", actual);
    printf("\n");
}

int main() {
    printf("=== Testing Bracket Checker ===\n\n");
    int tests_passed = 0;
    int total_tests = 0;
    
    // Тест 1: Простая корректная строка
    printf("--- Test 1: Simple correct brackets ---\n");
    const char* test1_input = "(a + b)";
    int test1_expected = 1;
    int test1_actual = check_brackets(test1_input);
    int test1_passed = (test1_actual == test1_expected);
    print_test_result("Simple parentheses", test1_passed, test1_input, test1_expected, test1_actual);
    tests_passed += test1_passed; total_tests++;
    
    // Тест 2: Несколько типов скобок
    printf("--- Test 2: Multiple bracket types ---\n");
    const char* test2_input = "({[<>]})";
    int test2_expected = 1;
    int test2_actual = check_brackets(test2_input);
    int test2_passed = (test2_actual == test2_expected);
    print_test_result("Multiple bracket types", test2_passed, test2_input, test2_expected, test2_actual);
    tests_passed += test2_passed; total_tests++;
    
    // Тест 3: Несбалансированные скобки
    printf("--- Test 3: Unbalanced brackets ---\n");
    const char* test3_input = "(a + b";
    int test3_expected = 0;
    int test3_actual = check_brackets(test3_input);
    int test3_passed = (test3_actual == test3_expected);
    print_test_result("Unbalanced parentheses", test3_passed, test3_input, test3_expected, test3_actual);
    tests_passed += test3_passed; total_tests++;
    
    // Тест 4: Неправильный порядок скобок
    printf("--- Test 4: Wrong bracket order ---\n");
    const char* test4_input = "([)]";
    int test4_expected = 0;
    int test4_actual = check_brackets(test4_input);
    int test4_passed = (test4_actual == test4_expected);
    print_test_result("Wrong bracket order", test4_passed, test4_input, test4_expected, test4_actual);
    tests_passed += test4_passed; total_tests++;
    
    // Тест 5: Пустая строка
    printf("--- Test 5: Empty string ---\n");
    const char* test5_input = "";
    int test5_expected = 1;
    int test5_actual = check_brackets(test5_input);
    int test5_passed = (test5_actual == test5_expected);
    print_test_result("Empty string", test5_passed, test5_input, test5_expected, test5_actual);
    tests_passed += test5_passed; total_tests++;
    
    // Тест 6: Строка без скобок
    printf("--- Test 6: No brackets ---\n");
    const char* test6_input = "Hello World 123";
    int test6_expected = 1;
    int test6_actual = check_brackets(test6_input);
    int test6_passed = (test6_actual == test6_expected);
    print_test_result("No brackets", test6_passed, test6_input, test6_expected, test6_actual);
    tests_passed += test6_passed; total_tests++;
    
    // Тест 7: Сложное выражение
    printf("--- Test 7: Complex expression ---\n");
    const char* test7_input = "if (x) { arr[i] = value; }";
    int test7_expected = 1;
    int test7_actual = check_brackets(test7_input);
    int test7_passed = (test7_actual == test7_expected);
    print_test_result("Complex expression", test7_passed, test7_input, test7_expected, test7_actual);
    tests_passed += test7_passed; total_tests++;
    
    // Тест 8: Только закрывающие скобки
    printf("--- Test 8: Only closing brackets ---\n");
    const char* test8_input = "})]";
    int test8_expected = 0;
    int test8_actual = check_brackets(test8_input);
    int test8_passed = (test8_actual == test8_expected);
    print_test_result("Only closing brackets", test8_passed, test8_input, test8_expected, test8_actual);
    tests_passed += test8_passed; total_tests++;
    
    // Тест 9: Вложенные скобки
    printf("--- Test 9: Nested brackets ---\n");
    const char* test9_input = "({<[()]>})";
    int test9_expected = 1;
    int test9_actual = check_brackets(test9_input);
    int test9_passed = (test9_actual == test9_expected);
    print_test_result("Deeply nested brackets", test9_passed, test9_input, test9_expected, test9_actual);
    tests_passed += test9_passed; total_tests++;
    
    // Тест 10: Реальный пример кода
    printf("--- Test 10: Real code example ---\n");
    const char* test10_input = "void func() { if (arr[i] == 1) { return; } }";
    int test10_expected = 1;
    int test10_actual = check_brackets(test10_input);
    int test10_passed = (test10_actual == test10_expected);
    print_test_result("Real code example", test10_passed, test10_input, test10_expected, test10_actual);
    tests_passed += test10_passed; total_tests++;
    
    // Дополнительные тесты для edge cases
    
    // Тест 11: NULL pointer
    printf("--- Test 11: NULL pointer ---\n");
    int test11_expected = 1; // По спецификации обычно возвращают true для NULL
    int test11_actual = check_brackets(NULL);
    int test11_passed = (test11_actual == test11_expected);
    print_test_result("NULL pointer", test11_passed, "NULL", test11_expected, test11_actual);
    tests_passed += test11_passed; total_tests++;
    
    // Тест 12: Специальные символы
    printf("--- Test 12: Special characters ---\n");
    const char* test12_input = "(!@#$%^&*()_+{})";
    int test12_expected = 1;
    int test12_actual = check_brackets(test12_input);
    int test12_passed = (test12_actual == test12_expected);
    print_test_result("Special characters", test12_passed, test12_input, test12_expected, test12_actual);
    tests_passed += test12_passed; total_tests++;
    
    printf("=== Final Results: %d/%d tests passed ===\n", tests_passed, total_tests);
    
    if (tests_passed == total_tests) {
        printf("🎉 All tests passed! Your bracket checker works correctly.\n");
    } else {
        printf("❌ Some tests failed. Check the implementation.\n");
    }
    
    return tests_passed == total_tests ? 0 : 1;
}