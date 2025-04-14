#include "monom.h" 

// Установка степени монома по осям 
void Monom::SetPower(int pow_x, int pow_y, int pow_z) {
    if ((pow_x > 9) || (pow_y > 9) || (pow_z > 9))
        throw "Pow more 9"; // Генерация исключения, если степень больше 9
    // Проверка на отрицательные значения степени
    else if ((pow_x < 0) || (pow_y < 0) || (pow_z < 0))
        throw "Pow less that 0"; // Генерация исключения, если степень меньше 0
    else {
        // Установка степени монома как целого числа, где:
        // pow_x - старшие 2 цифры, pow_y - средние, pow_z - младшие
        power = pow_x * 100 + pow_y * 10 + pow_z;
    }
}

// Конструктор класса Monom, принимающий коэффициент и степени по осям x, y и z
Monom::Monom(double factor_new, int pow_x, int pow_y, int pow_z) {
    // Проверка на превышение максимального значения степени
    if ((pow_x > 9) || (pow_y > 9) || (pow_z > 9))
        throw "Pow more 9"; // Генерация исключения, если степень больше 9
    // Проверка на отрицательные значения степени
    else if ((pow_x < 0) || (pow_y < 0) || (pow_z < 0))
        throw "Pow less that 0"; // Генерация исключения, если степень меньше 0
    else {
        // Установка степени монома как целого числа
        power = pow_x * 100 + pow_y * 10 + pow_z;
        factor = factor_new; // Установка коэффициента монома
    }
}

// Конструктор копирования для класса Monom
Monom::Monom(Monom& m2) {
    factor = m2.GetFactor(); // Копирование коэффициента из другого монома
    power = m2.GetPower();   // Копирование степени из другого монома
}

// Деструктор класса Monom
Monom::~Monom() {}

// Оператор присваивания для класса Monom
Monom& Monom::operator=(Monom& m2) {
    factor = m2.GetFactor(); // Копирование коэффициента
    power = m2.GetPower();   // Копирование степени
    return *this; // Возврат текущего объекта для поддержки цепочек присваиваний
}
