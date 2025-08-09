#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include <cmath>
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
    // Part 2: Total referral count (BFS traversal)
    int getTotalReferralCount(const string& user) {
        unordered_set<string> visited;
        queue<string> q;
        q.push(user);
        visited.insert(user);

        int count = 0;
        while (!q.empty()) {
            string current = q.front(); q.pop();
            vector<string>& children = graph[current];
            for (size_t i = 0; i < children.size(); ++i) {
                string& child = children[i];
                if (!visited.count(child)) {
                    visited.insert(child);
                    count++;
                    q.push(child);
                }
            }
        }
        return count;
    }

    // Part 2: Get top K referrers by total reach
    vector<pair<string, int> > getTopKReferrers(int k) {
        vector<pair<string, int> > result;
        for (unordered_map<string, vector<string> >::iterator it = graph.begin(); it != graph.end(); ++it) {
            string user = it->first;
            int reach = getTotalReferralCount(user);
            result.push_back(make_pair(user, reach));
        }

        sort(result.begin(), result.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

        if (k > result.size()) k = result.size();
        return vector<pair<string, int> >(result.begin(), result.begin() + k);
    }
        // Part 3: Unique Reach Expansion
    vector<string> getTopInfluencersByUniqueReach(int count) {
        unordered_map<string, unordered_set<string> > reachSets;
        for (unordered_map<string, vector<string> >::iterator it = graph.begin(); it != graph.end(); ++it) {
            string user = it->first;
            reachSets[user] = getReachSet(user);
        }

        unordered_set<string> globalCovered;
        set<string> selected;

        while (selected.size() < (size_t)count) {
            string bestUser;
            int maxNew = -1;

            for (unordered_map<string, unordered_set<string> >::iterator it = reachSets.begin(); it != reachSets.end(); ++it) {
                string user = it->first;
                if (selected.count(user)) continue;

                int newCount = 0;
                for (unordered_set<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                    if (!globalCovered.count(*it2)) newCount++;
                }

                if (newCount > maxNew) {
                    maxNew = newCount;
                    bestUser = user;
                }
            }

            if (maxNew <= 0) break;

            selected.insert(bestUser);
            for (unordered_set<string>::iterator it = reachSets[bestUser].begin(); it != reachSets[bestUser].end(); ++it) {
                globalCovered.insert(*it);
            }
        }

        return vector<string>(selected.begin(), selected.end());
    }

    // Part 3: Flow Centrality
    vector<pair<string, int> > getTopFlowCentralUsers(int k) {
        unordered_map<string, int> centrality;

        for (unordered_map<string, vector<string> >::iterator it1 = graph.begin(); it1 != graph.end(); ++it1) {
            string source = it1->first;
            unordered_map<string, int> distFromSource = bfsDistances(source);

            for (unordered_map<string, vector<string> >::iterator it2 = graph.begin(); it2 != graph.end(); ++it2) {
                string target = it2->first;
                if (source == target) continue;
                unordered_map<string, int> distFromTarget = bfsDistances(target);
                if (!distFromSource.count(target)) continue;

                int shortest = distFromSource[target];

                for (unordered_map<string, vector<string> >::iterator it3 = graph.begin(); it3 != graph.end(); ++it3) {
                    string v = it3->first;
                    if (v == source || v == target) continue;
                    if (!distFromSource.count(v) || !distFromTarget.count(v)) continue;

                    if (distFromSource[v] + distFromTarget[v] == shortest) {
                        centrality[v]++;
                    }
                }
            }
        }

        vector<pair<string, int> > result;
        for (unordered_map<string, int>::iterator it = centrality.begin(); it != centrality.end(); ++it) {
            result.push_back(make_pair(it->first, it->second));
        }

        sort(result.begin(), result.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

        if (k > result.size()) k = result.size();
        return vector<pair<string, int> >(result.begin(), result.begin() + k);
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