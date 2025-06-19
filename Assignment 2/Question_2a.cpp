#include<bits/stdc++.h>
using namespace std;

double f(double x){
    return sin(5.0 * x);
}

void ComputeLU(vector<vector<double>> a, vector<vector<double>> &l, vector<vector<double>> &u, int n){
   for(int k = 0; k <= n; k++){
        l[k][k] = 1.0;
        for(int j = k; j <= n; j++){
            double sum = 0;
            for(int p = 0; p <= k - 1; p++){
                sum += l[k][p] * u[p][j];
            }
            u[k][j] = a[k][j] - sum;
        }

        for(int i = k + 1; i <= n; i++){
            double sum = 0;
            for(int p = 0; p <= k - 1; p++){
                sum += l[i][p] * u[p][k];
            }
            l[i][k] = (a[i][k] - sum) / u[k][k];
       }
   }
}

void forwardSubstitution(vector<vector<double>> l, vector<double> b, vector<double> &z, int n){
    z[0] = b[0] / l[0][0];
    for(int i = 1; i <= n; i++){
        double sum = 0;
        for(int j = 0; j <= i - 1; j++){
            sum += l[i][j] * z[j];
        }
        z[i] = (b[i] - sum) / l[i][i];
    }
}

void backwardSubstitution(vector<vector<double>> u, vector<double> z, vector<double> &y, int n){
    y[n] = z[n] / u[n][n];
    for(int i = n - 1; i >= 0; i--){
        double sum = 0;
        for(int j = i + 1; j <= n; j++){
            sum += u[i][j] * y[j];
        }
        y[i] = (z[i] - sum) / u[i][i];
    }
}

int main(){
    int n = 15;

    vector<double> x(n + 1, 0.0);
    vector<vector<double>> a(n + 1, vector<double>(n + 1, 0.0));
    x[n] = 3;
    for(int i = 1; i < n; i++){
        x[i] = (3.0 * i) / n;
    }
    a[0][0] = 1;
    a[0][1] = 2;
    a[n][n - 1] = 2;
    a[n][n] = 1;
    for(int i = 1; i < n; i++){
        a[i][i - 1] = 1;
        a[i][i] = 4;
        a[i][i + 1] = 1;
    }

    vector<double> d(n + 1);
    d[0] = n * (-2.5 * f(x[0]) + 2 * f(x[1]) + 0.5 * f(x[2])) / 3.0;
    d[n] = n * (2.5 * f(x[n]) - 2 * f(x[n - 1]) - 0.5 * f(x[n - 2])) / 3.0;
    for(int i = 1; i < n; i++){
        d[i] = n * (f(x[i + 1]) - f(x[i - 1]));
    }

    vector<vector<double>> l(n + 1, vector<double>(n + 1, 0.0)), u(n + 1, vector<double>(n + 1, 0.0));
    vector<double> z(n + 1, 0.0), y(n + 1, 0.0);

    ComputeLU(a, l, u, n);
    forwardSubstitution(l, d, z, n);
    backwardSubstitution(u, z, y, n);

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            cout << l[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i <= n; i++){
        cout << x[i] << " " << y[i] << " " << 5 * cos(5 * x[i]) << endl;
        // cout << d[i] << endl;
    }

    return 0;
}