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
		vector<vector<int> > vec_res;
		vector<int> vec_empty;
		vec_res.push_back(vec_empty);
		subsets_recursion(nums, vec_res, vec_empty);
		// printf("%lu\n", vec_res.size());
		return vec_res;
    }
	void subsets_recursion(vector<int>& nums, vector<vector<int> >& vec_res, vector<int> stored) {
		if (0 == nums.size())
			return;
		for(int i = 0; i < nums.size(); i++) {
			if (stored.size() > 0 && stored.back() > nums[i])
				continue;
			stored.push_back(nums[i]);
			vec_res.push_back(stored);
			int erase_num = nums[i];
			nums.erase(nums.begin() + i);
			subsets_recursion(nums, vec_res, stored);
			stored.pop_back();
			nums.insert(nums.begin() + i, erase_num);
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
