#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> input_data; // �Է� ������ �ְ� ������ ����

void insertionSorting(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int CurrentElement = input_data[i];
        int j = i - 1;
        while ((j >= 0) && (input_data[j] > CurrentElement)) {
            input_data[j + 1] = input_data[j]; // �ڸ� �̵�
            j = j - 1;
        }
        input_data[j + 1] = CurrentElement;
    }
}

int main() {
    ifstream input_file("input.txt"); //���� ����

    if (!input_file.is_open()) {
        cerr << "������ �о�� �� �����ϴ�." << endl;
        return EXIT_FAILURE;
    }

    int tmp, n = 0;

    while (input_file >> tmp) {
        input_data.push_back(tmp);
    }

    n = input_data.size();

    input_file.close(); // �Է� ���� �ݱ�

    // �ܺ� ���� ����
    int chunk_size = 100; // �޸𸮿��� ó���� �� �ִ� �ִ� ������ ����
    vector<int> sorted_data;

    // �����͸� 100���� ������ �����ϰ� ����
    for (int i = 0; i < n; i += chunk_size) {
        vector<int> buffer;
        for (int j = i; j < i + chunk_size && j < n; ++j) {
            buffer.push_back(input_data[j]);
        }

        insertionSorting(buffer); // ���� �� ������ ����

        // ���ĵ� �����͸� sorted_data�� ����
        sorted_data.insert(sorted_data.end(), buffer.begin(), buffer.end());
    }

    // ��ü �����͸� ���� ���ķ� ����
    sort(sorted_data.begin(), sorted_data.end());

    // ���� ��� ���� ����
    ofstream external_output("external_output.txt");
    for (int i = 0; i < sorted_data.size(); i++) {
        external_output << sorted_data[i];
        if (i != sorted_data.size() - 1) {
            external_output << " "; // �� ������ ���� ����
            cout << sorted_data[i] << " ";
        }
    }

    external_output.close();

    cout << "���� �Ϸ�" << endl;

    return 0;
}
