#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>

int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void swap(uint32_t *xp, uint32_t *yp) {
    uint32_t temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void merge(uint32_t arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;


    //uint32_t L[n1], R[n2];

    uint32_t *L = (uint32_t*)malloc(n1 * sizeof(uint32_t));
    uint32_t *R = (uint32_t*)malloc(n2 * sizeof(uint32_t));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(uint32_t arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


int main() {
    printf("Elements MergeSort\n");
    for (int n = 50000; n <= 1000000; n = n + 50000){
        uint32_t *arr_merge = (uint32_t*)malloc(sizeof(uint32_t) * n);

        double tMerge;

        for (int i = 0; i < n; i++) {
            arr_merge[i] = getrand(1, 100000);
        }

        double start_time = wtime();
        mergeSort(arr_merge, 0, n - 1);
        tMerge = wtime() - start_time;

        printf("%d\t\t%f\n", n, tMerge);

        free(arr_merge);
    }
    return 0;
}