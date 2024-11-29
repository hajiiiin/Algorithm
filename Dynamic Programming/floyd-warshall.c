#include <stdio.h>
#define INF 99999 // 간선이 없는 경우
#define V 10

// 도시 이름 배열
const char* cityNames[V] = { "서울", "원주", "강릉", "천안", "논산", "대전", "대구", "포항", "광주", "부산" };

// 그래프 초기화 (인접 행렬)
int graph[V][V] = {
    {0, 15, INF, 12, INF, INF, INF, INF, INF, INF}, // 서울
    {15, 0, 21, INF, INF, INF, 7, INF, INF, INF},  // 원주
    {INF, 21, 0, INF, INF, INF, INF, 25, INF, INF}, // 강릉
    {12, INF, INF, 0, 4, 10, INF, INF, INF, INF},  // 천안
    {INF, INF, INF, 4, 0, 3, INF, INF, 13, INF},   // 논산
    {INF, INF, INF, 10, 3, 0, 10, INF, INF, INF},  // 대전
    {INF, 7, INF, INF, INF, 10, 0, 19, INF, 9},    // 대구
    {INF, INF, 25, INF, INF, INF, 19, 0, INF, 5},  // 포항
    {INF, INF, INF, INF, 13, INF, INF, INF, 0, 15}, // 광주
    {INF, INF, INF, INF, INF, INF, 9, 5, 15, 0}    // 부산
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

    // 결과 출력
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
