#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define MAX_COLS 100 // 최대 열 수 가정
#define INF 99999

int main() {
    ifstream inputFile("matrix_input.txt"); // 행렬이 포함된 파일
    if (!inputFile.is_open()) {
        cout << "파일을 열 수 없습니다." << endl;
        return 1;
    }

    string line;
    int dIndex = 0;
    vector<int> d; // 행렬의 크기 저장할 벡터

    while (getline(inputFile, line)) {
        if (line.empty()) continue;

        if (line.find('=') != string::npos) {  // 행렬 이름이 시작되는 줄인 경우
            string matrixName = line.substr(0, line.find('='));
            line = line.substr(line.find('=') + 1); // '=' 이후부터 행렬 데이터 읽음
            int rowCount = 0, colCount = 0;

            // 첫 번째 줄에서 열 수 계산
            if (line.find('[') != string::npos) {
                rowCount++;
                istringstream iss(line);
                string temp;
                while (iss >> temp) {
                    if (temp != "[[" && temp != "]") {
                        colCount++;
                    }
                }
            }

            // 다음 줄부터 행렬 데이터를 읽음
            while (getline(inputFile, line)) {
                if (line.find('[') != string::npos) {
                    rowCount++;
                }
                else if (line.empty() || line.find('=') != string::npos) {
                    break;
                }
            }

            cout << matrixName << "의 크기: " << rowCount << " x " << colCount << endl;

            if (d.empty()) {
                d.push_back(rowCount);
                d.push_back(colCount);
            }
            else {
                d.push_back(colCount);
            }

            dIndex = d.size();
        }
    }

    for (size_t i = 0; i < d.size(); ++i) {
        cout << "d" << i << " = " << d[i] << "  " ;
    }
    cout << endl << endl;

    inputFile.close();


    int N = d.size() - 1;
    vector<vector<int>> C(N + 1, vector<int>(N + 1, INF));

    for (int i = 1; i <= N; i++) {
        C[i][i] = 0;
    }
    for (int L = 1; L < N; L++) {
        for (int i = 1; i <= N - L; i++) {
            int j = i + L;
            C[i][j] = INF;

            for (int k = i; k < j; k++) {
                int temp = C[i][k] + C[k + 1][j] + d[i - 1] * d[k] * d[j];
                if (temp < C[i][j])
                    C[i][j] = temp;
            }
        }
    }

    // 최소 곱셈 횟수 출력
    cout << "최소 곱셈 횟수 : " << C[1][N] << endl;

    cout << setw(8) << "C";
    for (int j = 1; j <= N; ++j) {
        cout << setw(8) << j;
    }
    cout << endl;

    // C 테이블 내용 출력
    for (int i = 1; i <= N; ++i) {
        cout << setw(8) << i; // 첫 번째 열 (행 번호 출력)
        for (int j = 1; j <= N; ++j) {
            if (C[i][j] == INF)
                cout << setw(8) << ""; // INF인 경우 빈칸 출력
            else
                cout << setw(8) << C[i][j];
        }
        cout << endl;
    }


    return 0;
}
