#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 원형 선언.
int** create_Matrix(int rows, int cols);
void fill_Matrix(int** matrix, int rows, int cols);
void Print_Matrix(int** matrix, int rows, int cols);
void Add_Matrix(int** matrixA, int** matrixB, int** result, int rows, int cols);
void Subtract_Matrix(int** matrixA, int** matrixB, int** result, int rows, int cols);
void Transpose_Matrix_a(int** matrix, int** result, int rows, int cols);
int Multiply_Matrix(int** matrixA, int** matrixB, int** result, int rowsA, int colsA, int rowsB, int colsB);
void free_Matrix(int** matrix, int rows);

int main() {
    int rowsA, colsA, rowsB, colsB;  // 행렬 A와 B의 행과 열의 개수.

    printf("----------[정새연] [2023041074]----------\n");

    // 행렬 A와 B의 행과 열의 개수 입력
    printf("행렬 A의 행의 개수를 입력하시오. : ");
    scanf("%d", &rowsA);
    printf("행렬 A의 열의 개수를 입력하시오. : ");
    scanf("%d", &colsA);
    printf("행렬 B의 행의 개수를 입력하시오. : ");
    scanf("%d", &rowsB);
    printf("행렬 B의 열의 개수를 입력하시오. : ");
    scanf("%d", &colsB);

    // 행렬 덧셈과 뺄셈이 가능한지 확인.
    if (rowsA != rowsB || colsA != colsB) {
        printf("행렬 덧셈과 뺄셈이 불가능합니다. 프로그램을 종료합니다.\n");
        return 0;
    }

    // A, B, result 행렬 생성
    int** matrixA = create_Matrix(rowsA, colsA);
    int** matrixB = create_Matrix(rowsB, colsB);
    int** result = create_Matrix(rowsA, colsA);

    // 행렬 A와 B에 랜덤한 값 채우기
    srand(time(NULL));
    fill_Matrix(matrixA, rowsA, colsA);
    fill_Matrix(matrixB, rowsB, colsB);

    // 행렬 A와 B 출력
    printf("\n행렬 A:\n");
    Print_Matrix(matrixA, rowsA, colsA);
    printf("\n행렬 B:\n");
    Print_Matrix(matrixB, rowsB, colsB);

    // 행렬 A와 B 더하기
    printf("\nA + B의 결과 :\n");
    Add_Matrix(matrixA, matrixB, result, rowsA, colsA);
    Print_Matrix(result, rowsA, colsA);

    // 행렬 A와 B 빼기
    printf("\nA - B의 결과 :\n");
    Subtract_Matrix(matrixA, matrixB, result, rowsA, colsA);
    Print_Matrix(result, rowsA, colsA);

    // 행렬 A의 전치행렬 구하기
    int** transposedMatrix = create_Matrix(colsA, rowsA);
    printf("\n행렬 A의 전치 행렬 T :\n");
    Transpose_Matrix_a(matrixA, transposedMatrix, rowsA, colsA);
    Print_Matrix(transposedMatrix, colsA, rowsA);
    free_Matrix(transposedMatrix, colsA);

    // A X B 행렬 곱셈
    int** productMatrix = create_Matrix(rowsA, colsB);   // 결과 행렬 동적 할당
    printf("\nA X B의 결과 :\n");

    // 행렬 곱셈이 불가능한 경우 판단하기
    if (Multiply_Matrix(matrixA, matrixB, productMatrix, rowsA, colsA, rowsB, colsB) == -1) { 
        printf("행렬 곱셈이 불가능합니다.\n");
    } else {
        Print_Matrix(productMatrix, rowsA, colsB);
    }
    free_Matrix(productMatrix, rowsA);                   // 동적으로 할당된 메모리 해제

    // 동적으로 할당된 메모리 해제
    free_Matrix(matrixA, rowsA);
    free_Matrix(matrixB, rowsB);
    free_Matrix(result, rowsA);

    return 0;
}

// 행렬을 동적으로 생성하기
int** create_Matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));  // 행의 개수에 대하여 메모리 할당
    for (int i = 0; i < rows; i++) {                    // 각 행에 대해
        matrix[i] = (int*)malloc(cols * sizeof(int));   // 열의 개수에 대하여 메모리 할당
    }
    return matrix;
}

// 행렬에 랜덤 값 채우기
void fill_Matrix(int** matrix, int rows, int cols) {     // 행렬에 랜덤한 값 채우기
    for (int i = 0; i < rows; i++) {                    // 각 행에 대해
        for (int j = 0; j < cols; j++) {                // 각 열에 대해
            matrix[i][j] = rand() % 100;                // 0~99 사이의 랜덤한 값 생성
        }
    }
}

// 행렬 출력하기
void Print_Matrix(int** matrix, int rows, int cols) {  // 함수 인자로 행렬과 행과 열의 개수를 받기
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// 두 행렬 A, B에 대하여 A+B를 연산하는 함수
void Add_Matrix(int** matrixA, int** matrixB, int** result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

// A-B를 연산하는 함수
void Subtract_Matrix(int** matrixA, int** matrixB, int** result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
}

// 행렬 A에 대하여 전치행렬을 구하는 함수
void Transpose_Matrix_a(int** matrix, int** result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];               // 전치행렬 -> 행과 열을 바꾸어 저장
        }
    }
}

// AXB를 연산하는 함수
int Multiply_Matrix(int** matrixA, int** matrixB, int** result, int rowsA, int colsA, int rowsB, int colsB) {
    // 행렬 곱셈이 불가능한 경우 (= A의 열의 개수와 B의 행의 개수가 다른 경우) 판단하기
    if (colsA != rowsB) {
        return -1;
    }

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;                           // 최종 행렬의 원소들을 0으로 초기화한 후 계산하여 대입
            for (int k = 0; k < colsA; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return 0;
}

// 메모리 해제
void free_Matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
