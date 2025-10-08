#ifndef UNITY_H
#define UNITY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Basic test macros
#define TEST_ASSERT(condition) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s:%d: %s\n", __FILE__, __LINE__, #condition); \
            exit(1); \
        } \
    } while(0)

#define TEST_ASSERT_EQUAL(expected, actual) \
    TEST_ASSERT((expected) == (actual))

#define TEST_ASSERT_EQUAL_STRING(expected, actual) \
    TEST_ASSERT(strcmp((expected), (actual)) == 0)

#define TEST_ASSERT_NULL(pointer) \
    TEST_ASSERT((pointer) == NULL)

#define TEST_ASSERT_NOT_NULL(pointer) \
    TEST_ASSERT((pointer) != NULL)

#define TEST_ASSERT_EQUAL_PTR(expected, actual) \
    TEST_ASSERT((void*)(expected) == (void*)(actual))

#define TEST_ASSERT_GREATER_THAN(threshold, actual) \
    TEST_ASSERT((actual) > (threshold))

#define TEST_ASSERT_LESS_THAN(threshold, actual) \
    TEST_ASSERT((actual) < (threshold))

#define TEST_ASSERT_EQUAL_CHAR(expected, actual) \
    TEST_ASSERT((char)(expected) == (char)(actual))

#define TEST_ASSERT_EQUAL_CHAR_ARRAY(expected, actual, length) \
    TEST_ASSERT(my_memcmp((expected), (actual), (length)) == 0)

// Test runner
static int tests_passed = 0;
static int tests_failed = 0;

#define RUN_TEST(test) \
    do { \
        printf("Running %s... ", #test); \
        test(); \
        printf("PASS\n"); \
        tests_passed++; \
    } while(0)

#define UNITY_BEGIN() \
    do { \
        tests_passed = 0; \
        tests_failed = 0; \
        printf("=== Starting Tests ===\n"); \
    } while(0)

#define UNITY_END() \
        printf("=== Tests Complete ===\n"); \
        printf("Passed: %d, Failed: %d\n", tests_passed, tests_failed); \
        return tests_failed; \

#endif