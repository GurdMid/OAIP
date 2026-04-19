#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return pow(x, 3) + 6 * pow(x, 2) - 0.02 * exp(x) - 14;
}

double df(double x) {
    return 3 * pow(x, 2) + 12 * x - 0.02 * exp(x);
}

double newton(double x0, double epsilon) {
    double x = x0;
    double prev;

    for (int i = 0; i < 1000; ++i)
    {
        prev = x;
        double fx = f(x);
        double dfx = df(x);

        x = x - fx / dfx;

        if (fabs(x - prev) < epsilon)
            return x;
    }
    return x;
}

void Roots(double a, double b, double epsilon) {
    double* roots = new double[100];
    int rootCount = 0;

    int segments = 100;
    double step = (b - a) / segments;

    for (int i = 0; i <= segments; ++i) 
    {
        double x0 = a + i * step;
        double root = newton(x0, epsilon);

        if (root < a || root > b)
            continue;

        bool isNewRoot = true;
        for (int j = 0; j < rootCount; ++j) 
        {
            if (fabs(root - roots[j]) < epsilon * 100)
            {
                isNewRoot = false;
                break;
            }
        }

        if (isNewRoot && fabs(f(root)) < epsilon * 100)
        {
            roots[rootCount] = root;
            rootCount++;
        }
    }

    cout << "Найдено корней: " << rootCount << endl;

    if (rootCount > 0) 
    {
        for (int i = 0; i < rootCount; ++i)
            cout << "x" << i + 1 << " = " << roots[i] << endl;
    }

    delete[] roots;
}

void problem(double& a) {
    while (1)
    {
        if (!(cin >> a))
        {
            cout << "Неверный ввод, повторите попытку!" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        else break;
    }

}

int main() 
{
    setlocale(LC_ALL, "RU");
    double a, b, epsilon;
    while (1)
    {
        cout << "Введите а: ";
        problem(a);
        cout << "Введите b: ";
        problem(b);
        if (a >= b)
            cout << "a больше или равно b, повторите ввод" << endl;
        else
            break;
    }
    cout << "\nВведите погрешность: ";
    problem(epsilon);
    Roots(a, b, epsilon);

    return 0;
}