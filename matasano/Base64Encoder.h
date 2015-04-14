/*
 * Base64.h
 *
 * This file contains the class definition for the Base64Encoder class
 *
 * 14-04-2015
 */
 
 #ifndef __BASE64_ENCODER_H
 #define __BASE64_ENCODER_H
 
 /* ************************************************************************ */

#include "TextEncoder.h"

/* ************************************************************************ */

class Base64Encoder : public TextEncoder
{
public:
	Base64Encoder() = default;
	~Base64Encoder() = default;
	
	/*
	 * decode function
	 *
	 * Takes a string of base64 characters, and produces a blob of binary data
	 */
	std::vector<unsigned char> decode(const std::string &encoded); 

	/*
	 * encode function
	 *
	 * takes a blob of binary data, and produces a base64 string
	 */
	std::string encode(const std::vector<unsigned char> &data);
	
	/*
	 * static decode function
	 *
	 * Decode function provided to allow a better interface to the Base64Encoder
	 */
	static std::vector<unsigned char> Decode(const std::string &encoded);

	/*
	 * static encode function
	 *
	 * Encode function provided to allow a better interface to the Base64Encoder
	 */
	static std::string Encode(const std::vector<unsigned char> &data);

protected:

private:
};

/* ************************************************************************ */

bool Base64EncoderTest();

/* ************************************************************************ */
 
 #endif  // __BASE64_ENCODER_H
