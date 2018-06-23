//created by John Stanco 6.21.18

#include <iostream>


template<class T>
class t_array{

private:

	size_t len;
	size_t n_elem;
	T **arr;

	template<class U>
	friend int swap(t_array<U>&, t_array<U>&);
	int copyData(T**, T**);
	int resetData(const size_t);
	int expand();
	int initialize(const size_t);

	int shiftLeft(const size_t);
	int shiftRight(const size_t);

public:
	t_array(size_t len = 5);
	t_array(const t_array<T>&);
	~t_array();

	int insert(const T&, const size_t);
	int remove(const size_t);
	int push(const T&);
	T pop(const size_t);

	t_array<T>& operator=(t_array<T>);
	T& operator[](const size_t);

	int print();
	
};


template <class T>
t_array<T>::t_array(size_t _len) : len(_len), n_elem(0), arr(_len? new T*[_len] : nullptr) {}


//------------------ Rule of Three -------------------//


template <class T>
t_array<T>::t_array(const t_array& other) : len(other.len), n_elem(other.n_elem), arr(new T*[other.len]){
	for(size_t i = 0; i < n_elem; i++){
		this->arr[i] = new T(*other.arr[i]);
	}
}


template<class T>
int swap(t_array<T>& first, t_array<T>& second){
	std::swap(first.len, second.len);
	std::swap(first.n_elem, second.n_elem);
	std::swap(first.arr, second.arr);
	return 1;
}


template<class T>
t_array<T>&
t_array<T>::operator=(t_array<T> other){
	swap(*this, other);
	return *this;
}


template <class T>
t_array<T>::~t_array(){
	for(size_t i = 0; i < n_elem; i++){
		if(arr[i]) delete arr[i];
	}
	delete [] arr;
}


//---------------------------------------------------//


template<class T>
int
t_array<T>::initialize(const size_t from){
	for(size_t i = from; i < len; i++){
		arr[i] = nullptr;
	}
	return 1;
}


template<class T>
int
t_array<T>::copyData(T** first, T** second){
	for(size_t i = 0; i < n_elem; i++){
		first[i] = new T(*second[i]);
	}
	return 1;
}


template<class T>
int
t_array<T>::resetData(const size_t index){
	if(arr[index]){
		delete arr[index];
		arr[index] = nullptr;
		return 1;
	}
	return 0;
}


template<class T>
int
t_array<T>::expand(){

	if(len == 0) len++;
	else len *= 2;

	T **tmpArr = new T*[len];

	for (size_t i = 0; i < n_elem; i++){
		tmpArr[i] = arr[i];
	}

	delete [] arr;
	arr = tmpArr;
	return initialize(n_elem);
}


template<class T>
int
t_array<T>::shiftLeft(const size_t index){
	std::cout << "shiftLeft" << std::endl;
	for(size_t i = index; i < n_elem - 1; i++){
		arr[i] = arr[i + 1];
	}
	return 1;
}


template<class T>
int
t_array<T>::shiftRight(const size_t index){
	if(n_elem == len) expand();
	for(size_t i = n_elem; i > index; i--){
		arr[i] = arr[i - 1];
	}
	arr[index] = nullptr;
	return 1;
}


template<class T>
int
t_array<T>::insert(const T& toAdd, const size_t index){
	if(index == n_elem) return push(toAdd);
	if(index < 0 || index > n_elem){
		throw ("Index out of bounds!");
	}

	shiftRight(index);
	arr[index] = new T(toAdd);
	n_elem++;
	return 1;
}


template<class T>
int
t_array<T>::remove(const size_t index){
	if(index < 0 || index >= n_elem){
		throw ("Index out of bounds!");
	}

	delete arr[index];
	shiftLeft(index);
	n_elem--;
	return 1;
}


template<class T>
int
t_array<T>::push(const T& toAdd){
	if(n_elem == len) expand();
	arr[n_elem++] = new T(toAdd);
	return 1;
}


template<class T>
T
t_array<T>::pop(const size_t index){
	if(index < 0 || index >= n_elem){
		throw ("Index out of bounds!");
	}
	T tmp(*arr[index]);
	remove(index);
	return tmp;
}


template<class T>
T&
t_array<T>::operator[](const size_t index){
	if(index < 0 || index >= len){
		throw ("index out of bounds!");
	}
	return *arr[index];
}

template<class T>
int
t_array<T>::print(){
	for(size_t i = 0; i < n_elem; i++){
		std::cout << *arr[i] << std::endl;
	}
	return 1;
}