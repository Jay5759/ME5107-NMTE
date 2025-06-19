#include<bits/stdc++.h>
using namespace std;
#define double long double

double f(double x){
	return x - 5.0 + 5.0 * exp(-1.0 * x);
}

double fx(double x){
	return 1.0 - 5.0 * exp(-1.0 * x);
}

int main(){
    double x = 1.8;
    double prev = x;
    
    while(1){
    	cout << x << " " << f(x) << " " << fx(x) << " ";
    	x = x - f(x) / fx(x);
        cout << x << endl;
        double error = (x - prev) * (x - prev);
        error = sqrt(error);
        if(error < 1e-10){
            break;
        }
        prev = x;
    }
    
    cout << "lamda * T is " << 14390 / x << endl;
    
    return 0;
}
