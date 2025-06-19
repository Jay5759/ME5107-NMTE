#include<bits/stdc++.h>
using namespace std;
const double PI = 3.14159265358979323846;

double exact(double t){
    return cos(4.0 * t);
}

int main(){
    double h = 0.1, size = 9.0 / h;
    vector<double> v(size + 1, 0.0), y_exact(size + 1, 0.0), y(size + 1, 0.0), t(size + 1, 0.0);
    v[0] = 0.0;
    y[0] = 1.0; // Initial condition
    y_exact[0] = exact(0.0); // Exact solution at t=0

    for(int i = 1; i <= size; i++){
        t[i] = t[i - 1] + h;
        y_exact[i] = exact(t[i]);
    }

    for(int i = 1; i <= size; i++){
        if(i == 1){
            v[i] = v[i - 1] - h * 16.0 * y[i - 1];
            y[i] = y[i - 1] + h * v[i - 1];
        }
        else{
            v[i] = v[i - 2] - 2.0 * h * 16.0 * y[i - 1];
            y[i] = y[i - 2] + 2.0 * h * v[i - 1];
        }
    }

    for(int i = 0; i <= size; i++){
        // cout << "t: " << t[i] << ", y: " << y[i] << ", exact: " << y_exact[i] << endl;
        // cout << t[i] << endl;
    }

    vector<double> error;

    for(int i = 0; i < size + 1; i++){
        // cout << x << " " << y[x] << " " << y_exact[x] << endl;
        error.push_back(abs(y[i] - y_exact[i]));
    }

    cout << "Error: " << endl;
    for(int i = 0; i < error.size(); i++){
        cout << error[i] << endl;
    }

    vector<double> peaks(6);

    // Find positive peaks (maxima)
    for (int n = 0; n <= 5; ++n) {
        double peak_time = n * M_PI / 2.0; // Peaks occur at t = nπ/2 for ω=4
        
        if (peak_time > 9.0) break;
        
        // Find the closest time point in our simulation
        int closest_idx = static_cast<int>(round(peak_time / h));
        
        if (closest_idx < size + 1 && n % 2 == 0) { // Even n gives positive peaks
            double error = abs(y[closest_idx] - y_exact[closest_idx]);
            peaks[n] = error;
            // cout << fixed << setprecision(4);
            // cout << t[closest_idx] << "\t\t" << y[closest_idx] << "\t\t" 
            //          << y_exact[closest_idx] << "\t\t" << error << "\n";
        }
    }
    
    // Find negative peaks (minima)
    for (int n = 1; n <= 5; n += 2) { // Odd n gives negative peaks
        double peak_time = n * M_PI / 2.0;
        
        if (peak_time > 9.0) break;
        
        // Find the closest time point in our simulation
        int closest_idx = static_cast<int>(round(peak_time / h));
        
        if (closest_idx < size + 1) {
            double error = abs(y[closest_idx] - y_exact[closest_idx]);
            peaks[n] = error;
            // cout << fixed << setprecision(4);
            // cout << t[closest_idx] << "\t\t" << y[closest_idx] << "\t\t" 
            //          << y_exact[closest_idx] << "\t\t" << error << "\n";
        }
    }

    cout << fixed << setprecision(8);
    cout << "Peaks: " << endl;
    for (int i = 0; i < peaks.size(); i++) {
        cout << peaks[i] << endl;
    }

    return 0;
}