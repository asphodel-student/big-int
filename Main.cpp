#include "BigInt.h"
#include <cassert>


int main()
{
	BigInt t("10000000000000");
	std::cout << t << std::endl;

	//Some tests
	BigInt a1("2704760917523510972930987743880103076470895356980355360720461615396161989555927024");
	BigInt b1("52746597834653657829586269547563475634875623784534");
	BigInt c1 = a1 / b1;
	BigInt div_ans("51278395736578236578236523765736");
	std::cout << c1 << std::endl;
	assert(c1 == div_ans);
	
	BigInt a2("51278395736578236578236523765736");
	BigInt b2("52746597834653657829586269547563475634875623784534");
	BigInt c2 = a2 * b2;
	BigInt mult_ans("2704760917523510972930987743880103076470895356980355360720461615396161989555927024");
	std::cout << c2 << std::endl;
	assert(c2 == mult_ans);

	BigInt a3("7325673965736473268965012635062347563875230536705");
	BigInt b3("25796485606345465736753647856347856937");
	BigInt c3 = a3 + b3;
	BigInt add_ans("7325673965762269754571358100799101211731578393642");
	std::cout << c3 << std::endl;
	assert(c3 == add_ans);

	BigInt a4("-7325673965736473268965012635062347563875230536705");
	BigInt b4("25796485606345465736753647856347856937");
	BigInt c4 = a4 + b4;
	BigInt add_ans2("-7325673965710676783358667169325593916018882679768");
	std::cout << c4 << std::endl;
	assert(c4 == add_ans2);

	BigInt a5("346756328564563456345632860984362578");
	BigInt b5("-5676576349785639475832");
	BigInt c5 = a5 - b5;
	BigInt min_ans("346756328564569132921982646623838410");
	std::cout << c5 << std::endl;
	assert(c5 == min_ans);

	BigInt a6("4379563205346053425083465037465830658340563484");
	BigInt b6("5763105623058632805675613");
	BigInt c6 = a6 % b6;
	BigInt rest_ans("1489735011801688045654534");
	std::cout << c6 << std::endl;
	assert(c6 == rest_ans);


	BigInt a7("-232423");
	BigInt b7("-36576");
	BigInt c7 = a7 ^ b7;
	std::cout << c7 << std::endl;
	std::cout << c7 << std::endl;

	BigInt a8("1");
	a8--;
	a8--;
	std::cout << a8 << std::endl;


	BigInt a9;
	std::cin >> a9;
	std::cout << a9;
	/*BigInt a8("47329657348658");
	std::cout << (~a8) << std::endl;*/

	return 0;
}

