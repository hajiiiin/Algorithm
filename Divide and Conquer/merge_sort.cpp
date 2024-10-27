#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono> // ���� Ÿ�� ������ ���� ���

using namespace std;
using namespace chrono;

vector<int> input_data; //�Է� ������ �ְ� ������ ����
int N; //������ �迭�� ũ��
int* temp; //�ӽ� �� ����

// �����ϸ鼭 �պ��ϱ�
void merge(int left, int right) {
	int mid = (left + right) / 2;

	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid && j <= right) {
		//������ ��������
		//�պκ��� ������
		if (input_data[i] <= input_data[j])
			//�պκ��� temp�� ����
			temp[k++] = input_data[i++];
		//�޺κ��� ������
		else
			//�޺κ��� ����
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

// input_data �ɰ���
void divide(int left, int right) {
	int mid;

	if (left < right) { //���̰� 1�� �ƴ϶��
		mid = (left + right) / 2;
		divide(left, mid);
		divide(mid + 1, right);
		merge(left, right);
	}

}

int main() {
	ifstream input_file("input_sort.txt"); //���� ����

	if (!input_file.is_open()) {
		cerr << "������ �о�� �� �����ϴ�." << endl;
		return EXIT_FAILURE;
	}

	int tmp;

	while (input_file >> tmp) {
		input_data.push_back(tmp);
	}

	input_file.close(); // �Է� ���� �ݱ�

	N = input_data.size();
	temp = new int[N];

	// ���� Ÿ�� ���� ����
	auto start = high_resolution_clock::now();

	divide(0, N - 1);

	// ���� Ÿ�� ���� ����
	auto end = high_resolution_clock::now();

	// ��� �ð� ���
	auto duration = duration_cast<milliseconds>(end - start);
	cout << "���� �ð�: " << duration.count() << " �и���" << endl;

	ofstream output_merge_sort("output_merge_sort.xlsx");
	for (int i = 0; i < input_data.size(); i++) {
		output_merge_sort << input_data[i];
		if (i != input_data.size() - 1) {
			output_merge_sort << ","; // �� ������ ���̿� ��ǥ �߰�
		}
	}

	output_merge_sort.close();

	delete[] temp; // ���� �迭 �޸� ����

	return 0;
}