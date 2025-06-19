#include<bits/stdc++.h>
using namespace std;

double S(double x){
    return -(x * x - 4.0 * x + 2.0) * exp(-x);
}

double T_steady(double x){
    return x * x * exp(-x);
}

double norm(vector<double> T_prev, vector<double> T){
    double ans = 0.0;
    for(int i = 0; i < T.size(); i++){
        ans += abs(T[i] - T_prev[i]);
    }
    return (ans);
}

void ThomasAlgorithm_Implicit(double n, double delta_x, double delta_t, vector<double> &T_prev, vector<double> &T){
    double lamda = 2.0 + (delta_x * delta_x) / delta_t;
    vector<double> a(n + 1, 0.0), b(n + 1, 0.0), c(n + 1, 0.0);
    c[0] = 1.0;
    b[0] = -lamda;
    b[n] = -lamda;
    a[n] = 1.0;
    for(int i = 1; i < n; i++){
        a[i] = 1.0;
        b[i] = -lamda;
        c[i] = 1.0;
    }
    vector<double> d(n + 1);
    for(int i = 0; i <= n; i++){
        d[i] = -(lamda - 2.0) * T_prev[i + 1] - delta_x * delta_x * S((i + 1) * delta_x);
    }
    d[n] -= T_steady(15.0);

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
        T[i + 1] = y[i];
    }
}

void ThomasAlgorithm_CN(double n, double delta_x, double delta_t, vector<double> &T_prev, vector<double> &T){
    double lamda = 2.0 + 2.0 * (delta_x * delta_x) / delta_t;
    vector<double> a(n + 1, 0.0), b(n + 1, 0.0), c(n + 1, 0.0);
    c[0] = 1.0;
    b[0] = -lamda;
    b[n] = -lamda;
    a[n] = 1.0;
    for(int i = 1; i < n; i++){
        a[i] = 1.0;
        b[i] = -lamda;
        c[i] = 1.0;
    }
    vector<double> d(n + 1);
    for(int i = 0; i <= n; i++){
        d[i] = -(lamda - 2.0) * T_prev[i + 1] - 2.0 * delta_x * delta_x * S((i + 1) * delta_x) - (T_prev[i + 2] + T_prev[i] - 2.0 * T_prev[i + 1]);
    }
    d[n] -= T_steady(15.0);

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
        T[i + 1] = y[i];
    }
}

vector<double> Explicit(double delta_x, double delta_t){
    double size = 15.0 / delta_x, time = 0.0;
    vector<double> T_prev(size + 1, 0.0), T(size + 1, 0.0);
    T_prev[size] = T[size] = T_steady(15.0);

    while(1){
        time += delta_t;
        for(int i = 1; i < size; i++){
            T[i] = T_prev[i] + delta_t * (T_prev[i + 1] - 2.0 * T_prev[i] + T_prev[i - 1]) / (delta_x * delta_x) + delta_t * S(i * delta_x);
        }
        double error = norm(T_prev, T);
        cout << error << endl;
        if(error < 1e-6) break;
        T_prev = T;
    }
    cout << "Time = " << time << endl;

    return T;
}

vector<double> Implicit(double delta_x, double delta_t){
    double size = 15.0 / delta_x, time = 0.0;
    vector<double> T_prev(size + 1, 0.0), T(size + 1, 0.0);
    T_prev[size] = T[size] = T_steady(15.0);

    while(1){
        time += delta_t;
        ThomasAlgorithm_Implicit(size - 2, delta_x, delta_t, T_prev, T);
        double error = norm(T_prev, T);
        cout << error << endl;
        if(error < 1e-6) break;
        T_prev = T;
    }
    cout << "Time = " << time << endl;

    return T;
}

vector<double> Crank_Nicolson(double delta_x, double delta_t){
    double size = 15.0 / delta_x, time = 0.0;
    vector<double> T_prev(size + 1, 0.0), T(size + 1, 0.0);
    T_prev[size] = T[size] = T_steady(15.0);

    while(1){
        time += delta_t;
        ThomasAlgorithm_CN(size - 2, delta_x, delta_t, T_prev, T);
        double error = norm(T_prev, T);
        cout << error << endl;
        if(error < 1e-6) break;
        T_prev = T;
    }
    cout << "Time = " << time << endl;

    return T;
}

int main(){
    vector<double> delta_x_values = {1.0};
    double delta_t = 0.005;

    // cout << fixed << setprecision(10);

    for(auto delta_x: delta_x_values){
        vector<double> T_exact(15.0 / delta_x + 1, 0.0);
        vector<double> T_Explicit = Explicit(delta_x, delta_t);
        vector<double> T_Implicit = Implicit(delta_x, delta_t);
        vector<double> T_Crank_Nicolson = Crank_Nicolson(delta_x, delta_t);
        for(int i = 0; i < T_exact.size(); i++){
            T_exact[i] = T_steady(i * delta_x);
            cout << i * delta_x << " " << T_Explicit[i] << " " << T_Implicit[i] << " " << T_Crank_Nicolson[i] << " " << T_steady(i * delta_x) << endl;
            // cout << T_Crank_Nicolson[i] << endl;
        }
        double error_Explicit = norm(T_Explicit, T_exact);
        double error_Implicit = norm(T_Implicit, T_exact);
        double error_Crank_Nicolson = norm(T_Crank_Nicolson, T_exact);
        cout << "Error Explicit = " << error_Explicit << endl;
        cout << "Error Implicit = " << error_Implicit << endl;
        cout << "Error Crank-Nicolson = " << error_Crank_Nicolson << endl;
    }

    return 0;
}