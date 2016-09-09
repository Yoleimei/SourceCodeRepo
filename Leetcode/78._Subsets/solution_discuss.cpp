#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <stack>
#include <map>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int> > vec_res;
		vector<int> vec_empty;
		subsets_recursion(nums, vec_res, vec_empty, 0);
		printf("%lu\n", vec_res.size());
		return vec_res;
    }
	void subsets_recursion(vector<int>& nums, vector<vector<int> >& vec_res, vector<int> &stored, int start) {
		vec_res.push_back(stored);
		for(int i = start; i < nums.size(); i++) {
			stored.push_back(nums[i]);
			subsets_recursion(nums, vec_res, stored, i + 1);
			stored.pop_back();
		}
	}
};

void test(vector<int>& nums)
{
	Solution sol;
	sol.subsets(nums);
}

int main()
{
	vector<int> veca { 1, 2, 3};
					// []
					// 1
					// 1 2
					// 1 2 3
					// 1 3
					// 2
					// 2 3
					// 3
	test(veca);
}
