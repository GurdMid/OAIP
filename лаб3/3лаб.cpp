#include <iostream>
using namespace std;

struct Spis2 {
	double info;
	Spis2* prev, * next;
} *begin, *end;

void Create(Spis2** begin, Spis2** end, double in)
{
	Spis2* t = new Spis2;
	t->info = in;                 
	t->prev = NULL;
	t->next = NULL;
	*begin = t;                   
	*end = t;                   
}
void Spisb(Spis2** begin, double in)
{
	Spis2* t = new Spis2;           
	t->info = in;                   
	t->prev = NULL;
	t->next = *begin;   

	if (*begin != NULL)
		(*begin)->prev = t;    
	
	*begin = t;                   
}
void Spise(Spis2** end, double in)
{
	Spis2* t = new Spis2;        
	t->info = in;                   
	t->next = NULL;
	t->prev = *end;   

	if (*end != NULL)
		(*end)->next = t;  
	*end = t;                       
}

void Viewb(Spis2* begin) {
	cout << endl;
	Spis2* t = begin;
	while (t != NULL) {

		cout << t->info << endl;
		t = t->next;
	}
}
	cout << t->info << endl;
	recurs(t->next);
}

void Viewe(Spis2* end) {
	cout << endl;
	Spis2* t = end;

	while (t != NULL) {
	
		cout << t->info << endl;
		t = t->prev;
	}
}
void Del_All(Spis2** begin) {
	Spis2* t;
	while (*begin != NULL) {
		t = *begin;
		*begin = (*begin)->next;
		delete t;
	}
}
void problem(double& a)
{
	while (1)
	{
		if (!(cin >> a))
		{
			cout << "Неверный ввод" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		else break;
	}
}
void Menu()
{
	cout << endl << "1 - cоздать" << endl << "2 - добавить в начало" << endl << "3 - добавить в конец" << endl << "4 - просмотр с начала" << endl
		<< "5 - просмотр с конца" << endl << "6 - удалить" << endl << "7 - среднее арифимитическое" << endl << "иначе - выход" << endl;
}
double task(Spis2* begin)
{
	Spis2* t = begin;
	double sum = 0, count = 0;

	while (t != NULL)
	{
		sum += t->info;
		count++;
		t = t->next;
	}
	double average = sum / count;
	return average;
}
void taskview(Spis2** begin, Spis2** end) 
{
	if (*begin == NULL)
	{
		cout << "Cписок пуст";
		return;	
	}

	double average = task(*begin);
	(*begin)->info = average;

	Viewb(*begin);                     
}

int main()
{
	
	Spis2* begin = NULL;
	Spis2* end = NULL;
	Spis2* t = begin;
    setlocale(LC_ALL, "RU");
	double n, in;
	int k;

	do {
		Menu();
		cin >> k;
		switch (k)
		{
		case 1:
			cout << "Количество элементов: ";
			problem(n);
			cout << "Введите " << n << " элементов: ";
			problem(in);
			Create(&begin, &end, in);
			for (int i = 1; i < n; i++)
			{
				problem(in);
				Spise(&end, in);
			}
			Viewb(begin);
			break;
		case 2:
			cout << "Введите элемент для добавления в начале: ";
			problem(in);
			Spisb(&begin, in);
			break;
		case 3:
			cout << "Введите элемент для добавления в конце: ";
			problem(in);
			Spise(&end, in);
			break;
		case 4:		
			Viewb(begin);
			break;
		case 5:
			Viewe(end);
			break;
		case 6:
			Del_All(&begin);
			cout << "Список удален" << endl;
			break;
		case 7:
			taskview(&begin, &end); break;
		default:
			Del_All(&begin);
			cout << "Список удален" << endl;
			exit(0);
		}

	} while (k != 0);
	
    return 0;
}
