import java.io.*;

public class QuickSort {
    public static void main(String[] args) {
        try (BufferedReader input_file = new BufferedReader(new FileReader("input_sort.txt"));
             BufferedWriter output_file = new BufferedWriter(new FileWriter("output_sort.txt"))) {

            int[] arr = inputArrayFromFile(input_file);

            long startTime = System.currentTimeMillis();
            quickSort(arr);
            long endTime = System.currentTimeMillis();

            long timeElapsed = endTime - startTime;

            // 결과를 파일로 출력
            for (int i : arr) {
                output_file.write(i + "\n");
            }

            System.out.println("milli seconds : " +  timeElapsed);
            System.out.println("seconds : " + (double)timeElapsed / 1000);
        } catch (IOException e) {
            System.out.println("파일 처리 중 오류가 발생했습니다: " + e.getMessage());
        }
    }

    // 파일에서 정수를 읽어 배열로 반환
//    public static int[] inputArrayFromFile(BufferedReader input_file) throws IOException {
//        return input_file.lines().mapToInt(Integer::parseInt).toArray();
//    }
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


    public static void quickSort(int[] arr) {
        quickSort(arr, 0, arr.length - 1);
    }

    private static void quickSort(int[] arr, int left, int right) {
        // 배열 길이가 1개 이상일 때, quick sort 진행
        if (left >= right)
            return;


        // 1. 중간값을 pivot으로 지정
        int mid = left + (right - left) / 2;
        int pivot = medianOfThree(arr, left, mid, right);

        // 2. 피봇과 첫번째 원소 교환
        swap(arr, left, pivot);
        pivot = arr[left];

        int lo = left + 1;
        int hi = right;


        //3. 피봇과 각 배열 원소 비교
        // lo는 현재 부분배열의 왼쪽, hi는 오른쪽을 의미
        // 서로 엇갈리게 될 경우 while문 종료
        while (lo <= hi) {
            while (lo <= right && arr[lo] <= pivot) // 피벗보다 큰 값을 만날 때까지
                lo++;
            while (hi > left && arr[hi] >= pivot) // 피벗보다 작은 값을 만날 때까지
                hi--;
            if (lo > hi) // 엇갈리면 피벗을 피벗보다 작은값과 교체
                swap(arr, left, hi);
            else
                swap(arr, lo, hi); // 엇갈리지 않으면 lo, hi 값 교체
        }

        // 엇갈렸을 경우,
        // 피벗값과 hi값을 교체한 후 해당 피벗을 기준으로 앞 뒤로 배열을 분할하여 정렬 진행
        quickSort(arr, left, hi - 1);
        quickSort(arr, hi + 1, right);

    }

    // 세 값 중 중간값을 찾아 반환하는 함수
    private static int medianOfThree(int[] arr, int left, int mid, int right) {
        if (arr[left] > arr[mid]) swap(arr, left, mid);
        if (arr[left] > arr[right]) swap(arr, left, right);
        if (arr[mid] > arr[right]) swap(arr, mid, right);
        return mid; // 중간값의 인덱스를 반환
    }

    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


