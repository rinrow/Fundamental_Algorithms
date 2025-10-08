// #include <string.h>
#include <stdio.h>
#include "unity.h"
#include <errno.h>
#include "../include/Funcs.h"
#include "../include/ErrorMsgs.h"

// ==================== my_memchr ====================
void test_memchr_basic(void) {
    char str[] = "Hello World";
    void *result = my_memchr(str, 'W', 11);
    TEST_ASSERT_EQUAL_PTR(str + 6, result);
    TEST_ASSERT_EQUAL_CHAR('W', *(char*)result);
}

void test_memchr_not_found(void) {
    char str[] = "Hello World";
    void *result = my_memchr(str, 'X', 11);
    TEST_ASSERT_NULL(result);
}

void test_memchr_null_ptr(void) {
    void *result = my_memchr(NULL, 'A', 5);
    TEST_ASSERT_NULL(result);
}

void test_memchr_trim_c(void) {
    char str[] = "Hello";
    // 'e' = 101, 0x12345665 тоже имеет младший байт 101
    void *result = my_memchr(str, 0x12345665, 5);
    TEST_ASSERT_EQUAL_PTR(str + 1, result);
}

// ==================== my_memcmp ====================
void test_memcmp_equal(void) {
    char str1[] = "Hello";
    char str2[] = "Hello";
    int result = my_memcmp(str1, str2, 5);
    TEST_ASSERT_EQUAL(0, result);
}

void test_memcmp_greater(void) {
    char str1[] = "Hello";
    char str2[] = "Helln"; // 'o' > 'n'
    int result = my_memcmp(str1, str2, 5);
    TEST_ASSERT_GREATER_THAN(0, result);
}

void test_memcmp_less(void) {
    char str1[] = "Hellm";
    char str2[] = "Hello"; // 'm' < 'o'
    int result = my_memcmp(str1, str2, 5);
    TEST_ASSERT_LESS_THAN(0, result);
}

void test_memcmp_null_ptrs(void) {
    TEST_ASSERT_EQUAL(0, my_memcmp(NULL, NULL, 5));
    TEST_ASSERT_LESS_THAN(0, my_memcmp(NULL, "test", 5));
    TEST_ASSERT_GREATER_THAN(0, my_memcmp("test", NULL, 5));
}

// ==================== memcpy ====================
void test_memcpy_basic(void) {
    char src[] = "Hello";
    char dest[10];
    void *result = my_memcpy(dest, src, 6);
    TEST_ASSERT_EQUAL_PTR(dest, result);
    TEST_ASSERT_EQUAL_STRING("Hello", dest);
}

void test_memcpy_null_ptrs(void) {
    void *result = my_memcpy(NULL, "test", 5);
    TEST_ASSERT_NULL(result);
    
    char dest[10];
    result = my_memcpy(dest, NULL, 5);
    TEST_ASSERT_NULL(result);
}

// ==================== memset ====================
void test_memset_basic(void) {
    char str[10] = "Hello";
    void *result = my_memset(str, 'X', 5);
    TEST_ASSERT_EQUAL_PTR(str, result);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("XXXXX", str, 5);
}

void test_memset_null_ptr(void) {
    void *result = my_memset(NULL, 'A', 5);
    TEST_ASSERT_NULL(result);
}

// ==================== strncat ====================
void test_strncat_basic(void) {
    char dest[20] = "Hello";
    char *result = my_strncat(dest, " World", 6);
    TEST_ASSERT_EQUAL_PTR(dest, result);
    TEST_ASSERT_EQUAL_STRING("Hello World", dest);
}

void test_strncat_partial(void) {
    char dest[20] = "Hello";
    char *result = my_strncat(dest, " World", 3);
    TEST_ASSERT_EQUAL_STRING("Hello Wo", dest);
}

void test_strncat_null_ptrs(void) {
    char dest[20] = "Hello";
    char *result = my_strncat(dest, NULL, 5);
    TEST_ASSERT_EQUAL_PTR(dest, result);
    TEST_ASSERT_EQUAL_STRING("Hello", dest);
    
    result = my_strncat(NULL, "test", 5);
    TEST_ASSERT_NULL(result);
}

// ==================== strchr ====================
void test_strchr_basic(void) {
    char str[] = "Hello World";
    char *result = my_strchr(str, 'W');
    TEST_ASSERT_EQUAL_PTR(str + 6, result);
}

void test_strchr_not_found(void) {
    char str[] = "Hello World";
    char *result = my_strchr(str, 'X');
    TEST_ASSERT_NULL(result);
}

void test_strchr_null_term(void) {
    char str[] = "Hello";
    char *result = my_strchr(str, '\0');
    TEST_ASSERT_EQUAL_PTR(str + 5, result);
}

void test_strchr_null_ptr(void) {
    char *result = my_strchr(NULL, 'A');
    TEST_ASSERT_NULL(result);
}

// ==================== strncmp ====================
void test_strncmp_equal(void) {
    int result = my_strncmp("Hello", "Hello", 5);
    TEST_ASSERT_EQUAL(0, result);
}

void test_strncmp_different(void) {
    int result = my_strncmp("Hello", "Helln", 5);
    TEST_ASSERT_GREATER_THAN(0, result);
}

void test_strncmp_partial(void) {
    int result = my_strncmp("Hello", "Hello World", 5);
    TEST_ASSERT_EQUAL(0, result);
}

void test_strncmp_null_ptrs(void) {
    TEST_ASSERT_EQUAL(0, my_strncmp(NULL, NULL, 5));
    TEST_ASSERT_LESS_THAN(0, my_strncmp(NULL, "test", 5));
    TEST_ASSERT_GREATER_THAN(0, my_strncmp("test", NULL, 5));
}

// ==================== strncpy ====================
void test_strncpy_basic(void) {
    char dest[10];
    char *result = my_strncpy(dest, "Hello", 6);
    TEST_ASSERT_EQUAL_PTR(dest, result);
    TEST_ASSERT_EQUAL_STRING("Hello", dest);
}

void test_strncpy_partial(void) {
    char dest[10];
    char *result = my_strncpy(dest, "Hello World", 5);
    dest[5] = '\0'; // manually null terminate
    TEST_ASSERT_EQUAL_STRING("Hello", dest);
}

void test_strncpy_null_ptrs(void) {
    char *result = my_strncpy(NULL, "test", 5);
    TEST_ASSERT_NULL(result);
}

// ==================== strcspn ====================
void test_strcspn_basic(void) {
    size_t result = my_strcspn("Hello World", " ");
    TEST_ASSERT_EQUAL(5, result);
}

void test_strcspn_not_found(void) {
    size_t result = my_strcspn("Hello", "xyz");
    TEST_ASSERT_EQUAL(5, result);
}

void test_strcspn_first_char(void) {
    size_t result = my_strcspn("Hello", "H");
    TEST_ASSERT_EQUAL(0, result);
}

void test_strcspn_null_ptrs(void) {
    size_t result = my_strcspn(NULL, "abc");
    TEST_ASSERT_EQUAL(0, result);
    
    result = my_strcspn("test", NULL);
    TEST_ASSERT_EQUAL(0, result);
}

// ==================== my_strerror ====================
void test_strerror_basic(void) {
    char *result = my_strerror(0);
    TEST_ASSERT_EQUAL_STRING("Success", result);
}

void test_strerror_known_error(void) {
    char *result = my_strerror(EPERM);
    TEST_ASSERT_EQUAL_STRING("Operation not permitted", result);
}

void test_strerror_unknown(void) {
    char *result = my_strerror(9999);
    TEST_ASSERT_EQUAL_STRING("Unknown error", result);
}

// ==================== strlen ====================
void test_strlen_basic(void) {
    size_t result = my_strlen("Hello");
    TEST_ASSERT_EQUAL(5, result);
}

void test_strlen_empty(void) {
    size_t result = my_strlen("");
    TEST_ASSERT_EQUAL(0, result);
}

void test_strlen_null_ptr(void) {
    size_t result = my_strlen(NULL);
    TEST_ASSERT_EQUAL(0, result);
}

// ==================== my_strpbrk ====================
void test_strpbrk_basic(void) {
    char str[] = "Hello World";
    char *result = my_strpbrk(str, " ");
    TEST_ASSERT_EQUAL_PTR(str + 5, result);
}

void test_strpbrk_not_found(void) {
    char str[] = "Hello";
    char *result = my_strpbrk(str, "xyz");
    TEST_ASSERT_NULL(result);
}

void test_strpbrk_null_ptrs(void) {
    char *result = my_strpbrk(NULL, "abc");
    TEST_ASSERT_NULL(result);
}

// ==================== my_strrchr ====================
void test_strrchr_basic(void) {
    char str[] = "Hello World";
    char *result = my_strrchr(str, 'l');
    TEST_ASSERT_EQUAL_PTR(str + 9, result);
}

void test_strrchr_not_found(void) {
    char str[] = "Hello";
    char *result = my_strrchr(str, 'x');
    TEST_ASSERT_NULL(result);
}

void test_strrchr_null_ptr(void) {
    char *result = my_strrchr(NULL, 'A');
    TEST_ASSERT_NULL(result);
}

// ==================== my_strstr ====================
void test_strstr_basic(void) {
    char str[] = "Hello World";
    char *result = my_strstr(str, "World");
    TEST_ASSERT_EQUAL_PTR(str + 6, result);
}

void test_strstr_not_found(void) {
    char str[] = "Hello World";
    char *result = my_strstr(str, "XYZ");
    TEST_ASSERT_NULL(result);
}

void test_strstr_empty_needle(void) {
    char str[] = "Hello";
    char *result = my_strstr(str, "");
    TEST_ASSERT_EQUAL_PTR(str, result);
}

void test_strstr_null_ptrs(void) {
    char *result = my_strstr("test", NULL);
    TEST_ASSERT_EQUAL_PTR("test", result);
    
    result = my_strstr(NULL, "test");
    TEST_ASSERT_NULL(result);
}

// ==================== strtok ====================
void test_strtok_basic(void) {
    char str[] = "Hello, !! World, !  !Test",
     delim[] = ", !";
    char *token = my_strtok(str, delim);
    TEST_ASSERT_EQUAL_STRING("Hello", token);
    token = my_strtok(NULL, delim);
    TEST_ASSERT_EQUAL_STRING("World", token);
    token = my_strtok(NULL, delim);
    TEST_ASSERT_EQUAL_STRING("Test", token);
    
    token = my_strtok(NULL, delim);
    TEST_ASSERT_NULL(token);
}

void test_strtok_null_delim(void) {
    char str[] = "Hello World";
    char *token = my_strtok(str, NULL);
    TEST_ASSERT_NULL(token);
}

// ==================== Main ====================
int main(void) {
    UNITY_BEGIN();

    // my_memchr tests
    RUN_TEST(test_memchr_basic);
    RUN_TEST(test_memchr_not_found);
    RUN_TEST(test_memchr_null_ptr);
    RUN_TEST(test_memchr_trim_c);

    // my_memcmp tests
    RUN_TEST(test_memcmp_equal);
    RUN_TEST(test_memcmp_greater);
    RUN_TEST(test_memcmp_less);
    RUN_TEST(test_memcmp_null_ptrs);

    // memcpy tests
    RUN_TEST(test_memcpy_basic);
    RUN_TEST(test_memcpy_null_ptrs);

    // memset tests
    RUN_TEST(test_memset_basic);
    RUN_TEST(test_memset_null_ptr);

    // strncat tests
    RUN_TEST(test_strncat_basic);
    RUN_TEST(test_strncat_partial);
    RUN_TEST(test_strncat_null_ptrs);

    // strchr tests
    RUN_TEST(test_strchr_basic);
    RUN_TEST(test_strchr_not_found);
    RUN_TEST(test_strchr_null_term);
    RUN_TEST(test_strchr_null_ptr);

    // my_strncmp tests
    RUN_TEST(test_strncmp_equal);
    RUN_TEST(test_strncmp_different);
    RUN_TEST(test_strncmp_partial);
    RUN_TEST(test_strncmp_null_ptrs);

    // strncpy tests
    RUN_TEST(test_strncpy_basic);
    RUN_TEST(test_strncpy_partial);
    RUN_TEST(test_strncpy_null_ptrs);

    // strcspn tests
    RUN_TEST(test_strcspn_basic);
    RUN_TEST(test_strcspn_not_found);
    RUN_TEST(test_strcspn_first_char);
    RUN_TEST(test_strcspn_null_ptrs);

    // my_strerror tests
    RUN_TEST(test_strerror_basic);
    RUN_TEST(test_strerror_known_error);
    RUN_TEST(test_strerror_unknown);

    // strlen tests
    RUN_TEST(test_strlen_basic);
    RUN_TEST(test_strlen_empty);
    RUN_TEST(test_strlen_null_ptr);

    // my_strpbrk tests
    RUN_TEST(test_strpbrk_basic);
    RUN_TEST(test_strpbrk_not_found);
    RUN_TEST(test_strpbrk_null_ptrs);

    // my_strrchr tests
    RUN_TEST(test_strrchr_basic);
    RUN_TEST(test_strrchr_not_found);
    RUN_TEST(test_strrchr_null_ptr);

    // my_strstr tests
    RUN_TEST(test_strstr_basic);
    RUN_TEST(test_strstr_not_found);
    RUN_TEST(test_strstr_empty_needle);
    RUN_TEST(test_strstr_null_ptrs);

    // my_strtok tests
    RUN_TEST(test_strtok_basic);
    RUN_TEST(test_strtok_null_delim);

    return UNITY_END();
}