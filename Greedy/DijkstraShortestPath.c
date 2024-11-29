#include <stdio.h>
#include <limits.h>
#include <time.h>
#define V 10

// 도시 이름 배열
const char* cityNames[V] = { "서울", "원주", "강릉", "천안", "논산", "대전", "대구", "포항", "광주", "부산" };

// 최소 거리의 정점을 찾는 함수
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

// 최단 경로 트리를 출력하는 함수
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

// Dijkstra 알고리즘 구현
void dijkstra(int graph[V][V], int src, int allDistances[V][V]) {
    int dist[V]; // 최단 거리 배열
    int sptSet[V]; // 최단 경로 트리에 포함 여부 배열

    // 초기화
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    dist[src] = 0; // 시작 정점의 거리는 0

    // 모든 정점에 대해 반복
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // 최단 거리의 정점 선택
        sptSet[u] = 1; // 선택된 정점을 최단 경로 트리에 포함

        // 선택된 정점의 인접 정점의 거리 업데이트
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // 결과 저장
    for (int i = 0; i < V; i++) {
        allDistances[src][i] = dist[i];
    }
}

int main() {
    // 그래프 초기화 (인접 행렬)
    int graph[V][V] = {
        {0, 15, 0, 12, 0, 0, 0, 0, 0, 0}, //서울
        {15, 0, 21, 0, 0, 0, 7, 0, 0, 0}, //원주
        {0, 21, 0, 0, 0, 0, 0, 25, 0, 0}, //강릉
        {12, 0, 0, 0, 4, 10, 0, 0, 0, 0}, //천안
        {0, 0, 0, 4, 0, 3, 0, 0, 13, 0}, //논산
        {0, 0, 0, 10, 3, 0, 10, 0, 0, 0}, //대전
        {0, 7, 0, 0, 0, 10, 0, 19, 0, 9}, //대구
        {0, 0, 25, 0, 0, 0, 19, 0, 0, 5}, //포항
        {0, 0, 0, 0, 13, 0, 0, 0, 0, 15}, //광주
        {0, 0, 0, 0, 0, 0, 9, 5, 15, 0} //부산
    };

    int allDistances[V][V];

    // 실행 시간 측정 시작
    long startTime = clock();

    for (int i = 0; i < V; i++) {
        dijkstra(graph, i, allDistances); // 모든 정점에서 최단 거리 계산
    }

    // 실행 시간 측정 종료
    long endTime = clock();
    double time_taken = ((double)(endTime - startTime)) / CLOCKS_PER_SEC * 1000;

    // 최종 출력
    printSolution(allDistances);

    printf("\nRunning time: %.2f ms\n", time_taken);

    return 0;
}
