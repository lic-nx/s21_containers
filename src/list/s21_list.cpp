#include "s21_list.h"
// #include "../s21_iterators.h"
namespace s21 {

template <typename T>
iterator insert(iterator pos, const_reference value){
  member<T>* tmp_member = new member<T>(value);
  if (pos._ptr->next ==nullptr){
    pos._ptr.add_New_member(tmp_member); // настроить ссылки обратно и настроить _n у листа 
  }
  else{
    tmp_member.before = pos._ptr;
    pos._ptr->next->before = tmp_member;
    tmp_member.next = pos._ptr->next;
    pos._ptr->next = tmp_member; // хуйня но ладно
  }
  
}




template <typename T>
void list<T>::merge(list& other) {
  list<T> tmp_list = new list<T>;
  while(this->next != nullptr && other->next !=nullptr){
    if(this->value < other->value){
      
    }
  }
}


}  // namespace s21

int main() {
  s21::list<int> test({1, 2, 3});
  std::cout << test.get_elenemt() << "\n" << test.get_elenemt();
  return 1;
}