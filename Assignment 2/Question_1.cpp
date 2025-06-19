#include<bits/stdc++.h>
using namespace std;

int main(){
    int n = 64;
    vector<double> u(n + 1);
    u[0] = u[1] = 2.96875;

    for(int i = 2; i <= n; i++){
        u[i] = 3.0 * u[i - 1] - 2.0 * u[i - 2];
    }

    for(int i = 0; i <= n; i++){
        cout << "u[" << i << "] = " << u[i] << endl;
    }

    return 0;
}