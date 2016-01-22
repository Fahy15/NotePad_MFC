
#include "stdafx.h"
#include "DataOperate.h"

template<typename T>
DataOperate<T>::DataOperate(T num1, T num2) : data1(num1), data2(num2)
{
}

template<typename T>
DataOperate<T>::~DataOperate()
{
}

template<typename T>
char* DataOperate<T>::Multiply()
{
	string data1(this->data1);
	string data2(this->data2);
	int length1 = data1.length();
	int length2 = data2.length();

	int length = length1 + length2;
	int* multi(new int[length]);
	memset(multi, 0, sizeof(int)*(length));

	for (int i = 0; i < length1; i++)
	{
		for (int j = 0; j < length2; j++)
		{
			multi[i + j + 1] += (data1[i] - '0') * (data2[j] - '0');
		}
	}
	for (int i = length - 1; i > 0; i--)
	{
		if (multi[i] >= 10)
		{
			multi[i - 1] += multi[i] / 10;
			multi[i] %= 10;
		}
	}

	int i = 0;
	while (multi[i] <= 0)
	{
		i++;
	}

	int j = 0;
	char* result(new char[length + 1]);
	memset(result, 0, sizeof(char)*(length + 1));
	for (; i < length; i++, j++)
	{
		result[j] = multi[i] + '0';
	}
	result[j] = '\0';
	return result;
}

template<typename T>
char* DataOperate<T>::Add()
{
	string data1(this->data1);
	string data2(this->data2);
	int length1 = data1.length();
	int length2 = data2.length();

	int length = length1 > length2 ? length1 : length2;
	int* add(new int[length + 1]);
	memset(add, 0, sizeof(int)*(length + 1));
	for (int i = length1 - 1, l = length; i >= 0; i--, l--)
	{
		add[l] += (data1[i] - '0');
	}
	for (int j = length2 - 1, l = length; j >= 0; j--, l--)
	{
		add[l] += (data2[j] - '0');
	}
	for (int l = length; l > 0; l--)
	{
		if (add[l] >= 10)
		{
			add[l - 1] += 1;
			add[l] -= 10;
		}
	}

	int l = 0;
	while (add[l] <= 0)
	{
		l++;
	}

	int m = 0;
	char* result(new char[length + 2]);
	memset(result, 0, length + 2);
	for (; l < length + 1; l++, m++)
	{
		result[m] = add[l] + '0';
	}
	result[m] = '\0';
	return result;
}

template<typename T>
char* DataOperate<T>::Subtract()
{
	string data1(this->data1);
	string data2(this->data2);
	int length1 = data1.length();
	int length2 = data2.length();

	int length = length1 > length2 ? length1 : length2;
	int* subtract(new int[length]);
	memset(subtract, 0, sizeof(int)*(length));
	for (int i = length1 - 1, l = length-1; i >= 0; i--, l--)
	{
		subtract[l] += (data1[i] - '0');
	}
	for (int j = length2 - 1, l = length-1; j >= 0; j--, l--)
	{
		subtract[l] -= (data2[j] - '0');

	}
	for (int l = length-1; l > 0; l--)
	{
		if (subtract[l] < 0)
		{
			subtract[l - 1] -= 1;
			subtract[l] += 10;
		}
	}

	int l = 0;
	while (subtract[l] == 0 && l < length-1)
	{
			l++;
	}

	int m = 0;
	char* result(new char[length + 2]);
	memset(result, 0, length + 2);
	for (; l < length; l++, m++)
	{
		if (subtract[l]<0)
		{
			result[m] = '-';
			++m;
			subtract[l] *= -1;
		}
		result[m] = subtract[l] + '0';
	}
	result[m] = '\0';
	return result;
}


template<typename T>
char* DataOperate<T>::Devide()
{
	double devide;
	try
	{
	double num1 = atof(this->data1.c_str());
	double num2 = atof(this->data2.c_str());	
	devide = (num2 == 0) ? throw 0 : num1 / num2;    //如果除数为零，触发异常
	}
	catch(int)
	{
		return 0;
	}
	CString result;
	result.Format("%lf", devide);
	
	char* resultChar = result.GetBuffer(result.GetLength());
	result.ReleaseBuffer();
	char* resultStr(new char[result.GetLength()]);
	strcpy(resultStr, resultChar);

	return resultStr;
}