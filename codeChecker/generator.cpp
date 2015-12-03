#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
	int count = atoi(argv[1]);

	//make random file 1 for correctnes
	for (int i = 0; i < count; i++)
	{
		cout << rand() % count<<endl;
	}
}
