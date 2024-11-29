#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> input_data; //입력 데이터 넣고 정렬할 벡터

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

	for (int i = 0; i < n; i++) {
		int CurrentElement = input_data[i];
		int j = i - 1;
		while ((j >= 0) && (input_data[j] > CurrentElement)) {
			input_data[j + 1] = input_data[j]; // 자리 이동
			j = j - 1;
		}
		input_data[j + 1] = CurrentElement;
	}

	ofstream insertion_output("insertion_output.txt");
	for (int i = 0; i < input_data.size(); i++) {
		insertion_output << input_data[i];
		if (i != input_data.size() - 1) {
			insertion_output << " "; // 각 데이터 사이 띄우기
			cout << input_data[i] << " ";
		}
	}

	insertion_output.close();

	return 0;
}