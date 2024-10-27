#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

// �迭 ���� �� ���� ��ȯ�ϴ� �Լ�
void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

// �� �� �� �߰����� �ε����� ��ȯ�ϴ� �Լ�
int medianOfThree(int arr[], int left, int mid, int right) {
	if (arr[left] > arr[mid]) swap(arr, left, mid);
	if (arr[left] > arr[right]) swap(arr, left, right);
	if (arr[mid] > arr[right]) swap(arr, mid, right);
	return mid; // �߰����� �ε����� ��ȯ
}

int Selection(int arr[], int left, int right, int k) {
	// �迭 ���̰� 1�� �̻��� ��, quick sort ����
	if (left >= right)
		return arr[left];

	// 1. �߰����� pivot���� ����
	int mid = left + (right - left) / 2;
	int pivot = medianOfThree(arr, left, mid, right);

	// 2. �Ǻ��� ù��° ���� ��ȯ
	swap(arr, left, pivot);
	pivot = arr[left];


	int lo = left + 1;
	int hi = right;


	while (lo <= hi) {
		//���� �׷쿡�� �Ǻ����� ū �� ã��
		while (lo <= right && arr[lo] < pivot)
			lo++;
		//������ �׷쿡�� �Ǻ����� ���� ���� ã��
		while (hi >= left && arr[hi] > pivot)
			hi--;
		if (lo > hi) {
			swap(arr, left, hi);
		}
		else {
			swap(arr, lo, hi);
		}
	}

	// ���� �׷��� ũ�� ���
	int S = (hi - 1) - left + 1; // small group size

	if (k <= S) {
		// k��° ���� ���Ұ� ���� �׷쿡 ���� ���
		return Selection(arr, left, hi - 1, k);
	}
	else if (k == S + 1) {
		// �Ǻ��� k��° ���� ������ ���
		return arr[hi];

	}
	else {
		// k��° ���� ���Ұ� ū �׷쿡 ���� ���
		return Selection(arr, hi + 1, right, k - S - 1);
	}


}

// 50��°�� 70��° ���� ����ϱ�
int main() {

	FILE* input_file;
	int* input_data = NULL; // ���� �迭
	int num, size = 0;

	//���� ����
	input_file = fopen("input_sort.txt", "r");
	if (input_file == NULL) {
		printf("���Ͽ��� ����\n");
	}
	else {
		printf("���Ͽ��� ����\n");
	}

	// ������ ó�� �о ������ ���� Ȯ��
	while (fscanf(input_file, "%d", &num) == 1) {
		size++; // ������ ���� ����
	}

	printf("size : %d\n", size);

	// �迭 �Ҵ�
	input_data = (int*)malloc(size * sizeof(int));
	if (input_data == NULL) {
		printf("�޸� �Ҵ� ����\n");
		fclose(input_file);
		return 1;
	}

	// ���� ��ġ �ٽ� ó������ �̵�
	rewind(input_file);

	// �� ��°�� ������ �о� input_data �迭�� ����
	for (int i = 0; i < size; i++) {
		fscanf(input_file, "%d", &input_data[i]);
	}

	fclose(input_file); // ���� �ݱ�

	int left = 0;
	int right = size - 1;

	clock_t start = clock();

	int data_50 = Selection(input_data, left, right, 50);
	int data_70 = Selection(input_data, left, right, 70);

	clock_t end = clock();

	printf("50��° ���� ���� : %d\n", data_50);
	printf("70��° ���� ���� : %d\n", data_70);
	printf("�ҿ� �ð�: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	// �޸� ����
	free(input_data);

	return 0;
}