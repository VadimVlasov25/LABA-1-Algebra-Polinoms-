// Класс Полином - упорядоченный односвязный список Мономов
// Поддерживает операции: Печать, Вставка монома, Удаление монома,  
// Поиск монома, Сложение полиномов (слияние упорядоченных списков), 
// Умножение полиномов

#include <iostream>
#include "monom.h"
using namespace std;

#ifndef __LIST_H__
#define __LIST_H__

template <class T>
class List
{
private:
    T pData; // Данные монома
    List* nextpList; // Указатель на следующий элемент списка

public:
    ~List() {}; // Деструктор
    List() { pData = T(); nextpList = nullptr; }; // Конструктор по умолчанию
    List(List<T>& now); // Конструктор копирования
    List(T& pData_new, List* nextpList_new) { pData = pData_new; nextpList = nextpList_new; }; // Конструктор с параметрами

    T& GetData() { return pData; }; // Получение данных
    void SetData(T& pData_new) { pData = pData_new; }; // Установка данных
    List<T>* GetPointerList() { return nextpList; }; // Получение указателя на следующий элемент
    void SetPointerList(List* nextpList_new) { nextpList = nextpList_new; }; // Установка указателя на следующий элемент

    List<T>& operator=(List& List_new); // Оператор присваивания
};

// Реализация конструктора копирования
template <class T>
List<T>::List(List<T>& now)
{
    pData = now.GetData();
    nextpList = now.GetPointerList();
}

// Реализация оператора присваивания
template <class T>
List<T>& List<T>::operator=(List<T>& List_new)
{
    if (this != &List_new) // Проверка на самоприсваивание
    {
        pData = List_new.GetData();
        nextpList = List_new.GetPointerList();
    }
    return *this;
}

class Polinom
{
public:
    List<Monom>* Head; // Указатель на голову списка

    Polinom(); 
    ~Polinom();  

    void SetListFirst(List<Monom>* list_new); // Установка первого элемента
    void DeletFirst(); // Удаление первого элемента
    void SetListMid(List<Monom>* list_new, List<Monom>* list_old); // Вставка элемента в середину
    void SetListMidh(List<Monom>* list_new); // Вставка элемента в голову
    void DeletMid(List<Monom>* list_old); // Удаление элемента из середины
    void Deletpolinom(); // Удаление всего полинома

    Polinom& operator+(Polinom& PL_Add); 
    Polinom& operator*(Polinom& PL_Add); 
    Polinom& operator-(Polinom& PL_Add); 
    Polinom& operator=(Polinom& PL_Add); 

    // Ввод полинома
    friend istream& operator>>(istream& in, Polinom& mt)
    {
        setlocale(LC_ALL, "Russian");
        bool ToF = false;
        double s;
        int a, b, c, d;
        List<Monom>* h = mt.Head;

        while (!ToF)
        {
            List<Monom> nw;
            cout << "Введите коэффициент монома" << endl;
            in >> s;
            cout << "Введите степень x" << endl;
            in >> a;
            cout << "Введите степень y" << endl;
            in >> b;
            cout << "Введите степень z" << endl;
            in >> c;

            nw.GetData().SetFactor(s);
            nw.GetData().SetPower(a, b, c);
            mt.SetListMidh(&nw);
            h = (*h).GetPointerList();

            do
            {
                cout << "Добавить еще моном? 1-Да 0-Нет" << endl;
                in >> d;
            } while ((d != 0) && (d != 1));

            if (d == 0)
                ToF = true;
        }

        // Удаление нулевого монома из начала списка
        if ((*(mt.Head)).GetData().GetFactor() == 0)
            mt.DeletFirst();

        return in;
    }

    // Вывод полинома
    friend ostream& operator<<(ostream& out, const Polinom& mt)
    {
        setlocale(LC_ALL, "Russian");
        List<Monom>* nw = mt.Head;

        while (nw != nullptr)
        {
            out << "+(" << (*nw).GetData().GetFactor() << ")"
                << "x^" << (*nw).GetData().GetPower() / 100
                << "y^" << (*nw).GetData().GetPower() / 10 % 10
                << "z^" << (*nw).GetData().GetPower() % 10;
            nw = (*nw).GetPointerList();
        }
        return out;
    }
};

#endif
