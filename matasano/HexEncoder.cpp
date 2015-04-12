/*
 * HexEncoder.cpp
 *
 * This file implements the HexEncoder class
 *
 * 13-04-2015
 */
 
/* ************************************************************************ */

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
	throw "HexEncoder::Decode: not implemented";
}

/* ************************************************************************ */

/* static */
std::string HexEncoder::Encode(const std::vector<unsigned char> &data)
{
	throw "HexEncoder::Encode: not implemented";
}

/* ************************************************************************ */
/* ************************************************************************ */
/* ************************************************************************ */
