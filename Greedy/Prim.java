import java.util.*;

class Edge {
    int source, destination, weight;

    public Edge(int source, int destination, int weight) {
        this.source = source;
        this.destination = destination;
        this.weight = weight;
    }
}

public class Prim {
    public static void main(String[] args) {
        int vertices = 6; // a: 0, b: 1, c: 2, d: 3, e: 4, f: 5
        int[][] graph = {
                {0, 3, 0, 2, 4, 0},
                {3, 0, 1, 4, 0, 0},
                {0, 1, 0, 0, 0, 1},
                {2, 4, 0, 0, 7, 0},
                {4, 0, 0, 7, 0, 9},
                {0, 0, 1, 0, 9, 0}
        };

        boolean[] inMST = new boolean[vertices];
        int[] key = new int[vertices];
        int[] parent = new int[vertices];
        Arrays.fill(key, Integer.MAX_VALUE);
        key[2] = 0; // 점 C에서 시작
        parent[2] = -1;

        long startTime = System.currentTimeMillis();

        for (int count = 0; count < vertices - 1; count++) {
            int u = minKey(key, inMST, vertices);
            inMST[u] = true;

            for (int v = 0; v < vertices; v++) {
                if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        long endTime = System.currentTimeMillis();
        long timeElapsed = endTime - startTime;

        List<Edge> mstEdges = new ArrayList<>();
        for (int i = 0; i < vertices; i++) {
            if (parent[i] != -1) {
                mstEdges.add(new Edge(parent[i], i, graph[parent[i]][i]));
            }
        }

        // 정렬하여 원하는 출력 순서와 일치하도록 함 (가중치, 그다음 소스와 목적지를 기준으로)
        mstEdges.sort(Comparator.comparingInt((Edge e) -> e.weight).thenComparingInt(e -> e.source).thenComparingInt(e -> e.destination));

        System.out.println("Minimum Spanning Tree:");
        for (Edge edge : mstEdges) {
            System.out.println("(" + edge.source + ", " + edge.destination + ", " + edge.weight + ")");
        }

        System.out.println("Running time: " + timeElapsed + " ms");
    }

    static int minKey(int[] key, boolean[] inMST, int vertices) {
        int min = Integer.MAX_VALUE, minIndex = -1;

        for (int v = 0; v < vertices; v++) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }

        return minIndex;
    }
}
