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

    cout << "\n=== Test 2: Days to reach 500 referrals with p = 0.1 ===\n";
    int days = Simulation::days_to_target(0.1, 500);
    cout << "Minimum days to reach 500 referrals: " << days << endl;

    cout << "\n=== Test 3: Min Bonus for 1000 hires in 30 days ===\n";
    int min_bonus = Simulation::min_bonus_for_target(
        30,
        1000,
        test_adoption_prob,
        1e-3
    );
    if (min_bonus == -1)
        cout << "Target not achievable with any bonus." << endl;
    else
        cout << "Minimum bonus required: $" << min_bonus << endl;

    return 0;
}
