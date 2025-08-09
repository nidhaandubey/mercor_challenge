# Mercor Challenge: Referral Network

**Project Structure**
mercor-challenge/
├── README.md
├── source/
│   ├── ReferralNetwork.cpp
│   └── Simulation.cpp
└── tests/
    ├── test_referral_network.cpp
    └── test_simulation.cpp



---

## Part 1: Referral Graph

**Data Structure:**
- `unordered_map<string, vector<string>> graph` — adjacency list for storing referrals.
- `unordered_map<string, string> parent` — quick lookup of a candidate’s referrer.

**Reasoning:**
- `unordered_map` ensures average **O(1)** lookups for referrals and parent relationships.
- `vector` for adjacency list since we expect relatively small direct referral counts per user.

**Constraints Enforced:**
- **No Self-Referrals:** Check if `referrer == candidate`.
- **Unique Referrer:** Reject if `parent` already contains the candidate.
- **Acyclic Graph:** BFS check to ensure no path exists from candidate back to referrer.

---

## Part 2: Full Network Reach

**Total Referral Count:**
- BFS traversal starting from the given user, counting unique reachable nodes.

**Top K Referrers:**
- For each user, compute total reach and sort by descending reach.

---

## Part 3: Identify Influencers

**Unique Reach Expansion:**
- Precompute reach sets for each user.
- Use a greedy set cover algorithm to select influencers who expand unique coverage the most.

**Flow Centrality:**
- BFS from every node to compute shortest paths.
- For every `(source, target, v)` triple, check if  
  `dist(s, v) + dist(v, t) == dist(s, t)`.

---

## Part 4: Network Growth Simulation

**Initial State:** 100 referrers, each with a capacity of 10.  
**Model:** Each day, active users attempt referrals with probability `p`.  
Successful referrals reduce capacity.

**Functions:**
- `simulate(p, days)` — returns daily cumulative referrals.
- `days_to_target(p, target)` — returns minimum days to reach target.

---

## Part 5: Referral Bonus Optimization

**Idea:**
- Binary search bonus values in increments of $10.
- Use `adoption_prob(bonus)` to get `p`.
- Run simulation to see if target is reached within given days.

**Return:** Minimum bonus meeting target, or `null` if unreachable.

---

## Time Complexity Analysis

- **Total Referral Count:** O(V + E) per query  
- **Top K Referrers:** O(V × (V + E) + V log V)  
- **Unique Reach Expansion:** O(V²) worst case (due to repeated set operations)  
- **Flow Centrality:** O(V² × (V + E)) BFS runs  
- **Simulation:** O(days × active_users)  
- **Bonus Optimization:** O(log(max_bonus) × simulation_cost)  

---

## AI Usage Disclosure

I used **ChatGPT** as an assistant for:
- Brainstorming algorithmic approaches
- Generating Testcases
- Reviewing and optimizing code readability


---

## Author
**Nidhaan Dubey**  
B.Tech CSE, IIIT Sonepat (Graduating 2026)
