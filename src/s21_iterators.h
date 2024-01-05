#ifndef S21_ITERATORS_H
#define S21_ITERATORS_H

#include <memory>
/*

*/
namespace s21{
 template<typename T>
    class Iterator{    
        // friend class member; // дружественный клас для разрешенгия работы с приватными методами 
        public:
            typedef T iterator_type; // тип итераторора и тип входящих значений
            typedef std::input_iterator_tag iterator_category; //  определяет категорию итератора. тегом для итераторов, которые могут быть использованы только для однопроходных операций чтения
            typedef member<T> value_type; // type for values
            typedef std::ptrdiff_t difference_type; // для хранения разности двух указателей
            typedef T& reference; // ссылка на тип T
            typedef T* pointer; // указатель на тип T

            iterator_type* value; // указатель на значение 
            Iterator() : { // создаем объект итератора
                member obj();
                value = &obj;
            };
            Iterator(T val) :  {
                member obj(val);
                value = &obj;
            }; 

            Iterator(const Iterator &other){ // копирование
                
            }
            
            Iterator(Iterator &&other){
                value = other.value;
                other.remove();
            }

            ~Iterator(){
                remove();
            }
            remove(){
                delete &value;
            }
            
            bool operator!=(Iterator const& other) const
            {
                return value != other.value;
            }

            bool operator==(Iterator const& other) const
            {
                return value == other.value;
            }

            typename Iterator::reference operator*() const // разименование 
            {
                return *value;
            }

            Iterator& operator++(){
                if (value->next != nullptr)
                    value = value->next.get();
                    // нужно рещить что делать когда дошли до последнего элемента 
                return *this;
            }

            Iterator& operator--(){
                if (value->before != nullptr)
                    value = value->before.get();
                    // нужно рещить что делать когда дошли до последнего элемента 
                return *this;
            }
            
            void end_add_member(member<T>){
                // для добавления в конец
            }

            Iterator begin(){ // самый левый элемент
                member<T>* tmp_iterator = this.value;
                while(tmp_iterator->before != nullptr){
                    tmp_iterator = tmp_iterator->before.get();
                }
                return iterator(tmp_iterator);
            }

            Iterator end(){ // самый правый элемент
                Iterator<T>* tmp_iterator = this;
                while(tmp_iterator->next != nullptr){
                    tmp_iterator = tmp_iterator->next.get();
                }
                member<T>* end(NULL, nullptr, *tmp_iterator); // создаем пустой элемент, чтоб потом вернуться к перыдущим записям 
                return iterator(tmp_iterator);
            }
            
            // Iterator begin()const{ // самый левый элемент
            //     member* tmp_iterator = this;
            //     while(tmp_iterator->before != nullptr){
            //         tmp_iterator = tmp_iterator->before.get();
            //     }
            //     return iterator(tmp_iterator);
            // }
            // const_iterator end() const{ // самый левый элемент
            //     member* tmp_iterator = this;
            //     while(tmp_iterator->next != nullptr){
            //         tmp_iterator = tmp_iterator->next.get();
            //     }
            //     member* end(null, nullptr, *tmp_iterator); // создаем пустой элемент, чтоб потом вернуться к перыдущим записям 
            //     return iterator(tmp_iterator);
            // }


        private:
            
            Iterator(T*  value): value(value){}; //констуктор 
    };
}




/*
пример мейна и того как я проверяла функционал работы члена. 
    int main(){
    member<int> test(8);
    
    member<int> test2(7,NULL, &test);
    std::cout<<" " <<test2.before<<"\n "<<test.next<<" ";
    
    Iterator<member<int>> test_1(test);
    ++test_1;
    std::cout<<" "<< test_1.value->value;
    // std::cout<<(test_1!=test2_1);
    return 0;
}
*/
#endif /*S21_ITERATORS_H*/