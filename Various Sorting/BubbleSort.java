import java.io.*;

public class BubbleSort {
    public static void main(String[] args) {
        try (BufferedReader input_file = new BufferedReader(new FileReader("input.txt"));
             BufferedWriter output_file = new BufferedWriter(new FileWriter("bubble_output.txt"))) {

            int[] arr = inputArrayFromFile(input_file);

            bubbleSort(arr);

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

    public static void bubbleSort(int[] arr) {
        for (int i = 0; i < arr.length - 1; i++) {
            for (int j = 0; j < arr.length - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    // Swap
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}
