/*
 * HexEncoder.cpp
 *
 * This file implements the HexEncoder class
 *
 * 13-04-2015
 */
 
/* ************************************************************************ */

#include <iostream>

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
	throw "[HexEncoder::Decode] Not implemented";
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

bool HexEncoderTest(const std::vector<unsigned char> &data, std::string encoded)
{
	std::string resultString = HexEncoder::Encode(data);
	if (resultString != encoded)
	{
		throw "HexEncoder::Encode failed";
	}
	
	std::vector<unsigned char> resultData = HexEncoder::Decode(encoded);
	if (resultData != data)
	{
		throw "HexEncoder::Decode failed";
	}
	
	return true;
}

/* ************************************************************************ */

bool HexEncoderTest()
{
	bool result = false;
	
	try
	{
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
