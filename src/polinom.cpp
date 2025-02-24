#include "polinom.h" 
#include "math.h"  
using namespace std;


Polinom::Polinom() {
    Head = new List<Monom>; 
}


Polinom::~Polinom() {
    do {
        DeletFirst(); // Удаление всех мономов из полинома
    } while (Head != 0);
}

// Установка первого элемента списка мономов
void Polinom::SetListFirst(List<Monom>* list_new) {
    (*this).SetListMid(Head, Head); // Установка нового элемента в начало списка
    (*Head).SetData((*list_new).GetData()); // Установка данных нового монома
}

// Удаление первого элемента списка мономов
void Polinom::DeletFirst() {
    List<Monom>* temp = new List<Monom>; // Создание временного указателя
    temp = Head; // Сохранение текущей головы
    Head = (*(Head)).GetPointerList(); // Перемещение головы на следующий элемент
    delete temp; // Удаление старой головы
}

// Удаление всех мономов из полинома
void Polinom::Deletpolinom() {
    do {
        DeletFirst(); // Удаление первого монома пока список не пуст
    } while (Head != 0);
}

// Удаление среднего элемента списка мономов
void Polinom::DeletMid(List<Monom>* list_old) {
    List<Monom>* midpoint; // Указатель на средний элемент
    midpoint = (*list_old).GetPointerList(); // Получение следующего элемента
    (*list_old).SetPointerList((*(*list_old).GetPointerList()).GetPointerList()); // Переподключение указателей
    delete midpoint; // Удаление среднего элемента
}

// Установка нового элемента между двумя элементами списка мономов
void Polinom::SetListMid(List<Monom>* list_new, List<Monom>* list_old) {
    List<Monom>* Li = new List<Monom>(*list_new); // Создание нового элемента
    Li->SetPointerList((*list_old).GetPointerList()); // Подключение к следующему элементу
    list_old->SetPointerList(Li); // Установка нового элемента в список
}

// Установка монома в список, сохраняя порядок по степеням
void Polinom::SetListMidh(List<Monom>* list_new) {
    List<Monom>* Lr = nullptr; // Указатель на предыдущий элемент
    List<Monom>* Lh = Head; // Указатель на текущий элемент
    List<Monom>* Li = new List<Monom>(*list_new); // Создание нового монома

    // Поиск позиции для вставки нового монома
    while (Lh != nullptr && Lh->GetData().GetPower() < list_new->GetData().GetPower()) {
        Lr = Lh; // Запоминаем предыдущий элемент
        Lh = Lh->GetPointerList(); // Переход к следующему элементу
    }

    // Проверка на совпадение степеней
    if (Lh != nullptr && Lh->GetData().GetPower() == list_new->GetData().GetPower()) {
        // Сложение коэффициентов
        double newFactor = Lh->GetData().GetFactor() + list_new->GetData().GetFactor();
        if (abs(newFactor) > 0.000000001) {
            Lh->GetData().SetFactor(newFactor); // Обновляем коэффициент
        }
        else {
            // Если коэффициент стал нулевым, удаляем моном
            if (Lr == nullptr) { // Если удаляем первый элемент
                DeletFirst();
            }
            else {
                Lr->SetPointerList(Lh->GetPointerList()); // Удаляем ссылку на Lh
                delete Lh; // Удаляем элемент
            }
        }
        return; // Завершаем, так как моном уже добавлен
    }

    // Вставка нового монома
    Li->SetPointerList(Lh); // Подключаем новый элемент к текущему
    if (Lr == nullptr) {
        Head = Li; // Если это первый элемент
    }
    else {
        Lr->SetPointerList(Li); // Устанавливаем новый элемент после Lr
    }
}


// Оператор сложения полиномов
Polinom& Polinom::operator+(Polinom& PL_Add) {
    Polinom* p_n = new Polinom; // Новый полином для результата
    List<Monom>* k1, * k2, * beta; // Указатели на элементы списков
    k1 = Head; // Указатель на текущий полином
    beta = p_n->Head; // Указатель на результат
    k2 = PL_Add.Head; // Указатель на добавляемый полином

    // Сложение полиномов
    while ((k1 != 0) && (k2 != 0)) {
        if ((*k1).GetData().GetPower() > (*k2).GetData().GetPower()) {
            p_n->SetListMid(k2, beta); // Вставка элемента из второго полинома
            beta = (*beta).GetPointerList();
            k2 = (*k2).GetPointerList();
        }
        else if ((*k1).GetData().GetPower() < (*k2).GetData().GetPower()) {
            p_n->SetListMid(k1, beta); // Вставка элемента из первого полинома
            beta = (*beta).GetPointerList();
            k1 = (*k1).GetPointerList();
        }
        else {
            // Сложение коэффициентов мономов с одинаковыми степенями
            List<Monom> sum(*k1);
            sum.GetData().SetFactor(sum.GetData().GetFactor() + (*k2).GetData().GetFactor());
            if (abs(sum.GetData().GetFactor()) < 0.000000001) {
                k1 = (*k1).GetPointerList();
                k2 = (*k2).GetPointerList();
            }
            else {
                p_n->SetListMid(&sum, beta); // Вставка суммы
                k1 = (*k1).GetPointerList();
                k2 = (*k2).GetPointerList();
                beta = (*beta).GetPointerList();
            }
        }
    }

    // Добавление оставшихся мономов
    while (k1 != 0) {
        p_n->SetListMid(k1, beta);
        beta = (*beta).GetPointerList();
        k1 = (*k1).GetPointerList();
    }
    while (k2 != 0) {
        p_n->SetListMid(k2, beta);
        beta = (*beta).GetPointerList();
        k2 = (*k2).GetPointerList();
    }
    p_n->DeletFirst(); // Удаление первого элемента (если он пустой)
    return *p_n; // Возврат результата
}

// Оператор вычитания полиномов
Polinom& Polinom::operator-(Polinom& PL_Add) {
    Polinom* p_n = new Polinom; // Новый полином для результата
    List<Monom>* k1, * k2, * beta; // Указатели на элементы списков
    k1 = Head; // Указатель на текущий полином
    beta = p_n->Head; // Указатель на результат
    k2 = PL_Add.Head; // Указатель на вычитаемый полином

    // Вычитание полиномов
    while ((k1 != 0) && (k2 != 0)) {
        if ((*k1).GetData().GetPower() > (*k2).GetData().GetPower()) {
            p_n->SetListMid(k2, beta); // Вставка элемента из второго полинома
            beta = (*beta).GetPointerList();
            k2 = (*k2).GetPointerList();
        }
        else if ((*k1).GetData().GetPower() < (*k2).GetData().GetPower()) {
            p_n->SetListMid(k1, beta); // Вставка элемента из первого полинома
            beta = (*beta).GetPointerList();
            k1 = (*k1).GetPointerList();
        }
        else {
            // Вычитание коэффициентов мономов с одинаковыми степенями
            List<Monom> sum(*k1);
            sum.GetData().SetFactor(sum.GetData().GetFactor() - (*k2).GetData().GetFactor());
            if (abs(sum.GetData().GetFactor()) < 0.000000001) {
                k1 = (*k1).GetPointerList();
                k2 = (*k2).GetPointerList();
            }
            else {
                p_n->SetListMid(&sum, beta); // Вставка разности
                k1 = (*k1).GetPointerList();
                k2 = (*k2).GetPointerList();
                beta = (*beta).GetPointerList();
            }
        }
    }

    // Добавление оставшихся мономов
    while (k1 != 0) {
        p_n->SetListMid(k1, beta);
        beta = (*beta).GetPointerList();
        k1 = (*k1).GetPointerList();
    }
    while (k2 != 0) {
        p_n->SetListMid(k2, beta);
        beta = (*beta).GetPointerList();
        k2 = (*k2).GetPointerList();
    }
    p_n->DeletFirst(); // Удаление первого элемента (если он пустой)
    return *p_n; 
}

// Оператор умножения полиномов
Polinom& Polinom::operator*(Polinom& PL_Add) {
    Polinom* p_n = new Polinom; // Новый полином для результата
    List<Monom>* k1, * k2, * beta2, beta; // Указатели на элементы списков
    k1 = Head; // Указатель на текущий полином
    k2 = PL_Add.Head; // Указатель на умножаемый полином

    // Умножение полиномов
    while (k1 != 0) {
        Polinom sum2; // Полином для хранения промежуточных результатов
        beta2 = sum2.Head; // Указатель на промежуточный результат
        k2 = PL_Add.Head; // Сброс указателя на умножаемый полином

        while (k2 != 0) {
            beta.GetData().SetFactor((*k1).GetData().GetFactor() * (*k2).GetData().GetFactor()); // Умножение коэффициентов
            if (beta.GetData().GetFactor() > 0.0000001) {
                try {
                    // Установка степени результата
                    beta.GetData().SetPower((*k1).GetData().GetPower() / 100 + (*k2).GetData().GetPower() / 100,
                        ((*k1).GetData().GetPower() / 10) % 10 + ((*k2).GetData().GetPower() / 10) % 10,
                        (*k1).GetData().GetPower() % 10 + (*k2).GetData().GetPower() % 10);
                }
                catch (...) {
                    cout << "Ошибка: степень больше 9, проверьте входные данные" << endl;
                    return *p_n; // Возврат пустого полинома в случае ошибки
                }
                sum2.SetListMidh(&beta); // Вставка результата в промежуточный полином
                beta2 = &beta; // Сохранение указателя
            }
            k2 = (*k2).GetPointerList(); // Переход к следующему моном
        }
        *p_n = (*p_n) + sum2; // Сложение промежуточного результата с основным полином
        k1 = (*k1).GetPointerList(); // Переход к следующему моном
    }

    // Удаление нулевых мономов в начале
    while ((p_n->Head->GetData().GetFactor() == 0) && (p_n->Head->GetPointerList() != 0))
        p_n->DeletFirst();
    return *p_n; // Возврат результата
}

// Оператор присваивания полиномов
Polinom& Polinom::operator=(Polinom& PL_start) {
    if (this->Head == PL_start.Head) {
        return *this; // Проверка на самоприсваивание
    }
    delete Head; // Удаление старого списка
    Head = new List<Monom>; // Создание нового списка

    List<Monom>* k1, * k2; // Указатели на элементы списков
    this->Head = PL_start.Head; // Копирование головы
    k1 = PL_start.Head->GetPointerList(); // Указатель на следующий элемент в исходном полиноме
    k2 = this->Head; // Указатель на текущий элемент в новом полиноме

    // Копирование всех мономов
    while (k1 != 0) {
        SetListMid(k1, k2); // Установка монома
        k1 = k1->GetPointerList(); // Переход к следующему моном
        k2 = k2->GetPointerList(); // Переход к следующему моном
    }
    return *this; // Возврат текущего полинома
}
