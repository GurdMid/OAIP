#include <iostream>
#include <string>
#include<windows.h>
using namespace std;

struct Tree {
	int info;
	string data;
	Tree* left, * right;
} *root;

Tree* List(int inf, string dat) {
	Tree* t = new Tree;		
	t->info = inf;
	t->data = dat;
	t->left = t->right = NULL;	
	return t;				
}

void Add_List(Tree*& root, int key, string dat) 
{ 
    if (root == NULL) 
    {
        root = List(key, dat);
        cout << "Паспорт добавлен";
        return;
    }

    Tree* prev = NULL;
    Tree* t = root;
    bool find = true;

    while (t && find)
    {
        prev = t;
        if (key == t->info)
        {
            find = false;
            cout << "Номер дублируется";
            return;
        }
        else if (key < t->info)
            t = t->left;
        else
            t = t->right;
    }

    if (find) 
    {
        t = List(key, dat);
        if (key < prev->info)
            prev->left = t;
        else
            prev->right = t;
        cout << "Паспорт добавлен\n";
    }
}

void View_Tree(Tree* p, int level) {

	if (p)
    {
        View_Tree(p->left, level + 1);         // Левое поддерево
		
		for (int i = 0; i < level; i++) 
			cout << "    ";
		cout << p->info << endl;

        View_Tree(p->right, level + 1);        // Правое поддерево
	}
}

void Del_Tree(Tree* t) {
	if (t != NULL)
    {
		Del_Tree(t->left);
		Del_Tree(t->right);
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

void InputData(int& key, string& data) {
    system("cls");
    cout << "Введите номер паспорта: ";
    problem(key);
    cin.ignore();
    cout << "Введите ФИО: ";
    getline(cin, data);
}

Tree* Search(Tree* root, int key) 
{
    if (root == NULL || root->info == key)
        return root;

    if (key < root->info)
        return Search(root->left, key);
    else
        return Search(root->right, key);
}

Tree* FindMin(Tree* root) 
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

void pramoi(Tree* p, int level) {
    if (p) 
    {
        for (int i = 0; i < level; i++)
            cout << "    ";
        cout << p->info << " : " << p->data << endl;

        pramoi(p->left, level + 1);
        pramoi(p->right, level + 1);
    }
}

void obrat(Tree* p, int level) {
    if (p)
    {
        obrat(p->left, level + 1);
        obrat(p->right, level + 1);

        for (int i = 0; i < level; i++)
            cout << "    ";
        cout << p->info << " : " << p->data << endl;
    }
}

Tree* DeleteList(Tree* root, int key)
{
    if (!nullornot(root))
        return;

    if (key < root->info)
        root->left = DeleteList(root->left, key);
    else if (key > root->info)
        root->right = DeleteList(root->right, key);
    else 
    {
        if (root->left == NULL)
        {
            Tree* temp = root->right;
            delete root;
            cout << "Паспорт удален!\n";
            return temp;
        }
        else if (root->right == NULL) 
        {
            Tree* temp = root->left;
            delete root;
            cout << "Паспорт удален!\n";
            return temp;
        }

        // Узел имеет двух потомков
        Tree* temp = FindMin(root->right);
        root->info = temp->info;
        root->data = temp->data;
        root->right = DeleteList(root->right, temp->info);
    }
    return root;
}

bool nullornot(Tree* root) {
    if (root == NULL) {
        cout << "Дерево пусто!\n";
        return false;
    }
    return true;
}

int task(Tree* root, char letter) {
    if (!nullornot(root))
        return;

    int count = 0;

    if (root->data[0] == letter || root->data[0] == letter - 32 || root->data[0] == letter + 32)
        count = 1;

    return count + task(root->left, letter) + task(root->right, letter);
}

void Make_Blns(Tree** p, int n, int k, int* a, string* data_arr) {
    if (n == k)
    {
        *p = NULL;
        return;
    }
    else 
    {
        int m = (n + k) / 2;
        *p = new Tree;
        (*p)->info = a[m];
        (*p)->data = data_arr[m];
        (*p)->left = NULL;
        (*p)->right = NULL;
        Make_Blns(&(*p)->left, n, m, a, data_arr);
        Make_Blns(&(*p)->right, m + 1, k, a, data_arr);
    }
}

int Count(Tree* root) {
    if (!nullornot(root))
        return;
    return 1 + Count(root->left) + Count(root->right);
}

void Mass(Tree* root, int* keys, string* data_arr, int& index) {
    if (root == NULL) return;

    Mass(root->left, keys, data_arr, index);
    keys[index] = root->info;
    data_arr[index] = root->data;
    index++;
    Mass(root->right, keys, data_arr, index);
}

void Sort(int* keys, string* data_arr, int n) {
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (keys[j] > keys[j + 1]) 
            {
                int temp_key = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = temp_key;

                string temp_data = data_arr[j];
                data_arr[j] = data_arr[j + 1];
                data_arr[j + 1] = temp_data;
            }
        }
    }
}

void Balance(Tree*& root) {
    if (!nullornot(root))
        return;

    int n = Count(root);

    int* keys = new int[n];
    string* data_arr = new string[n];

    int index = 0;
    Mass(root, keys, data_arr, index);

    Sort(keys, data_arr, n);

    Del_Tree(root);
    root = NULL;

    Make_Blns(&root, 0, n, keys, data_arr);

    delete[] keys;
    delete[] data_arr;

    cout << "Дерево сбалансировано!\n";
}

void Menu()
{

    cout << "\n========== МЕНЮ ==========\n";
    cout << "1. Добавить паспорт\n";
    cout << "2. Показать дерево\n";
    cout << "3. Показать дерево прямым обходом\n";
    cout << "4. Показать дерево обратным обходом\n";
    cout << "5. Поиск\n";
    cout << "6. Удалить паспорт\n";
    cout << "7. Подсчет по первой букве ФИО\n";
    cout << "8. Сбалансировать дерево\n";
    cout << "0. Выход\n";
    cout << "==========================\n";
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RU");
    root = NULL;
    int choice, key;
    string data;
    Tree* result;

    do {
        Menu();
        problem(choice);

        switch (choice) 
        {
        case 1: // Добавление
            InputData(key, data);
            Add_List(root, key, data);
            break;

        case 2: // Показать дерево
            system("cls");
            if (!nullornot(root))
               break;
            else 
            {
                cout << "Дерево: \n";
                View_Tree(root, 0);
            }
            break;

        case 3: // Прямой обход
            system("cls");
            if (!nullornot(root))
                break;
            cout << "Дерево:\n";
            pramoi(root, 0);
            break;

        case 4: // Обратный обход
            system("cls");
            if (!nullornot(root)) break;
            cout << "Дерево:\n";
            obrat(root, 0);
            break;

        case 5: // Поиск
            system("cls");
            if (!nullornot(root))
                break;

            cout << "Введите номер паспорта: ";
            problem(key); 
            result = Search(root, key);
            system("cls");
            if (result)
                cout << "Номер паспорта: " << result->info <<"\n ФИО: " << result->data << endl;
            else
            {
                system("cls");
                cout << "Паспорт не найден\n"; 
            }
            break;

        case 6: // Удаление элемента
            system("cls");
            if (!nullornot(root))
                break;

            cout << "Введите номер паспорта для удаления: ";
            problem(key);
            root = DeleteList(root, key);
            break;

        case 7: // Подсчет по первой букве
            system("cls");
            if (!nullornot(root))
                break;
            {
                char letter;
                cout << "Введите букву для поиска: ";
                cin >> letter;
                cin.ignore();

                int result = task(root, letter);
                system("cls");
                cout << "Количество ФИО, начинающихся с буквы '" << letter << "': " << result << endl;
            }
            break;

        case 8: // Балансировка
            system("cls");
            Balance(root);
            break;

        case 0: //dsвыход
            Del_Tree(root);
            cout << "Дерево удалено. Выход";
            break;
        }
    } while (choice != 0);

    return 0;
}
