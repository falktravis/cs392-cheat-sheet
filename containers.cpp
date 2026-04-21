#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <tuple>
#include <utility>
#include <string>
#include <algorithm>
#include <numeric>
#include <cctype>

using namespace std;
using ll = ll;

ll main() {

	// =========================================================================
	// 1. VECTORS
	// =========================================================================
	// Dynamic array. Random access O(1). push/pop_back O(1).
	// insert/erase in the middle O(N).

	// Initialization
	vector<ll> v;                               // empty
	vector<ll> v(n);                            // n zeros
	vector<ll> v(n, 10);                        // n copies of 10 -> {10,10,...}
	vector<ll> v = {5, 2, 8, 1, 9};
	vector<ll> v2(v.begin(), v.begin() + 3);    // copy range -> {5, 2, 8}

	// 2D vector (n rows x m cols, filled with 0)
	vector<vector<ll>> matrix(n, vector<ll>(m, 0));

	// Modifiers
	v.push_back(7);                              // O(1) amort.
	v.emplace_back(7);                           // O(1) amort., construct in-place
	v.pop_back();                                // O(1) - remove last
	v.insert(v.begin() + 2, 99);                 // O(N) - insert at index 2
	v.erase(v.begin() + 2);                      // O(N) - remove index 2
	v.erase(v.begin(), v.begin() + 2);           // O(N) - remove [0, 2)
	v.clear();                                   // O(N) - remove all
	v.resize(10);                                // grow w/ 0s, or shrink
	v.resize(10, -1);                            // grow with -1s
	fill(v.begin(), v.end(), 0);                 // overwrite all with 0

	// Access
	ll a  = v[0];                               // O(1), no bounds check
	ll b  = v.at(0);                            // O(1), throws if OOB
	ll sz = v.size();
	bool e = v.empty();

	// --- D. Sorting ---
	sort(v.begin(), v.end());                           // asc,  O(N log N)
	sort(v.begin(), v.end(), greater<ll>());           // desc
	sort(v.begin(), v.end(), [](ll a, ll b){          // custom comparator
		return a > b;
	});
	reverse(v.begin(), v.end());                        // O(N)

	// Binary Search (VECTOR MUST BE SORTED) - all O(log N)
	bool found = binary_search(v.begin(), v.end(), 5);

	// Four bound shapes. Mental model:
	//   first >= x   lower_bound(x)
	//   first >  x   upper_bound(x)
	//   last  <  x   lower_bound(x), --it    (skip if it == begin)
	//   last  <= x   upper_bound(x), --it    (skip if it == begin)
	auto lb = lower_bound(v.begin(), v.end(), 4);       // first >= 4
	auto ub = upper_bound(v.begin(), v.end(), 4);       // first >  4

	// Predecessor (last < 4):
	auto pr = lower_bound(v.begin(), v.end(), 4);
	if (pr != v.begin()) { 
		--pr; /* *pr is last < 4 */ 
	}

	// Once you have a bound iterator (example uses lb from above):
	if (lb != v.end()) { 
		/* first >= 4 exists */ 
	}
	ll val  = *lb;                                      // value
	ll idx  = lb - v.begin();                           // index, O(1) (random-access)
	*lb = 99;                                           // mutate value
	v.erase(lb);                                        // remove, O(N), invalidates lb
	auto nx = lb + 1, pv = lb - 1;                      // neighbors (no bounds check)


	// =========================================================================
	// 2. QUEUES  (FIFO)
	// =========================================================================
	// Header: <queue>.  All ops O(1).

	queue<ll> q;
	q.push(1);                                   // add to back
	q.push(2);
	ll qf = q.front();                          // peek front (oldest)
	ll qb = q.back();                           // peek back  (newest)
	q.pop();                                     // remove front (void)
	ll qs = q.size();
	bool qe = q.empty();


	// =========================================================================
	// 3. PRIORITY QUEUES  (binary heap; max-heap by default)
	// =========================================================================
	// push/pop O(log N), top O(1).

	// Max-heap (default)
	priority_queue<ll> pq;
	pq.push(10); 
	pq.push(5); 
	pq.push(20);
	ll top = pq.top();                          // 20 (largest)
	pq.pop();                                    // removes 20

	// Min-heap (CRITICAL: 3 template args)
	priority_queue<ll, vector<ll>, greater<ll>> minpq;
	minpq.push(10); 
	minpq.push(5);
	ll lo = minpq.top();                        // 5

	// Priority queue of pairs/tuples
	// Default compare is LEXICOGRAPHIC: by first, tiebreak by second, ...
	priority_queue<pair<ll,ll>> pqp;
	pqp.push({3, 100});
	pqp.push({5, 1});
	auto [pri, val] = pqp.top();                 // {5, 1}
	pqp.pop();

	// Min-heap of pairs (e.g. Dijkstra: {dist, node})
	priority_queue<pair<ll,ll>,
	               vector<pair<ll,ll>>,
	               greater<pair<ll,ll>>> pqmin;

	priority_queue<tuple<ll,ll,ll>> pqt;
	pqt.push({1, 2, 3});
	auto [t0, t1, t2] = pqt.top();               // structured binding


	// =========================================================================
	// 4. STACKS  (LIFO)
	// =========================================================================
	// Header: <stack>.  All ops O(1).

	stack<ll> st;
	st.push(1);
	st.push(2);
	if (!st.empty()) {
		ll t = st.top();                        // 2 - peek, does NOT remove
		st.pop();                                // removes 2 (void)
	}
	ll sts = st.size();


	// =========================================================================
	// 5. MAPS  (std::map  and  std::unordered_map)
	// =========================================================================
	// map:           Ordered (red-black tree). O(log N). Key needs operator<.
	// unordered_map: Hash table.               O(1) avg / O(N) worst. Key needs hash.

	// Initialization
	map<string, ll> m;
	map<ll, ll>    m2 = {{1, 2}, {3, 4}};
	unordered_map<string, ll> um;

	// Insert / Modify / Access
	m["apple"] = 5;                              // creates (default 0) if absent, then assigns
	ll mv = m["apple"];                         // WARNING: creates key if absent
	m.insert({"banana", 3});                     // no-op if key present; returns {iter, bool}
	m.emplace("cherry", 7);

	m.erase("apple");                            // erase by key
	m.erase(m.begin());                          // erase by iterator

	// Safe existence (does NOT insert)
	if (m.count("apple")) { 
		/* 0 or 1 for map */ 
	}
	if (m.find("apple") != m.end()) { 
		/* same */ 
	}

	// Iteration
	// map: sorted key order.  unordered_map: arbitrary order.
	for (auto it = m.begin(); it != m.end(); ++it) {
		// it->first  = key
		// it->second = value
	}

	// Ordered-map binary search (NOT on unordered_map) - all O(log N)
	map<ll, string> om = {{10,"A"}, {20,"B"}, {30,"C"}};
	auto it1 = om.lower_bound(15);               // first key >= 15 -> {20,"B"}
	auto it2 = om.upper_bound(20);               // first key >  20 -> {30,"C"}
	// Last key <  x: auto p = om.lower_bound(x); if (p != om.begin()) --p;
	// Last key <= x: auto p = om.upper_bound(x); if (p != om.begin()) --p;

	// Once you have a bound iterator (example uses it1):
	if (it1 == om.end()) { /* no such key */ }
	auto k     = it1->first;                     // key (const)
	auto mval  = it1->second;                    // value
	it1->second = "Z";                           // modify value in-place (OK)
	om.erase(it1);                               // remove, O(log N)
	auto mnx = next(it1), mpv = prev(it1);       // neighbors (no bounds check)
	// distance(om.begin(), it1) is O(N) -- map iterators aren't random-access.

	// Min / max key (check empty first!)
	ll mink = om.begin()->first;                // smallest key
	ll maxk = om.rbegin()->first;               // largest  key (reverse iter)


	// =========================================================================
	// 6. SETS  (set, multiset, unordered_set)
	// =========================================================================
	// set:            Ordered, unique.      O(log N).  Element needs operator<.
	// multiset:       Ordered, dupes OK.    O(log N).
	// unordered_set:  Hash, unique.         O(1) avg / O(N) worst.

	// Initialization
	set<ll>           s  = {3, 1, 4, 1, 5};     // -> {1, 3, 4, 5}
	multiset<ll>      ms = {1, 1, 2};           // -> {1, 1, 2}
	unordered_set<ll> us = {1, 2, 3};

	// Modifiers
	s.insert(2);                                 // O(log N), no-op if present
	s.erase(3);                                  // O(log N), erase by value

	// Multiset erase semantics
	ms.erase(1);                                 // removes ALL 1s
	ms.erase(ms.find(1));                        // removes exactly ONE 1

	// Contains
	bool has  = s.count(2);                      // 0 or 1 for set/unordered_set
	bool has2 = s.find(2) != s.end();
	ll  freq = ms.count(1);                     // actual count in multiset

	// Iteration (ordered set: strictly increasing)
	for (auto it = s.begin(); it != s.end(); ++it) {
		// *it is the value (read-only)
	}

	// Ordered-set binary search (NOT on unordered_set) - all O(log N)
	auto itl = s.lower_bound(4);                 // first >= 4
	auto itu = s.upper_bound(4);                 // first >  4
	// Last <  4:  auto p = s.lower_bound(4); if (p != s.begin()) --p;  // *p is largest <  4
	// Last <= 4:  auto p = s.upper_bound(4); if (p != s.begin()) --p;  // *p is largest <= 4

	// Once you have a bound iterator (example uses itl):
	if (itl == s.end()) { 
		/* no element >= 4 */
	}
	ll sval = *itl;                              // value (read-only; can't mutate)
	s.erase(itl);                                // remove, O(log N)
	auto snx = next(itl), spv = prev(itl);       // neighbors (no bounds check)
	// distance(s.begin(), itl) is O(N) -- set iterators aren't random-access.

	// Min / max (check empty!)
	ll smallest = *s.begin();
	ll largest  = *s.rbegin();


	// =========================================================================
	// 7. PAIRS
	// =========================================================================
	// Two-element heterogeneous bundle. Compared LEXICOGRAPHICALLY.

	pair<ll, string> p = {1, "hi"};
	ll pf = p.first;
	string ps = p.second;

	// Structured binding (C++17)
	auto [pf1, ps2] = p;

	// Vector of pairs, sorted by first then second
	vector<pair<ll,ll>> vp = {{3,1}, {1,5}, {2,2}};
	sort(vp.begin(), vp.end());                  // -> {{1,5},{2,2},{3,1}}


	// =========================================================================
	// 8. TUPLES
	// =========================================================================
	// N heterogeneous elements. Compared LEXICOGRAPHICALLY like pair.

	tuple<ll, double, string> t = {1, 3.14, "Pi"};
	auto t2 = make_tuple(2, 1.41, "Root");

	ll ti = get<0>(t);
	double td = get<1>(t);
	string ts = get<2>(t);

	// Structured binding (C++17) - preferred
	auto [A, B, C] = t;

	// Unpack llo existing vars (C++11)
	ll xi; double xd; string xs;
	tie(xi, xd, xs) = t;


	// =========================================================================
	// 9. STRINGS
	// =========================================================================
	// Mutable sequence of chars.

	// Init & Input
	string str  = "hello";
	string str2(5, 'a');                         // "aaaaa"
	string str3(str.begin(), str.begin() + 3);   // "hel"
	// cin >> str;              // stops at whitespace

	// Modifiers
	str += " world";                             // O(N) - concat
	str.push_back('!');                          // O(1)
	str.pop_back();                              // O(1)
	str.insert(5, "XYZ");                        // O(N) - insert at index 5
	str.erase(0, 3);                             // O(N) - erase 3 chars from index 0
	str.replace(0, 5, "HELLO");                  // O(N) - replace [0,5) with "HELLO"
	reverse(str.begin(), str.end());             // O(N)

	// Access / Substring / Size
	char ch  = str[0];
	char lch = str.back();
	ll  len = str.size();                       // same as str.length()
	string sub = str.substr(0, 4);               // (start, length) -> first 4 chars
	string suf = str.substr(4);                  // from index 4 to end

	// Search (returns index, or string::npos if not found)
	size_t pos = str.find("lo");                 // first occurrence
	size_t rp  = str.rfind("lo");                // last  occurrence
	if (pos != string::npos) { /* found */ }

	// Conversions
	ll l1 = stoll("12345678901");         // string -> ll
	double    d1 = stod("3.14");                 // string -> double
	string    sn = to_string(42);                // number -> string

	// Char utilities (<cctype>)
	// isdigit(c), isalpha(c), isalnum(c), isspace(c), islower(c), isupper(c)
	// tolower(c), toupper(c)
	for (ll i = 0; i < (ll)str.size(); i++) {
		if (isalpha(str[i])) str[i] = tolower(str[i]);
	}

	return 0;
}
