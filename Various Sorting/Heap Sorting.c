#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning(disable:4996)

void DownHeap(int A[], int n, int i) {
    int leftChild = 2 * i + 1; // i의 왼쪽 자식 노드
    int rightChild = 2 * i + 2; // i의 오른쪽 자식 노드
    int bigger = i;

    // 왼쪽 자식 노드가 존재하고, 현재 노드보다 크면 bigger를 왼쪽 자식으로 설정
    if ((leftChild < n) && (A[leftChild] > A[i])) {
        bigger = leftChild;
    }

    // 오른쪽 자식 노드가 존재하고, bigger보다 크면 bigger를 오른쪽 자식으로 설정
    if ((rightChild < n) && (A[rightChild] > A[bigger])) {
        bigger = rightChild;
    }

    // 만약 현재 노드와 가장 큰 값의 위치가 다르면 교환하고, 재귀적으로 DownHeap 호출
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
    int* input_data = NULL; // 동적 배열
    int num = 0, size = 0, temp = 0;

    //파일 열기
    input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("파일열기 실패\n");
        return 1;
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

    // 최대 힙 구성 (BuildHeap)
    for (int i = floor(size / 2); i > 1; i--) {
        DownHeap(input_data, size, i);
    }

    // 힙 정렬 수행
    for (int i = size - 1; i > 0; i--) {
        // 현재 가장 큰 값을 배열의 끝으로 이동
        temp = input_data[0];
        input_data[0] = input_data[i];
        input_data[i] = temp;

        // 힙 크기를 줄이고, 다시 최대 힙을 유지
        DownHeap(input_data, i, 0);
    }

    // heap_output.txt로 출력
    output_file = fopen("heap_output.txt", "w");
    if (output_file == NULL) {
        printf("출력 파일 열기 실패\n");
        free(input_data);
        return 1;
    }

    for (int i = 0; i < size; i++) {
        fprintf(output_file, "%d\n", input_data[i]);
        printf("%d ", input_data[i]);
    }

    printf("\n정렬 완료!\n");

    fclose(output_file); // 출력 파일 닫기
    free(input_data); // 동적 메모리 해제

    return 0;
}
