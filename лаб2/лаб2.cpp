#include <iostream>
using namespace std;

struct Stack
{
	double info;
	Stack *next;
} *start, *t;

Stack* push(Stack* p, int in)
{
	Stack* t = new Stack;			// Захватываем память для элемента
	t->info = in;			// Формируем информационную часть
	t->next = p;			// Формируем адресную часть
	return t;
}

void View(Stack* p) {
	Stack* t = p;
    cout << '\n';
	while (t != NULL) {
		// Вывод на экран информационной части
		cout <<  t -> info << endl;
		t = t->next;
	}
    cout << '\n';
}
void Del_All(Stack** p) {
	Stack* t;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
    cout << endl << "Стек очищен" << endl << endl;
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

void Sort_p(Stack** p) {
    Stack* t = NULL, * t1, * r;
    if ((*p)->next->next == NULL) return;
    do {
        for (t1 = *p; t1->next->next != t; t1 = t1->next)
            if (t1->next->info > t1->next->next->info)
            {
                r = t1->next->next;
                t1->next->next = r->next;
                r->next = t1->next;
                t1->next = r;
            }
        t = t1->next;
    } while ((*p)->next->next != t);
    cout << endl;
    View(start);
}
void Sort_info(Stack* p) {
    Stack* t = NULL, * t1;
    int r;
    do {
        for (t1 = p; t1->next != t; t1 = t1->next)
            if (t1->info > t1->next->info) 
            {
                r = t1->info;
                t1->info = t1->next->info;
                t1->next->info = r;
            }
        t = t1;
    } while (p->next != t);
    View(start);
}

void Menu()
{
		cout << "1 - cоздать" << endl << "2 - добавить" << endl << "3 - удалить" << endl << "4 - Задание" << endl << "5 - Сортировка 1" << endl
            << "6 - Сортировка 2" << endl << "иначе - выход" << endl;
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
    (*p)->info = average;

    cout << "Стек после добавления среднего арифмитического: " << endl;
    View(*p);
}

int main()
{
    setlocale(LC_ALL, "RU");
    int k, n, in;

    do {
        Menu();
        cin >> k;
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
            break;
        case 4: taskview(&start); break;
        case 5: Sort_p(&start); break;
        case 6: Sort_info(start); break;
        default: 
            break;
        }
        
    } while (k != 0);
    Del_All(&start);
    return 0;
}
