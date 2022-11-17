#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

class BigInt
{
public:
	std::vector<int> number;
	bool sign;

	std::vector<int> zero = { 0 };
	std::vector<int> one = { 1 };

	BigInt() { this->sign = true; };
	BigInt(int x);
	BigInt(std::string other); // бросать исключение std::invalid_argument при ошибке
	BigInt(const BigInt&);
	BigInt(unsigned int);

	~BigInt() = default;

	unsigned int getBase() { return this->base; }
	unsigned int getNumOfZeroes() { return this->zerosNums; }

	//bool getSign() { return this->sign; }

	BigInt& operator=(const BigInt& other);
	BigInt operator~() const;
	BigInt& operator++();
	const BigInt operator++(int);
	BigInt& operator--();
	const BigInt operator--(int);

	BigInt& operator+=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator/=(const BigInt&);
	BigInt& operator^=(const BigInt&);
	BigInt& operator%=(const BigInt&);
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	BigInt operator+() const;  // unary +
	BigInt operator-() const;  // unary -

	bool operator==(const BigInt& other) const;
	bool operator!=(const BigInt& other) const;
	bool operator<(const BigInt& other) const;
	bool operator>(const BigInt& other) const;
	bool operator<=(const BigInt& other) const;
	bool operator>=(const BigInt& other) const;

	operator int() const;
	operator std::string() const;

	size_t size() const;  // size in bytes

	int countLeadingNullsInString(std::string str);
	void removeLeadingZeros();
	void addLeadingZeros(int num);

private:
	//Current power is 10^9
	static const unsigned long long int base = 1000000000;
	const int zerosNums = 9;
};


BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream& o, const BigInt& i);
std::istream& operator>>(std::istream& o, const BigInt& i);

BigInt powBI(const BigInt&, const BigInt&);

std::vector<int> _to_2_30Base(BigInt& a);
int _2_divide(std::vector<int>& a);

const BigInt& min(const BigInt& a, const BigInt& b);

const BigInt& max(const BigInt& a, const BigInt& b);
