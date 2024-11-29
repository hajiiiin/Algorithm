#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> input_data; // 입력 데이터 넣고 정렬할 벡터

void radix_lsd(vector<int>& arr) {
    int max_value = *max_element(arr.begin(), arr.end());
    if (max_value == 0) {
        return; // 모든 값이 0인 경우 더 이상 정렬 필요 없음
    }

    int radix = 1; // 자리수 표현

    while (max_value / radix > 0) {
        vector<vector<int>> buckets(10); // 0~9를 표현하는 버킷 초기화

        // 각 자리수를 기준으로 버킷에 값 추가
        for (int num : arr) {
            int digit = (num / radix) % 10; // 현재 자리수의 값
            buckets[digit].push_back(num); // 해당 버킷에 값 추가 (정렬)
        }

        // 버킷에서 값을 꺼내어 다시 배열로 합치기
        int idx = 0;
        for (int i = 0; i < 10; i++) {
            for (int num : buckets[i]) {
                arr[idx++] = num;
            }
        }

        // 자리수를 증가시켜서 더 높은 자리수로 이동
        radix *= 10;
    }
}

void radix_msd_recursive(vector<int>& arr, int exp) {
    // 정렬할 데이터가 하나 이하이거나 exp(radix)가 0인 경우 종료
    if (arr.size() <= 1 || exp == 0) return; 

    vector<vector<int>> buckets(10); // 0~9를 표현하는 버킷

    // 현재 자리수를 기준으로 버킷에 값 추가
    for (int num : arr) {
        int digit = (num / exp) % 10; // 현재 자리수의 값
        buckets[digit].push_back(num);
    }

    // 각 버킷에 대해 재귀적으로 정렬하고, 결과를 원래 배열에 합침
    int idx = 0;
    for (int i = 0; i < 10; i++) {
        if (!buckets[i].empty()) {
            radix_msd_recursive(buckets[i], exp / 10); // 같은 요소끼리 다음 radix를 정렬해야함
            for (int num : buckets[i]) {
                arr[idx++] = num;
            }
        }
    }
}

void radix_msd(vector<int>& arr) {
    int max_value = *max_element(arr.begin(), arr.end());
    if (max_value == 0) {
        return; // 모든 값이 0인 경우 더 이상 정렬 필요 없음
    }

    int exp = 1;

    // 가장 큰 수의 자리수를 구함
    while (max_value / exp >= 10) {
        exp *= 10;
    }

    radix_msd_recursive(arr, exp);
}

int main() {
    ifstream input_file("input.txt"); // 파일 열기

    if (!input_file.is_open()) {
        cerr << "파일을 읽어올 수 없습니다." << endl;
        return EXIT_FAILURE;
    }

    int tmp;
    while (input_file >> tmp) {
        input_data.push_back(tmp);
    }

    input_file.close(); // 입력 파일 닫기

    if (input_data.empty()) {
        cerr << "입력 데이터가 비어 있습니다." << endl;
        return EXIT_FAILURE;
    }

    // LSD 기수 정렬 수행
    vector<int> lsd_sorted = input_data; // 입력 데이터를 복사하여 사용
    radix_lsd(lsd_sorted);

    ofstream radix_lsd_output("radix_lsd_output.txt");
    if (!radix_lsd_output.is_open()) {
        cerr << "파일을 쓸 수 없습니다 (radix_lsd_output.txt)." << endl;
        return EXIT_FAILURE;
    }
    for (int i = 0; i < lsd_sorted.size(); i++) {
        radix_lsd_output << lsd_sorted[i];
        if (i != lsd_sorted.size() - 1) {
            radix_lsd_output << " "; // 각 데이터 사이 띄우기
        }
    }
    radix_lsd_output.close();
    cout << "LSD 완료" << endl;

    // MSD 기수 정렬 수행
    vector<int> msd_sorted = input_data; // 입력 데이터를 복사하여 사용
    radix_msd(msd_sorted);

    ofstream radix_msd_output("radix_msd_output.txt");
    if (!radix_msd_output.is_open()) {
        cerr << "파일을 쓸 수 없습니다 (radix_msd_output.txt)." << endl;
        return EXIT_FAILURE;
    }
    for (int i = 0; i < msd_sorted.size(); i++) {
        radix_msd_output << msd_sorted[i];
        if (i != msd_sorted.size() - 1) {
            radix_msd_output << " "; // 각 데이터 사이 띄우기
        }
    }
    radix_msd_output.close();
    cout << "MSD 완료" << endl;

    return 0;
}
