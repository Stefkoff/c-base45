#include <stdio.h>
#include <string.h>
#include "base45.h"

void test1() {
    char *str = "AB";
    char *result = base45_encode(str, strlen(str));
    printf("%s\n", result);
}

void test2(){
    char* str = "Hello!!";
    char* result = base45_encode(str, strlen(str));
    printf("%s\n", result);
}

void test3(){
    char* str = "base-45";
    char* result = base45_encode(str, strlen(str));
    printf("%s\n", result);
}

void test4() {
    char* str = "base-46&$%#@!^&*()_+{}[]|\\:;\"'<>,.?/`~";
    char* result = base45_encode(str, strlen(str));
    printf("%s\n", result);
}

void test5() {
    char* str = "QED8WEX0";
    char* result = base45_decode(str, strlen(str));
    printf("%s\n", result);
}

void test6() {
    char* str = "UJCLQE7W581";
    char* result = base45_decode(str, strlen(str));
    printf("%s\n", result);
}

void test7() {
    char* str = "Hello World!";
    char* result = base45_encode(str, strlen(str));
    printf("%s\n", result);
    char* decoded = base45_decode(result, strlen(result));
    printf("%s\n", decoded);

    if(strcmp(str, decoded) == 0) {
        printf("Test 7 passed\n");
    } else {
        printf("Test 7 failed\n");
    }
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    return 0;
}
