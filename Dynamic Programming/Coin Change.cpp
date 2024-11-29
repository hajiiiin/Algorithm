#include <iostream>
#include <vector>
#define INF 99999

using namespace std;

int main() {

	int n = 20; // �Ž�����
	int k = 4; //������ ������ ����
	int d[] = { 16, 10, 5, 1 }; // ����
	vector<int> c(n + 1, INF); // �Ž������� ���� ���̺�

	for (int i = 1; i <= n; i++) {
		c[i] = INF;
	}
	c[0] = 0;
	for (int j = 1; j <= n; j++) {
		for (int i = 0; i < k; i++) { // �迭 �ε��� ������ 0~k-1
			if (d[i] <= j && c[j - d[i]] + 1 < c[j])
				c[j] = c[j - d[i]] + 1;
		}
	}

	// ��� ���
	cout << "�ݾ�\t\t";
	for (int j = 0; j <= n; j++) {
		cout << j << "\t";
	}
	cout << endl;

	cout << "���� ����\t";
	for (int j = 0; j <= n; j++) {
		if (c[j] == INF) {
			cout << "INF\t"; // �Ž������� ���� �� ���� ���
		}
		else {
			cout << c[j] << "\t";
		}
	}
	cout << endl;



	return 0;
}