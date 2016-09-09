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
        vector<int> res(nums.size(), 1);
		for (int i = 1; i < nums.size(); i++) {
			for (int j = 0; j < i; j++) {
				if(nums[i] > nums[j]) 
					res[i] = max(res[i], res[j] + 1);
			}
		}
		return (max_element(res.begin(), res.end()) == res.end()) ? 0 : *max_element(res.begin(), res.end());
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
	test(veca, 4);

	vector<int> vecb { 11, 12, 13, 1, 2, 14 };
	test(vecb, 4);

	vector<int> vecc { 11, 12, 13, 1, 2, 3, 4, 14 };
	test(vecc, 5);

	vector<int> vecd;
	test(vecd, 0);

	vector<int> vece { 1 };
	test(vece, 1);
}
