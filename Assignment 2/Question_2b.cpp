#include<bits/stdc++.h>
using namespace std;

double f(double x){
    return sin(5.0 * x);
}

int main(){
    int n = 50;

    vector<double> x(n + 1, 0.0);
    vector<double> a(n + 1, 0.0), b(n + 1, 0.0), c(n + 1, 0.0);
    x[n] = 3;
    for(int i = 1; i < n; i++){
        x[i] = (3.0 * i) / n;
    }
    b[0] = 1.0;
    c[0] = 2.0;
    a[n] = 2.0;
    b[n] = 1.0;
    for(int i = 1; i < n; i++){
        a[i] = 1.0;
        b[i] = 4.0;
        c[i] = 1.0;
    }

    vector<double> d(n + 1);
    d[0] = n * (-2.5 * f(x[0]) + 2 * f(x[1]) + 0.5 * f(x[2])) / 3.0;
    d[n] = n * (2.5 * f(x[n]) - 2 * f(x[n - 1]) - 0.5 * f(x[n - 2])) / 3.0;
    for(int i = 1; i < n; i++){
        d[i] = n * (f(x[i + 1]) - f(x[i - 1]));
    }

    vector<double> l(n + 1), u(n + 1), z(n + 1, 0.0), y(n + 1, 0.0);

    u[0] = b[0];
    z[0] = d[0];
    for (int k = 0; k < n; k++){
        l[k + 1] = a[k + 1] / u[k];
        u[k + 1] = b[k + 1] - l[k + 1] * c[k];
        z[k + 1] = d[k + 1] - l[k + 1] * z[k];
    }

    y[n] = z[n] / u[n];
    for(int i = n - 1; i >= 0; i--){
        y[i] = (z[i] - c[i] * y[i + 1]) / u[i];
    }

    for(int i = 0; i <= n; i++){
        cout << x[i] << " " << y[i] << " " << 5 * cos(5 * x[i]) << endl;
    }

    return 0;
}