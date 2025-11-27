#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 1000000

void generate_random_array(double A[], int n);
void copy_array(double B[], double A[], int n);
int is_sorted(double B[], int n);

void selection_sort(double B[], int n);
void insertion_sort(double B[], int n);
void quick_sort(double B[], int left, int right);

int main(void) {
    static double A[MAX_N];
    static double B[MAX_N];
    static double A_sorted[MAX_N];
    static double A_reverse[MAX_N];

    int n_cases[] = { 1000, 10000, 100000, 1000000 };
    int case_count = sizeof(n_cases) / sizeof(n_cases[0]);

    clock_t start, end;
    double elapsed;

    srand((unsigned int)time(NULL));

    printf("12.1. 랜덤 생성 데이터의 정렬\n");

    for (int i = 0; i < case_count; i++) {
        int n = n_cases[i];
        printf("  원소 수 : %d\n", n);

        generate_random_array(A, n);

        copy_array(B, A, n);
        start = clock();
        selection_sort(B, n);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        if (!is_sorted(B, n)) printf("selection sort error!\n");
        printf("  selection sort time: %.6f\n", elapsed);

        copy_array(B, A, n);
        start = clock();
        insertion_sort(B, n);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        if (!is_sorted(B, n)) printf("insertion sort error!\n");
        printf("  insertion sort time: %.6f\n", elapsed);

        copy_array(B, A, n);
        start = clock();
        quick_sort(B, 0, n - 1);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        if (!is_sorted(B, n)) printf("quick sort error!\n");
        printf("      quick sort time: %.6f\n\n", elapsed);
    }

    printf("12.2. 정렬된 데이터의 정렬\n");
    printf("12.2.1. 오름차순 정렬된 데이터의 정렬\n");

    for (int i = 0; i < case_count; i++) {
        int n = n_cases[i];
        printf("  원소 수 : %d\n", n);

        generate_random_array(A, n);
        copy_array(A_sorted, A, n);
        quick_sort(A_sorted, 0, n - 1);

        copy_array(B, A_sorted, n);
        start = clock();
        selection_sort(B, n);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("  selection sort time: %.6f\n", elapsed);

        copy_array(B, A_sorted, n);
        start = clock();
        insertion_sort(B, n);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("  insertion sort time: %.6f\n", elapsed);

        copy_array(B, A_sorted, n);
        start = clock();
        quick_sort(B, 0, n - 1);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("      quick sort time: %.6f\n\n", elapsed);
    }

    printf("12.2.2. 내림차순 정렬된 데이터의 정렬\n");

    for (int i = 0; i < case_count; i++) {
        int n = n_cases[i];
        printf("  원소 수 : %d\n", n);

        generate_random_array(A, n);
        copy_array(A_sorted, A, n);
        quick_sort(A_sorted, 0, n - 1);

        for (int j = 0; j < n; j++)
            A_reverse[j] = A_sorted[n - 1 - j];

        copy_array(B, A_reverse, n);
        start = clock();
        selection_sort(B, n);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("  selection sort time: %.6f\n", elapsed);

        copy_array(B, A_reverse, n);
        start = clock();
        insertion_sort(B, n);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("  insertion sort time: %.6f\n", elapsed);

        copy_array(B, A_reverse, n);
        start = clock();
        quick_sort(B, 0, n - 1);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("      quick sort time: %.6f\n\n", elapsed);
    }

    return 0;
}

void selection_sort(double B[], int n) {
    int i, j, min;
    double t;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (B[j] < B[min]) min = j;
        t = B[i]; B[i] = B[min]; B[min] = t;
    }
}

void insertion_sort(double B[], int n) {
    int i, j;
    double key;
    for (i = 1; i < n; i++) {
        key = B[i];
        j = i - 1;
        while (j >= 0 && B[j] > key) {
            B[j + 1] = B[j];
            j--;
        }
        B[j + 1] = key;
    }
}

void quick_sort(double B[], int left, int right) {
    int i = left, j = right;
    double pivot = B[(left + right) / 2], t;
    while (i <= j) {
        while (B[i] < pivot) i++;
        while (B[j] > pivot) j--;
        if (i <= j) {
            t = B[i]; B[i] = B[j]; B[j] = t;
            i++; j--;
        }
    }
    if (left < j) quick_sort(B, left, j);
    if (i < right) quick_sort(B, i, right);
}

void generate_random_array(double A[], int n) {
    for (int i = 0; i < n; i++)
        A[i] = (rand() / (0x7fff * 1.0)) * 100000000.0;
}

void copy_array(double B[], double A[], int n) {
    for (int i = 0; i < n; i++)
        B[i] = A[i];
}

int is_sorted(double B[], int n) {
    for (int i = 0; i < n - 1; i++)
        if (B[i] > B[i + 1]) return 0;
    return 1;
}
