#include<bits/stdc++.h>
using namespace std;

void inverse(vector<vector<double>> &a) { // O(n^3)
    int n = a.size();   
    
    // Augment the matrix with an identity matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i].push_back(i == j ? 1.0 : 0.0);
        }
    }
    
    // Perform Gauss-Jordan elimination with partial pivoting
    for (int i = 0; i < n; i++) {
        // Find pivot
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(a[j][i]) > abs(a[pivot][i])) {
                pivot = j;
            }
        }
        
        // Swap rows if necessary
        if (pivot != i) {
            swap(a[i], a[pivot]);
        }
        
        // Check for singular matrix
        if (abs(a[i][i]) < 1e-10) {
            cerr << "Error: Matrix is singular or nearly singular." << endl;
            return;
        }
        
        // Make diagonal element 1
        double div = a[i][i];
        for (int j = i; j < 2 * n; j++) {
            a[i][j] /= div;
        }
        
        // Eliminate other rows
        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = a[j][i];
                for (int k = i; k < 2 * n; k++) {
                    a[j][k] -= factor * a[i][k];
                }
            }
        }
    }
    
    // Extract the inverse matrix
    for (int i = 0; i < n; i++) {
        a[i].erase(a[i].begin(), a[i].begin() + n);
    }
}

vector<double> matrix_multiply(vector<vector<double>> &a, vector<double> &b) {
    int n = a.size();
    int m = b.size();
    vector<double> res(m, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[i] += a[i][j] * b[j];
        }
    }
    
    return res;
}

void vector_subtract(vector<double> &a, vector<double> &b){
    int n = a.size();
    
    for(int i = 0; i < n; i++){
        a[i] -= b[i];
    }
}

void calculate_jacobian(vector<vector<double>> &jacobian, double x, double y, double z){
	jacobian[0][0] = 1.0;
	jacobian[0][1] = 1.0;
	jacobian[0][2] = 1.0;
	jacobian[1][0] = 2.0 * x;
	jacobian[1][1] = 2.0 * y;
	jacobian[1][2] = 2.0 * z;
	jacobian[2][0] = exp(x) + y - z;  
	jacobian[2][1] = x;
	jacobian[2][2] = -1.0 * x;
}

void calculate_f(vector<double> &f, vector<double> &x){
	f[0] = x[0] + x[1] + x[2] - 3.0;
	f[1] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5.0;
	f[2] = exp(x[0]) + x[0] * x[1] - x[0] * x[2] - 1.0; 
}

int main(){
    vector<double> x(3);
    vector<vector<double>> jacobian(3, vector<double>(3, 0.0));
    vector<double> f(3);
    x[0] = 0.1;
    x[1] = 1.2;
    x[2] = 2.5;
    // x[0] = 1.0;
    // x[1] = 0.0;
    // x[2] = 1.0;
    vector<double> prev(3);
    prev = x;
    
    while(1){
    	calculate_jacobian(jacobian, x[0], x[1], x[2]);
    	calculate_f(f, x);
    	inverse(jacobian);
    	vector<double> temp = matrix_multiply(jacobian, f);
    	vector_subtract(x, temp);
        double error = 0.0;
        for(int i = 0; i < 3; i++){
            error += (x[i] - prev[i]) * (x[i] - prev[i]);
        }
        error = sqrt(error);
        if(error < 1e-10){
            break;
        }
        prev = x;
    	cout << x[0] << " " << x[1] << " " << x[2] << endl;
    }
    
    return 0;
}
