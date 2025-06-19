#include<bits/stdc++.h>
using namespace std;

double f(double t, double y){
	return -10.0 * (y - exp(-t)) - exp(-t);
}

double exact(double t){
	return exp(-t) + (10.0 - 1.0) * exp(-10.0 * t);
}

double NR(double t0, double y0, double h){
	double y_prev = y0, y = y0;
	
	while(1){
		y = y - (y + 10.0 * h * y - y0 - 9.0 * h * exp(t0 + h)) / (1.0 + 10.0 * h);
		double error = (y - y_prev) * (y - y_prev);
		if(error < 1e-9) break;
		y_prev = y;
	}
	
	return y;
}

double slope(double x, double y, double h, int scheme){
	if(scheme == 1){ // Explicit Euler Method
		return f(x, y);
	}
	else if(scheme == 2){ // Implicit Euler Method
		double y_next = NR(x, y, h);
		return f(x + h, y_next);
	}
	else if(scheme == 3){ // Trapezoidal Method
		double y_next = NR(x, y, h);
		return (f(x, y) + f(x + h, y_next)) / 2.0;
	}
	else if(scheme == 4){ // 2nd Order Runge-Kutta Method
		double k1 = f(x, y);
		double k2 = f(x + h / 2.0, y + (h * k1) / 2.0);
		return k2; 
	}
	else if(scheme == 5){ // 4th Order Runge-Kutta Method
		double k1 = f(x, y);
		double k2 = f(x + h / 2.0, y + (h * k1) / 2.0);
		double k3 = f(x + h / 2.0, y + (h * k2) / 2.0);
		double k4 = f(x + h, y + h * k3);
		return (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;  
	}
	else if(scheme == 6){ // Runge-Kutta-Fehlberg Method
		double k1 = h * f(x, y);
		double k2 = h * f(x + h / 4.0, y + k1 / 4.0);
		double k3 = h * f(x + (3.0 * h) / 8.0, y + (3.0 * k1 + 9.0 * k2) / 32.0);
		double k4 = h * f(x + (12.0 * h) / 13.0, y + (1932.0 * k1 - 7200.0 * k2 + 7296.0 * k3) / 2197.0);
		double k5 = h * f(x + h, y + (439.0 * k1) / 216.0 - 8.0 * k2 + (3680 * k3) / 513.0 - (845.0 * k4) / 4104.0);
		double k6 = h *f(x + h / 2.0, y - (8.0 * k1) / 27.0 + 2.0 * k2 - (3544.0 * k3) / 2565.0 + (1859.0 * k4) / 4104.0 - (11.0 * k5) / 40.0);
		return ((16.0 * k1) / 135.0 + (6656.0 * k3) / 12825.0 + (28561.0 * k4) / 56430.0 - (9.0 * k5) / 50.0 + (2.0 * k6) / 55.0) / h; 
	}
	return 0;
}

int main() {
    vector<double> h_values = {0.1, 0.05, 0.025, 0.0125, 0.00625};
	vector<string> scheme_names = {
		"Explicit Euler Method",
		"Implicit Euler Method",
		"Trapezoidal Method",
		"2nd Order Runge-Kutta Method",
		"4th Order Runge-Kutta Method",
		"Runge-Kutta-Fehlberg Method"
	};
    
    cout << fixed << setprecision(10);
    
    for(int scheme = 1; scheme <= 6; scheme++){
		vector<double> error;
		for(auto h: h_values){
			int size = 0.8 / h;
			vector<double> y(size + 1, 0.0), t(size + 1, 0.0), y_exact(size + 1, 0.0);
			y[0] = 10.0;
			y_exact[0] = exact(0.0);
			for(int i = 1; i <= size; i++){
				t[i] = t[i - 1] + h;
			}
			for(int i = 1; i <= size; i++){
				y[i] = y[i - 1] + h * slope(t[i - 1], y[i - 1], h, scheme);
				y_exact[i] = exact(t[i]);
			}
			error.push_back(abs(y[size] - y_exact[size]));
			// for(int i = 0; i <= size; i++){
			// 	cout << "t = " << t[i] << " " << y[i] << " " << y_exact[i] << endl;
			// }
		}
		
		cout << scheme_names[scheme - 1] << endl;
		for(int i = 0; i < 4; i++){
			cout << "Order = "<< log2(error[i] / error[i + 1]) << endl;
		}
		cout << endl;
	}

    return 0;
}

