#include <iostream>
#include <string>

int main()
{
	char* c[6] = "Hello";
	std::string s(c);
	std::cout << strlen(c) << endl;
	std::cout << s.size() << endl;
	return 0;
}