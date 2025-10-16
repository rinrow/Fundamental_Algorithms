#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/Print.h"

// Вспомогательная функция для сравнения строк с выводом
void test_assert(const char* test_name, const char* expected, const char* actual) {
    if (strcmp(expected, actual) == 0) {
        printf("✓ %s\n", test_name);
    } else {
        printf("✗ %s\n", test_name);
        printf("  Expected: \"%s\"\n", expected);
        printf("  Actual:   \"%s\"\n", actual);
    }
}

void test_roman() {
    printf("=== Testing %%Ro (Roman numerals) ===\n");
    
    char buffer[100];
    
    oversprintf(buffer, "%Ro", 1);
    test_assert("1 -> I", "I", buffer);
    
    oversprintf(buffer, "%Ro", 4);
    test_assert("4 -> IV", "IV", buffer);
    
    oversprintf(buffer, "%Ro", 9);
    test_assert("9 -> IX", "IX", buffer);
    
    oversprintf(buffer, "%Ro", 58);
    test_assert("58 -> LVIII", "LVIII", buffer);
    
    oversprintf(buffer, "%Ro", 1994);
    test_assert("1994 -> MCMXCIV", "MCMXCIV", buffer);
    
    oversprintf(buffer, "%Ro", 3999);
    test_assert("3999 -> MMMCMXCIX", "MMMCMXCIX", buffer);
    
    // Граничные случаи
    oversprintf(buffer, "Number: %Ro", 123);
    test_assert("Mixed text with Roman", "Number: CXXIII", buffer);
}

void test_zeckendorf() {
    printf("\n=== Testing %%Zr (Zeckendorf representation) ===\n");
    
    char buffer[100];
    
    oversprintf(buffer, "%Zr", 0);
    test_assert("0 -> 01", "01", buffer);
    
    oversprintf(buffer, "%Zr", 1);
    test_assert("1 -> 11", "11", buffer);
    
    oversprintf(buffer, "%Zr", 2);
    test_assert("2 -> 011", "011", buffer);
    
    oversprintf(buffer, "%Zr", 3);
    test_assert("3 -> 0011", "0011", buffer);
    
    oversprintf(buffer, "%Zr", 4);
    test_assert("4 -> 1011", "1011", buffer);
    
    oversprintf(buffer, "%Zr", 5);
    test_assert("5 -> 00011", "00011", buffer);

    
    oversprintf(buffer, "%Zr", 33);
    test_assert("33 -> 10101011", "10101011", buffer);
}

void test_base_conversion() {
    printf("\n=== Testing %%Cv and %%CV (base conversion) ===\n");
    
    char buffer[100];
    
    // %Cv - нижний регистр
    oversprintf(buffer, "%Cv", 255, 16);
    test_assert("255 in hex lower", "ff", buffer);
    
    oversprintf(buffer, "%Cv", 255, 2);
    test_assert("255 in binary", "11111111", buffer);
    
    oversprintf(buffer, "%Cv", -255, 16);
    test_assert("-255 in hex lower", "-ff", buffer);
    
    // %CV - верхний регистр
    oversprintf(buffer, "%CV", 255, 16);
    test_assert("255 in hex upper", "FF", buffer);
    
    oversprintf(buffer, "%CV", 255, 2);
    test_assert("255 in binary upper", "11111111", buffer);
    
    // Некорректное основание
    oversprintf(buffer, "%Cv", 255, 37);
    test_assert("Invalid base -> decimal", "255", buffer);
    
    oversprintf(buffer, "%Cv", 255, 1);
    test_assert("Base 1 -> decimal", "255", buffer);
}

void test_base_to_decimal() {
    printf("\n=== Testing %%to and %%TO (base to decimal) ===\n");
    
    char buffer[100];
    
    // %to - нижний регистр
    oversprintf(buffer, "%to", "ff", 16);
    test_assert("hex 'ff' to decimal", "255", buffer);
    
    oversprintf(buffer, "%to", "11111111", 2);
    test_assert("binary to decimal", "255", buffer);
    
    oversprintf(buffer, "%to", "-ff", 16);
    test_assert("negative hex to decimal", "-255", buffer);
    
    // %TO - верхний регистр
    oversprintf(buffer, "%TO", "FF", 16);
    test_assert("hex 'FF' to decimal", "255", buffer);
    
    // Некорректное основание
    oversprintf(buffer, "%to", "ff", 37);
    test_assert("invalid base conversion", "255", buffer); 
    
    // Некорректное число
    oversprintf(buffer, "%to", "xyz", 16);
    // Результат зависит от вашей обработки ошибок
}

void test_memory_dump() {
    printf("\n=== Testing memory dumps (%%mi, %%mu, %%md, %%mf) ===\n");
    
    char buffer[500];
    
    // %mi - знаковый int
    int test_int = -1;
    oversprintf(buffer, "%mi", test_int);
    printf("int 1 dump: %s\n", buffer);
    // На little-endian: 00000001 00000000 00000000 00000000
    
    // %mu - беззнаковый int
    unsigned int test_uint = 1;
    oversprintf(buffer, "%mu", test_uint);
    printf("unsigned int 1 dump: %s\n", buffer);
    
    // %mf - float
    float test_float = 3.14f;
    oversprintf(buffer, "%mf", test_float);
    printf("float 1.0 dump: %s\n", buffer);
    
    // %md - double
    double test_double = 1.0;
    oversprintf(buffer, "%md", test_double);
    printf("double 1.0 dump: %s\n", buffer);
}

void test_mixed_specifiers() {
    printf("\n=== Testing mixed specifiers ===\n");
    
    char buffer[200];
    
    oversprintf(buffer, "Roman: %Ro, Binary: %Cv, Zeck: %Zr", 123, 123, 2, 10u);
    printf("Mixed: %s\n", buffer);
    // Ожидается: "Roman: CXXIII, Binary: 001001000000000000000000000000000000000000000000001, Zeck: 011"
    
    oversprintf(buffer, "Hex: %Cv, Uppercase: %CV", 255, 16, 255, 16);
    printf("Mixed base: %s\n", buffer);
    // Ожидается: "Hex: ff, Uppercase: FF"
}

void test_standard_specifiers() {
    printf("\n=== Testing standard specifiers ===\n");
    
    char buffer[100];
    
    // Проверяем, что стандартные спецификаторы работают через vsprintf
    oversprintf(buffer, "Number: %d, String: %s", 42, "test");
    test_assert("Standard specifiers", "Number: 42, String: test", buffer);
    
    oversprintf(buffer, "Percent: %%");
    test_assert("Percent sign", "Percent: %", buffer);
    
    oversprintf(buffer, "Char: %c", 'A');
    test_assert("Character", "Char: A", buffer);
}

void test_edge_cases() {
    printf("\n=== Testing edge cases ===\n");
    
    char buffer[100];
    
    // Пустая строка
    oversprintf(buffer, "");
    test_assert("Empty format", "", buffer);
    
    // Только текст
    oversprintf(buffer, "Hello World");
    test_assert("Only text", "Hello World", buffer);
    
    // Неизвестный спецификатор
    oversprintf(buffer, "%xyz");
    // Результат зависит от реализации vsprintf
    
    // Спецификатор без завершения
    oversprintf(buffer, "Test%");
    // Результат зависит от реализации
}

void test_error_handling() {
    printf("\n=== Testing error handling ===\n");
    
    char buffer[100];
    int result;
    
    // Римские цифры: число вне диапазона
    result = oversprintf(buffer, "%Ro", 0);
    printf("Roman 0: %s (result: %d)\n", buffer, result);
    
    result = oversprintf(buffer, "%Ro", 4000);
    printf("Roman 4000: %s (result: %d)\n", buffer, result);
    
    // Основание системы счисления вне диапазона
    result = oversprintf(buffer, "%Cv", 123, 50);
    printf("Base 50: %s (result: %d)\n", buffer, result);
}

int main() {
    printf("Starting oversprintf tests...\n\n");
    
    test_roman();
    test_zeckendorf();
    test_base_conversion();
    test_base_to_decimal();
    test_memory_dump();
    test_mixed_specifiers();
    test_standard_specifiers();
    test_edge_cases();
    test_error_handling();
    
    printf("\nAll tests completed!\n");
    return 0;
}