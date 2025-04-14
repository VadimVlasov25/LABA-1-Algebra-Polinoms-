#include "polinom.h"

int main()
{
    int a;
    Polinom p1;
    setlocale(LC_ALL, "Russian");
    cout << "Введите первый полином" << endl;
    cin >> p1;
    do
    {
        cout << "Выберите действие с полином 1" << endl;
        cout << "Сложить с полином 2" << endl;
        cout << "Вычесть полином 2" << endl;
        cout << "Умножить на полином 2" << endl;
        Polinom p2, p3;
        do
        {
            cin >> a;
        } while ((a != 1) && (a != 2) && (a != 3));

        cout << "Введите второй полином" << endl;
        cin >> p2;

        if (a == 1)
        {
            p3 = p1;
            p1 = p3 + p2;
        }
        else if (a == 2)
            p1 = p1 - p2;
        else
            p1 = p1 * p2;

        cout << p1;
        cout << "Чтобы продолжить, введите 1, чтобы закончить - 0" << endl;
        cin >> a;
    } while (a != 0);

    return 0;
}
