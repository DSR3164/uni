#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

void print_matrix(const vector<vector<double>>& A, const vector<double>& B) {
    cout << "Матрица A:" << endl;
    for (const auto& row : A) {
        for (double val : row) {
            cout << fixed << setprecision(4) << val << " ";
        }
        cout << endl;
    }
    cout << "Вектор B:" << endl;
    for (double bi : B) {
        cout << fixed << setprecision(4) << bi << " ";
    }
    cout << endl;
}

vector<double> gauss(vector<vector<double>> A, vector<double> B) {
    int n = A.size();
    
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > fabs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        if (fabs(A[maxRow][i]) < EPS) {
            cout << "Ошибка: система не имеет единственного решения." << endl;
            return {};
        }
        
        swap(A[i], A[maxRow]);
        swap(B[i], B[maxRow]);

        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            B[j] -= factor * B[i];
        }
    }

    vector<double> X(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * X[j];
        }
        X[i] = (B[i] - sum) / A[i][i];
    }

    return X;
}

int main() {
    int n;
    cout << "Введите количество уравнений: ";
    while (!(cin >> n) || n <= 0) {
        cout << "Ошибка! Введите целое положительное число: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> B(n);

    cout << "Введите коэффициенты матрицы A построчно:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            while (!(cin >> A[i][j])) {
                cout << "Ошибка! Введите число: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }

    cout << "Введите вектор свободных членов B:" << endl;
    for (int i = 0; i < n; i++) {
        while (!(cin >> B[i])) {
            cout << "Ошибка! Введите число: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    print_matrix(A, B);
    
    char choose;
    cout << "Если все верно, введите 1, иначе любой другой символ: ";
    cin >> choose;
    if (choose != '1') {
        cout << "Перезапустите программу и введите корректные данные." << endl;
        return 1;
    }

    vector<double> result = gauss(A, B);

    if (!result.empty()) {
        cout << "Решение системы:" << endl;
        for (double x : result) {
            cout << fixed << setprecision(4) << x << " ";
        }
        cout << endl;
    }

    return 0;
}
