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

// vpw 비교 함수
bool compareByVPW(const Goods& a, const Goods& b) {
	return a.vpw > b.vpw;
}

int main() {
	// 물품 목록 정의
	vector<Goods> goodsList = {
		{'A', 10, 600000},  // 백금
		{'B', 15, 750000},  // 금
		{'C', 25, 100000},  // 은
		{'D', 50, 50000}    // 주석
	};

	double C = 40; // 배낭의 최대 용량

	// 단위 무게 당 가치 계산
	for (auto& goods : goodsList) {
		goods.vpw = goods.value / goods.weight;
	}

	// 단위 무게 당 가치 기준으로 내림차순 정렬
	sort(goodsList.begin(), goodsList.end(), compareByVPW);

	// 배낭에 담긴 물건 정보
	vector<pair<Goods, double>> L; // 물건 리스트
	double w = 0; // 담긴 무게
	double v = 0; // 담긴 가치

	// 러닝 타임 측정 시작
	auto start = high_resolution_clock::now();

	// 단위 무게당 가치가 가장 큰 물건을 x에 담기
	Goods x = goodsList[0];

	while (w + x.weight <= C && !goodsList.empty()) {
		L.push_back({ x, x.weight });
		w += x.weight;
		v += x.value;
		// goodsList의 0번째 인덱스 삭제
		goodsList.erase(goodsList.begin());

		//다음으로 가치가 큰 물건을 가져옴
		if (!goodsList.empty()) {
			x = goodsList[0];
		}
		else {
			break;
		}
	}

	if (C - w > 0 && !goodsList.empty()) {
		double remaining_capacity = C - w; //남은 무게
		L.push_back({ x, remaining_capacity });
		//x에서 C-w만큼의 무게만 추가
		w += remaining_capacity;
		//x에서 C-w만큼의 가치만 추가
		v += x.vpw * remaining_capacity;
	}

	// 러닝 타임 측정 종료
	auto end = high_resolution_clock::now();

	// 결과 출력
	cout << fixed << setprecision(2); // 소수점 이하 2자리 출력
	cout << left << setw(10) << "Goods" << setw(25) << "Weight of goods in knapsack " << setw(25) << " Value of goods in knapsack" << endl;
	cout << "-----------------------------------------------------------------" << endl;

	for (auto& item : L) {
		double item_value = item.first.value * (item.second / item.first.weight); // 부분적으로 가져온 물건의 가치 계산
		cout << left << setw(15) << item.first.name << setw(30) << item.second << item_value / 10000 << "만원" << endl;
	}

	cout << "Sum" << setw(12) << "" << setw(30) << w << v / 10000 << "만원" << endl;

	// 경과 시간 계산
	auto duration = duration_cast<milliseconds>(end - start);
	cout << "정렬 시간: " << duration.count() << " 밀리초" << endl;

	return 0;
}