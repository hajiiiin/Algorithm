#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> input_data; // �Է� ������ �ְ� ������ ����

void radix_lsd(vector<int>& arr) {
    int max_value = *max_element(arr.begin(), arr.end());
    if (max_value == 0) {
        return; // ��� ���� 0�� ��� �� �̻� ���� �ʿ� ����
    }

    int radix = 1; // �ڸ��� ǥ��

    while (max_value / radix > 0) {
        vector<vector<int>> buckets(10); // 0~9�� ǥ���ϴ� ��Ŷ �ʱ�ȭ

        // �� �ڸ����� �������� ��Ŷ�� �� �߰�
        for (int num : arr) {
            int digit = (num / radix) % 10; // ���� �ڸ����� ��
            buckets[digit].push_back(num); // �ش� ��Ŷ�� �� �߰� (����)
        }

        // ��Ŷ���� ���� ������ �ٽ� �迭�� ��ġ��
        int idx = 0;
        for (int i = 0; i < 10; i++) {
            for (int num : buckets[i]) {
                arr[idx++] = num;
            }
        }

        // �ڸ����� �������Ѽ� �� ���� �ڸ����� �̵�
        radix *= 10;
    }
}

void radix_msd_recursive(vector<int>& arr, int exp) {
    // ������ �����Ͱ� �ϳ� �����̰ų� exp(radix)�� 0�� ��� ����
    if (arr.size() <= 1 || exp == 0) return; 

    vector<vector<int>> buckets(10); // 0~9�� ǥ���ϴ� ��Ŷ

    // ���� �ڸ����� �������� ��Ŷ�� �� �߰�
    for (int num : arr) {
        int digit = (num / exp) % 10; // ���� �ڸ����� ��
        buckets[digit].push_back(num);
    }

    // �� ��Ŷ�� ���� ��������� �����ϰ�, ����� ���� �迭�� ��ħ
    int idx = 0;
    for (int i = 0; i < 10; i++) {
        if (!buckets[i].empty()) {
            radix_msd_recursive(buckets[i], exp / 10); // ���� ��ҳ��� ���� radix�� �����ؾ���
            for (int num : buckets[i]) {
                arr[idx++] = num;
            }
        }
    }
}

void radix_msd(vector<int>& arr) {
    int max_value = *max_element(arr.begin(), arr.end());
    if (max_value == 0) {
        return; // ��� ���� 0�� ��� �� �̻� ���� �ʿ� ����
    }

    int exp = 1;

    // ���� ū ���� �ڸ����� ����
    while (max_value / exp >= 10) {
        exp *= 10;
    }

    radix_msd_recursive(arr, exp);
}

int main() {
    ifstream input_file("input.txt"); // ���� ����

    if (!input_file.is_open()) {
        cerr << "������ �о�� �� �����ϴ�." << endl;
        return EXIT_FAILURE;
    }

    int tmp;
    while (input_file >> tmp) {
        input_data.push_back(tmp);
    }

    input_file.close(); // �Է� ���� �ݱ�

    if (input_data.empty()) {
        cerr << "�Է� �����Ͱ� ��� �ֽ��ϴ�." << endl;
        return EXIT_FAILURE;
    }

    // LSD ��� ���� ����
    vector<int> lsd_sorted = input_data; // �Է� �����͸� �����Ͽ� ���
    radix_lsd(lsd_sorted);

    ofstream radix_lsd_output("radix_lsd_output.txt");
    if (!radix_lsd_output.is_open()) {
        cerr << "������ �� �� �����ϴ� (radix_lsd_output.txt)." << endl;
        return EXIT_FAILURE;
    }
    for (int i = 0; i < lsd_sorted.size(); i++) {
        radix_lsd_output << lsd_sorted[i];
        if (i != lsd_sorted.size() - 1) {
            radix_lsd_output << " "; // �� ������ ���� ����
        }
    }
    radix_lsd_output.close();
    cout << "LSD �Ϸ�" << endl;

    // MSD ��� ���� ����
    vector<int> msd_sorted = input_data; // �Է� �����͸� �����Ͽ� ���
    radix_msd(msd_sorted);

    ofstream radix_msd_output("radix_msd_output.txt");
    if (!radix_msd_output.is_open()) {
        cerr << "������ �� �� �����ϴ� (radix_msd_output.txt)." << endl;
        return EXIT_FAILURE;
    }
    for (int i = 0; i < msd_sorted.size(); i++) {
        radix_msd_output << msd_sorted[i];
        if (i != msd_sorted.size() - 1) {
            radix_msd_output << " "; // �� ������ ���� ����
        }
    }
    radix_msd_output.close();
    cout << "MSD �Ϸ�" << endl;

    return 0;
}
