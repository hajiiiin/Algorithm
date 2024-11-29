import java.io.*;

public class ShellSorting {
    public static void main(String[] args) {
        try (BufferedReader input_file = new BufferedReader(new FileReader("input.txt"));
             BufferedWriter output_file = new BufferedWriter(new FileWriter("shell_output.txt"))) {

            int[] arr = inputArrayFromFile(input_file);

            int[] gap ={100, 50, 10, 5, 1};
            for(int h : gap){
                for(int i = h; i<arr.length; i++){
                    int currentElement = arr[i];
                    int j = i;
                    while (j >= h && arr[j - h] > currentElement) {
                        arr[j] = arr[j - h];
                        j -= h;
                    }
                    arr[j] = currentElement;
                }
            }

            // 결과를 파일로 출력
            for (int i : arr) {
                output_file.write(i + "\n");
                System.out.print(i + " ");
            }

        } catch (IOException e) {
            System.out.println("파일 처리 중 오류가 발생했습니다: " + e.getMessage());
        }
    }

    public static int[] inputArrayFromFile(BufferedReader input_file) throws IOException {
        return input_file.lines()
                .filter(line -> !line.trim().isEmpty()) // 빈 줄 제거
                .mapToInt(line -> {
                    try {
                        return Integer.parseInt(line.trim());
                    } catch (NumberFormatException e) {
                        System.err.println("잘못된 숫자 형식: " + line);
                        return 0; // 예외가 발생한 경우 0으로 처리
                    }
                })
                .toArray();
    }
}
