#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

// 배열 내의 두 값을 교환하는 함수
void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

// 세 값 중 중간값의 인덱스를 반환하는 함수
int medianOfThree(int arr[], int left, int mid, int right) {
	if (arr[left] > arr[mid]) swap(arr, left, mid);
	if (arr[left] > arr[right]) swap(arr, left, right);
	if (arr[mid] > arr[right]) swap(arr, mid, right);
	return mid; // 중간값의 인덱스를 반환
}

int Selection(int arr[], int left, int right, int k) {
	// 배열 길이가 1개 이상일 때, quick sort 진행
	if (left >= right)
		return arr[left];

	// 1. 중간값을 pivot으로 지정
	int mid = left + (right - left) / 2;
	int pivot = medianOfThree(arr, left, mid, right);

	// 2. 피봇과 첫번째 원소 교환
	swap(arr, left, pivot);
	pivot = arr[left];


	int lo = left + 1;
	int hi = right;


	while (lo <= hi) {
		//왼쪽 그룹에서 피봇보다 큰 값 찾기
		while (lo <= right && arr[lo] < pivot)
			lo++;
		//오른쪽 그룹에서 피봇보다 작은 값을 찾음
		while (hi >= left && arr[hi] > pivot)
			hi--;
		if (lo > hi) {
			swap(arr, left, hi);
		}
		else {
			swap(arr, lo, hi);
		}
	}

	// 작은 그룹의 크기 계산
	int S = (hi - 1) - left + 1; // small group size

	if (k <= S) {
		// k번째 작은 원소가 작은 그룹에 있을 경우
		return Selection(arr, left, hi - 1, k);
	}
	else if (k == S + 1) {
		// 피봇이 k번째 작은 원소일 경우
		return arr[hi];

	}
	else {
		// k번째 작은 원소가 큰 그룹에 있을 경우
		return Selection(arr, hi + 1, right, k - S - 1);
	}


}

// 50번째와 70번째 숫자 출력하기
int main() {

	FILE* input_file;
	int* input_data = NULL; // 동적 배열
	int num, size = 0;

	//파일 열기
	input_file = fopen("input_sort.txt", "r");
	if (input_file == NULL) {
		printf("파일열기 실패\n");
	}
	else {
		printf("파일열기 성공\n");
	}

	// 파일을 처음 읽어서 정수의 개수 확인
	while (fscanf(input_file, "%d", &num) == 1) {
		size++; // 정수의 개수 증가
	}

	printf("size : %d\n", size);

	// 배열 할당
	input_data = (int*)malloc(size * sizeof(int));
	if (input_data == NULL) {
		printf("메모리 할당 실패\n");
		fclose(input_file);
		return 1;
	}

	// 파일 위치 다시 처음으로 이동
	rewind(input_file);

	// 두 번째로 파일을 읽어 input_data 배열에 저장
	for (int i = 0; i < size; i++) {
		fscanf(input_file, "%d", &input_data[i]);
	}

	fclose(input_file); // 파일 닫기

	int left = 0;
	int right = size - 1;

	clock_t start = clock();

	int data_50 = Selection(input_data, left, right, 50);
	int data_70 = Selection(input_data, left, right, 70);

	clock_t end = clock();

	printf("50번째 작은 원소 : %d\n", data_50);
	printf("70번째 작은 원소 : %d\n", data_70);
	printf("소요 시간: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	// 메모리 해제
	free(input_data);

	return 0;
}