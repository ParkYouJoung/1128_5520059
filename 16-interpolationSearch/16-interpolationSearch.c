#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> // 1�� ��⸦ ���� sleep�� �������� ���̺귯��

#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount = 0; //��Ƚ��

//���� �迭 ����
void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 10000;  // 0~9999 ������ ����
	}
}

// �� ���� ����
int partition(int array[], int low, int high) {
	int pivot = array[high];
	int i = low - 1;
	int temp;

	for (int j = low; j < high; j++) {
		compareCount++; // �� Ƚ�� ����
		if (array[j] <= pivot) {
			i++;
			SWAP(array[i], array[j], temp);
		}
	}
	SWAP(array[i + 1], array[high], temp);
	return i + 1;
}

// �� ����
void QuickSort(int array[], int low, int high) {
	if (low < high) {
		int pi = partition(array, low, high);
		QuickSort(array, low, pi - 1);
		QuickSort(array, pi + 1, high);
	}
}

//����Լ�
void printArray(int* array) {
	printf("Array Sorting Result:\n");

	for (int i = 0; i < 20; i++)
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%3d ", array[i]);
	printf("\n\n");
}


//����Ž��
int search_binary(int key, int low, int high, int list[])
{
	int middle;

	while (low <= high) { 				// ���� ���ڵ��� ���� ������
		compareCount++; //��Ƚ�� ����

		middle = (low + high) / 2;
		if (key == list[middle]) return middle; 	// Ž�� ����
		else if (key > list[middle]) low = middle + 1; 	// ���� �κи���Ʈ Ž��
		else high = middle - 1; 			// ������ �κи���Ʈ Ž��
	}
	return -1; 					// Ž�� ����
}

// ����Ž�� ��� �� Ƚ�� ���
double getAverageBinarySearchCompareCount(int array[]) {
	
	compareCount = 0; // �� Ƚ�� �ʱ�ȭ

	for (int i = 0; i < 1000; i++) {
		int target = array[rand() % SIZE]; // �׻� �����ϴ� �����Ϳ� ���� Ž���ϱ� ����
		search_binary(target, 0, SIZE - 1, array);
	}
	return (double)compareCount / 1000.0; // ��� �� Ƚ�� ��ȯ
}


// ����Ž��
int interpol_search(int key, int n, int list[]) {
	int low, high, j;
	low = 0;
	high = n - 1;

	while ((list[high] >= key) && (key >= list[low])) {
		compareCount++; // �� Ƚ�� ����

		j = ((float)(key - list[low]) / (list[high] - list[low])
			* (high - low)) + low;
		if (key > list[j]) low = j + 1;

		else if (key < list[j]) high = j - 1;

		else return j; // Ž�� ����	
	}

	if (list[low] == key)
		compareCount++; // ������ ��
	return low; // Ž�� ����

	return -1; // Ž�� ����
}

// ���� Ž�� ��� �� Ƚ�� ���
double getAverageInterpolationSearchComparecount(int array[]) {
	compareCount = 0; // �� Ƚ�� �ʱ�ȭ

	for (int i = 0; i < 1000; i++) {
		int target = array[rand() % SIZE]; // �׻� �迭 �� �����ϴ� �� ����
		interpol_search(target, SIZE, array);
	}

	return (double)compareCount / 1000.0; // ��� �� Ƚ�� ��ȯ
}

int main() {
	srand(time(NULL));
	int array[SIZE];

	for (int i = 1; i <= 3; i++) {
		printf("\n\n");

		generateRandomArray(array);

		QuickSort(array, 0, SIZE - 1);
		printArray(array);

		printf("Average Compare Count of Binary Search: %.2f\n",
			getAverageBinarySearchCompareCount(array));

		printf("Average Compare Count of Interpolation Search: %.2f\n",
			getAverageInterpolationSearchComparecount(array));

		Sleep(1000); // 1�� ���

	}

	return 0;

}
