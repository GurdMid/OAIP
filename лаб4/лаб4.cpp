#include <iostream>
using namespace std;

struct Stack {
    char info;
    Stack* next;
} *begin;

Stack* push(Stack* p, char in)
{
	Stack* t = new Stack;			
	t->info = in;			
	t->next = p;		
	return t;
}

Stack* pop(Stack* p) {
    if (p == NULL) return NULL;
    Stack* t = p->next;
    delete p;
    return t;
}

char top(Stack* p) {
    if (p == NULL) return '\0';
    return p->info;
}

struct NumStack {
    double info;
    NumStack* next;
};

NumStack* numStack = NULL;


NumStack* pushNum(NumStack* p, double val) {
    NumStack* t = new NumStack;
    t->info = val;
    t->next = p;
    return t;
}

NumStack* popNum(NumStack* p) {
    if (p == NULL) return NULL;
    NumStack* t = p->next;
    delete p;
    return t;
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

void perevod(char* mass, char* opz)
{
    Stack* st = NULL;
    int j = 0;
    for (int i = 0; mass[i] != '\0'; i++)
    {
        char in = mass[i];
        if (in == ' ') continue;

        if (in == '(')                  //скобка в стек
            st = push(st, in);
        
        else if (in == ')')
        {
            while (st != NULL && top(st) != '(')         //записываем в опз опреаторы из стека до откр.скобки
            {
                opz[j++] = top(st);
                st = pop(st);
            }
            if (st != NULL) st = pop(st);               // удаляем (
        }

        else if (in == '+' || in == '-')       
        {
            while (st != NULL && (top(st) == '*' || top(st) == '/' || top(st) == '+' || top(st) == '-'))  //вытаскиваем +-*/ из стека
            {
                opz[j++] = top(st);     
                st = pop(st);
            }
            st = push(st, in);   //засовывавем в стек +-
        }

        else if (in == '*' || in == '/') 
        {
            while (st != NULL && (top(st) == '*' || top(st) == '/'))
            {
                opz[j++] = top(st);
                st = pop(st);
            }
            st = push(st, in);
        }
        else 
            opz[j++] = in; //буква в опз

    }

    while (st != NULL) 
    {
        opz[j++] = top(st);//вытаскиваем всё из стека и пишем в опз, чистка стека
        st = pop(st);
    }
    opz[j] = '\0';
}

double calc(char* opz, double a, double b, double c, double d, double e)
{
    for (int i = 0; opz[i] != '\0'; i++)
    {
        if (opz[i] == ' ') continue;

        if (opz[i] >= 'a' && opz[i] <= 'e')
        {
            double val;
            switch (opz[i]) 
            {
            case 'a': val = a; break;
            case 'b': val = b; break;
            case 'c': val = c; break;
            case 'd': val = d; break;
            case 'e': val = e; break;
            default: val = 0;
            }
            numStack = pushNum(numStack, val);
        }
        else if (opz[i] == '+' || opz[i] == '-' || opz[i] == '*' || opz[i] == '/') 
        {
            // Достаём из стека правый операнд (последний положенный)
            double b_val = numStack->info;      // берём значение с вершины стека
            numStack = popNum(numStack);        // удаляем вершину стека

            // Достаём из стека левый операнд (предпоследний)
            double a_val = numStack->info;      // новое значение на вершине — это левый операнд
            numStack = popNum(numStack);            

            double result;
            switch (opz[i]) 
            {
            case '+': result = a_val + b_val; break;
            case '-': result = a_val - b_val; break;
            case '*': result = a_val * b_val; break;
            case '/': result = a_val / b_val; break;
            default: result = 0;
            }
            // Кладём результат обратно в стек
            numStack = pushNum(numStack, result);
        }
    }
    double result = numStack->info;

    while (numStack != NULL) 
       numStack = popNum(numStack);
    
    return result;
}

int main()
{
    double a, b, c, d, e;
    setlocale(LC_ALL, "RU");

    char mass[100];
    char opz[100];

	cout << "Введите выражение: ";
	cin.getline(mass, 100);

    perevod(mass, opz);
    cout << endl << opz << endl;

    cout << "Введите a: " << endl;
    problem(a);
    cout << "Введите b: " << endl;
    problem(b);
    cout << "Введите c: " << endl;
    problem(c);
    cout << "Введите d: " << endl;
    problem(d);
    cout << "Введите e: " << endl;
    problem(e);

   calc(opz, a, b, c, d, e);


    return 0;
}
