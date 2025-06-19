#include<bits/stdc++.h>
using namespace std;
#define double long double
double x_true = 2898.0;
vector<double> error;

double f(double x){
	return x - 5.0 + 5.0 * exp(-1.0 * x);
}

double fx(double x){
	return 1.0 - 5.0 * exp(-1.0 * x);
}

double bisectionMethod(double a, double b) {
    for (int i = 0; i < 10; ++i) {
        double c = (a + b) / 2.0;
        if (f(c) == 0.0) {
            break;
        } else if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
        double temp = (a + b) / 2.0;
        error.push_back(pow(14390.0 / temp - x_true, 2));
    }

    return (a + b) / 2.0;
}

int main(){
    double x = bisectionMethod(0.0, 6.0);

    double prev = x;
    
    while(1){
    	cout << x << " " << f(x) << " " << fx(x) << " ";
    	x = x - f(x) / fx(x);
        cout << x << endl;
        double e = (x - prev) * (x - prev);
        e = sqrt(e);
        if(e < 1e-10){
            break;
        }
        prev = x;
        error.push_back(pow(14390.0 / x - x_true, 2));
    }
    
    cout << "lamda * T is " << 14390 / x << endl;

    for(auto e : error){
        cout << e << endl;
    }
    
    return 0;
}
