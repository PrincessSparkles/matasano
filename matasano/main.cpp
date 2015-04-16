#include <iostream>

#include "HexEncoder.h"
#include "Base64Encoder.h"

using namespace std;

bool Test()
{
	if (HexEncoderTest() == false)
	{
		return false;
	}
	
	if (Base64EncoderTest() == false)
	{
		return false;
	}
	
	return true;
}

bool Set1Challenge1()
{
	std::string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	std::string expected = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
	
	std::vector<unsigned char> data = HexEncoder::Decode(input);
	std::string result = Base64Encoder::Encode(data);
	
	if (result == expected)
	{
		cout << "[set1] challenge 1 passed" << endl;
		return true;
	}
	else
	{
		cout << "[set1] challenge 1 failed" << endl;
		return false;
	}
}

int main (int argc, char *argv[])
{
	cout << "matasano" << endl;
	
	if (Test() == false)
	{
		return -1;
	}
	cout << "All tests pass" << endl;
	
	do
	{
		if (Set1Challenge1() == false)
		{
			break;
		}
		
		cout << "ALL CHALLENGES PASSED" << endl;
	}
	while (false);
		
	return 0;
}

