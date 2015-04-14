/*
 * HexEncoder.cpp
 *
 * This file implements the HexEncoder class
 *
 * 13-04-2015
 */
 
/* ************************************************************************ */

#include <iostream>
#include <memory>

#include "HexEncoder.h"

/* ************************************************************************ */

/* ************************************************************************ */
/* ************************************************************************ */

std::vector<unsigned char> HexEncoder::decode(const std::string &encoded)
{
	return HexEncoder::Decode(encoded);
}

/* ************************************************************************ */

std::string HexEncoder::encode(const std::vector<unsigned char> &data)
{
	return HexEncoder::Encode(data);
}

/* ************************************************************************ */
/* ************************************************************************ */

/* static */
std::vector<unsigned char> HexEncoder::Decode(const std::string &encoded)
{
	if ((encoded.length() % 2) == 1)
	{
		throw "[HexEncoder::Decode] Odd string length";
	}
	
	std::vector<unsigned char> result;
	for (std::string::const_iterator iter = encoded.begin(); iter != encoded.end(); iter++)
	{
		unsigned char tmp = HexEncoder::decodeHexChar(*iter);
		iter++;
		tmp <<= 4;
		tmp |= HexEncoder::decodeHexChar(*iter);
		
		result.push_back(tmp);
	}
	
	return result;
}

/* ************************************************************************ */

/* static */
unsigned char HexEncoder::decodeHexChar(char hex)
{
	unsigned char result;
	if (hex >= '0' && hex <= '9')
	{
		result = hex - '0';
	}
	else if (hex >= 'a' && hex <= 'f')
	{
		result = 0x0a + (hex - 'a');
	}
	else if (hex >= 'A' && hex <= 'F')
	{
		result = 0x0A + (hex - 'A');
	}
	else
	{
		throw "[HexEncoder::decodeHexChar] non-hex char detected";
	}
	
	return result;
}

/* ************************************************************************ */

/* static */
std::string HexEncoder::Encode(const std::vector<unsigned char> &data)
{
	std::string result;
	char tmp[3];
	
	for (std::vector<unsigned char>::const_iterator iter = data.begin(); iter != data.end(); iter++)
	{
		std::snprintf(tmp, sizeof(tmp), "%02x", *iter);
		result += tmp;	
	}
	
	return result;
}

/* ************************************************************************ */
/* ************************************************************************ */

bool HexEncoderTest(const std::vector<unsigned char> &data, const std::string &encoded)
{
	// test the static interface
	std::string resultString = HexEncoder::Encode(data);
	if (resultString != encoded)
	{
		throw "HexEncoder::Encode failed";
	}
	
	std::vector<unsigned char> resultData = HexEncoder::Decode(encoded);
	
	if (resultData != data)
	{
		if (resultData.size() != data.size())
		{
			throw "HexEncoder::Decode lengths differ";
		}
		
		for (unsigned int i = 0; i < resultData.size(); i++)
		{
			if (resultData[i] != data[i])
			{
				std::printf("failed at %d 0x%02x != 0x%02x", i, resultData[i], data[i]);
				throw "HexEncoder::Decode mismatch";
			}
		}
		
		throw "HexEncoder::Decode failed";
	}
	
	// now make sure the object interface works as well
	auto encoder = std::make_unique<HexEncoder>();
	std::string resultString2 = encoder->encode(data);
	if (resultString != encoded)
	{
		throw "HexEncoder::encode failed";
	}
	
	std::vector<unsigned char> resultData2 = encoder->decode(encoded);
	if (resultData2 != data)
	{
		throw "HexEncoder::decode failed";
	}
	
	return true;
}

/* ************************************************************************ */

bool HexEncoderDecodeExceptionTest(const std::string &bad_string)
{
	bool caught = false;
	
	try
	{
		std::vector<unsigned char> resultData = HexEncoder::Decode(bad_string);
	}
	catch (const char *msg)
	{
		caught = true;	// we're expecting an exception here
	}
	
	if (caught == false)
	{
		throw "HexEncoder::Decode failed to throw";
	}
	
	return true;
} 

/* ************************************************************************ */

bool HexEncoderTest()
{
	bool result = false;
	
	try
	{
		std::string oddStringLength = "49276d2";
		HexEncoderDecodeExceptionTest(oddStringLength);
		
		std::string nonHexCharacters1 = "49276d!0";	// non-hex char first in pair
		HexEncoderDecodeExceptionTest(nonHexCharacters1);

		std::string nonHexCharacters2 = "49276$20";	// non-hex char second in pair
		HexEncoderDecodeExceptionTest(nonHexCharacters2);
		
		std::vector<unsigned char> data1 = { 0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 
											 0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f, 0x75, 0x72, 
											 0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c, 
											 0x69, 0x6b, 0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 
											 0x69, 0x73, 0x6f, 0x6e, 0x6f, 0x75, 0x73, 0x20, 
											 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d };
		std::string encoded1 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
		
		HexEncoderTest(data1, encoded1);
		
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
