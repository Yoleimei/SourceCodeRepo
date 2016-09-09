#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
	int combinationSum4(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		vector<int> res(target + 1, -1);
		res[0] = 1;
		combinationSum4_recursion(nums, target, res);
		return res[target];
	}
	int combinationSum4_recursion(vector<int>& nums, int target, vector<int> &res) {
		if (-1 != res[target])
			return res[target];
		int ret = 0;
		for (int idx = 0; idx < nums.size() && nums[idx] <= target; idx++) {
			ret += combinationSum4_recursion(nums, target - nums[idx], res);
		}
		res[target] = ret;
		return ret;
	}
};

void test(vector<int>& nums, int target, int ret)
{
	Solution sol;
	int foo = sol.combinationSum4(nums, target);
	if (foo == ret)
		printf("true\n");
	else
		printf("false\n");
}

int main()
{
	//vector<int> veca { 1, 2, 3 };
	//test(veca, 4, 7);

	//vector<int> vecb { 1, 2, 4 };
	//test(vecb, 32, 0);

	vector<int> vecc { 3, 33, 333 };
	test(vecc, 10000, 0);

	vector<int> vecd { 10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,111 };
	test(vecd, 999, 0);
}
