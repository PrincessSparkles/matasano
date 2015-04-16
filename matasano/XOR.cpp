/*
 * XOR.cpp
 *
 * This file implements the XOR class
 *
 * 16-04-2015
 */
 
/* ************************************************************************ */

#include <iostream>

#include "HexEncoder.h"
#include "XOR.h"

/* ************************************************************************ */

/* ************************************************************************ */
/* ************************************************************************ */

/* static */
std::vector<unsigned char> XOR::Xor(const std::vector<unsigned char> &data, const std::vector<unsigned char> &key)
{
	int keylen = key.size();
	
	if (keylen == 0)
	{
		throw "[XOR::Xor] zero-length key";
	}
	
	int keyidx = 0;
	
	std::vector<unsigned char> result;
	
	for (std::vector<unsigned char>::const_iterator iter = data.begin(); iter != data.end(); iter++)
	{
		unsigned char keyval = key[keyidx];
		keyidx++;
		if (keyidx == keylen)
		{
			// off the end of the key - so wrap back round to the start
			keyidx = 0;
		}
		
		result.push_back(*iter ^ keyval);
	}
	
	return result;
}

/* ************************************************************************ */
/* ************************************************************************ */

bool XorTest()
{
	std::vector<unsigned char> data = HexEncoder::Decode("1c0111001f010100061a024b53535009181c");
	std::vector<unsigned char> key = HexEncoder::Decode("686974207468652062756c6c277320657965");
	std::vector<unsigned char> expected = HexEncoder::Decode("746865206b696420646f6e277420706c6179");
	
	std::vector<unsigned char> result = XOR::Xor(data, key);
	
	if (result != expected)
	{
		if (result.size() != expected.size())
		{
			std::cout << "XOR::Xor lengths differ" << std::endl;
		}
		else
		{
			for (unsigned int i = 0; i < result.size(); i++)
			{
				if (result[i] != expected[i])
				{
					std::printf("failed at %d 0x%02x != 0x%02x\n", i, result[i], expected[i]);
				}
			}
		}
				
		std::cout << "[XOR] Bad result from XOR::Xor" << std::endl;
		return false;
	}
	
	try
	{
		result = XOR::Xor(data, HexEncoder::Decode(""));
		std::cout << "[XOR] failed to throw on zero length key" << std::endl;
		return false;		
	}
	catch (const char *msg)
	{
		// we caught the expected exception - this is good :-)
	}
	
	return true;
}

/* ************************************************************************ */
/* ************************************************************************ */
/* ************************************************************************ */
