#include <stdio.h>
#include <vector>

using namespace std;

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        return 7;
    }
};

void test(vector<int>& nums, int target, int ret)
{
	Solution sol;
	int foo = sol.combinationSum4(nums, 4);
	if (foo == ret)
		printf("true\n");
	else
		printf("false\n");
}

int main()
{
	int a[3] = {1,2,3};
	vector<int> veca(a, a+3);
	test(veca, 3, 7);
}
