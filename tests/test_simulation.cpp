#include "../source/Simulation.cpp"
#include <iostream>
#include <cmath>

using namespace std;

double test_adoption_prob(int bonus) {
    // Simple monotonically increasing function
    return 1.0 - exp(-bonus / 100.0);
}

void printVector(const vector<double>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << "Day " << i + 1 << ": " << v[i] << endl;
    }
}

int main() {
    cout << "\n=== Test 1: Simulate 10 Days with p = 0.1 ===\n";
    vector<double> growth = Simulation::simulate(0.1, 10);
    printVector(growth);
    return 0;
}