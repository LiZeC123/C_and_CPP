#include <fstream>
#include "zz\StatementList.h"

int main()
{
	std::ifstream inf("input.txt");
	StatementList R(inf);

	R.Run();

	return 0;
}



