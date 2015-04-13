#include <iostream>

#include "HexEncoder.h"

using namespace std;

bool Test()
{
	if (HexEncoderTest() == false)
	{
		return false;
	}
	
	return true;
}

int main (int argc, char *argv[])
{
	cout << "matasano" << endl;
	
	if (Test() == false)
	{
		return -1;
	}
	cout << "All tests pass" << endl;
	
	return 0;
}

