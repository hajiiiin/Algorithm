#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace chrono;

struct Goods {
	char name;
	int weight;
	double value;
	double vpw; // value_per_weight
};

// vpw �� �Լ�
bool compareByVPW(const Goods& a, const Goods& b) {
	return a.vpw > b.vpw;
}

int main() {
	// ��ǰ ��� ����
	vector<Goods> goodsList = {
		{'A', 10, 600000},  // ���
		{'B', 15, 750000},  // ��
		{'C', 25, 100000},  // ��
		{'D', 50, 50000}    // �ּ�
	};

	double C = 40; // �賶�� �ִ� �뷮

	// ���� ���� �� ��ġ ���
	for (auto& goods : goodsList) {
		goods.vpw = goods.value / goods.weight;
	}

	// ���� ���� �� ��ġ �������� �������� ����
	sort(goodsList.begin(), goodsList.end(), compareByVPW);

	// �賶�� ��� ���� ����
	vector<pair<Goods, double>> L; // ���� ����Ʈ
	double w = 0; // ��� ����
	double v = 0; // ��� ��ġ

	// ���� Ÿ�� ���� ����
	auto start = high_resolution_clock::now();

	// ���� ���Դ� ��ġ�� ���� ū ������ x�� ���
	Goods x = goodsList[0];

	while (w + x.weight <= C && !goodsList.empty()) {
		L.push_back({ x, x.weight });
		w += x.weight;
		v += x.value;
		// goodsList�� 0��° �ε��� ����
		goodsList.erase(goodsList.begin());

		//�������� ��ġ�� ū ������ ������
		if (!goodsList.empty()) {
			x = goodsList[0];
		}
		else {
			break;
		}
	}

	if (C - w > 0 && !goodsList.empty()) {
		double remaining_capacity = C - w; //���� ����
		L.push_back({ x, remaining_capacity });
		//x���� C-w��ŭ�� ���Ը� �߰�
		w += remaining_capacity;
		//x���� C-w��ŭ�� ��ġ�� �߰�
		v += x.vpw * remaining_capacity;
	}

	// ���� Ÿ�� ���� ����
	auto end = high_resolution_clock::now();

	// ��� ���
	cout << fixed << setprecision(2); // �Ҽ��� ���� 2�ڸ� ���
	cout << left << setw(10) << "Goods" << setw(25) << "Weight of goods in knapsack " << setw(25) << " Value of goods in knapsack" << endl;
	cout << "-----------------------------------------------------------------" << endl;

	for (auto& item : L) {
		double item_value = item.first.value * (item.second / item.first.weight); // �κ������� ������ ������ ��ġ ���
		cout << left << setw(15) << item.first.name << setw(30) << item.second << item_value / 10000 << "����" << endl;
	}

	cout << "Sum" << setw(12) << "" << setw(30) << w << v / 10000 << "����" << endl;

	// ��� �ð� ���
	auto duration = duration_cast<milliseconds>(end - start);
	cout << "���� �ð�: " << duration.count() << " �и���" << endl;

	return 0;
}