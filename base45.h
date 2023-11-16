//
// Created by stefkoff on 16.11.23.
//

#ifndef BASE46_BASE45_H
#define BASE46_BASE45_H

#include <malloc.h>
#include <stdlib.h>

#define BASE46_SIZE 45

const char base46encodingTable[BASE46_SIZE] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";
const char base46valueTable[BASE46_SIZE]= {
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A,
        0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
        0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x20, 0x24, 0x25, 0x2A,
        0x2B, 0x2D, 0x2E, 0x2F, 0x3A
};

int* base45_encode2(int input) {
    static int result[2];
    int desired = abs(input);
    int c, d;
    for(c = 0; c < BASE46_SIZE; c++) {
        for(d = 0; d < BASE46_SIZE; d++) {
            int x = (c + (BASE46_SIZE * d));
            if(x == desired) {
                result[0] = c;
                result[1] = d;
                return result;
            }
        }
    }

    return NULL;
}

int* base45_encode3(int input) {
    static int result[3];
    int c, d, e;
    for(c = 0; c < BASE46_SIZE; c++) {
        for(d = 0; d < BASE46_SIZE; d++) {
            for(e = 0; e < BASE46_SIZE; e++) {
                int x = (c + (BASE46_SIZE * d) + (BASE46_SIZE * BASE46_SIZE * e));
                if(x == input) {
                    result[0] = c;
                    result[1] = d;
                    result[2] = e;
                    return result;
                }
            }
        }
    }

    return NULL;
}

int base45_decode3(int c, int d, int e) {
    static char result[3];
    return c + (BASE46_SIZE * d) + (BASE46_SIZE * BASE46_SIZE * e);
}

int base45_decode2(int c, int d) {
    static char result[2];
    return c + (BASE46_SIZE * d);
}

int findIndex(char c) {
    for(int i = 0; i < BASE46_SIZE; i++) {
        if(base46valueTable[i] == c) {
            return i;
        }
    }

    return -1;
}

char* base45_decode(const char* str, int size) {
    char* result = (char*) malloc(size * (size / 2));
    int resultCount = 0;
    for(int i = 0; i < size; i+=3) {
        int c, d, e, n;
        c = findIndex(str[i]);
        d = findIndex(str[i + 1]);
        if((i + 2) >= size) {
            n = base45_decode2(c, d);
        } else {
            e = findIndex(str[i + 2]);
            n = base45_decode3(c, d, e);
        }

        int a = n >> 8;
        int b = n & 0xFF;

        if(i + 2 < size) {
            result[resultCount++] = a;
        }
        result[resultCount++] = b;
    }

    return result;
}

char *base45_encode(const char *str, int size) {
    char *result = (char *) malloc(size * (size / 2));
    int resultSize = 0;

    for(int i = 0; i < size; i+=2) {
        int a = str[i];
        int b = str[i + 1];
        int c, d, e;
        if(i + 1 >= size) {
            int *base45 = base45_encode2(a);
            c = base45[0];
            d = base45[1];
        } else {
            int* base45 = base45_encode3((a << 8) | b);
            c = base45[0];
            d = base45[1];
            e = base45[2];
        }

        result[resultSize++] = base46encodingTable[c];
        result[resultSize++] = base46encodingTable[d];
        if(i + 1 < size) {
            result[resultSize++] = base46encodingTable[e];
        }
    }

    return result;
}

#endif //BASE46_BASE45_H
