#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>


struct Base 
{

	virtual void bark() = 0;
		

};

struct Der1 : public Base
{
	virtual void bark()
	{
		std::cout << "der1\n";
	}
};

struct Der2 : public Base
{
	virtual void bark()
	{
		std::cout << "der2\n";
	}
};

int main()
{
	Base *b1 = new Der1();
	Base *b2 = new Der2();


	Base *cobai = new Der1();

	cobai->bark();
	memcpy(cobai, b2, 8);
	cobai->bark();


	std::cin.get();
	
	return 0;
}
