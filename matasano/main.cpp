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
	
	if (Test())
	{
		return -1;
	}
	
	return 0;
}

