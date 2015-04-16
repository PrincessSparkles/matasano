/*
 * XOR.h
 *
 * This file contains the class definition for the XOR class
 *
 * 16-04-2015
 */
 
 #ifndef __XOR_H
 #define __XOR_H
 
/* ************************************************************************ */

#include <vector>

/* ************************************************************************ */

class XOR
{
public:
	XOR() = default;
	~XOR() = default;
	
	/*
	 * XOR the data with the key, repeating the key as necessary
	 */
	static std::vector<unsigned char> Xor(const std::vector<unsigned char> &data, const std::vector<unsigned char> &key);

protected:

private:
};

/* ************************************************************************ */

bool XorTest();

/* ************************************************************************ */

#endif  // __XOR_H
