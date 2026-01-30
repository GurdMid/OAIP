#include <iostream>
using namespace std;

struct Stack
{
	double info;
	Stack *next;
} *start, *t;

Stack* push(Stack*, int);
void View(Stack*);
void Del_All(Stack**);

Stack* push(Stack* p, int in)
{
	Stack* t = new Stack;			// Захватываем память для элемента
	t->info = in;			// Формируем информационную часть
	t->next = p;			// Формируем адресную часть
	return t;
}

void View(Stack* p) {
	Stack* t = p;
	while (t != NULL) {
		// Вывод на экран информационной части, например,
		cout <<  t -> info << endl;
		t = t->next;
	}
}
void Del_All(Stack** p) {
	Stack* t;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}
void problem(int& a)
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
		cout << "1 - cоздать" << endl << "2 - добавить" << endl << "3 - удалить" << endl << "иначе - выход" << endl;
}
double task(Stack* p)
{
    Stack* t = p;
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
void taskview(Stack** p)
{
    double average = task(*p);
    *p = push(*p, average);

    cout << "Стек после добавления среднего арифмитического: " << endl;
    View(*p);
}
int main()
{
    setlocale(LC_ALL, "RU");
    int k, n, in;

    do {
        Menu();
        problem(k);
        switch (k)
        {
        case 1:  
            cout << "Количество элементов: ";
            problem(n);
            cout << "Введите " << n << " элементов: ";
            for (int i = 0; i < n; i++)
            {
                problem(in);
                start = push(start, in);
            }
            View(start);
            break;
        case 2:  
            cout << "Введите элемент для добавления: ";
            problem(in);
            start = push(start, in); 
            View(start);
            break;
        case 3: 
            Del_All(&start);
            cout << "Стек удален" << endl;
            break;
        case 4: taskview(&start);
        default: 
            exit(0);
        }
        
    } while (k != 0);

    return 0;
}
