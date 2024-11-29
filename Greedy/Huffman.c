#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma warning(disable:4996)

#define MAX_TREE_HT 100
#define INPUT_FILE "Huffman_input.txt"

// ��� ����ü ���� - Ʈ������ ������ �����ϱ� ���� ���
typedef struct MinHeapNode {
    char data; // ��忡 ������ ����
    unsigned freq; // �� ��
    struct MinHeapNode* left, * right; // �� ����� �ڽ��� ����Ű�� ������
} MinHeapNode;

// ���ο� ��� ���� �Լ�
MinHeapNode* newNode(char data, unsigned freq) {
    MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

// Huffman Ʈ�� ���� �Լ�
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeapNode* left, * right, * top; // ���ο� Ʈ�� ��带 �����ϱ� ���� ������
    MinHeapNode** nodes = (MinHeapNode**)malloc(size * sizeof(MinHeapNode*)); //�� ����
    // MinHeapNode* (MinHeapNode�� ����Ű�� ������)���� �迭 ���·� ����Ű�� ������
    // ���� ������ �迭ó�� ����ϱ� ���� �����

    for (int i = 0; i < size; ++i) {
        nodes[i] = newNode(data[i], freq[i]);
    }

    while (size > 1) {
        // �� ���� �ּ� �� ��带 ã��
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

        // ���ο� ��ģ ��� ����
        left = nodes[min1];
        right = nodes[min2];
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        // ��� �迭 ����
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

// �ڵ� ��� �Լ�
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

// ���� ���� �Լ�
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
    // ���Ͽ��� �󵵼� �б�
    FILE* file = fopen(INPUT_FILE, "r");
    if (!file) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    int freq[4] = { 0 }; //data�� �� �� ����
    char data[4] = { 'A', 'T', 'G', 'C' };

    clock_t start = clock();

    // ���� �о �ش��ϴ� ������ �� �� ����
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        for (int i = 0; i < 4; ++i) {
            if (ch == data[i]) {
                freq[i]++;
            }
        }
    }
    fclose(file);

    int size = 4; //data �迭�� ũ��

    printf("Huffman Codes:\n");
    MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);

    // ���� ���� ���
    const char* encodedStr = "10110010001110101010100";
    decode(root, encodedStr);

    clock_t end = clock();
    printf("�ҿ� �ð�: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
