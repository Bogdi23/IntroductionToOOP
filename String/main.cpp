﻿#include <iostream>
using namespace std;

#define delimiter "\n--------------------------------------------------\n"

class String
{
	int size;	//размер строки в Байтах (с учётом NULL-Terminator)
	char* str;	//адрес строки в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}


	//		Constructors:
	explicit String(int size = 80)
	{
		//Конструктор по умолчанию создаёт пустую строку размером 80 Байт
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(const char* str)
	{
		this->size = strlen(str) + 1;	//strlen() возвращает размер строки в символах, +1нужен чтобы выделилась память под NULL-Terminator
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		//this->str = other.str;	//Shallow copy
		//Deep copy:
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	~String()
	{
		delete[] str;
		str = nullptr;
		size = 0;
		cout << "Destructor:\t\t" << this << endl;
	}
	//		Operators:
	String& operator=(const String& other)
	{
		//0) Проверяем, не является ли тот объект нашим объектом:
		if (this == &other)return *this;
		//1) Удаляем старую динамическую память:
		delete[] this->str;
		//Deep copy:
		this->size = other.size;
		//2) Выделяем новую динамическую память:
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	char operator[](int i)const
	{
		return str[i];
	}
	char& operator[](int i)
	{
		return str[i];
	}
	//		Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};
String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
	{
		result[i] = left[i];
		//result.get_str()[i] = left.get_str()[i];
	}
	for (int i = 0; i < right.get_size(); i++)
		result[i + left.get_size() - 1] = right[i];
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return result;
}
std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

#define CONSTRUCTORS_CHECK
//#define COPY_SEMANTIC_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str1;
	str1.print();

	String str2(5);	//Conversion from 'int' to 'String'
	str2.print();

	String str3 = "Hello";
	str3.print();
	cout << str3 << endl;

	String str4 = "World";
	cout << str4 << endl;

	cout << delimiter << endl;
	String str5 = str3 + str4;
	cout << delimiter << endl;
	cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef COPY_SEMANTIC_CHECK
	String str1 = "Hello";
	cout << str1 << endl;

	String str2 = str1;
	cout << str2 << endl;

	String str3 = "World";
	String str4;
	str4 = str3;
	cout << str4 << endl;
#endif // COPY_SEMANTIC_CHECK

}