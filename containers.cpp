#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>     // queue, priority_queue
#include <stack>

using namespace std;

int main() {

    // =========================================================================
    // 1. VECTORS
    // =========================================================================

	// Initialization
	vector<int> v1;
	vector<int> v1(5);
	vector<int> v1(5, 10);              // {10, 10, 10, 10, 10}
	vector<int> v2 = {5, 2, 8, 1, 9};
	vector<int> v3(v2.begin(), v2.begin() + 3); // Copy range {5, 2, 8}
	
	vector<vector<int> matrix;

	// Common Modifiers & Access
	v2.push_back(7);
	v2.emplace_back(7);     	// Construct in-place
	v2.pop_back();
    v.erase(v.begin()+2); 		// Removes element at index 2
    v.erase(v.begin(),v.begin()+2);	// Removed elements from 0-2
	
	// Access
	int x = v2[0];          // No bounds check
	int y = v2.at(0);       // Bounds check
	int first = v2.front(); // Ref to first
	int last = v2.back();   // Ref to last
	bool isEmpty = v2.empty();

	// Key Algorithms for Vectors
	
	// SORTING: O(N log N)
	sort(v2.begin(), v2.end());                 // Ascending: {1, 2, 5, 8, 9}
	sort(v2.rbegin(), v2.rend());               // Descending: {9, 8, 5, 2, 1}
	
	// REVERSE:
	reverse(v2.begin(), v2.end());

	// --- D. Searching & Bounds (Binary Search) ---
	// Requirement: Vector must be sorted!
	vector<int> search_v = {1, 3, 5, 7, 9};
	
	// binary_search: Returns bool (exists or not)
	bool exists = binary_search(search_v.begin(), search_v.end(), 5); // true

	// lower_bound: First element >= val
	auto lb = lower_bound(search_v.begin(), search_v.end(), 4); 
	int lb_idx = lb - search_v.begin(); // Returns index of '5' (value 2)

	// upper_bound: First element <= val
	auto ub = upper_bound(search_v.begin(), search_v.end(), 5);
	// Points to '7'
	
	// =========================================================================
    // 2. MAPS (std::map & std::unordered_map)
    // =========================================================================

    // --- A. Initialization ---
    map<string, int> m;                     // Ordered. Key must have < operator defined.
    map<int, int> m2 = {{1, 2}, {3, 4}};    // Initializer list
    
    // --- B. Modifiers & Access ---
    m["apple"] = 5;         // O(log N) - Inserts (val 0) if missing, then assigns.
    int x = m["apple"];     // O(log N) - Returns val. CAUTION: Creates key if missing!
    
    // Check existence without creating
    if (m.count("apple")) { /* Key exists (returns 1 or 0) */ }

    m.insert({"banana", 3});    // Insert pair. Does NOTHING if key already exists.
    m.erase("apple");           // Removes by key.

    // --- C. Iteration ---    
    // Old school iterator access
    for (auto it = m.begin(); it != m.end(); ++it) {
        // it->first is key, it->second is value
    }

    // --- D. Searching ---
    auto it2 = m.find("banana"); // Returns iterator to pair or m.end()
    if (it2 != m.end()) {
        // Found: it2->first = "banana", it2->second = 3
    }

    // --- E. Ordered Map Specifics (Binary Search) ---    
    map<int, string> ord_m = {{10, "A"}, {20, "B"}, {30, "C"}};
    
    auto lb = ord_m.lower_bound(15); // First key >= 15. Points to {20, "B"}
    auto ub = ord_m.upper_bound(20); // First key > 20. Points to {30, "C"}
    
    if (lb != ord_m.end()) cout << lb->second << endl; // Prints "B"
	
    // =========================================================================
	// 3. SETS (std::set & std::multiset)
	// =========================================================================
	// set: Ordered, Unique elements, O(log N). Header: <set>
	// multiset: Ordered, Duplicates allowed.

	// --- A. Initialization ---
	set<int> s = {3, 1, 4, 1, 5};   // Becomes {1, 3, 4, 5} (Sorted, Unique)
	multiset<int> ms = {1, 1, 2};   // Becomes {1, 1, 2}

	// --- B. Modifiers ---
	s.insert(2);                    // O(log N) - Ignores if already present
	s.erase(3);                     // O(log N) - Removes value 3
	
	// Contains
	bool isTwo = s.find(2) != s.end();
	
	// Removing in Multiset
	ms.erase(1);                    // Removes ALL instances of 1 -> {2}
	ms.erase(ms.find(1));           // Removes ONE instance of 1 -> {1, 2}

	// --- C. Iteration ---
	// Iterates in strictly increasing order
	for (auto it = s.begin(); it != s.end(); ++it) {
		// *it is the value (read-only)
	}

	// --- D. Ordered Set Specifics (Binary Search) ---
	auto it_lb = s.lower_bound(4);  // First element >= 4 O(logn)
	auto it_ub = s.upper_bound(4);  // First element > 4 O(n)
	
	// returns begin() or end() if not found.

	if (it_lb != s.end()) cout << *it_lb << endl;


	// =========================================================================
	// 4. QUEUES & PRIORITY QUEUES
	// =========================================================================

	// --- A. Queue ---
	queue<int> q;
	q.push(1);                      // Add to back
	q.pop();                        // Remove from front (void return)
	int f = q.front();              // Access front
	if (!q.empty()) {}				// Check if empty

	// --- B. Priority Queue ---
	priority_queue<int> pq;         // Default: Max Heap
	pq.push(10); pq.push(5);        // O(log N)
	int top = pq.top();             // O(1) - Returns 10 (Highest value)
	pq.pop();                       // O(log N) - Removes 10
	
	// --- B. Priority Queue With Tuples ---
	priority_queue<Tuple<int, int>> pq;         // Default: Max Heap
	pq.push(make_tuple(5, 10)); pq.push(make_tuple(6, 10));        // O(log N)
	int top = get<0>(pq.top());             // O(1) - Returns 6 (Highest value)
	pq.pop();                       // O(log N) - Removes (6, 10)
	
	// =========================================================================
	// 5. TUPLES
	// =========================================================================
	// tuple: N elements. Header: <tuple>

	// --- A. Tuple ---
	tuple<int, double, string> t = {1, 3.14, "Pi"};
	auto t2 = make_tuple(2, 1.41, "Root");

	// Access
	int i = get<0>(t);              // Returns 1


	// =========================================================================
	// 6. STRINGS
	// =========================================================================
	// Mutable sequence of chars. Header: <string>
	
	// --- A. Initialization & Input ---
	string s = "hello";
	string s2(5, 'a');              // "aaaaa"
	
	// Reading lines (cin stops at whitespace)
	// getline(cin, s);             // Reads entire line until \n

	// --- B. Modifiers ---
	s += " world";                  // O(N) - Concatenation
	s.push_back('!');               // O(1)
	s.pop_back();                   // O(1)
	
	// Substring: s.substr(start_index, length)
	string sub = s.substr(0, 4);    // "hell" - O(N)

	// reverse
	reverse(s.begin(), s.end());

	// --- D. Conversions ---
	int num = 123;
	string str_num = to_string(num);    // "123"
	int val = stoi("123");              // 123 (also stoll for long long)


	// =========================================================================
    // 7. STACKS (std::stack)
    // =========================================================================
    // LIFO (Last In First Out). Header: <stack>

    // --- A. Basic Operations ---
    stack<int> s;
    s.push(1);                      // O(1)
    s.push(2);
    
    // Access (CRITICAL: Check empty first! Segfaults if empty)
    if (!s.empty()) {
        int t = s.top();            // O(1) - Returns 2 (Does not remove)
        s.pop();                    // O(1) - Removes 2 (Void return)
    }


    return 0;
}
