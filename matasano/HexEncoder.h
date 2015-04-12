/*
 * HexEncoder.h
 *
 * This file contains the class definition for the HexEnocder class
 *
 * 13-04-2015
 */
 
 #ifndef __HEX_ENCODER_H
 #define __HEX_ENCODER_H
 
 /* ************************************************************************ */

#include "TextEncoder.h"

/* ************************************************************************ */

class HexEncoder : public TextEncoder
{
public:
	HexEncoder() = default;
	~HexEncoder() = default;
	
	/*
	 * decode function
	 *
	 * Takes a string of hex characters, and produces a blob of binary data
	 */
	std::vector<unsigned char> decode(const std::string &encoded); 

	/*
	 * encode function
	 *
	 * takes a blob of binary data, and produces a string of hex characters
	 */
	std::string encode(const std::vector<unsigned char> &data);
	
	/*
	 * static decode function
	 *
	 * Decode function provided to allow a better interface to the HexEncoder
	 */
	static std::vector<unsigned char> Decode(const std::string &encoded);

	/*
	 * static encode function
	 *
	 * Encode function provided to allow a better interface to the HexEncoder
	 */
	static std::string Encode(const std::vector<unsigned char> &data);

protected:

private:
};

/* ************************************************************************ */
 
 #endif  // __HEX_ENCODER_H
