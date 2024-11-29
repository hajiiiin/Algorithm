#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define MAX_COLS 100 // �ִ� �� �� ����
#define INF 99999

int main() {
    ifstream inputFile("matrix_input.txt"); // ����� ���Ե� ����
    if (!inputFile.is_open()) {
        cout << "������ �� �� �����ϴ�." << endl;
        return 1;
    }

    string line;
    int dIndex = 0;
    vector<int> d; // ����� ũ�� ������ ����

    while (getline(inputFile, line)) {
        if (line.empty()) continue;

        if (line.find('=') != string::npos) {  // ��� �̸��� ���۵Ǵ� ���� ���
            string matrixName = line.substr(0, line.find('='));
            line = line.substr(line.find('=') + 1); // '=' ���ĺ��� ��� ������ ����
            int rowCount = 0, colCount = 0;

            // ù ��° �ٿ��� �� �� ���
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

            // ���� �ٺ��� ��� �����͸� ����
            while (getline(inputFile, line)) {
                if (line.find('[') != string::npos) {
                    rowCount++;
                }
                else if (line.empty() || line.find('=') != string::npos) {
                    break;
                }
            }

            cout << matrixName << "�� ũ��: " << rowCount << " x " << colCount << endl;

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

    // �ּ� ���� Ƚ�� ���
    cout << "�ּ� ���� Ƚ�� : " << C[1][N] << endl;

    cout << setw(8) << "C";
    for (int j = 1; j <= N; ++j) {
        cout << setw(8) << j;
    }
    cout << endl;

    // C ���̺� ���� ���
    for (int i = 1; i <= N; ++i) {
        cout << setw(8) << i; // ù ��° �� (�� ��ȣ ���)
        for (int j = 1; j <= N; ++j) {
            if (C[i][j] == INF)
                cout << setw(8) << ""; // INF�� ��� ��ĭ ���
            else
                cout << setw(8) << C[i][j];
        }
        cout << endl;
    }


    return 0;
}
