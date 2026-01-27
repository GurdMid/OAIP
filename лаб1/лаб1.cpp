#include <iostream>
using namespace std;

double funct(int a)
{
	double rez;
	if (a == 1)
		return 1.0 / (1.0 + 1.0 / 2.0);

	rez = 1.0 / (a + funct(a-1));
}

int main()
{
	setlocale(LC_ALL, "RU");
	int n;
	while (1)
	{
		cout << "Введите n: ";
		if (!(cin >> n) || n <= 1)
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		else break;	
	}
	cout << funct(n) << endl;

	return 0;
}

