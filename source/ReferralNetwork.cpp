#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class ReferralNetwork {
private:
    unordered_map<string, vector<string> > graph;  // Adjacency list
    unordered_map<string, string> parent;          // Child -> Parent

public:
    // Part 1: Add a new user to the network
    void addUser(const string& user) {
        graph[user]; // Ensure the user exists in the graph
    }

    // Part 1: Add a referral link if valid (no self-loop, no multiple parents, no cycle)
    bool addReferral(const string& referrer, const string& candidate) {
        if (referrer == candidate) return false;               // No self-referrals
        if (parent.count(candidate)) return false;             // Unique parent only
        if (createsCycle(referrer, candidate)) return false;   // Acyclic constraint

        graph[referrer].push_back(candidate);
        parent[candidate] = referrer;
        return true;
    }

    // Part 1: Get direct referrals
    vector<string> getDirectReferrals(const string& user) {
        return graph[user];
    }
    private:
        bool createsCycle(const string& referrer, const string& candidate) {
            queue<string> q;
            unordered_set<string> visited;
            q.push(candidate);

            while (!q.empty()) {
                string current = q.front(); q.pop();
                if (current == referrer) return true;

                vector<string>& children = graph[current];
                for (size_t i = 0; i < children.size(); ++i) {
                    string& next = children[i];
                    if (!visited.count(next)) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
            return false;
        }

        unordered_map<string, int> bfsDistances(const string& source) {
            unordered_map<string, int> dist;
            queue<string> q;
            q.push(source);
            dist[source] = 0;

            while (!q.empty()) {
                string current = q.front(); q.pop();
                vector<string>& children = graph[current];
                for (size_t i = 0; i < children.size(); ++i) {
                    string& next = children[i];
                    if (!dist.count(next)) {
                        dist[next] = dist[current] + 1;
                        q.push(next);
                    }
                }
            }
            return dist;
        }

        unordered_set<string> getReachSet(const string& user) {
            unordered_set<string> visited;
            queue<string> q;
            q.push(user);

            while (!q.empty()) {
                string current = q.front(); q.pop();
                vector<string>& children = graph[current];
                for (size_t i = 0; i < children.size(); ++i) {
                    string& next = children[i];
                    if (!visited.count(next)) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
            return visited;
        }
};