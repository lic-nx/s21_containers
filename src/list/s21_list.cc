#include "s21_list.h"
// #include "../s21_iterators.h"
namespace s21 {






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


template <typename T>
int list<T>::recursSort(list& mainList){
  if(mainList->size() <=1){
    return 1;
  }
  if (mainList->size() > 1){
    list<T> leftList;
    list<T> rightList;
    for (int i = 0 ; i < mainList->_n; i++){
      if (i < mainList->_n /2){
        leftList.add_New_member(mainList->value); // сомнения по поводу этой тоски 
      } 
      else {
        rightList.add_New_member(mainList->value);
      }
    }
     merge_two_lists(recursSort(leftList), recursSort(rightList)) ;
    mainList->begin_member = leftList->begin_member;

  }
  
  
}

}  // namespace s21

// int main() {
//   s21::list<int> my_list;
//   std::cout<<my_list.size();
//   std::cout<<"tmthf";
//   return 0;
// }