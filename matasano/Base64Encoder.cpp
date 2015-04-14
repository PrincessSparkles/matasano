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
	throw "[Base64Encoder::Decode] Not implemented";
}

/* ************************************************************************ */

/* static */
std::string Base64Encoder::Encode(const std::vector<unsigned char> &data)
{
	throw "[Base64Encoder::Encode] Not implemented";
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
		std::vector<unsigned char> data1 = { 0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 
											 0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f, 0x75, 0x72, 
											 0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c, 
											 0x69, 0x6b, 0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 
											 0x69, 0x73, 0x6f, 0x6e, 0x6f, 0x75, 0x73, 0x20, 
											 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d };
		std::string encoded1 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
		
		Base64EncoderTest(data1, encoded1);
		
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
