#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono> // 러닝 타임 측정을 위한 헤더

using namespace std;
using namespace chrono;

vector<int> input_data; //입력 데이터 넣고 정렬할 벡터
int N; //정렬할 배열의 크기
int* temp; //임시 값 저장

// 정렬하면서 합병하기
void merge(int left, int right) {
	int mid = (left + right) / 2;

	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid && j <= right) {
		//절반을 기준으로
		//앞부분이 작으면
		if (input_data[i] <= input_data[j])
			//앞부분을 temp에 저장
			temp[k++] = input_data[i++];
		//뒷부분이 작으면
		else
			//뒷부분을 저장
			temp[k++] = input_data[j++];
	}

	int tmp = i > mid ? j : i;
	while (k <= right) {
		temp[k++] = input_data[tmp++];
	}

	for (int i = left; i <= right; i++) {
		input_data[i] = temp[i];
	}
}

// input_data 쪼개기
void divide(int left, int right) {
	int mid;

	if (left < right) { //길이가 1이 아니라면
		mid = (left + right) / 2;
		divide(left, mid);
		divide(mid + 1, right);
		merge(left, right);
	}

}

int main() {
	ifstream input_file("input_sort.txt"); //파일 열기

	if (!input_file.is_open()) {
		cerr << "파일을 읽어올 수 없습니다." << endl;
		return EXIT_FAILURE;
	}

	int tmp;

	while (input_file >> tmp) {
		input_data.push_back(tmp);
	}

	input_file.close(); // 입력 파일 닫기

	N = input_data.size();
	temp = new int[N];

	// 러닝 타임 측정 시작
	auto start = high_resolution_clock::now();

	divide(0, N - 1);

	// 러닝 타임 측정 종료
	auto end = high_resolution_clock::now();

	// 경과 시간 계산
	auto duration = duration_cast<milliseconds>(end - start);
	cout << "정렬 시간: " << duration.count() << " 밀리초" << endl;

	ofstream output_merge_sort("output_merge_sort.xlsx");
	for (int i = 0; i < input_data.size(); i++) {
		output_merge_sort << input_data[i];
		if (i != input_data.size() - 1) {
			output_merge_sort << ","; // 각 데이터 사이에 쉼표 추가
		}
	}

	output_merge_sort.close();

	delete[] temp; // 동적 배열 메모리 해제

	return 0;
}