#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <stack>
#include <map>

using namespace std;

class Solution {
public:
	vector<vector<int> > fourSum(vector<int>& nums, int target) {
		vector<vector<int>> lRetVal;
		vector<int> lQuad( 4, 0 ); // Pre-allocate the size of the result
		// Sort to provide a mechanism for avoiding duplicates
		sort( nums.begin(), nums.end() );
		KSum( 4, nums, 0, nums.size()-1, target, lRetVal, lQuad, 0 );
		return( lRetVal );		
	}
private:
	// Valid for K >= 2
	void KSum(int k, vector<int>& nums, int l, int r, int target, vector<vector<int>>& retVal, vector<int>& cur, int ci ) {
		int i, mn, mx;
		int km1 = k - 1;
		if ( r-l+1 < k ) 
			return;
		while ( l < r ) {
			mn = nums[l];
			mx = nums[r];
			// If K minus 1 largest + min < target, move to larger
			if ( ( mn + km1*mx ) < target ) 
				l++;
			// If K minus 1 smaller + max > target, move to smaller
			else if ( ( km1*mn + mx ) > target ) 
				r--;
			// If K * min > target, stop looking
			else if ( k*mn > target ) 
				break;
			// If K * min == target, reached the threshold, check then stop looking
			else if ( k*mn == target ) {
				if ( ( l + km1 <= r ) && ( mn == ( nums[l+km1] ) ) ) {
					for ( i = 0; i < k; i++ ) 
						cur[ci+i] = mn;
					retVal.push_back( cur );
				}
				break;
			}
			// If K * max < target, stop looking
			else if ( k*mx < target ) 
				break;
			// If K * max == target, reached the threshold, check then stop looking
			else if ( k*mx == target ) {
				if ( ( l <= r - km1 ) && ( mx == ( nums[r-km1] ) ) ) {
					for ( i = 0; i < k; i++ ) 
						cur[ci+i] = mx;
					retVal.push_back( cur );
				}
				break;				
			}
			// If K == 2, we found a match!
			else if ( k == 2 ) {
				cur[ci] = mn;
				cur[ci+1] = mx;
				retVal.push_back( cur );
				l++;
				while ( ( l < r ) && ( nums[l] == mn ) ) 
					l++;
				r--;
				while ( ( l < r ) && ( nums[r] == mx ) ) 
					r--;
			}
			// Otherwise, convert the problem to a K-1 problem
			else {
				cur[ci] = mn;
				KSum( km1, nums, ++l, r, target - mn, retVal, cur, ci+1 );
				while ( ( l < r ) && ( nums[l] == nums[l-1] ) ) 
					l++;
			}
		}
	}
};

void test(vector<int>& nums, int target)
{
	Solution sol;
	sol.fourSum(nums, target);
}

int main()
{
	vector<int> veca { 1, 0, -1, 0, -2, 2};
	test(veca, 0);

	vector<int> vecb { 1, 2, 3, 4};
	test(vecb, 10);

	vector<int> vecc { 1, 2, 3, 4};
	test(vecc, 11);

	vector<int> vecd { 0, 0, 0, 0, 0, 0 };
	test(vecd, 0);  // 1

	vector<int> vece { -3, -2, -1, 0, 0, 1, 2, 3 };
	test(vece, 0);  // 8

	vector<int> vecf { -498,-492,-473,-455,-441,-412,-390,-378,-365,-359,-358,-326,-311,-305,-277,-265,-264,-256,-254,-240,-237,-234,-222,-211,-203,-201,-187,-172,-164,-134,-131,-91,-84,-55,-54,-52,-50,-27,-23,-4,0,4,20,39,45,53,53,55,60,82,88,89,89,98,101,111,134,136,209,214,220,221,224,254,281,288,289,301,304,308,318,321,342,348,354,360,383,388,410,423,442,455,457,471,488,488 };
	test(vecf, -2808);  // 

	vector<int> vecg { 91277418,66271374,38763793,4092006,11415077,60468277,1122637,72398035,-62267800,22082642,60359529,-16540633,92671879,-64462734,-55855043,-40899846,88007957,-57387813,-49552230,-96789394,18318594,-3246760,-44346548,-21370279,42493875,25185969,83216261,-70078020,-53687927,-76072023,-65863359,-61708176,-29175835,85675811,-80575807,-92211746,44755622,-23368379,23619674,-749263,-40707953,-68966953,72694581,-52328726,-78618474,40958224,-2921736,-55902268,-74278762,63342010,29076029,58781716,56045007,-67966567,-79405127,-45778231,-47167435,1586413,-58822903,-51277270,87348634,-86955956,-47418266,74884315,-36952674,-29067969,-98812826,-44893101,-22516153,-34522513,34091871,-79583480,47562301,6154068,87601405,-48859327,-2183204,17736781,31189878,-23814871,-35880166,39204002,93248899,-42067196,-49473145,-75235452,-61923200,64824322,-88505198,20903451,-80926102,56089387,-58094433,37743524,-71480010,-14975982,19473982,47085913,-90793462,-33520678,70775566,-76347995,-16091435,94700640,17183454,85735982,90399615,-86251609,-68167910,-95327478,90586275,-99524469,16999817,27815883,-88279865,53092631,75125438,44270568,-23129316,-846252,-59608044,90938699,80923976,3534451,6218186,41256179,-9165388,-11897463,92423776,-38991231,-6082654,92275443,74040861,77457712,-80549965,-42515693,69918944,-95198414,15677446,-52451179,-50111167,-23732840,39520751,-90474508,-27860023,65164540,26582346,-20183515,99018741,-2826130,-28461563,-24759460,-83828963,-1739800,71207113,26434787,52931083,-33111208,38314304,-29429107,-5567826,-5149750,9582750,85289753,75490866,-93202942,-85974081,7365682,-42953023,21825824,68329208,-87994788,3460985,18744871,-49724457,-12982362,-47800372,39958829,-95981751,-71017359,-18397211,27941418,-34699076,74174334,96928957,44328607,49293516,-39034828,5945763,-47046163,10986423,63478877,30677010,-21202664,-86235407,3164123,8956697,-9003909,-18929014,-73824245 };
	test(vecg, -236727523);  // 
	
	

}
