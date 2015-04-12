/*
 * TextEncoder.h
 *
 * This file contains the definition for the TextEncoder class
 *
 * 12-04-2015
 */
 
#ifndef __TEXT_ENCODER_H
#define __TEXT_ENCODER_H

/* ************************************************************************ */

#include <vector>
#include <string>

/* ************************************************************************ */

/*
 * virtual class providing an abstract definition of the TextEncoder.
 * Using a pure-virtual class, as interfaces are not available in C++ (to the best of my knowledge)
 */
class TextEncoder
{
public:
	/*
	 * destructor
	 */
	virtual ~TextEncoder() = default;
	
	/*
	 * Decode function
	 *
	 * Takes a string of characters, and produces a blob of bytes
	 */
	virtual std::vector<unsigned char> decode(const std::string &encoded) = 0;
	
	/*
	 * Encode function
	 *
	 * Takes a blob of bytes, and produces a string of characters
	 */
	virtual std::string encode(const std::vector<unsigned char> &data) = 0;

protected:

private:
};

/* ************************************************************************ */

#endif  // __TEXT_ENCODER_H
