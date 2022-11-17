#include "BigInt.h"

//Add some leading zeros to the number
void BigInt::addLeadingZeros(int num)
{
	for (int i = 0; i < num; i++)
	{
		this->number.push_back(0);
	}
}

//Remove all leading zeros
void BigInt::removeLeadingZeros()
{
	if (this->number.size() == 0) return;
	while (this->number.size() != 1 && this->number.back() == 0)
	{
		this->number.pop_back();
	}
}

int BigInt::countLeadingNullsInString(std::string str)
{
	long long int count = 0;
	char currentSymbol = str[count];
	while (currentSymbol == '0')
	{
		currentSymbol = str[++count];
	}

	return count;
}

BigInt::BigInt(int x)
{
	this->sign = (x < 0) ? false : true;
	this->number.push_back(abs(x));
}

static int isValid(std::string arg)
{
	for (auto i : arg) 
	{
		if (!isdigit(i)) throw std::invalid_argument("Argument is not a valid number");
	}
}

//BigInt constructor.
//Throw std::invalid_argument if input value is not a valid number.
BigInt::BigInt(std::string other)
{
	bool sign = (other[0] == '-' ? false : true);

	std::string tempStr;
	for (int i = other.length(); i > 0 + !sign; i -= zerosNums)
	{
		if (i > zerosNums)
		{
			tempStr = other.substr(i - zerosNums, zerosNums);
			isValid(tempStr);
			this->number.push_back(std::stoi(tempStr, nullptr, 10));
		}
		else
		{
			tempStr = other.substr(!sign, i - !sign);
			isValid(tempStr);
			this->number.push_back(std::stoi(tempStr, nullptr, 10));
			break;
		}
	}

	this->sign = sign;
}

BigInt::BigInt(const BigInt& other)
{
	this->sign = other.sign;
	this->number = other.number;
}

BigInt::BigInt(unsigned int other)
{
	this->sign = (other < 0) ? false : true;
	this->number.push_back(other);
}

BigInt::operator int() const
{
	return this->number[0];
}

BigInt::operator std::string() const
{
	std::string outputValue, tempStr;

	if (this->number == this->zero) return outputValue += "0";
	if (!this->sign) outputValue.push_back('-');

	int currentSize = this->number.size() - 1;
	for (long long int i = currentSize; i >= 0; i--)
	{
		tempStr.erase();
		//Добавляем нули в числа, где необходимо
		if (this->number[i] == 0) tempStr = "000000000";
		else if (this->number[i] < (this->base / 10 - 1) && i != currentSize)
		{
			int temp = this->number[i], count = 0;
			while (temp < (this->base / 10 - 1) && i != currentSize)
			{
				temp *= 10;
				count++;
			}
			for (int j = 0; j < count; j++)
				tempStr += "0";
		}

		tempStr += std::to_string(this->number[i]);
		outputValue += tempStr;
	}
	return outputValue;
}

size_t BigInt::size() const
{
	//replace
	return this->number.size();
}

std::ostream& operator<<(std::ostream& o, const BigInt& i)
{
	std::string outputValue = std::string(i);
	for (long long i = 0; i < outputValue.size(); i++)
		o << outputValue[i];
	return o;
}

std::istream& operator>>(std::istream& o, const BigInt& i)
{
	BigInt& i_ref = const_cast<BigInt&>(i);
	std::string inputValue;

	o >> inputValue;
	i_ref = BigInt(inputValue);

	return o;
}

const BigInt& min(const BigInt& a, const BigInt& b)
{
	if (a <= b) return a;
	return b;
}

const BigInt& max(const BigInt& a, const BigInt& b)
{
	if (a < b) return b;
	return a;
}