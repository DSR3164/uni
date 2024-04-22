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

void bubbleSort(uint32_t arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void countingSort(uint32_t arr[], int n) {
    uint32_t max = arr[0];
    for (int i = 1; i < n; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }

    uint32_t count[max + 1];
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[index] = i;
            index++;
            count[i]--;
        }
    }
}

void merge(uint32_t arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    uint32_t L[n1], R[n2];

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
    printf("Elements\tBubbleSort\tCountingSort\tMergeSort\n");
    for (int n = 50000; n <= 1000000; n = n + 50000){
        uint32_t *arr_bubble = malloc(n * sizeof(uint32_t));
        uint32_t *arr_counting = malloc(n * sizeof(uint32_t));
        uint32_t *arr_merge = malloc(n * sizeof(uint32_t));

        double tBubble, tCounting, tMerge;

        for (int i = 0; i < n; i++) {
            arr_bubble[i] = arr_counting[i] = arr_merge[i] = getrand(1, 100000);
        }

        // Bubble Sort
        double start_time = wtime();
        bubbleSort(arr_bubble, n);
        tBubble = wtime() - start_time;

        // Counting Sort
        start_time = wtime();
        countingSort(arr_counting, n);
        tCounting = wtime() - start_time;

        // Merge Sort
        start_time = wtime();
        mergeSort(arr_merge, 0, n - 1);
        tMerge = wtime() - start_time;

        printf("%d\t\t%f\t%f\t%f\n", n, tBubble, tCounting, tMerge);

        free(arr_bubble);
        free(arr_counting);
        free(arr_merge);
    }
    return 0;
}