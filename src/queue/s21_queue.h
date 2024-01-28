#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <iostream>
// #include <memory>
#include <initializer_list>  // предоставляет инициализационный список
// #include "s21_list_iterator.h"
#include "../list/s21_list.h"

namespase s21{

    template <typename T>
    class queue: private list{
        queue(){
            this->begin_member = nullptr;
            this->end_member = nullptr;
            this->_n = 0;
            this->now_point = 0;
        }
        queue(std:initializer_lists<value_type> const &items){
            create_first(*(items.begin()));
            for (auto it = items.begin() + 1; it != items.end(); ++it) {
                const auto& item = *it;
                add_New_member(item);
            }
        }
        queue(const queue &q){
            if (q._n != 0) {
                queue<T> tmp;
                tmp.begin_member = q.begin_member;
                tmp.end_member = q.end_member;
                tmp._n = q._n;
                this->create_first(tmp.begin_member->value);
                // tmp.begin_member=tmp.begin_member->next;
                for (auto iter = tmp.begin()++; iter !=  nullptr; iter++)
                {
                    const auto& item = *iter;
                    this->add_New_member(item);
                }
                tmp.neutral_earthing();
            }
        }



    }

}

#endif /*S21_QUEUE_H*/