#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <stack>
#include <map>

using namespace std;

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> res;
		for (int i = 0; i < nums.size(); i++) {
			auto it = lower_bound(res.begin(), res.end(), nums[i]);  // binary search
			if(it == res.end()) 
				res.push_back(nums[i]);
			else 
				*it = nums[i];
		}
		return res.size();
	}
};

void test(vector<int>& nums, int ret)
{
	Solution sol;
	int foo = sol.lengthOfLIS(nums);
	if (foo == ret)
		printf("true\n");
	else
		printf("false\n");
}

int main()
{
	vector<int> veca { 11, 1, 12, 2, 13, 3, 14 };
	                // 11
				    // 1
				    // 1 12
				    // 1 2
					// 1 2 13
					// 1 2 3
					// 1 2 3 14
	test(veca, 4);

	vector<int> vecb { 11, 12, 13, 1, 2, 14 };
					// 11
					// 11 12
					// 11 12 13
					// 1 12 13
					// 1 2 13
					// 1 2 13 14
	test(vecb, 4);

	vector<int> vecc { 11, 12, 13, 1, 2, 3, 4, 14 };
					// 11
					// 11 12
					// 11 12 13
					// 1 12 13
					// 1 2 13
					// 1 2 3
					// 1 2 3 4
					// 1 2 3 4 14
	test(vecc, 5);

	vector<int> vecd;
	test(vecd, 0);

	vector<int> vece { 1 };
	test(vece, 1);
}
