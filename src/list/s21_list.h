#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream> 
#include <initializer_list> // предоставляет инициализационный список
#include "s21_iterators.h"
namespace s21
{    
    template<typename T>
    class member{ 
        friend class Iterator;
        // буду использовать композицию вместо наследования
        // так смогу создать элементы существующего класса в другом классе
        private:
            T value;
            std::shared_ptr<member> next; 
            /* умный указатель. он сам очищает память как только станет ненужен
            так же не дает другим умным указателям указывать на эту область памяти. профит 
            по умолчанию инициализируется значением nullptr*/
            member* before;
            member():value(NULL), next(std::move(NULL)), before(NULL){}
            
            member(const T& value, std::shared_ptr<member> next = NULL, member* before = NULL)
             : next(std::move(next)), before(before), value(value) {
                // this = std::make_shared<member>();
                if (before != NULL) {
                    before->initializer_member_next(*this);
                }
            }
            ~member(){
                next = nullpt;
                before = nullpt;
                value = 0;
                
            };
            member(const member& other):value(other.value), next(std::move(other.next)), before(other.before){}
            void initializer_member_next(member update) {   
              next = std::make_shared<member>(update);
            }
    };




    template <typename T>
    class list  { 
        public:
            typedef T value_type ; // определяет тип
            typedef T& reference; // определяет тип ссылки на элемент можно использовать как возворащаемый тип из функции
            typedef const T& const_reference; // тип ссылки на константу
            typedef ListIterator<T> iterator; // определяет тип итератора
            typedef ListConstIterator<T> const_iterator; // определяет тип константного итератора
            typedef std::size_t size_type; // определяет тип размера контейнера 

            list(); // construtor done
            list(size_type n); // construtor creates the list of size n
            list(std::initializer_list<value_type> const &items); // construtor creates the list listt from the initializer lis
            list(const list &l); // copy construtor
            list(list &&l); // move construtor
            ~list(); // destructor
            operator=(list &&l); // перегрузка оператора перемещения


            iterator begin();
            size_type size(); // возвращает сколько элементов в листе
            /*ну сделала*/ size_type max_size(); // возвращает сколько всего можно создать элементов в листе
            

            void add_New_member();
        private:
            int _n; // колличество элементов 
            reference begin; //ну думаю что мы знаем что у нас идет первым 
            reference end; // ну мы же можем знать какой элемент у нас последний да?

    }
}



#endif /*S21_LIST_H*/