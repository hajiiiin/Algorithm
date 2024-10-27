import java.util.*;

public class SetCover {
    static class Village {
        int id;
        List<Village> neighbors;

        Village(int id) {
            this.id = id;
            this.neighbors = new ArrayList<>();
        }

        void addNeighbor(Village neighbor) {
            neighbors.add(neighbor);
        }
    }

    public static void main(String[] args) {
        // 1. Graph creation
        Map<Integer, Village> villages = new HashMap<>();
        for (int i = 1; i <= 10; i++) {
            villages.put(i, new Village(i));
        }

        // Connect the villages
        connect(villages, 1, 2);
        connect(villages, 1, 4);
        connect(villages, 2, 3);
        connect(villages, 2, 4);
        connect(villages, 3, 4);
        connect(villages, 4, 5);
        connect(villages, 4, 7);
        connect(villages, 5, 6);
        connect(villages, 5, 10);
        connect(villages, 6, 9);
        connect(villages, 7, 9);

        // 2. Greedy solution for Set Cover
        long startGreedy = System.currentTimeMillis();
        List<Integer> greedyCover = greedySetCover(villages);
        long endGreedy = System.currentTimeMillis();
        long timeGreedy = endGreedy - startGreedy;
        System.out.println("Greedy Set Cover Solution: " + greedyCover);
        System.out.println("Greedy Solution Running Time: " + timeGreedy + " ms");

        // 3. Optimal solution for Set Cover (Brute Force)
        long startOptimal = System.currentTimeMillis();
        List<Integer> optimalCover = optimalSetCover(villages);
        long endOptimal = System.currentTimeMillis();
        long timeOptimal = endOptimal - startOptimal;
        System.out.println("Optimal Set Cover Solution: " + optimalCover);
        System.out.println("Optimal Solution Running Time: " + timeOptimal + " ms");

        // Compare Running Times
        System.out.println("\nRunning Time Comparison:");
        System.out.println("Greedy: " + timeGreedy + " ms vs Optimal: " + timeOptimal + " ms");
    }

    private static void connect(Map<Integer, Village> villages, int v1, int v2) {
        villages.get(v1).addNeighbor(villages.get(v2));
        villages.get(v2).addNeighbor(villages.get(v1));
    }

    // Greedy Set Cover Algorithm
    private static List<Integer> greedySetCover(Map<Integer, Village> villages) {
        Set<Integer> covered = new HashSet<>();
        List<Integer> cover = new ArrayList<>();

        while (covered.size() < villages.size()) {
            Village maxVillage = null;
            int maxCoverage = -1;

            for (Village village : villages.values()) {
                if (covered.contains(village.id)) continue;
                int coverage = 0;
                for (Village neighbor : village.neighbors) {
                    if (!covered.contains(neighbor.id)) {
                        coverage++;
                    }
                }
                if (coverage > maxCoverage) {
                    maxVillage = village;
                    maxCoverage = coverage;
                }
            }

            if (maxVillage != null) {
                cover.add(maxVillage.id);
                covered.add(maxVillage.id);
                for (Village neighbor : maxVillage.neighbors) {
                    covered.add(neighbor.id);
                }
            }
        }
        return cover;
    }

    // Optimal Set Cover Algorithm using Brute Force
    private static List<Integer> optimalSetCover(Map<Integer, Village> villages) {
        List<Integer> ids = new ArrayList<>(villages.keySet());
        List<Integer> bestCover = null;

        int n = ids.size();
        for (int i = 1; i < (1 << n); i++) {
            Set<Integer> covered = new HashSet<>();
            List<Integer> currentCover = new ArrayList<>();

            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) != 0) {
                    int villageId = ids.get(j);
                    currentCover.add(villageId);
                    covered.add(villageId);
                    for (Village neighbor : villages.get(villageId).neighbors) {
                        covered.add(neighbor.id);
                    }
                }
            }

            if (covered.size() == villages.size()) {
                if (bestCover == null || currentCover.size() < bestCover.size()) {
                    bestCover = new ArrayList<>(currentCover);
                }
            }
        }
        return bestCover;
    }
}
