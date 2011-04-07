#include <time.h>
#include <iostream.h>

int main(int argc, char* argv[])
{			 
	char buf[128];

	cout << _strtime(buf) << endl;
	cout << _strdate(buf) << endl;

	return 0;
}
