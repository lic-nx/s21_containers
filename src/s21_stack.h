#ifndef S21_STACK_H
#define S21_STACK_H

#include <iostream>

namespase 21 {
  template <typename T>
  class stack {
   public:
    using value_type = T;  // определяет тип
    using reference = value_type &;  // определяет тип ссылки на элемент
    using const_reference = const value_type &;  // тип ссылки на константу
    using size_type = std::size_t;  // определяет тип размера контейнера

    stack();  // создание стека
    stack(std::initializer_list<value_type> const
              &items);      // конструктор инициализации
    stack(const stack &s);  // копируем
    stack(stack &&s);       // перемещаем
    ~stack();               // деструктор

    const_reference top();  // получаем верхний элемент
    bool empty();           // пуст ли контейнер
    size_type size();  // возвращает число элементов
    operator=(stack &&s);  // тоже как конструктор перемещения
    void push(const_reference value);  // положить элемент вверх
    void pop();  // удаление верхнего элемента
    void swap(stack &other);  // смена местами элементов
   private:
    struct st_stack {
      value_type value;
      struct *next;
    };

    value_type create_stack();
  };
}
#endif /*S21_STACK_H*/