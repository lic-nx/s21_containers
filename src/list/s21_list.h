#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream> 
#include <memory>
// #include <initializer_list> // предоставляет инициализационный список
// #include "s21_iterators.h"
namespace s21
{    
    template<typename T>
    class member{ 
        // friend class Iterator;
        // буду использовать композицию вместо наследования
        // так смогу создать элементы существующего класса в другом классе
        public:
            T value;
            member<T>* next; 
            /* умный указатель. он сам очищает память как только станет ненужен
            так же не дает другим умным указателям указывать на эту область памяти. профит 
            по умолчанию инициализируется значением nullptr*/
            member<T>* before;
            member();
            // member(T value);
            member( T value, member* next = nullptr, member* before = nullptr);
            ~member();
            void destroy();
            member(const member& other);
            member<T>* operator*();
            void initializer_member_next(member* update);
    };




    template <typename T>
    class list  { 
        public:
            typedef T value_type ; // определяет тип
            typedef T& reference; // определяет тип ссылки на элемент можно использовать как возворащаемый тип из функции
            typedef const T& const_reference; // тип ссылки на константу
            // typedef ListIterator<T> iterator; // определяет тип итератора
            // typedef ListConstIterator<T> const_iterator; // определяет тип константного итератора
            typedef std::size_t size_type; // определяет тип размера контейнера 

            list(); // construtor done
            list(size_type n); // construtor creates the list of size n
            list(std::initializer_list<value_type> const &items); // construtor creates the list listt from the initializer lis
            list(const list &l); // copy construtor
            list(list &&l); // move construtor
            ~list(); // destructor
            // operator=(list &&l); // перегрузка оператора перемещения

            



            // iterator begin();
            size_type size(); // возвращает сколько элементов в листе
            /*ну сделала*/ size_type max_size(); // возвращает сколько всего можно создать элементов в листе
            T next_el();
            T get_elenemt();
            void add_New_member(T value_member = 0);
        private:
            int _n; // колличество элементов 
            member<T>* begin; //ну думаю что мы знаем что у нас идет первым 
            member<T>* end; // ну мы же можем знать какой элемент у нас последний да?

    };
}




#endif /*S21_LIST_H*/