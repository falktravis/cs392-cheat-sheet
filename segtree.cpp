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

class SegmentTree
{
public:
    vector<int> tree;
    int n;

    /**
     * Constructor
     */
    SegmentTree(vector<int> &ar)
    {
        n = ar.size();
        tree.resize(n);
        tree.insert(tree.end(), ar.begin(), ar.end());
        for (int i = n - 1; i > 0; i--)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    /**
	 * @param i - index to original array, inclusive
	 * @param value - new value to be saved off
	 */
    void update(int i, int value) {
        i += n;
        tree[i] = value;
        int newValue;
        
        while (i > 1) {
            i >>= 1; // shift right is the same as divide by 2
            newValue = tree[2 * i] + tree[2 * i + 1];
            
            if (tree[i] != newValue) {
            	tree[i] = newValue;	
            } else {
            	return; // since no update is made 
            }
        }
    }

    /**
	 * Starts at the bottom of the tree and works its way up until reaching nodes that cover the requested range.
	 * Note how we always start from the right end of the array. Then on each iteration of the loop, the index variables 'from' and 'to' are halved. 
	 * Thus, on each iteration we go up one level on the tree.
	 * 
	 * Note that we only update ans if the indexes 'from' and 'to' are odd. Why is that? It's because if the index is even, then it's 
	 * the left child node. We don't need to bother reading it since we'll get another chance at doing it on the next level up. Of course, this same 
	 * logic applies on the next level up.
	 * 
	 * @param from - inclusive
	 * @param to - exclusive
	 * @return
	 */
    int query(int from, int to) {
        from += n; // go to second half of the array
        to += n;
        // Initialize ans accordingly
        int ans = 0;

        while (from < to) {
            cout<<from<<" "<<to<<endl;
            if ((from & 1) == 1) { // 'from' is odd, so it is the right child of its parent, then interval includes node 'from' but doesn't include its parent
                ans = ans + tree[from];
                from++;
            }
            if ((to & 1) == 1) { // 'to' is odd, so it's the right child of its parent, then might as well use the parent
                to--;
                ans = ans + tree[to];
            }
            from >>= 1; // shift right is the same as divide by 2 but a little faster
            to >>= 1;     
            cout<<from<<" "<<to<<endl;       
        }
        
        return ans;
    }

};

int main()
{

    vector<int> ar = {10,1,5,9,23,7,7,11};
    SegmentTree sg(ar);
    sg.update(6,2);
    for (int i : sg.tree)
        cout << i << " ";
    cout << endl;
    cout<<sg.query(0,1)<<endl;
    return 0;
}
