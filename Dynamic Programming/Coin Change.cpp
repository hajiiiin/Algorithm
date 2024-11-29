#include <iostream>
#include <vector>
#define INF 99999

using namespace std;

int main() {

	int n = 20; // 거스름돈
	int k = 4; //동전의 종류의 개수
	int d[] = { 16, 10, 5, 1 }; // 동전
	vector<int> c(n + 1, INF); // 거스름돈의 개수 테이블

	for (int i = 1; i <= n; i++) {
		c[i] = INF;
	}
	c[0] = 0;
	for (int j = 1; j <= n; j++) {
		for (int i = 0; i < k; i++) { // 배열 인덱스 때문에 0~k-1
			if (d[i] <= j && c[j - d[i]] + 1 < c[j])
				c[j] = c[j - d[i]] + 1;
		}
	}

	// 결과 출력
	cout << "금액\t\t";
	for (int j = 0; j <= n; j++) {
		cout << j << "\t";
	}
	cout << endl;

	cout << "동전 개수\t";
	for (int j = 0; j <= n; j++) {
		if (c[j] == INF) {
			cout << "INF\t"; // 거스름돈을 만들 수 없는 경우
		}
		else {
			cout << c[j] << "\t";
		}
	}
	cout << endl;



	return 0;
}