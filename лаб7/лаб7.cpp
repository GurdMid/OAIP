#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    return pow(x, 3) + 6 * pow(x, 2) - 0.02 * exp(x);
}

// Поиск ближайшего узла к точке xT
int find(const double* x, double m, double xT) {
    int nearest = 0;
    double minDist = fabs(xT - x[0]);

    for (int i = 1; i < m; i++)
    {
        double dist = fabs(xT - x[i]);
        if (dist < minDist)
        {
            minDist = dist;
            nearest = i;
        }
    }
    return nearest;
}

double newton(const double* x, const double* y, double m, double xT) {
    // Находим ближайший узел
    int nearest = find(x, m, xT);

    int i_left, i_right;

    // Определяем левый и правый узлы для интерполяции
    if (nearest == 0) 
    {
        // Ближайший узел - первый, берём его и следующий
        i_left = 0;
        i_right = 1;
    }
    else if (nearest == m - 1) 
    {
        // Ближайший узел - последний, берём предыдущий и его
        i_left = m - 2;
        i_right = m - 1;
    }
    else 
    {
        // Ближайший узел внутри таблицы
        // Проверяем, с какой стороны от узла находится xT
        if (xT >= x[nearest]) 
        {
            i_left = nearest;
            i_right = nearest + 1;
        }
        else
        {
            i_left = nearest - 1;
            i_right = nearest;
        }
    }

    double result = y[i_left] + (xT- x[i_left])*(y[i_right] - y[i_left])/(x[i_right] -x[i_left]);
    return result;
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
    double a, b, m, Check;

    cout << "Введите количество точек m: ";
    problem(m);
    cout << "Введите левую границу a: ";
    problem(a);
    cout << "Введите правую границу b: ";
    problem(b);

    double* x = new double[m];
    double* y = new double[m];

    cout << "   i        xi          yi     " << endl;

    for (int i = 0; i < m; i++)
    {
        x[i] = a + i * (b - a)/(m - 1);
        y[i] = f(x[i]);
        cout << "   " << i + 1 << "    ";
        cout << x[i] << " \t " << y[i] << endl;
    }

    cout << "Введите количество проверочных точек: ";
    problem(Check);

    cout << "\nПроверка качества аппроксимации:" << endl;
    cout << "     xT      Точное значение    N1(xT)    Погрешность" << endl;

    for (int i = 0; i <= Check; i++)
    {
        double xT = a + i * (b - a) / Check;
        double exact = f(xT);
        double approx = newton(x, y, m, xT);
        double error = fabs(exact - approx);

        cout << xT << " \t " << exact << " \t " << approx << " \t " << error << endl;
    }


    delete[] x;
    delete[] y;

    return 0;
}