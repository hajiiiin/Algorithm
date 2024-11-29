#include <stdio.h>
#include <limits.h>
#include <time.h>
#define V 10

// ���� �̸� �迭
const char* cityNames[V] = { "����", "����", "����", "õ��", "���", "����", "�뱸", "����", "����", "�λ�" };

// �ּ� �Ÿ��� ������ ã�� �Լ�
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// �ִ� ��� Ʈ���� ����ϴ� �Լ�
void printSolution(int allDistances[V][V]) {
    printf("\t");
    for (int i = 0; i < V; i++) {
        printf("%s\t", cityNames[i]);
    }
    printf("\n");

    for (int i = 0; i < V; i++) {
        printf("%s\t", cityNames[i]);
        for (int j = 0; j < V; j++) {
            if (i < j && allDistances[i][j] != INT_MAX) {
                printf("%.1f\t", (float)allDistances[i][j]);
            }
            else {
                printf("\t");
            }
        }
        printf("\n");
    }
}

// Dijkstra �˰��� ����
void dijkstra(int graph[V][V], int src, int allDistances[V][V]) {
    int dist[V]; // �ִ� �Ÿ� �迭
    int sptSet[V]; // �ִ� ��� Ʈ���� ���� ���� �迭

    // �ʱ�ȭ
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    dist[src] = 0; // ���� ������ �Ÿ��� 0

    // ��� ������ ���� �ݺ�
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // �ִ� �Ÿ��� ���� ����
        sptSet[u] = 1; // ���õ� ������ �ִ� ��� Ʈ���� ����

        // ���õ� ������ ���� ������ �Ÿ� ������Ʈ
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // ��� ����
    for (int i = 0; i < V; i++) {
        allDistances[src][i] = dist[i];
    }
}

int main() {
    // �׷��� �ʱ�ȭ (���� ���)
    int graph[V][V] = {
        {0, 15, 0, 12, 0, 0, 0, 0, 0, 0}, //����
        {15, 0, 21, 0, 0, 0, 7, 0, 0, 0}, //����
        {0, 21, 0, 0, 0, 0, 0, 25, 0, 0}, //����
        {12, 0, 0, 0, 4, 10, 0, 0, 0, 0}, //õ��
        {0, 0, 0, 4, 0, 3, 0, 0, 13, 0}, //���
        {0, 0, 0, 10, 3, 0, 10, 0, 0, 0}, //����
        {0, 7, 0, 0, 0, 10, 0, 19, 0, 9}, //�뱸
        {0, 0, 25, 0, 0, 0, 19, 0, 0, 5}, //����
        {0, 0, 0, 0, 13, 0, 0, 0, 0, 15}, //����
        {0, 0, 0, 0, 0, 0, 9, 5, 15, 0} //�λ�
    };

    int allDistances[V][V];

    // ���� �ð� ���� ����
    long startTime = clock();

    for (int i = 0; i < V; i++) {
        dijkstra(graph, i, allDistances); // ��� �������� �ִ� �Ÿ� ���
    }

    // ���� �ð� ���� ����
    long endTime = clock();
    double time_taken = ((double)(endTime - startTime)) / CLOCKS_PER_SEC * 1000;

    // ���� ���
    printSolution(allDistances);

    printf("\nRunning time: %.2f ms\n", time_taken);

    return 0;
}
