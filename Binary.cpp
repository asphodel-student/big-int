#include "BigInt.h"

int _2_divide(std::vector<int>& a) 
{
	int carry = 0, b = 2;
	for (int i = a.size() - 1; i >= 0; --i)
	{
		long long cur = a[i] + carry * 1LL * 1000000000; 
		a[i] = static_cast<int>(cur / b);
		carry = static_cast<int>(cur % b);
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();

	return carry;
}

//Convert BigInt to 2^30 base number
static std::vector<int> _to_2_30Base(BigInt& a)
{
	int count_bits = 0;
	std::vector<int> _currentNumCopy(a.number);
	std::vector<int> num_2_30Base;

	num_2_30Base.reserve(a.number.size() * 2);
	while (_currentNumCopy[0] >= 1)
	{
		int carry = _2_divide(_currentNumCopy);
		if (count_bits / 30 >= num_2_30Base.size())
			num_2_30Base.push_back((a.sign) ? carry : ~carry);
		else
			num_2_30Base[count_bits / 30] ^= (carry << (count_bits % 30));

		count_bits++;
	}
	
	if (!a.sign) num_2_30Base[0]++;

	return num_2_30Base;
}

//Inversing number
BigInt BigInt::operator~() const
{
	BigInt outputValue;
	switch (this->sign)
	{
		case(true):
			outputValue = (*this + BigInt(1));
			outputValue.sign = false;
			break;

		case(false):
			outputValue = (*this - BigInt(1));
			outputValue.sign = true;
			break;
	}
		
	return outputValue;
}

//Bitwise 'and'
BigInt operator&(const BigInt& a, const BigInt& b)
{
	BigInt outputValue(0), outputValue_2_30, _2_30Base("1073741824");
	BigInt& _a = const_cast<BigInt&>(a), &_b = const_cast<BigInt&>(b);

	//Convert to 2^30 base
	std::vector<int> a_2_30 = _to_2_30Base(_a);
	std::vector<int> b_2_30 = _to_2_30Base(_b);

	//Adding additional 0 or -1 if needed
	while (a_2_30.size() < b_2_30.size()) a_2_30.push_back((a.sign) ? 0 : 0xFFFFFFFF);
	while (a_2_30.size() > b_2_30.size()) b_2_30.push_back((b.sign) ? 0 : 0xFFFFFFFF);
	
	for (int i = 0; i < a_2_30.size(); i++)
		outputValue_2_30.number.push_back((a_2_30[i] & b_2_30[i]));
	
	outputValue_2_30.removeLeadingZeros();

	//Convert back to 10^9 base
	for (int i = 0; i < outputValue_2_30.number.size(); i++)
		outputValue += (BigInt(outputValue_2_30.number[i]) * powBI(_2_30Base, BigInt(i)));

	outputValue.sign = a.sign || b.sign;
	
	return outputValue;
}

//Bitwise 'or'
BigInt operator|(const BigInt& a, const BigInt& b)
{
	BigInt outputValue(0), outputValue_2_30, _2_30Base("1073741824");
	BigInt& _a = const_cast<BigInt&>(a), & _b = const_cast<BigInt&>(b);

	//Convert to 2^30 base
	std::vector<int> a_2_30 = _to_2_30Base(_a);
	std::vector<int> b_2_30 = _to_2_30Base(_b);

	//Adding additional 0 or -1 if needed
	while (a_2_30.size() < b_2_30.size()) a_2_30.push_back((a.sign) ? 0 : 0xFFFFFFFF);
	while (a_2_30.size() > b_2_30.size()) b_2_30.push_back((b.sign) ? 0 : 0xFFFFFFFF);

	for (int i = 0; i < a_2_30.size(); i++)
		outputValue_2_30.number.push_back((a_2_30[i] | b_2_30[i]));

	outputValue_2_30.removeLeadingZeros();

	//Convert back to 10^9 base
	for (int i = 0; i < outputValue_2_30.number.size(); i++)
		outputValue += (BigInt(outputValue_2_30.number[i]) * powBI(_2_30Base, BigInt(i)));

	outputValue.sign = a.sign && b.sign;

	return outputValue;
}

//Xor
BigInt operator^(const BigInt& a, const BigInt& b)
{
	BigInt outputValue(0), outputValue_2_30, _2_30Base("1073741824");

	BigInt& _a = const_cast<BigInt&>(a),
		& _b = const_cast<BigInt&>(b);

	//Convert to 2^30 base
	std::vector<int> a_2_30 = _to_2_30Base(_a);
	std::vector<int> b_2_30 = _to_2_30Base(_b);

	//Adding additional 0 or -1 if needed
	while (a_2_30.size() < b_2_30.size()) a_2_30.push_back((a.sign) ? 0 : 0xFFFFFFFF);
	while (a_2_30.size() > b_2_30.size()) b_2_30.push_back((b.sign) ? 0 : 0xFFFFFFFF);

	for (int i = 0; i < a_2_30.size(); i++)
		outputValue_2_30.number.push_back((a_2_30[i] ^ b_2_30[i]));

	//Remove leading zeroes
	outputValue_2_30.removeLeadingZeros();

	//Convert back to 10^9 base
	for (int i = 0; i < outputValue_2_30.number.size(); i++)
		outputValue += (BigInt(outputValue_2_30.number[i]) * powBI(_2_30Base, BigInt(i)));

	outputValue.sign = !(a.sign ^ b.sign);

	return outputValue;
}

BigInt& BigInt::operator&=(const BigInt& other)
{
	return *this = *this & other;
}

BigInt& BigInt::operator|=(const BigInt& other)
{
	return *this = *this | other;
}


BigInt& BigInt::operator^=(const BigInt& other)
{
	return *this = *this ^ other;
}
