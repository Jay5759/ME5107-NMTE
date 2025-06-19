#include <bits/stdc++.h>
using namespace std;

void forward_elimination(vector<vector<double>> &a){
	int n = a.size() - 1; 
	for(int k = 1; k < n; k++){
		for(int i = k + 1; i <= n; i++){
			for(int j = k + 1; j <= n + 1; j++){
				a[i][j] -= ((a[i][k] / a[k][k]) * a[k][j]);
			}
		}
	}
}

void backward_substituion(vector<double> &x, vector<vector<double>> &a){
	int n = a.size() - 1;
	x[n] = a[n][n + 1] / a[n][n];
	for(int i = n - 1; i >= 1; i--){
		double sum = a[i][n + 1];
		for(int j = i + 1; j <= n; j++){
			sum -= a[i][j] * x[j];
		} 
		x[i] = sum / a[i][i];
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	
	int n = 32;
	vector<vector<double>> augmented(n + 1, vector<double>(n + 2, 1));
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			augmented[i][j] = max(i, j);
		}
	}
	
	forward_elimination(augmented);
	
	vector<double> x(n + 1);
	backward_substituion(x, augmented);
	
	double sum = 0.0;
	cout << "Solution vector is " << endl;
	for(int i = 1; i <= n; i++){
		cout << x[i] << " ";
		sum += x[i] * x[i];
	}
	sum = 1.0 / sum;
	cout << endl << "1/(summation of x_i^2) = " << sum << endl;
	
	return 0;
}
