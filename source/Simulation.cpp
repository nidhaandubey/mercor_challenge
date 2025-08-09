#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

class Simulation {
private:
    static const int INITIAL_REFERRERS = 100;
    static const int REFERRAL_CAPACITY = 10;

public:
    // Part 4: simulate referral growth over a number of days
    static vector<double> simulate(double p, int days) {
        vector<double> result;
        double totalReferrals = 0.0;
        double activeUsers = INITIAL_REFERRERS;
        double exhaustedUsers = 0.0;

        for (int day = 0; day < days; ++day) {
            double newReferrals = activeUsers * p;

            if (newReferrals == 0) {
                result.push_back(totalReferrals);
                continue;
            }

            totalReferrals += newReferrals;
            double referralsPerUser = newReferrals / activeUsers;

            exhaustedUsers += activeUsers * (referralsPerUser / REFERRAL_CAPACITY);
            activeUsers += newReferrals - (activeUsers * (referralsPerUser / REFERRAL_CAPACITY));
            result.push_back(totalReferrals);
        }
        return result;
    }

    // Part 4: find minimum number of days to reach a referral target
    static int days_to_target(double p, int target_total) {
        int low = 1, high = 10000; // set reasonable upper bound
        while (low < high) {
            int mid = (low + high) / 2;
            vector<double> sim = simulate(p, mid);
            if (sim.back() >= target_total) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        vector<double> finalSim = simulate(p, low);
        if (finalSim.back() >= target_total) return low;
        return -1; // target unreachable
    }

    // Part 5: compute minimum bonus to reach hiring target using binary search
    static int min_bonus_for_target(int days, int target_hires, function<double(int)> adoption_prob, double eps) {
        int low = 0;
        int high = 1000000; // $10 to $10,000,000

        while (low < high) {
            int mid = ((low + high) / 10) * 10; // round to nearest 10
            double p = adoption_prob(mid);
            vector<double> sim = simulate(p, days);

            if (sim.back() >= target_hires) {
                high = mid;
            } else {
                low = mid + 10;
            }
        }

        if (low > 1000000) return -1; // unreachable
        double finalProb = adoption_prob(low);
        vector<double> finalSim = simulate(finalProb, days);
        if (finalSim.back() >= target_hires - eps) return low;
        return -1;
    }
};
