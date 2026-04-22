#include <stdio.h>
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

unsigned int S[8][4][16] = {
    // S1
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    // S2
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    // S3
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    // S4
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    // S5
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    // S6
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    // S7
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    // S8
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

unsigned int E[] = {
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};

unsigned int P[] = {
    16,  7, 20, 21,
    29, 12, 28, 17,
     1, 15, 23, 26,
     5, 18, 31, 10,
     2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25
};

unsigned int PC1[] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,

    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

unsigned int PC2[] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

uint8_t get_bit(unsigned char *data, int n) {   //비트로 변환
    // n은 1 ~ 64
    int byte_index = (n - 1) / 8; // 몇 번째 바이트에 있는지 계산 (0 ~ 7)
    int bit_index = (n - 1) % 8;  // 그 바이트 내에서 몇 번째 비트인지 계산 (0 ~ 7)

    // 바이트 내에서는 왼쪽(MSB)부터 0번 인덱스 취급하므로 7에서 빼줍니다.
    return (data[byte_index] >> (7 - bit_index)) & 1;
}

void f_function(unsigned int *R, unsigned int *Key) {
    unsigned int ER[49];
    for (int i = 1; i < 49; i++){   //Expansion & Key XOR
        ER[i] = R[E[i-1]];
        ER[i] ^= Key[i];
    }
    unsigned int row;
    unsigned int column;
    for (int i = 0; i < 8; i++) //ER을 S박스에 넣어서 나온 값을 R에 넣기
    {
        row = (ER[i * 6 + 1] << 1) | ER[i * 6 + 6];
        column = (ER[i * 6 + 2] << 3) | (ER[i * 6 + 3] << 2) | (ER[i * 6 + 4] << 1) | ER[i * 6 + 5];
        R[i*4 + 1] = (S[i][row][column] >> 3) & 1; // 8의 자리
        R[i*4 + 2] = (S[i][row][column] >> 2) & 1; // 4의 자리
        R[i*4 + 3] = (S[i][row][column] >> 1) & 1; // 2의 자리
        R[i*4 + 4] = (S[i][row][column] >> 0) & 1; // 1의 자리
    }
    unsigned int Final_R[33];
    for (int i = 0; i < 32; i ++)
        Final_R[i+1] = R[P[i]];
    memcpy(R + 1, Final_R + 1, sizeof(unsigned int) * 32);  //코드 복사
};

void Key_Transform(unsigned int *C, unsigned int *D) {
    //Left Shift
    unsigned int num = C[1];
    memcpy(C + 1, C + 2, sizeof(unsigned int) * 27);
    C[28] = num;
    num = D[1];
    memcpy(D + 1, D + 2, sizeof(unsigned int) * 27);
    D[28] = num;
};

unsigned char plaintext[] = "QWERASDF";
unsigned char key_str[] = "KCHTBLOG";

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

    unsigned int bitpt[65]; //평문 비트화
    unsigned int R[33]; //평문 R
    unsigned int L[33]; //평문 L
    for (int i = 1; i <= 64; i++)
        bitpt[i] = get_bit(plaintext, IP[i-1]);  //평문 비트화 하기, IP까지 한번에
    memcpy(L + 1, bitpt + 1, sizeof(unsigned int) * 32);
    memcpy(R + 1, bitpt + 33, sizeof(unsigned int) * 32);
    
    unsigned int Key[65];
    unsigned int C[29]; //Key C
    unsigned int D[29]; //Key D
    for (int i = 1; i <= 64; i++)
        Key[i] = get_bit(key_str, i);  //키 비트화 하기
    for (int i = 1; i <= 28; i++){
        C[i] = Key[PC1[i - 1]];
        D[i] = Key[PC1[i + 27]];
    }
    
    //round 1
    unsigned int Round_Key[49];
    unsigned int Out_R[33];
    unsigned int Out_L[33];

    for (int k = 1; k <= 16; k++){
        Key_Transform(C,D);     //transform
        if (k != 1 && k != 2 && k != 9 && k != 16) //이 때는 2번이므로
            Key_Transform(C,D);     //transform
        memcpy(Key + 1, C + 1, sizeof(unsigned int) * 28);
        memcpy(Key + 29, D + 1, sizeof(unsigned int) * 28);
        for (int i = 1; i <= 48; i++)   //라운드 키 생성
            Round_Key[i] = Key[PC2[i-1]];   //PC22
        memcpy(Out_L + 1, R + 1, sizeof(unsigned int) * 32);    //Out_L 만들기
        f_function(R, Round_Key);   //R에 f-function 적용
        for (int i = 1; i <= 32; i++)     //Out_R 만들기
            Out_R[i] = L[i] ^ R[i];
        memcpy(R + 1, Out_R + 1, sizeof(unsigned int) * 32);    //R에 Out_R 대입 (f_function 반복사용하기 위함)
        memcpy(L + 1, Out_L + 1, sizeof(unsigned int) * 32);    //L에 Out_L 대입 (f_function 반복사용하기 위함)
    }
    memcpy(bitpt + 1, R + 1, sizeof(unsigned int) * 32);    //마지막에 한번 더 전치를 하기 때문에 R이 먼저
    memcpy(bitpt + 33, L + 1, sizeof(unsigned int) * 32);
    unsigned int bitct[65]; //암호문
    for (int i = 1; i <= 64; i++)  //inv_IP
        bitct[i] = bitpt[inv_IP[i-1]];
    
    printf("Ciphertext (HEX): ");
    for (int i = 0; i < 8; i++) {
        unsigned int byte = 0;
        for (int j = 1; j <= 8; j++)
            byte = (byte << 1) | bitct[i * 8 + j];
        printf("%02X ", byte);
    }
    printf("\n");

    return 0;
}