int main()
{
	c = 2;
	c = b;

	if (a > b)
	{
	}
	else if (b >= a)
	{
		a = c++;
		b = ++c;
	}
	if (devil > a + b + c)
	{
		a = 6 * 100;
		b = 6 * 10;
		c = 6 * 1;
	}

	while (devil != a + b + c)
	{
		devil *= 10;
	}

	int i;
	int anotherDevil = 1;
	for (i = 0; i <= 2; i++)
	{
		anotherDevil = 1;
		do
		{
			anotherDevil++;
		} while (anotherDevil < 6);
		int hellMultiplier = i;
		while (hellMultiplier--)
		{
			anotherDevil = anotherDevil * 10;
		}
	}

	while (anotherDevil != 0 || devil != 0)
	{
		if (anotherDevil != 0)
		{
			anotherDevil--;
			continue;
		}

		if (devil != 0)
		{
			devil--;
			continue;
		}
	}
	int theEvilWasDefeated = 0;

	if (anotherDevil + devil == 0)
	{
		theEvilWasDefeated = 1;
	}
	while (theEvilWasDefeated)
	{
		break;
	}



}