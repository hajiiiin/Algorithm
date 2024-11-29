#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning(disable:4996)

void DownHeap(int A[], int n, int i) {
    int leftChild = 2 * i + 1; // i�� ���� �ڽ� ���
    int rightChild = 2 * i + 2; // i�� ������ �ڽ� ���
    int bigger = i;

    // ���� �ڽ� ��尡 �����ϰ�, ���� ��庸�� ũ�� bigger�� ���� �ڽ����� ����
    if ((leftChild < n) && (A[leftChild] > A[i])) {
        bigger = leftChild;
    }

    // ������ �ڽ� ��尡 �����ϰ�, bigger���� ũ�� bigger�� ������ �ڽ����� ����
    if ((rightChild < n) && (A[rightChild] > A[bigger])) {
        bigger = rightChild;
    }

    // ���� ���� ���� ���� ū ���� ��ġ�� �ٸ��� ��ȯ�ϰ�, ��������� DownHeap ȣ��
    if (bigger != i) {
        int temp = A[i];
        A[i] = A[bigger];
        A[bigger] = temp;

        DownHeap(A, n, bigger);
    }
}

int main() {

    FILE* input_file;
    FILE* output_file;
    int* input_data = NULL; // ���� �迭
    int num = 0, size = 0, temp = 0;

    //���� ����
    input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("���Ͽ��� ����\n");
        return 1;
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

    // �ִ� �� ���� (BuildHeap)
    for (int i = floor(size / 2); i > 1; i--) {
        DownHeap(input_data, size, i);
    }

    // �� ���� ����
    for (int i = size - 1; i > 0; i--) {
        // ���� ���� ū ���� �迭�� ������ �̵�
        temp = input_data[0];
        input_data[0] = input_data[i];
        input_data[i] = temp;

        // �� ũ�⸦ ���̰�, �ٽ� �ִ� ���� ����
        DownHeap(input_data, i, 0);
    }

    // heap_output.txt�� ���
    output_file = fopen("heap_output.txt", "w");
    if (output_file == NULL) {
        printf("��� ���� ���� ����\n");
        free(input_data);
        return 1;
    }

    for (int i = 0; i < size; i++) {
        fprintf(output_file, "%d\n", input_data[i]);
        printf("%d ", input_data[i]);
    }

    printf("\n���� �Ϸ�!\n");

    fclose(output_file); // ��� ���� �ݱ�
    free(input_data); // ���� �޸� ����

    return 0;
}
