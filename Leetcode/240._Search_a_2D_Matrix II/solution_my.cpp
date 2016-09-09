#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <stack>
#include <map>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
		if (0 == rows)
			return false;
		int cols = matrix[0].size();
		if (0 == cols)
			return false;
		for (int row = 0, col = cols - 1; row < rows && col >= 0;) {
			if (target == matrix[row][col])
				return true;
			else if (target < matrix[row][col])
				col--;
			else 
				row++;
		}
		return false;
    }
};

void test(vector<vector<int>>& matrix, int target, bool ret)
{
	Solution sol;
	bool foo = sol.searchMatrix(matrix, target);
	if (foo == ret)
		printf("true\n");
	else
		printf("false\n");
}

int main()
{
	
}
