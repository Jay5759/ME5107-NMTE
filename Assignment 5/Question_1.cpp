#include<bits/stdc++.h>
using namespace std;

double f(double x) {
    return 7.0 - x * tan(x);
}

// Exact derivative of u(x)
double exact_derivative_u(double x) {
    return -tan(x) - x / (cos(x) * cos(x));
}

// First-order forward difference
double first_order_forward(double x, double dx, int scheme) {
    if(scheme == 1) return (f(x + dx) - f(x)) / dx;
    else return (f(x) - f(x - dx)) / dx;
}

// Second-order forward difference
double second_order_forward(double x, double dx, int scheme){
    if(scheme == 1) return (-f(x + 2 * dx) + 4.0 * f(x + dx) - 3.0 * f(x)) / (2.0 * dx);
    else return (3.0 * f(x) - 4.0 * f(x - dx) + f(x - 2 * dx)) / (2.0 * dx);
}

// Fourth-order forward difference
double fourth_order_forward(double x, double dx, int scheme) {
    if(scheme == 1) return (-3.0 * f(x + 4 * dx) + 16.0 * f(x + 3 * dx) - 36.0 * f(x + 2 * dx) + 48.0 * f(x + dx) - 25.0 * f(x)) / (12.0 * dx);
    else return (25.0 * f(x) - 48.0 * f(x - dx) + 36.0 * f(x - 2 * dx) - 16.0 * f(x - 3 * dx) + 3.0 * f(x - 4 * dx)) / (12.0 * dx);
}

int main() {
    vector<double> dx_values = {0.001};
    double start = -1.0, end = 1.0;

    cout << fixed << setprecision(10);

    // Loop through each grid size and compute errors
    for (double dx : dx_values) {
        double error_first = 0.0;
        double error_second = 0.0;
        double error_fourth = 0.0;
        for(double x = start; x <= end; x += dx) {
            double first_order;
            double exact_derivative = exact_derivative_u(x);
            if(x + dx <= end) first_order = first_order_forward(x, dx, 1);
            else first_order = first_order_forward(x, dx, 2);

            error_first = max(error_first, abs(first_order - exact_derivative));

            cout << "x = " << x << endl;
            cout << "First-order forward difference: " << first_order << endl;
            cout << "Exact derivative: " << exact_derivative << endl;
            cout << endl;
        }
        for(double x = start; x <= end; x += dx) {
            double second_order;
            double exact_derivative = exact_derivative_u(x);
            if(x + 2.0 * dx <= end) second_order = second_order_forward(x, dx, 1);
            else second_order = second_order_forward(x, dx, 2);

            error_second = max(error_second, abs(second_order - exact_derivative));

            cout << "x = " << x << endl;
            cout << "Second-order forward difference: " << second_order << endl;
            cout << "Exact derivative: " << exact_derivative << endl;
            cout << endl;
        }
        for(double x = start; x <= end; x += dx) {
            double fourth_order;
            double exact_derivative = exact_derivative_u(x);
            if(x + 4.0 * dx <= end) fourth_order = fourth_order_forward(x, dx, 1);
            else fourth_order = fourth_order_forward(x, dx, 2);

            error_fourth = max(error_fourth, abs(fourth_order - exact_derivative));

            cout << "x = " << x << endl;
            cout << "fourth-order forward difference: " << fourth_order << endl;
            cout << "Exact derivative: " << exact_derivative << endl;
            cout << endl;
        }
        cout << "dx = " << dx << endl;
        cout << "Max error for first-order forward difference: " << error_first << endl;
        cout << "Max error for second-order forward difference: " << error_second << endl;
        cout << "Max error for fourth-order forward difference: " << error_fourth << endl;
    }

    return 0;
}

