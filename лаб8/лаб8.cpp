#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return pow(x, 3) + 6.0 * x * x - 0.02 * exp(x);
}

double gaus(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        double mid = a + h * (i + 0.5);
        double dx = h / 2.0 * 0.5773502692;
        double x1 = mid - dx;
        double x2 = mid + dx;
        sum += f(x1) + f(x2);
    }
    return (h / 2.0) * sum;
}

double gausEps(double a, double b, double eps, int& nUsed) {
    int    n = 1;
    double prev = gaus(a, b, n);
    while (1) 
    {
        n++;
        double curr = gaus(a, b, n);
        if (fabs(curr - prev) < eps) 
        {
            nUsed = n;
            return curr;
        }
        prev = curr;
    }
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

int main() {
    setlocale(LC_ALL, "RU");
    double a, b, eps, n;

    cout << "Введите a: ";
    problem(a);
    cout << "Введите b: ";
    problem(b);
    cout << "Введите n: ";
    problem(n);
    cout << "Введите точность: ";
    problem(eps);

    cout << "\nПо числу разбиений" << endl;
    double res1 = gaus(a, b, n);
    cout << "Ответ: " << res1 << "\n";

    cout << "\nПо точности eps" << endl;
    int nUsed = 0;
    double res2 = gausEps(a, b, eps, nUsed);
    cout << "Ответ: " << res2 << "  (потребовалось " << nUsed << " разбиений)" << endl;

    return 0;
}