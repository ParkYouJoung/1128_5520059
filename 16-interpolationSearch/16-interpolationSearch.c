#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> // 1초 대기를 위해 sleep을 쓰기위한 라이브러리

#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount = 0; //비교횟수

//난수 배열 생성
void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 10000;  // 0~9999 사이의 난수
	}
}

// 퀵 정렬 분할
int partition(int array[], int low, int high) {
	int pivot = array[high];
	int i = low - 1;
	int temp;

	for (int j = low; j < high; j++) {
		compareCount++; // 비교 횟수 증가
		if (array[j] <= pivot) {
			i++;
			SWAP(array[i], array[j], temp);
		}
	}
	SWAP(array[i + 1], array[high], temp);
	return i + 1;
}

// 퀵 정렬
void QuickSort(int array[], int low, int high) {
	if (low < high) {
		int pi = partition(array, low, high);
		QuickSort(array, low, pi - 1);
		QuickSort(array, pi + 1, high);
	}
}

//출력함수
void printArray(int* array) {
	printf("Array Sorting Result:\n");

	for (int i = 0; i < 20; i++)
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%3d ", array[i]);
	printf("\n\n");
}


//이진탐색
int search_binary(int key, int low, int high, int list[])
{
	int middle;

	while (low <= high) { 				// 아직 숫자들이 남아 있으면
		compareCount++; //비교횟수 증가

		middle = (low + high) / 2;
		if (key == list[middle]) return middle; 	// 탐색 성공
		else if (key > list[middle]) low = middle + 1; 	// 왼쪽 부분리스트 탐색
		else high = middle - 1; 			// 오른쪽 부분리스트 탐색
	}
	return -1; 					// 탐색 실패
}

// 이진탐색 평균 비교 횟수 계산
double getAverageBinarySearchCompareCount(int array[]) {
	
	compareCount = 0; // 비교 횟수 초기화

	for (int i = 0; i < 1000; i++) {
		int target = array[rand() % SIZE]; // 항상 존재하는 데이터에 대해 탐색하기 위함
		search_binary(target, 0, SIZE - 1, array);
	}
	return (double)compareCount / 1000.0; // 평균 비교 횟수 반환
}


// 보간탐색
int interpol_search(int key, int n, int list[]) {
	int low, high, j;
	low = 0;
	high = n - 1;

	while ((list[high] >= key) && (key >= list[low])) {
		compareCount++; // 비교 횟수 증가

		j = ((float)(key - list[low]) / (list[high] - list[low])
			* (high - low)) + low;
		if (key > list[j]) low = j + 1;

		else if (key < list[j]) high = j - 1;

		else return j; // 탐색 성공	
	}

	if (list[low] == key)
		compareCount++; // 마지막 비교
	return low; // 탐색 성공

	return -1; // 탐색 실패
}

// 보간 탐색 평균 비교 횟수 계산
double getAverageInterpolationSearchComparecount(int array[]) {
	compareCount = 0; // 비교 횟수 초기화

	for (int i = 0; i < 1000; i++) {
		int target = array[rand() % SIZE]; // 항상 배열 내 존재하는 값 선택
		interpol_search(target, SIZE, array);
	}

	return (double)compareCount / 1000.0; // 평균 비교 횟수 반환
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

		Sleep(1000); // 1초 대기

	}

	return 0;

}
