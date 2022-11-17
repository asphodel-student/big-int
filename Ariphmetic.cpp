#include "BigInt.h"

//Unary plus
BigInt BigInt::operator+() const
{
	BigInt outputValue(*this);
	if (!outputValue.sign) outputValue.sign = !outputValue.sign;
	return outputValue;
}

//Unary minus
BigInt BigInt::operator-() const
{
	BigInt outputValue(*this);
	outputValue.sign = !outputValue.sign;
	return outputValue;
}

bool BigInt::operator==(const BigInt& other) const
{

	if (this->sign != other.sign)
		return false;

	if (this->number.size() != other.number.size())
		return false;

	for (long long numbers_position = this->number.size() - 1; numbers_position >= 0; numbers_position--)
	{
		if (this->number[numbers_position] != other.number[numbers_position])
			return false;
	}

	return true;
}

bool BigInt::operator!=(const BigInt& other) const
{
	return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const
{
	if (*this == other) return false;
	if (this->sign > other.sign || this->number.size() > other.number.size()) return false;
	if (this->sign < other.sign || this->number.size() < other.number.size()) return true;

	switch (this->sign)
	{
	case(true):	//If both values are positive
		for (int i = this->number.size() - 1; i >= 0; i--)
		{
			if (this->number[i] < other.number[i]) return true;
			if (this->number[i] > other.number[i]) return false;
		}
		break;

	case(false): //If both values are negative
		for (int i = this->number.size() - 1; i >= 0; i--)
		{
			if (this->number[i] > other.number[i]) return true;
			if (this->number[i] < other.number[i]) return false;
		}
		break;
	}

	return false;
}

bool BigInt::operator>(const BigInt& other) const
{
	if (!(*this < other) && (*this != other)) 
		return true;
	return false;
}

bool BigInt::operator<=(const BigInt& other) const
{
	if (*this < other || *this == other)
		return true;
	return false;
}

bool BigInt::operator>=(const BigInt& other) const
{
	if (*this > other || *this == other)
		return true;
	return false;
}

BigInt operator+(const BigInt& a, const BigInt& b)
{
	if (!a.sign && b.sign) return b - (-a);
	if (!a.sign && !b.sign) return -(a - b);

	unsigned long long int rest = 0;
	unsigned long long int num = 0;

	BigInt outputValue = BigInt();
	BigInt& minValue = const_cast<BigInt&>(min(a, b));
	BigInt& maxValue = const_cast<BigInt&>(max(a, b));

	unsigned long long int base = outputValue.getBase();

	minValue.addLeadingZeros(maxValue.number.size() - minValue.number.size());

	for (auto i = 0; i < maxValue.number.size(); i++)
	{
		num = maxValue.number[i] * 1ULL + minValue.number[i] + rest;
		outputValue.number.push_back(static_cast<unsigned int>(num % base));
		rest = num / base;
	}

	outputValue.removeLeadingZeros();
	minValue.removeLeadingZeros();

	return outputValue;
}

BigInt operator-(const BigInt& a, const BigInt& b)
{
	if (a.sign == false && b.sign == false) return -(-a - -b);
	if (b.sign == false) return a + (-b);
	if (a.sign == false) return -(-a + b);
	if (a < b) return -(b - a);

	long long int rest = 0;
	long long int num = 0;

	BigInt outputValue;
	outputValue.number.reserve(a.number.size() * 3);

	BigInt& minValue = const_cast<BigInt&>(min(a, b));
	BigInt& maxValue = const_cast<BigInt&>(max(a, b));

	unsigned int base = outputValue.getBase();
	for (auto i = 0; i < maxValue.number.size(); i++)
	{
		num = (i < b.number.size() ? static_cast<int>(a.number[i] - b.number[i] - rest) : static_cast<int>(a.number[i] - rest));
		rest = num < 0;
		if (rest) num += base;
		outputValue.number.push_back(static_cast<unsigned int>(num));
	}

	outputValue.removeLeadingZeros();

	return outputValue;
}

BigInt operator%(const BigInt& a, const BigInt& b)
{
	if (b == a) return 0;
	if (b > a) return a;

	BigInt outputValue;
	outputValue = (a - ((a / b) * b));

	return outputValue;
}

BigInt operator*(const BigInt& a, const BigInt& b)
{
	BigInt outputValue = BigInt();
	unsigned int base = outputValue.getBase();
	outputValue.number.resize(a.number.size() + b.number.size());

	if (b.number == b.zero) return BigInt(0);
	if (b.number == b.one) return a;

	unsigned long long int rest, current;
	for (auto i = 0; i < a.number.size(); i++)
	{
		rest = 0;
		for (auto j = 0; j < b.number.size() || rest; j++)
		{
			current = outputValue.number[i + j] + a.number[i] * 1ULL * (j < b.number.size() ? b.number[j] : 0) + rest;
			outputValue.number[i + j] = static_cast<unsigned int>(current % base);
			rest = static_cast<unsigned int>(current / base);
		}
	}

	if (a.sign == b.sign) outputValue.sign = true;
	else outputValue.sign = false;

	outputValue.removeLeadingZeros();

	return outputValue;
}

BigInt operator/(const BigInt& a, const BigInt& b)
{
	if (b.number == b.zero) throw "Division by zero!";
	if (a < b) return 0;

	unsigned int quotient, left, middle, right;
	BigInt tmp, result, part;

	result.sign = (a.sign == b.sign);
	result.number.resize(0);
	part.number.resize(0);

	for (long long pos = a.number.size() - 1; pos >= 0; pos--)
	{
		std::reverse(part.number.begin(), part.number.end());
		part.number.push_back(a.number[pos]);
		std::reverse(part.number.begin(), part.number.end());

		quotient = 0;
		left = 0;
		right = 1000000000;

		while (left <= right)
		{
			middle = (left + right) / 2;
			tmp = b * BigInt(middle);

			if (tmp <= part)
			{
				quotient = middle;
				left = middle + 1;
			}
			else
			{
				right = middle - 1;
			}
		}

		part = part - (b * BigInt(quotient));

		if (!result.number.empty() || quotient != 0)
			result.number.push_back(quotient);

		if (part.number == a.zero)
			part.number.resize(0);
	}

	std::reverse(result.number.begin(), result.number.end());
	return result;
}

BigInt& BigInt::operator-=(const BigInt& other)
{
	return *this = *this - other;
}

BigInt& BigInt::operator/=(const BigInt& other)
{
	return *this = *this / other;
}

BigInt& BigInt::operator%=(const BigInt& other)
{
	return *this = *this % other;
}

BigInt& BigInt::operator*=(const BigInt& other)
{
	return *this = *this * other;
}

BigInt& BigInt::operator--()
{
	return *this = (*this - BigInt(1));
}

const BigInt BigInt::operator--(int)
{
	*this -= 1;
	return *this;
}


BigInt& BigInt::operator+=(const BigInt& other)
{
	return *this = *this + other;
}

BigInt& BigInt::operator++()
{
	return *this += 1;
}

const BigInt BigInt::operator++(int) 
{
	*this += 1;
	return *this;
}

BigInt& BigInt::operator=(const BigInt& other)
{
	if (*this == other) return *this;

	if (other.number.size() == 0) return *this = BigInt();

	this->number.resize(other.number.size());
	std::copy(other.number.begin(), other.number.end(), this->number.begin());
	this->sign = other.sign;

	return *this;
}

BigInt powBI(const BigInt& a, const BigInt& b)
{
	BigInt outputValue(1);
	for (BigInt i(0); i < b; ++i)
	{
		outputValue *= a;
	}

	return outputValue;
}