#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/vector.h"

// Функции для работы со строками
char* copy_string(char* str) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    char* new_str = malloc(len + 1);
    if (new_str) {
        strcpy(new_str, str);
    }
    return new_str;
}

void delete_string(char* str) {
    free(str);
}

void print_test_result(const char* test_name, int passed) {
    printf("%s: %s\n", test_name, passed ? "PASSED" : "FAILED");
}

DEFINE_VEC(char *)

int main() {
    printf("=== Testing String Vector ===\n");
    int tests_passed = 0;
    int total_tests = 0;
    
    // Тест 1: Создание и базовые операции
    printf("\n--- Test 1: Creation and basic operations ---\n");
    vector v = create_vector(2, copy_string, delete_string);
    printf("Vector created: size=%zu, capacity=%zu\n", v.sz, v.cap);
    printf("Expected: size=0, capacity=2\n");
    int test1 = (v.sz == 0 && v.cap == 2);
    print_test_result("Create vector with capacity 2", test1);
    tests_passed += test1; total_tests++;
    
    push_back_vector(&v, copy_string("Hello"));
    push_back_vector(&v, copy_string("World"));
    push_back_vector(&v, copy_string("Test"));
    printf("After push_back: size=%zu, capacity=%zu\n", v.sz, v.cap);
    printf("Expected: size=3, capacity=4 (double when full)\n");
    int test2 = (v.sz == 3 && v.cap == 4);
    print_test_result("Push back with reallocation", test2);
    tests_passed += test2; total_tests++;

    printf("Elements: %s, %s, %s\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1), 
           get_at_vector(&v, 2));
    printf("Expected: Hello, World, Test\n");
    int test3 = (strcmp(get_at_vector(&v, 0), "Hello") == 0 &&
                 strcmp(get_at_vector(&v, 1), "World") == 0 &&
                 strcmp(get_at_vector(&v, 2), "Test") == 0);
    print_test_result("Get elements by index", test3);
    tests_passed += test3; total_tests++;
    
    // Тест 2: Удаление элемента
    printf("\n--- Test 2: Delete operation ---\n");
    delete_at_vector(&v, 1);
    printf("After delete at index 1: size=%zu\n", v.sz);
    printf("Expected: size=2\n");
    int test4 = (v.sz == 2);
    print_test_result("Delete middle element", test4);
    tests_passed += test4; total_tests++;
    
    printf("Elements after delete: %s, %s\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1));
    printf("Expected: Hello, Test\n");
    int test5 = (strcmp(get_at_vector(&v, 0), "Hello") == 0 &&
                 strcmp(get_at_vector(&v, 1), "Test") == 0);
    print_test_result("Elements shifted after delete", test5);
    tests_passed += test5; total_tests++;
    
    // Тест 3: Копирование векторов
    printf("\n--- Test 3: Copy operations ---\n");
    vector v2 = create_vector(2, copy_string, delete_string);
    push_back_vector(&v2, copy_string("One"));
    push_back_vector(&v2, copy_string("Two"));
    
    printf("Before copy - v2: ");
    for(size_t i = 0; i < v2.sz; i++) {
        printf("%s ", get_at_vector(&v2, i));
    }
    printf("\n");
    printf("Expected: One Two\n");
    
    copy_vector(&v, &v2);
    printf("After copy - v: ");
    for(size_t i = 0; i < v.sz; i++) {
        printf("%s ", get_at_vector(&v, i));
    }
    printf("\n");
    printf("Expected: One Two\n");
    int test6 = (v.sz == 2 && 
                 strcmp(get_at_vector(&v, 0), "One") == 0 &&
                 strcmp(get_at_vector(&v, 1), "Two") == 0);
    print_test_result("Copy vector contents", test6);
    tests_passed += test6; total_tests++;
    
    vector v3 = create_vector(2, copy_string, delete_string);
    push_back_vector(&v3, copy_string("One"));
    push_back_vector(&v3, copy_string("Three"));
    
    printf("Vectors v and v3 equal: %d\n", is_equal_vector(&v, &v3));
    printf("Expected: 0 (false)\n");
    int test8 = (is_equal_vector(&v, &v3) == 0);
    print_test_result("Different vectors comparison", test8);
    tests_passed += test8; total_tests++;
    
    // Тест 4: Копирование в новую память
    printf("\n--- Test 5: Copy to new vector ---\n");
    vector* v4 = copy_vector_new(&v2);
    if(v4) {
        printf("New vector copy: ");
        for(size_t i = 0; i < v4->sz; i++) {
            printf("%s ", get_at_vector(v4, i));
        }
        printf("\n");
        printf("Expected: One Two\n");
        int test9 = (v4->sz == 2 &&
                     strcmp(get_at_vector(v4, 0), "One") == 0 &&
                     strcmp(get_at_vector(v4, 1), "Two") == 0);
        print_test_result("Copy to new vector in heap", test9);
        tests_passed += test9; total_tests++;
        delete_vector(v4);
        free(v4);
    } else {
        printf("FAILED: copy_vector_new returned NULL\n");
    }
    
    // Тест 5: Очистка вектора
    printf("\n--- Test 6: Erase vector ---\n");
    printf("Before erase - v2 size: %zu\n", v2.sz);
    printf("Expected: 2\n");
    erase_vector(&v2);
    printf("After erase - v2 size: %zu, capacity: %zu\n", v2.sz, v2.cap);
    printf("Expected: size=0, capacity=0\n");
    int test10 = (v2.sz == 0 && v2.cap == 0);
    print_test_result("Erase vector (clear)", test10);
    tests_passed += test10; total_tests++;
    
    // Тест 6: Получение по неверному индексу
    printf("\n--- Test 7: Invalid index access ---\n");
    char* result = get_at_vector(&v, 10);
    printf("Get at invalid index: %s\n", result ? result : "NULL");
    printf("Expected: NULL or (null)\n");
    int test11 = (result == NULL || strcmp(result, "") == 0);
    print_test_result("Invalid index returns NULL", test11);
    tests_passed += test11; total_tests++;
    
    // Тест 7: Удаление по неверному индексу
    printf("Before invalid delete - v size: %zu\n", v.sz);
    printf("Expected: 2\n");
    size_t old_size = v.sz;
    delete_at_vector(&v, 10);
    printf("After invalid delete - v size: %zu\n", v.sz);
    printf("Expected: 2 (no change)\n");
    int test12 = (v.sz == old_size);
    print_test_result("Invalid delete doesn't change size", test12);
    tests_passed += test12; total_tests++;
    
    // Тест 8: Создание вектора с capacity 0
    printf("\n--- Test 9: Zero capacity vector ---\n");
    vector v5 = create_vector(0, copy_string, delete_string);
    printf("Zero capacity vector: size=%zu, capacity=%zu\n", v5.sz, v5.cap);
    printf("Expected: size=0, capacity=0\n");
    int test13 = (v5.sz == 0 && v5.cap == 0);
    print_test_result("Create vector with zero capacity", test13);
    tests_passed += test13; total_tests++;
    
    push_back_vector(&v5, copy_string("First"));
    printf("After push to zero capacity: size=%zu, capacity=%zu\n", v5.sz, v5.cap);
    printf("Expected: size=1, capacity=2 (initial capacity for empty vector)\n");
    int test14 = (v5.sz == 1 && v5.cap >= 1);
    print_test_result("Push to zero capacity vector", test14);
    tests_passed += test14; total_tests++;
    
    // Очистка
    printf("\n--- Cleanup ---\n");
    delete_vector(&v);
    delete_vector(&v2);
    delete_vector(&v3);
    delete_vector(&v5);
    printf("All vectors cleaned up\n");
    
    printf("\n=== Test Results: %d/%d passed ===\n\n", tests_passed, total_tests);
    
    return tests_passed == total_tests ? 0 : 1;
}