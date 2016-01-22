#pragma once

#include <iostream>
#include <string>

using namespace std;

template<typename T>
class DataOperate
{
public:
	DataOperate(T num1, T num2);
	~DataOperate();
	char* Add();
	char* Subtract();
	char* Multiply();
	char* Devide();
private:
	string data1;
	string data2;
};

