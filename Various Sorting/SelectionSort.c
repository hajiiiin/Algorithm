#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int main() {

	FILE* input_file;
	FILE* output_file;
	int* input_data = NULL; // ���� �迭
	int num = 0, size =0, temp = 0;

	//���� ����
	input_file = fopen("input.txt", "r");
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

	// selection_output.txt�� ���
	output_file = fopen("selection_output.txt", "w");
	if (output_file == NULL) {
		printf("��� ���� ���� ����\n");
		free(input_data);
		return 1;
	}

	for (int i = 0; i < size; i++) {
		fprintf(output_file, "%d\n", input_data[i]);
		printf("%d ", input_data[i]);
	}

	printf("���� �Ϸ�!");

	fclose(output_file); // ��� ���� �ݱ�
	free(input_data); // ���� �޸� ����


	return 0;
}