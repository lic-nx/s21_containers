#include "s21_list.h"
// #include "../s21_iterators.h"
namespace s21 {

template <typename T>
typename list<T>::iterator insert(typename list<T>::iterator pos, typename list<T>::const_reference value){
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
void list<T>::splice(const_iterator pos, list& other) {
  if (!other.empty()) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      this->insert(pos, *it);
    }
    other.clear();
  }
}





template <typename T>
void list<T>::merge(list& other) {
  list<T> tmp_list = new list<T>(1);
  ListIterator<T> iter = new ListIterator<T>(this->begin);
  ListIterator<T> iter_other = new ListIterator<T>(other->begin);
  while(iter_other!=nullptr){
    if (iter->next == nullptr || iter->value > iter_other->value){
      iter = insert(iter, iter_other->value);
      iter_other++;
    }
    else if(iter->value <= iter_other->value){
      iter++;
    }
    else{
      iter--;
      iter = insert(iter, iter_other->value);
      iter_other++;
    }

  }
  if(iter_other!=nullptr){
    iter = insert(iter, iter_other->value);
  }
}


template <typename T>
void list<T>::reverse() { // может стопаться из-за первого элемента
  if (!this->empty()) {
    member<T>* tmp_member;
    
    size_type step = 0;
    for (iterator it = this->begin(); it->ptr_->before != nullptr; --it) {
      tmp_member = it.ptr_->before;
      it.ptr_->before = it.ptr_->next;
      it.ptr_->next = tmp_member;
    }
    tmp_member = this->begin;
    this->begin = this->end;
    this->end = tmp_member;
  }
}

template <typename T>
void list<T>::sort(){

}

}  // namespace s21

// int main() {
//   s21::list<int> my_list;
//   std::cout<<my_list.size();
//   std::cout<<"tmthf";
//   return 0;
// }