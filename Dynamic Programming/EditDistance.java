public class EditDistance {

    public static void main(String[] args){

        String S = "strong";
        String T = "stone";
        int m = S.length();
        int n = T.length();
        int[][] E = new int[m + 1][n + 1];

        for (int i = 0; i<=m; i++){ // 0번 열의 초기화
            E[i][0] = i;
        }
        for (int j = 0; j<=n; j++){ // 0번 행의 초기화
            E[0][j] = j;
        }
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                int a = (S.charAt(i - 1) == T.charAt(j - 1)) ? 0 : 1; // 문자열이 같으면 0, 다르면 1
                E[i][j] = Math.min(Math.min(E[i][j-1]+1, E[i-1][j]+1), E[i-1][j-1]+a);
            }
        }

        // 테이블 출력
        System.out.print("  ");
        for (int j = 0; j <= n; j++) {
            if (j == 0) {
                System.out.print("   ");
            } else {
                System.out.print("  " + T.charAt(j - 1));
            }
        }
        System.out.println();

        for (int i = 0; i <= m; i++) {
            if (i == 0) {
                System.out.print("   ");
            } else {
                System.out.print(" " + S.charAt(i - 1) + " ");
            }
            for (int j = 0; j <= n; j++) {
                System.out.print(String.format("%3d", E[i][j]));
            }
            System.out.println();
        }

        System.out.println("\n최소 편집 거리: " + E[m][n]);
    }
}
