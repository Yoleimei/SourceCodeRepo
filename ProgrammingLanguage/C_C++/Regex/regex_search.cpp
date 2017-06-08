// regex_search example
#include <iostream>
#include <string>
#include <regex>

int main()
{
	std::string s("this subject has a submarine as a subsequence");
	std::smatch sm;
	std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

	std::cout << "Target sequence: " << s << std::endl;
	std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
	std::cout << "The following matches and submatches were found:" << std::endl;

	while (std::regex_search(s, sm, e)) {
		for (auto x : sm)
			std::cout << x << " ";
		std::cout << std::endl;
		s = sm.suffix().str();
	}

	getchar();

	return 0;
}
