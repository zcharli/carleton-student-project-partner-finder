#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
using namespace std;

typedef chrono::high_resolution_clock Clock;

void maximumThreeNumbersInList(int*, int, int*);

void setUpList(int** list, string input, int count)
{
	ifstream file;
	file.open(input);

	*list = new int[count];
	int number;
	int i = 0;
	while (file >> number && i < count)
	{
		(*list)[i] = number;
		i++;
	}
}

int main()
{
	ofstream resultFile;
	resultFile.open("result.txt");

	int *list = NULL;
	int answerList[3] = {9, 7, 6};
	int maxThreeList[3];

	//setup for correctness
	setUpList(&list, "test01.in", 10);
	maximumThreeNumbersInList(list, 10, maxThreeList);
	delete [] list;
	for (int i = 0; i < 3; i++)
	{
	  	if (answerList[i] != maxThreeList[i])
		{
			resultFile << "Incorrect Implementation" << endl;
			exit(-1);
		}
	}

	//setup for efficiency
	#define SLOWEST_TIME 2500
	setUpList(&list, "test02.in", 5000000);
	auto t1 = Clock::now();
	maximumThreeNumbersInList(list, 5000000, maxThreeList);
	auto t2 = Clock::now();
	resultFile << (SLOWEST_TIME-(double(chrono::duration_cast<chrono::milliseconds>(t2-t1).count())))/SLOWEST_TIME * 100.0;
}
