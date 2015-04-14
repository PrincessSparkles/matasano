/*
 * Base64Encoder.cpp
 *
 * This file implements the Base64Encoder class
 *
 * 14-04-2015
 */
 
/* ************************************************************************ */

#include <iostream>
#include <memory>

#include "Base64Encoder.h"

/* ************************************************************************ */

/* static */
const char *Base64Encoder::base64Characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* ************************************************************************ */
/* ************************************************************************ */

std::vector<unsigned char> Base64Encoder::decode(const std::string &encoded)
{
	return Base64Encoder::Decode(encoded);
}

/* ************************************************************************ */

std::string Base64Encoder::encode(const std::vector<unsigned char> &data)
{
	return Base64Encoder::Encode(data);
}

/* ************************************************************************ */
/* ************************************************************************ */

/* static */
std::vector<unsigned char> Base64Encoder::Decode(const std::string &encoded)
{
	int len = encoded.length();
	if ((len % 4) != 0)
	{
		throw "[Base64Encoder::Decode] bad string length";
	}
	
	std::vector<unsigned char> result;
	for (int i = 0; i < len; i += 4)
	{
		char c1 = encoded[i];
		char c2 = encoded[i + 1];
		char c3 = encoded[i + 2];
		char c4 = encoded[i + 3];
		
		int tmp = (decodeBase64Character(c1) << 18) | (decodeBase64Character(c2) << 12) | (decodeBase64Character(c3) << 6) | decodeBase64Character(c4);
		
		// always process the first byte, then look at the equals to see about the rest
		result.push_back((tmp >> 16) & 0xff);
		
		if (c3 != '=')
		{
			// two equals => only one data byte
			result.push_back((tmp >> 8) & 0xff);
		}

		if (c4 != '=')
		{
			// one equals => two data bytes
			result.push_back(tmp & 0xff);
		}
	}

	return result;
}

/* ************************************************************************ */

/* static */
int Base64Encoder::decodeBase64Character(char c)
{
	int result = -1;
	
	int	i;
	for (i = 0; i < 64; i++)
	{
		if (Base64Encoder::base64Characters[i] == c)
		{
			result = i;
			break;
		}	
	}
	
	if (result == -1)
	{
		if (c == '=')
		{
			result = 0;
		}
		else
		{
			throw "[Base64Encoder::decodeBase64Character] non base-64 character";
		}
	}
	
	return result & 0x3f;
}

/* ************************************************************************ */

/* static */
std::string Base64Encoder::Encode(const std::vector<unsigned char> &data)
{
	std::string result;
	int len = data.size();
	int	i = 0;
	
	while ((i + 2) < len)
	{
		int tmp = (data[i] << 16) | (data[i + 1] << 8) | data[i + 2];
		
		int index1 = (tmp >> 18) & 0x3f;
		int index2 = (tmp >> 12) & 0x3f;
		int index3 = (tmp >> 6) & 0x3f;
		int index4 = tmp & 0x3f;
		
		result += Base64Encoder::base64Characters[index1];
		result += Base64Encoder::base64Characters[index2];
		result += Base64Encoder::base64Characters[index3];
		result += Base64Encoder::base64Characters[index4];
		
		i += 3;
	}
	
	if ((len % 3) == 1)
	{
		// one extra character
		int tmp = (data[i] << 16);
		
		int index1 = (tmp >> 18) & 0x3f;
		int index2 = (tmp >> 12) & 0x3f;
		
		result += Base64Encoder::base64Characters[index1];
		result += Base64Encoder::base64Characters[index2];
		result += "==";
	}
	else if ((len % 3) == 2)
	{
		// two extras
		int tmp = (data[i] << 16) | (data[i + 1] << 8);
		
		int index1 = (tmp >> 18) & 0x3f;
		int index2 = (tmp >> 12) & 0x3f;
		int index3 = (tmp >> 6) & 0x3f;
		
		result += Base64Encoder::base64Characters[index1];
		result += Base64Encoder::base64Characters[index2];
		result += Base64Encoder::base64Characters[index3];
		result += "=";
	}
	
	return result;
}

/* ************************************************************************ */
/* ************************************************************************ */

bool Base64EncoderTest(const std::vector<unsigned char> &data, const std::string &encoded)
{
	std::string resultString = Base64Encoder::Encode(data);
	if (resultString != encoded)
	{
		throw "Base64Encoder::Encode failed";
	}
	
	std::vector<unsigned char> resultData = Base64Encoder::Decode(encoded);
	
	if (resultData != data)
	{
		if (resultData.size() != data.size())
		{
			throw "Base64Encoder::Decode lengths differ";
		}
		
		for (unsigned int i = 0; i < resultData.size(); i++)
		{
			if (resultData[i] != data[i])
			{
				std::printf("failed at %d 0x%02x != 0x%02x", i, resultData[i], data[i]);
				throw "Base64Encoder::Decode mismatch";
			}
		}
		
		throw "Base64Encoder::Decode failed";
	}
	
	// now make sure the object interface works as well
	auto encoder = std::make_unique<Base64Encoder>();
	std::string resultString2 = encoder->encode(data);
	if (resultString != encoded)
	{
		throw "Base64Encoder::encode failed";
	}
	
	std::vector<unsigned char> resultData2 = encoder->decode(encoded);
	if (resultData2 != data)
	{
		throw "Base64Encoder::decode failed";
	}
	
	return true;
}

/* ************************************************************************ */

bool Base64EncoderDecodeExceptionTest(const std::string &bad_string)
{
	bool caught = false;
	
	try
	{
		std::vector<unsigned char> resultData = Base64Encoder::Decode(bad_string);
	}
	catch (const char *msg)
	{
		caught = true;
	}
	
	if (caught == false)
	{
		throw "Base64Encoder::Decode failed to throw";
	}
	
	return true;
} 

/* ************************************************************************ */

bool Base64EncoderTest()
{
	bool result = false;
	
	try
	{
		Base64EncoderDecodeExceptionTest("a");		// bad string length
		Base64EncoderDecodeExceptionTest("abcdef");	// bad string length
		Base64EncoderDecodeExceptionTest("abc");	// bad string length
		Base64EncoderDecodeExceptionTest("ab cd");	// would be valid if the whitespace weren't there!
		Base64EncoderDecodeExceptionTest("a b c d ");	// would be valid if the whitespace weren't there. but the basic string length is a multiple of 4,
														// so we're going to throw on non-base64 character instead

		std::vector<unsigned char> data1 = { 0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 
											 0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f, 0x75, 0x72, 
											 0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c, 
											 0x69, 0x6b, 0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 
											 0x69, 0x73, 0x6f, 0x6e, 0x6f, 0x75, 0x73, 0x20, 
											 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d };
		std::string encoded1 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
		
		Base64EncoderTest(data1, encoded1);
		
		// taken from RFC-4648
		std::vector<unsigned char> rfcData1;
		std::string rfcEncoded1 = "";
		std::vector<unsigned char> rfcData2 = { 'f' };
		std::string rfcEncoded2 = "Zg==";
		std::vector<unsigned char> rfcData3 = { 'f', 'o' };
		std::string rfcEncoded3 = "Zm8=";
		std::vector<unsigned char> rfcData4 = { 'f', 'o', 'o' };
		std::string rfcEncoded4 = "Zm9v";
		std::vector<unsigned char> rfcData5 = { 'f', 'o', 'o', 'b' };
		std::string rfcEncoded5 = "Zm9vYg==";
		std::vector<unsigned char> rfcData6 = { 'f', 'o', 'o', 'b', 'a' };
		std::string rfcEncoded6 = "Zm9vYmE=";
		std::vector<unsigned char> rfcData7 = { 'f', 'o', 'o', 'b', 'a', 'r' };
		std::string rfcEncoded7 = "Zm9vYmFy";

		Base64EncoderTest(rfcData1, rfcEncoded1);
		Base64EncoderTest(rfcData2, rfcEncoded2);
		Base64EncoderTest(rfcData3, rfcEncoded3);
		Base64EncoderTest(rfcData4, rfcEncoded4);
		Base64EncoderTest(rfcData5, rfcEncoded5);
		Base64EncoderTest(rfcData6, rfcEncoded6);
		Base64EncoderTest(rfcData7, rfcEncoded7);

		result = true;
	}
	catch (const char *msg)
	{
		std::cout << "Unhandled Exception" << std::endl;
		std::cout << msg << std::endl;
	}
	
	return result;
}

/* ************************************************************************ */
/* ************************************************************************ */
/* ************************************************************************ */
