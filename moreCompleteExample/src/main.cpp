#include <iostream>
#include <myHeader.h>
#include <fstream>

int main()
{
	
	print();


	std::ifstream file(RESOURCES_PATH "file.txt");
	
	//read the file
	std::string str((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	std::cout << str;


	std::cin.get();
	return 0;
}