#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma warning(disable:4996)

#define MAX_TREE_HT 100
#define INPUT_FILE "Huffman_input.txt"

// 노드 구조체 정의 - 트리에서 연결을 저장하기 위해 사용
typedef struct MinHeapNode {
    char data; // 노드에 저장할 문자
    unsigned freq; // 빈도 수
    struct MinHeapNode* left, * right; // 이 노드의 자식을 가리키는 포인터
} MinHeapNode;

// 새로운 노드 생성 함수
MinHeapNode* newNode(char data, unsigned freq) {
    MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

// Huffman 트리 생성 함수
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeapNode* left, * right, * top; // 새로운 트리 노드를 생성하기 위한 포인터
    MinHeapNode** nodes = (MinHeapNode**)malloc(size * sizeof(MinHeapNode*)); //빈도 정보
    // MinHeapNode* (MinHeapNode을 가리키는 포인터)들을 배열 형태로 가리키는 포인터
    // 여러 노드들을 배열처럼 사용하기 위해 사용함

    for (int i = 0; i < size; ++i) {
        nodes[i] = newNode(data[i], freq[i]);
    }

    while (size > 1) {
        // 두 개의 최소 빈도 노드를 찾음
        int min1 = 0, min2 = 1;
        if (nodes[min1]->freq > nodes[min2]->freq) {
            min1 = 1;
            min2 = 0;
        }
        for (int i = 2; i < size; ++i) {
            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            }
            else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }

        // 새로운 합친 노드 생성
        left = nodes[min1];
        right = nodes[min2];
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        // 노드 배열 갱신
        if (min1 < min2) {
            nodes[min1] = top;
            nodes[min2] = nodes[size - 1];
        }
        else {
            nodes[min2] = top;
            nodes[min1] = nodes[size - 1];
        }
        size--;
    }

    MinHeapNode* root = nodes[0];
    free(nodes);
    return root;
}

// 코드 출력 함수
void printCodes(MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// 압축 해제 함수
void decode(MinHeapNode* root, const char* encodedStr) {
    MinHeapNode* current = root;
    printf("Decoded String: ");
    for (int i = 0; encodedStr[i] != '\0'; ++i) {
        if (encodedStr[i] == '0')
            current = current->left;
        else
            current = current->right;

        if (!(current->left) && !(current->right)) {
            printf("%c ", current->data);
            current = root;
        }
    }
    printf("\n");
}

int main() {
    // 파일에서 빈도수 읽기
    FILE* file = fopen(INPUT_FILE, "r");
    if (!file) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int freq[4] = { 0 }; //data의 빈도 수 저장
    char data[4] = { 'A', 'T', 'G', 'C' };

    clock_t start = clock();

    // 파일 읽어서 해당하는 글자의 빈도 수 증가
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        for (int i = 0; i < 4; ++i) {
            if (ch == data[i]) {
                freq[i]++;
            }
        }
    }
    fclose(file);

    int size = 4; //data 배열의 크기

    printf("Huffman Codes:\n");
    MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);

    // 압축 해제 출력
    const char* encodedStr = "10110010001110101010100";
    decode(root, encodedStr);

    clock_t end = clock();
    printf("소요 시간: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
