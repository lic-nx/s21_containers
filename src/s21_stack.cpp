#using S21_stack.h

stack::stack(){
    create_stack();
}


stack::stack(std::initializer_list<value_type> const &items){
    create_stack();
    //size_type	Тип, представляющий количество элементов в initializer_list.
    // iterator	Тип, предоставляющий итератор для initializer_list.
}

value_type stack::create_stack(){
    this->value = NULL;
    this->next = NULL;
}