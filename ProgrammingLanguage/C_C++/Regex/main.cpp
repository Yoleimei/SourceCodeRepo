#include <iostream>
#include <string>
#include <regex>

int main()
{
	// match result
	std::string str = "123";
	std::regex reg("[0-9]+");
	bool bRes = std::regex_match(str, reg);
	printf("match result: %d\n", bRes);

	// regex match
	str = "subject";
	reg = std::regex("(sub)(.*)");
	std::smatch sm;
	std::regex_match(str, sm, reg);
	for (int i = 0; i < sm.size(); i++) {
		std::cout << "match string " << i << ": " << sm[i] << std::endl;
	}

	// regex search
	str = "hh123a456b789c";
	reg = std::regex("[0-9]+");
	while (std::regex_search(str, sm, reg)) {
		for (int i = 0; i < sm.size(); i++) {
			std::cout << "search string " << i << ": " << sm[i] << std::endl;
		}
		str = sm.suffix().str();
	}

	getchar();
}
