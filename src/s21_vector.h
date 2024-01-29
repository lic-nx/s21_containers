#ifndef S21_VECTOR_H
#define S21_VECTOR_H

template <typename T>
class Vector {
 public:
  using value_type = T;  // определяет тип
  using reference = value_type &;  // определяет тип ссылки на элемент
  using const_reference = const value_type &;  // тип ссылки на константу
  using iterator = VectorIterator<T>;  // тип для итерации по контейнеру
  using const_iterator = VectorConstIterator<T>;
  using size_type = std::size_t;  // определяет тип размера контейнера
  using capacity;  // размер буффера

  Vector();  // конструктор по умолчанию
  Vector(size_type n);  // конструктор создания вектора размера n
  Vector(std::initializer_list<value_type> const
             &items);  // конструктор списка инициализаторов, создает вектор,
                       // инициализированный с помощью std::initializer_list
  vector(const vector &v);  // копирование
  vector(vector &&v);       // перемещение
  ~vector();                // деструктор
  vector &operator=(
      vector &&v);  // перегрузка оператора присваивания для движущегося объекта
 private:
};

#endif /*S21_VECTOR_H*/