#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void buildArray(int arr[], int size);
void printArray(int arr[], int size);
void printOddValues(int arr[], int size);
void printOddIndexValues(int arr[], int size);
int countEvenValues(int arr[], int size);
int sumArrayValues(int arr[], int size);
int findSmallestLocation(int arr[], int size);
int findLargestLocation(int arr[], int size);
void copyPositiveValues(int arr[], int size, int posArr[]);
void copyNegativeValues(int arr[], int size, int negArr[]);

int main(void) {
    int numbers[SIZE], positiveNumbers[SIZE], negativeNumbers[SIZE];
    int evenCount, totalSum, smallestIndex, largestIndex;

    srand(time(NULL));

    buildArray(numbers, SIZE);

    printf("a. Complete Array (10 values per line, aligned in rows):\n");
    printArray(numbers, SIZE);

    printf("\nb. Odd Values in the Array (10 values per line):\n");
    printOddValues(numbers, SIZE);

    printf("\nc. Values at Odd-Numbered Index Locations (10 values per line):\n");
    printOddIndexValues(numbers, SIZE);

    evenCount = countEvenValues(numbers, SIZE);
    totalSum = sumArrayValues(numbers, SIZE);
    smallestIndex = findSmallestLocation(numbers, SIZE);
    largestIndex = findLargestLocation(numbers, SIZE);

    printf("\nd. Count of Even Values:                     %d\n", evenCount);
    printf("e. Sum of All Values in the Array:           %d\n", totalSum);
    printf("f. Location of Smallest Value:               Index %d (Value: %d)\n", smallestIndex, numbers[smallestIndex]);
    printf("g. Location of Largest Value:                Index %d (Value: %d)\n", largestIndex, numbers[largestIndex]);

    printf("\nh. Positive Values Copied to New Array (Printed via Process a):\n");
    copyPositiveValues(numbers, SIZE, positiveNumbers);

    printf("\ni. Negative Values Copied to New Array (Printed via Process a):\n");
    copyNegativeValues(numbers, SIZE, negativeNumbers);

    return 0;
}

void buildArray(int arr[], int size) {
    int i, randomVal;

    for (i = 0; i < size; i++) {
        randomVal = (rand() % 999) + 1;
        if (randomVal % 3 == 0 || randomVal % 7 == 0) {
            randomVal = -randomVal;
        }
        arr[i] = randomVal;
    }
}

void printArray(int arr[], int size) {
    int i;

    for (i = 0; i < size; i++) {
        printf("%6d", arr[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    if (size % 10 != 0) {
        printf("\n");
    }
}

void printOddValues(int arr[], int size) {
    int i, count;

    count = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            printf("%6d", arr[i]);
            count++;
            if (count % 10 == 0) {
                printf("\n");
            }
        }
    }
    if (count % 10 != 0) {
        printf("\n");
    }
}

void printOddIndexValues(int arr[], int size) {
    int i, count;

    count = 0;
    for (i = 1; i < size; i += 2) {
        printf("%6d", arr[i]);
        count++;
        if (count % 10 == 0) {
            printf("\n");
        }
    }
    if (count % 10 != 0) {
        printf("\n");
    }
}

int countEvenValues(int arr[], int size) {
    int i, count;

    count = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int sumArrayValues(int arr[], int size) {
    int i, sum;

    sum = 0;
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int findSmallestLocation(int arr[], int size) {
    int i, minIndex;

    minIndex = 0;
    for (i = 1; i < size; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

int findLargestLocation(int arr[], int size) {
    int i, maxIndex;

    maxIndex = 0;
    for (i = 1; i < size; i++) {
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void copyPositiveValues(int arr[], int size, int posArr[]) {
    int i, posCount;

    posCount = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] > 0) {
            posArr[posCount] = arr[i];
            posCount++;
        }
    }
    printArray(posArr, posCount);
}

void copyNegativeValues(int arr[], int size, int negArr[]) {
    int i, negCount;

    negCount = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] < 0) {
            negArr[negCount] = arr[i];
            negCount++;
        }
    }
    printArray(negArr, negCount);
}
