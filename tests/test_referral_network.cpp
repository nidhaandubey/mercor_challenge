#include "../source/ReferralNetwork.cpp"
#include <iostream>
using namespace std;

void printVector(const vector<string>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void printTopList(const vector<pair<string, int> >& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i].first << " (" << v[i].second << ") ";
    }
    cout << endl;
}

int main() {
    ReferralNetwork rn;

    cout << "\n=== Test 1: Add Users ===\n";
    rn.addUser("A");
    rn.addUser("B");
    rn.addUser("C");
    rn.addUser("D");
    rn.addUser("E");
    rn.addUser("F");
    cout << "Users added: A B C D E F" << endl;

    cout << "\n=== Test 2: Add Valid Referrals ===\n";
    cout << rn.addReferral("A", "B") << " ";
    cout << rn.addReferral("A", "C") << " ";
    cout << rn.addReferral("B", "D") << " ";
    cout << rn.addReferral("C", "E") << " ";
    cout << rn.addReferral("D", "F") << endl; // All should be 1 (true)

    cout << "\n=== Test 3: Add Invalid Referrals ===\n";
    cout << rn.addReferral("A", "A") << " "; // false: self-referral
    cout << rn.addReferral("C", "D") << " "; // false: D already referred
    cout << rn.addReferral("F", "A") << endl; // false: creates cycle

    cout << "\n=== Test 4: Direct Referrals of A ===\n";
    vector<string> direct = rn.getDirectReferrals("A");
    printVector(direct);
    cout << "\n=== Test 5: Total Referral Count ===\n";
    cout << "A: " << rn.getTotalReferralCount("A") << endl;
    cout << "B: " << rn.getTotalReferralCount("B") << endl;
    cout << "C: " << rn.getTotalReferralCount("C") << endl;
    cout << "D: " << rn.getTotalReferralCount("D") << endl;

    cout << "\n=== Test 6: Top 3 Referrers by Reach ===\n";
    vector<pair<string, int> > topReferrers = rn.getTopKReferrers(3);
    printTopList(topReferrers);

    return 0;
}
