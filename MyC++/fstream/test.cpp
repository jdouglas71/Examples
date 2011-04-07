/**
* FStream Example
*
*/
#include <iostream.h>
#include <fstream.h>

int main(int argc, char* argv[])
{
	ofstream ofile( "jasond.tmp", ios::app );

	ofile << "Jason is really the coolest guy on the planet" << endl;
	ofile.flush();
	ofile.close();


	return 0;
}
