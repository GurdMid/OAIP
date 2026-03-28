#include <iostream>
using namespace std;

struct Stack {
    char info;
    Stack* next;
} *start;

void Del_All(Stack** p) {
    Stack* t;
    while (*p != NULL) {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}
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
} *start1;

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
void Del_All2(NumStack** p) {
    NumStack* t;
    while (*p != NULL) {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}
double values[26];

void perevod(char* mass, char* opz)
{
    Stack* st = NULL;
    int j = 0;
    for (int i = 0; mass[i] != '\0'; i++)
    {
        char in = mass[i];
        if (in == ' ') continue;

        if (in == '(')                  // скобка в стек
            st = push(st, in);

        else if (in == ')')
        {
            while (st != NULL && top(st) != '(')         // записываем в опз операторы из стека до откр.скобки
            {
                opz[j++] = top(st);
                st = pop(st);
            }
            if (st != NULL) st = pop(st);               // удаляем (
        }

        else if (in == '+' || in == '-')
        {
            while (st != NULL && top(st) != '(' && top(st) != '^')
            {
                opz[j++] = top(st);
                st = pop(st);
            }
            st = push(st, in);   // засовываем в стек +-
        }

        else if (in == '*' || in == '/')
        {
            // */
            while (st != NULL && top(st) != '(' && top(st) != '+' && top(st) != '-' && top(st) != '^')
            {
                opz[j++] = top(st);
                st = pop(st);
            }
            st = push(st, in);
        }

        else if (in == '^')
        {
            //вытаскиваем только ^
            while (st != NULL && top(st) == '^')
            {
                opz[j++] = top(st);
                st = pop(st);
            }
            st = push(st, in);
        }

        else
            opz[j++] = in; 
    }

    while (st != NULL)
    {
        opz[j++] = top(st); // вытаскиваем всё из стека и пишем в опз
        st = pop(st);
    }
    opz[j] = '\0';
}

double calc(char* opz)
{
    for (int i = 0; opz[i] != '\0'; i++)
    {
        if (opz[i] == ' ') continue;

        if (opz[i] >= 'a' && opz[i] <= 'z')
            numStack = pushNum(numStack, values[opz[i] - 'a']);
        else if (opz[i] == '+' || opz[i] == '-' || opz[i] == '*' || opz[i] == '/' || opz[i] == '^')
        {
            double right_val = numStack->info;
            numStack = popNum(numStack);

            double left_val = numStack->info;
            numStack = popNum(numStack);

            double result;
            switch (opz[i])
            {
            case '+': result = left_val + right_val; break;
            case '-': result = left_val - right_val; break;
            case '*': result = left_val * right_val; break;
            case '/':
                if (right_val == 0)
                {
                    cout << "Ошибка: деление на ноль!" << endl;
                    return 0;
                }
                result = left_val / right_val; break;
            case '^':
                result = pow(left_val, right_val); break;  
            default: result = 0;
            }
            //результат обратно в стек
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
    setlocale(LC_ALL, "RU");

    char mass[100];
    char opz[100];
    bool used[26] = {false}; 

    cout << "Введите выражение: ";
    cin.getline(mass, 100);

    perevod(mass, opz);
    cout << endl << "Обратная польская запись: " << opz << endl;

    for (int i = 0; opz[i] != '\0'; i++) 
    {
        if (opz[i] >= 'a' && opz[i] <= 'z') 
            used[opz[i] - 'a'] = true;
    }

    // Запрашиваем значени
    for (int i = 0; i < 26; i++)
    {
        if (used[i]) {
            char letter = 'a' + i;
            cout << "Введите " << letter << ": ";
            while (!(cin >> values[i])) {
                cout << "Ошибка! Введите число: ";
                cin.clear();
                cin.ignore(100, '\n');
            }
        }
    }

    cout << "Результат: " << calc(opz) << endl;

    Del_All(&start);
    Del_All2(&start1);
    return 0;
}