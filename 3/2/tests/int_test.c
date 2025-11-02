#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/vector.h"

// Функции для работы с int
int copy_int(int value) {
    return value;  // для int просто возвращаем значение
}

void delete_int(int value) {
    // для int ничего не делаем
    (void)value;
}

void print_test_result(const char* test_name, int passed) {
    printf("%s: %s\n", test_name, passed ? "PASSED" : "FAILED");
}

DEFINE_VEC(int)

void print_vector(vector* v, const char* name) {
    printf("%s: [", name);
    for(size_t i = 0; i < v->sz; i++) {
        printf("%d", get_at_vector(v, i));
        if(i < v->sz - 1) printf(", ");
    }
    printf("] (size=%zu, capacity=%zu)\n", v->sz, v->cap);
}

int main() {
    printf("=== Testing Int Vector ===\n");
    int tests_passed = 0;
    int total_tests = 0;
    
    // Тест 1: Создание и базовые операции
    printf("\n--- Test 1: Creation and basic operations ---\n");
    vector v = create_vector(3, copy_int, delete_int);
    printf("Vector created: size=%zu, capacity=%zu\n", v.sz, v.cap);
    printf("Expected: size=0, capacity=3\n");
    int test1 = (v.sz == 0 && v.cap == 3);
    print_test_result("Create vector with capacity 3", test1);
    tests_passed += test1; total_tests++;
    
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    push_back_vector(&v, 40);  // Должен вызвать realloc
    printf("After push_back: size=%zu, capacity=%zu\n", v.sz, v.cap);
    printf("Expected: size=4, capacity=6 (double when full)\n");
    int test2 = (v.sz == 4 && v.cap == 6);
    print_test_result("Push back with reallocation", test2);
    tests_passed += test2; total_tests++;

    printf("Elements: %d, %d, %d, %d\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1), 
           get_at_vector(&v, 2),
           get_at_vector(&v, 3));
    printf("Expected: 10, 20, 30, 40\n");
    int test3 = (get_at_vector(&v, 0) == 10 &&
                 get_at_vector(&v, 1) == 20 &&
                 get_at_vector(&v, 2) == 30 &&
                 get_at_vector(&v, 3) == 40);
    print_test_result("Get elements by index", test3);
    tests_passed += test3; total_tests++;
    
    // Тест 2: Удаление элементов
    printf("\n--- Test 2: Delete operations ---\n");
    delete_at_vector(&v, 1);  // Удаляем 20
    printf("After delete at index 1: size=%zu\n", v.sz);
    printf("Expected: size=3\n");
    int test4 = (v.sz == 3);
    print_test_result("Delete middle element", test4);
    tests_passed += test4; total_tests++;
    
    printf("Elements after delete: %d, %d, %d\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1),
           get_at_vector(&v, 2));
    printf("Expected: 10, 30, 40\n");
    int test5 = (get_at_vector(&v, 0) == 10 &&
                 get_at_vector(&v, 1) == 30 &&
                 get_at_vector(&v, 2) == 40);
    print_test_result("Elements shifted after delete", test5);
    tests_passed += test5; total_tests++;
    
    // Тест 3: Удаление первого и последнего элементов
    delete_at_vector(&v, 0);  // Удаляем первый (10)
    printf("After delete first: size=%zu\n", v.sz);
    printf("Expected: size=2\n");
    int test6 = (v.sz == 2);
    print_test_result("Delete first element", test6);
    tests_passed += test6; total_tests++;
    
    delete_at_vector(&v, 1);  // Удаляем последний (40)
    printf("After delete last: size=%zu\n", v.sz);
    printf("Expected: size=1\n");
    int test7 = (v.sz == 1);
    print_test_result("Delete last element", test7);
    tests_passed += test7; total_tests++;
    
    printf("Final element: %d\n", get_at_vector(&v, 0));
    printf("Expected: 30\n");
    int test8 = (get_at_vector(&v, 0) == 30);
    print_test_result("Correct final element", test8);
    tests_passed += test8; total_tests++;
    
    // Тест 4: Копирование векторов
    printf("\n--- Test 4: Copy operations ---\n");
    vector v2 = create_vector(2, copy_int, delete_int);
    push_back_vector(&v2, 100);
    push_back_vector(&v2, 200);
    push_back_vector(&v2, 300);
    
    printf("Before copy - v2: ");
    print_vector(&v2, "v2");
    printf("Expected: [100, 200, 300]\n");
    
    copy_vector(&v, &v2);
    printf("After copy - v: ");
    print_vector(&v, "v");
    printf("Expected: [100, 200, 300]\n");
    int test9 = (v.sz == 3 && 
                 get_at_vector(&v, 0) == 100 &&
                 get_at_vector(&v, 1) == 200 &&
                 get_at_vector(&v, 2) == 300);
    print_test_result("Copy vector contents", test9);
    tests_passed += test9; total_tests++;
    
    // Тест 5: Сравнение векторов
    printf("\n--- Test 5: Comparison ---\n");
    printf("Vectors v and v2 equal: %d\n", is_equal_vector(&v, &v2));
    printf("Expected: 1 (true)\n");
    int test10 = (is_equal_vector(&v, &v2) == 1);
    print_test_result("Equal vectors comparison", test10);
    tests_passed += test10; total_tests++;
    
    vector v3 = create_vector(2, copy_int, delete_int);
    push_back_vector(&v3, 100);
    push_back_vector(&v3, 201);  // Разный элемент
    
    printf("Vectors v and v3 equal: %d\n", is_equal_vector(&v, &v3));
    printf("Expected: 0 (false)\n");
    int test11 = (is_equal_vector(&v, &v3) == 0);
    print_test_result("Different vectors comparison", test11);
    tests_passed += test11; total_tests++;
    
    vector v4 = create_vector(2, copy_int, delete_int);
    push_back_vector(&v4, 100);
    push_back_vector(&v4, 200);
    // v4 имеет size=2, v имеет size=3
    
    printf("Vectors v and v4 equal: %d\n", is_equal_vector(&v, &v4));
    printf("Expected: 0 (false - different sizes)\n");
    int test12 = (is_equal_vector(&v, &v4) == 0);
    print_test_result("Different size vectors comparison", test12);
    tests_passed += test12; total_tests++;
    
    // Тест 6: Копирование в новую память
    printf("\n--- Test 6: Copy to new vector ---\n");
    vector* v5 = copy_vector_new(&v2);
    if(v5) {
        printf("New vector copy: ");
        print_vector(v5, "v5");
        printf("Expected: [100, 200, 300]\n");
        int test13 = (v5->sz == 3 &&
                     get_at_vector(v5, 0) == 100 &&
                     get_at_vector(v5, 1) == 200 &&
                     get_at_vector(v5, 2) == 300);
        print_test_result("Copy to new vector in heap", test13);
        tests_passed += test13; total_tests++;
        delete_vector(v5);
        free(v5);
    } else {
        printf("FAILED: copy_vector_new returned NULL\n");
        total_tests++;
    }
    
    // Тест 7: Очистка вектора
    printf("\n--- Test 7: Erase vector ---\n");
    printf("Before erase - v2 size: %zu\n", v2.sz);
    printf("Expected: 3\n");
    erase_vector(&v2);
    printf("After erase - v2 size: %zu, capacity: %zu\n", v2.sz, v2.cap);
    printf("Expected: size=0, capacity=0\n");
    int test14 = (v2.sz == 0 && v2.cap == 0);
    print_test_result("Erase vector (clear)", test14);
    tests_passed += test14; total_tests++;
    
    // Тест 8: Граничные случаи
    printf("\n--- Test 8: Edge cases ---\n");
    
    // Получение по неверному индексу
    int invalid_result = get_at_vector(&v, 10);
    printf("Get at invalid index: %d\n", invalid_result);
    printf("Expected: 0 (default value)\n");
    int test15 = (invalid_result == 0);
    print_test_result("Invalid index returns default", test15);
    tests_passed += test15; total_tests++;
    
    // Удаление по неверному индексу
    size_t old_size = v.sz;
    delete_at_vector(&v, 10);
    printf("After invalid delete - v size: %zu\n", v.sz);
    printf("Expected: %zu (no change)\n", old_size);
    int test16 = (v.sz == old_size);
    print_test_result("Invalid delete doesn't change size", test16);
    tests_passed += test16; total_tests++;
    
    // Тест 9: Создание вектора с capacity 0
    printf("\n--- Test 9: Zero capacity vector ---\n");
    vector v6 = create_vector(0, copy_int, delete_int);
    printf("Zero capacity vector: size=%zu, capacity=%zu\n", v6.sz, v6.cap);
    printf("Expected: size=0, capacity=0\n");
    int test17 = (v6.sz == 0 && v6.cap == 0);
    print_test_result("Create vector with zero capacity", test17);
    tests_passed += test17; total_tests++;
    
    push_back_vector(&v6, 999);
    printf("After push to zero capacity: size=%zu, capacity=%zu\n", v6.sz, v6.cap);
    printf("Expected: size=1, capacity=2\n");
    int test18 = (v6.sz == 1 && v6.cap >= 1);
    print_test_result("Push to zero capacity vector", test18);
    tests_passed += test18; total_tests++;
    
    // Тест 10: Множественные добавления (стресс-тест)
    printf("\n--- Test 10: Multiple push operations ---\n");
    vector v7 = create_vector(1, copy_int, delete_int);
    for(int i = 0; i < 15; i++) {
        push_back_vector(&v7, i * 10);
    }
    printf("After 15 pushes: size=%zu, capacity=%zu\n", v7.sz, v7.cap);
    printf("Expected: size=15, capacity=16 (powers of 2)\n");
    int test19 = (v7.sz == 15 && v7.cap == 16);
    print_test_result("Multiple pushes with reallocation", test19);
    tests_passed += test19; total_tests++;
    
    printf("Elements: ");
    for(size_t i = 0; i < v7.sz; i++) {
        printf("%d ", get_at_vector(&v7, i));
    }
    printf("\n");
    printf("Expected: 0 10 20 30 40 50 60 70 80 90 100 110 120 130 140\n");
    int correct_elements = 1;
    for(size_t i = 0; i < v7.sz; i++) {
        if (get_at_vector(&v7, i) != (int)(i * 10)) {
            correct_elements = 0;
            break;
        }
    }
    print_test_result("Correct elements after multiple pushes", correct_elements);
    tests_passed += correct_elements; total_tests++;

    // Очистка
    printf("\n--- Cleanup ---\n");
    delete_vector(&v);
    delete_vector(&v2);
    delete_vector(&v3);
    delete_vector(&v4);
    delete_vector(&v6);
    delete_vector(&v7);
    printf("All vectors cleaned up\n");
    
    printf("\n=== Test Results: %d/%d passed ===\n\n", tests_passed, total_tests);
    
    return tests_passed == total_tests ? 0 : 1;
}