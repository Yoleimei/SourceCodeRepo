#include <iostream>

using namespace std;

void ComputerlastSameIdxListfix(const char *control, int *lastSameIdxList) {
	int m = strlen(control);
	int lastSameIdx = -1;
	lastSameIdxList[0] = lastSameIdx;
	for (int i = 1; i < m; ++i) {
		while (lastSameIdx > -1 && control[lastSameIdx + 1] != control[i])
			lastSameIdx = lastSameIdxList[lastSameIdx];
		if (control[lastSameIdx + 1] == control[i])
			++lastSameIdx;
		lastSameIdxList[i] = lastSameIdx;
	}
}

void KMP_Matcher(const char *src, const char *control) {
	int n = strlen(src);
	int m = strlen(control);
	int *lastSameIdxList = new int[m];
	ComputerlastSameIdxListfix(control, lastSameIdxList);
	int lastSameIdx = -1;
	for (int i = 0; i < n; ++i) {
		while (lastSameIdx > -1 && control[lastSameIdx + 1] != src[i])
			lastSameIdx = lastSameIdxList[lastSameIdx];
		if (control[lastSameIdx + 1] == src[i])
			++lastSameIdx;
		if (lastSameIdx == m - 1){
			cout << "Match shift is " << i - m + 1 << endl;
			// lastSameIdx = lastSameIdxList[lastSameIdx];  //重新比较时偏移部分字符串
			lastSameIdx = -1;  // 重新比较时偏移整个字符串
		}
	}
	delete[] lastSameIdxList;
}

int main() {
	char src[] = "aaaa";
	char control[] = "aa";
	KMP_Matcher(src, control);
	system("pause");
}