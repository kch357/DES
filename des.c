#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

unsigned int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

unsigned int inv_IP[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

uint8_t get_bit(unsigned char *data, int n) {
    // n은 1 ~ 64
    int byte_index = (n - 1) / 8; // 몇 번째 바이트에 있는지 계산 (0 ~ 7)
    int bit_index = (n - 1) % 8;  // 그 바이트 내에서 몇 번째 비트인지 계산 (0 ~ 7)

    // 바이트 내에서는 왼쪽(MSB)부터 0번 인덱스 취급하므로 7에서 빼줍니다.
    return (data[byte_index] >> (7 - bit_index)) & 1;
}

char plaintext[] = "QWERASDF";

int main() {
    // printf("please chat your plaintext.\n");
    // scanf("%s", plaintext);
    /*
    char *plaintext = (void *)0; //자료형은 byte단위
    size_t len = 0;
    getline(&plaintext, &len, stdin);
    plaintext[len - 1] = 0;
    printf("%s is your plaintext.\n", plaintext);
    printf("%zu", len);
    */
    unsigned int bitpt[64];
    for (int i = 1; i < 65; i++)
    {
        bitpt[i-1] = get_bit(plaintext, i);
        printf("%d", bitpt[i-1]);
    }



    //initial Permutation IP(x)
    /*
    char ipx[64];
    for (size_t i = 0; i < 64; i++)
    {
        ipx[i] = plaintext[inv_IP[i]];
    }
    */

    return 0;
}