#include<bits/stdc++.h>
using namespace std;

void ComputeLUWithPivoting(vector<vector<double>>& a, vector<vector<double>>& l, vector<vector<double>>& u, int n) {
    for (int k = 1; k <= n; k++) {
        // Find pivot
        int pivot = k;
        for (int j = k + 1; j < n; j++) {
            if (abs(a[j][k]) > abs(a[pivot][k])) {
                pivot = j;
            }
        }
        
        // Swap rows if necessary
        if (pivot != k) {
            swap(a[k], a[pivot]);
        }

        // Compute U
        for (int j = k; j <= n; j++) {
            double sum = 0.0;
            for (int s = 1; s < k; s++) {
                sum += l[k][s] * u[s][j];
            }
            u[k][j] = a[k][j] - sum;
        }

        // Compute L
        l[k][k] = 1.0;
        for (int i = k + 1; i <= n; i++) {
            double sum = 0.0;
            for (int s = 1; s < k; s++) {
                sum += l[i][s] * u[s][k];
            }
            l[i][k] = (a[i][k] - sum) / u[k][k];
        }
    }
}

int main() {
    int n = 10;
    vector<vector<double>> l(n + 1, vector<double>(n + 1, 0.0));
    vector<vector<double>> u(n + 1, vector<double>(n + 1, 0.0));
    vector<vector<double>> a(n + 1, vector<double>(n + 1, 1e-8));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i > j) a[i][j] = -1.0 - 1e-8;
            else if (i == j || j == n) a[i][j] = 1.0 + 1e-8;
        }
    }

    ComputeLUWithPivoting(a, l, u, n);

    cout << "Matrix L:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << l[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Matrix U:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << u[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Growth Factor is " << u[n][n] << endl;

    return 0;
}
