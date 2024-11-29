#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> input_data; // 입력 데이터 넣고 정렬할 벡터

void insertionSorting(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int CurrentElement = input_data[i];
        int j = i - 1;
        while ((j >= 0) && (input_data[j] > CurrentElement)) {
            input_data[j + 1] = input_data[j]; // 자리 이동
            j = j - 1;
        }
        input_data[j + 1] = CurrentElement;
    }
}

int main() {
    ifstream input_file("input.txt"); //파일 열기

    if (!input_file.is_open()) {
        cerr << "파일을 읽어올 수 없습니다." << endl;
        return EXIT_FAILURE;
    }

    int tmp, n = 0;

    while (input_file >> tmp) {
        input_data.push_back(tmp);
    }

    n = input_data.size();

    input_file.close(); // 입력 파일 닫기

    // 외부 정렬 수행
    int chunk_size = 100; // 메모리에서 처리할 수 있는 최대 데이터 개수
    vector<int> sorted_data;

    // 데이터를 100개씩 나누어 정렬하고 병합
    for (int i = 0; i < n; i += chunk_size) {
        vector<int> buffer;
        for (int j = i; j < i + chunk_size && j < n; ++j) {
            buffer.push_back(input_data[j]);
        }

        insertionSorting(buffer); // 버퍼 내 데이터 정렬

        // 정렬된 데이터를 sorted_data에 병합
        sorted_data.insert(sorted_data.end(), buffer.begin(), buffer.end());
    }

    // 전체 데이터를 병합 정렬로 정렬
    sort(sorted_data.begin(), sorted_data.end());

    // 최종 출력 파일 생성
    ofstream external_output("external_output.txt");
    for (int i = 0; i < sorted_data.size(); i++) {
        external_output << sorted_data[i];
        if (i != sorted_data.size() - 1) {
            external_output << " "; // 각 데이터 사이 띄우기
            cout << sorted_data[i] << " ";
        }
    }

    external_output.close();

    cout << "정렬 완료" << endl;

    return 0;
}
