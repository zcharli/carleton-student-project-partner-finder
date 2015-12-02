void maximumThreeNumbersInList(int*list, int count, int*maxThree)
{
	maxThree[0] = -999999;
	maxThree[1] = -999999;
	maxThree[2] = -999999;
	for (int i = 0; i < count; i++)
	{
		if (list[i] > maxThree[0])
		{
			maxThree[2] = maxThree[1];
			maxThree[1] = maxThree[0];
			maxThree[0] = list[i];
		}
		else if(list[i] > maxThree[1])
		{
			maxThree[2] = maxThree[1];
			maxThree[1] = list[i];
		}
		else if(list[i] > maxThree[2])
		{
			maxThree[2] = list[i];
		}
	}
}
