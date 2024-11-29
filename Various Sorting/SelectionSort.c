#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int main() {

	FILE* input_file;
	FILE* output_file;
	int* input_data = NULL; // 동적 배열
	int num = 0, size =0, temp = 0;

	//파일 열기
	input_file = fopen("input.txt", "r");
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

	for (int i = 0; i < size; i++) {
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (input_data[j] < input_data[min])
				min = j;
		}
		temp = input_data[i];
		input_data[i] = input_data[min];
		input_data[min] = temp;
	}

	// selection_output.txt로 출력
	output_file = fopen("selection_output.txt", "w");
	if (output_file == NULL) {
		printf("출력 파일 열기 실패\n");
		free(input_data);
		return 1;
	}

	for (int i = 0; i < size; i++) {
		fprintf(output_file, "%d\n", input_data[i]);
		printf("%d ", input_data[i]);
	}

	printf("정렬 완료!");

	fclose(output_file); // 출력 파일 닫기
	free(input_data); // 동적 메모리 해제


	return 0;
}