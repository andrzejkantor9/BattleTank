// PolymorphismDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

int GetSize(int x)
{
	return x;
}
int GetSize(std::string x)
{
	return x.length();
}

class Animal
{
public:
	virtual void MakeNoise()
	{
		std::cout << "Animal Noise." << std::endl;
	}
};
class Dog : public Animal
{
public:
	void MakeNoise() override
	{
		std::cout << "Woof." << std::endl;
	}
};
class Cat : public Animal
{
public:
	void MakeNoise() override
	{
		std::cout << "Meow." << std::endl;
	}
};

void Stroke(Animal *animal)
{
	//subtype polymorphism
	animal->MakeNoise();
}
int main()
{
	std::cout << GetSize(5) << std::endl;
	//adhoc polymorphism
	std::cout << GetSize("Hello World!") << std::endl;
	
	Dog dog;
	Cat cat;
	Stroke(&dog);
	Stroke(&cat);

	return 0;
}