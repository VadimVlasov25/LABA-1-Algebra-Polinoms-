#include <iostream>
#include <locale> 
#include <clocale> 
#include "RedBlackTree.h"

int main() {
    setlocale(LC_ALL, "Russian");

    RedBlackTree tree; // Создаем экземпляр красно-черного дерева

    // Пример вставки данных
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);

    // Выводим элементы дерева в порядке возрастания
    std::cout << "Элементы дерева в порядке возрастания: ";
    tree.inorder();
    std::cout << std::endl;

    return 0; 
}

// #include <iostream>
// #include <locale> 
// #include <clocale> 
// #include "RedBlackTree.h" 

// int main() {
//     setlocale(LC_ALL, "Russian");
//     RedBlackTree tree; 

//     // Вставляем элементы в дерево
//     std::cout << "Вставляем элементы в дерево: " << std::endl;
//     int elements[] = { 20, 15, 25, 10, 5, 1, 30, 35, 40 }; // Массив элементов для вставки
//     for (int el : elements) { // Проходим по каждому элементу массива
//         std::cout << "Вставка: " << el << std::endl; // Выводим сообщение о вставке
//         tree.insert(el); // Вставляем элемент в дерево
//     }

//     // Выводим элементы дерева в порядке возрастания
//     std::cout << "Элементы дерева в порядке возрастания: ";
//     tree.inorder(); // Метод для вывода элементов дерева в порядке возрастания
//     std::cout << std::endl;

//     // Попытка вставить дублирующий элемент
//     std::cout << "Пытаемся вставить дублирующий элемент: 20" << std::endl;
//     tree.insert(20); // Предполагаем, что метод insert игнорирует дубликаты

//     // Выводим элементы дерева после попытки вставки дубликата
//     std::cout << "Элементы дерева после попытки вставки дубликата: ";
//     tree.inorder(); // Снова выводим элементы дерева
//     std::cout << std::endl;

//     // Вставка еще нескольких элементов для тестирования
//     std::cout << "Вставляем дополнительные элементы: 22, 18, 27" << std::endl;
//     tree.insert(22);
//     tree.insert(18); 
//     tree.insert(27); 

//     // Выводим элементы дерева после дополнительных вставок
//     std::cout << "Элементы дерева после дополнительных вставок: ";
//     tree.inorder(); 
//     std::cout << std::endl;

//     return 0; 
// }

