#include <stdio.h>
#define INF 99999 // ������ ���� ���
#define V 10

// ���� �̸� �迭
const char* cityNames[V] = { "����", "����", "����", "õ��", "���", "����", "�뱸", "����", "����", "�λ�" };

// �׷��� �ʱ�ȭ (���� ���)
int graph[V][V] = {
    {0, 15, INF, 12, INF, INF, INF, INF, INF, INF}, // ����
    {15, 0, 21, INF, INF, INF, 7, INF, INF, INF},  // ����
    {INF, 21, 0, INF, INF, INF, INF, 25, INF, INF}, // ����
    {12, INF, INF, 0, 4, 10, INF, INF, INF, INF},  // õ��
    {INF, INF, INF, 4, 0, 3, INF, INF, 13, INF},   // ���
    {INF, INF, INF, 10, 3, 0, 10, INF, INF, INF},  // ����
    {INF, 7, INF, INF, INF, 10, 0, 19, INF, 9},    // �뱸
    {INF, INF, 25, INF, INF, INF, 19, 0, INF, 5},  // ����
    {INF, INF, INF, INF, 13, INF, INF, INF, 0, 15}, // ����
    {INF, INF, INF, INF, INF, INF, 9, 5, 15, 0}    // �λ�
};

int main() {
    int dist[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // ��� ���
    printf("\t");
    for (int i = 0; i < V; i++) {
        printf("%s\t", cityNames[i]);
    }
    printf("\n");

    for (int i = 0; i < V; i++) {
        printf("%s\t", cityNames[i]);
        for (int j = 0; j < V; j++) {
            if (i <= j) {
                if (dist[i][j] == INF) {
                    printf("INF\t");
                }
                else {
                    printf("%d\t", dist[i][j]);
                }
            }
            else {
                printf("\t");
            }
        }
        printf("\n");
    }

    return 0;
}
