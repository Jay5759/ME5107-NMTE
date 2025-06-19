#include<bits/stdc++.h>
#include <chrono>
using namespace std;
#define double long double

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

void matrix_subtract(vector<vector<double>> &a, vector<vector<double>> &b){
    int n = a.size();
    int m = a[0].size();
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a[i][j] -= b[i][j];
        }
    }
}

vector<double> vector_subtract(vector<double> &a, vector<double> &b){
    int n = a.size();
    vector<double> res(n, 0);
    
    for(int i = 0; i < n; i++){
        res[i] = a[i] - b[i];
    }

    return res;
}

int main(){
    int n = 30, n_blk = 5;

    auto start = std::chrono::high_resolution_clock::now();
    
    vector<vector<vector<double>>> D(n, vector<vector<double>>(n_blk, vector<double>(n_blk, 0.0)));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n_blk; j++){
            if (j > 0) D[i][j][j - 1] = 1.0;
            D[i][j][j] = -4.0;
            if (j < n_blk - 1) D[i][j][j + 1] = 1.0;
        }
    }

    vector<vector<double>> f(n, vector<double>(n_blk, 1.0 / n_blk));

    for(int i = 0; i < n; i++){
        f[i][0] = 1.0;
        f[i][n_blk - 1] = 2.0;
    }

    for(int m = 0; m < n - 1; m++){
        // D_i^-1 * A_i
        inverse(D[m]); 
        // D_i^-1 * f_i
        f[m] = matrix_multiply(D[m], f[m]);
        // D_i+1 = D_i - D_i * B_i
        matrix_subtract(D[m + 1], D[m]);
        // f_i+1 = f_i+1 - D_i * f_i
        f[m + 1] = vector_subtract(f[m + 1], f[m]);
    }

    vector<vector<double>> x(n, vector<double>(n_blk, 0));

    inverse(D[n - 1]);
    x[n - 1] = matrix_multiply(D[n - 1], f[n - 1]);

    for(int m = n - 2; m >= 0; m--){
        // x_i = f_i - D_i * x_i+1
        vector<double> temp = matrix_multiply(D[m], x[m + 1]);
        x[m] = vector_subtract(f[m], temp);
    }

    for(int j = 0; j < n_blk; j++){
        cout << x[n/2][j] << endl;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double seconds = elapsed.count();
    
    std::cout << "Time elapsed: " << seconds << " seconds" << std::endl;

    return 0;
}