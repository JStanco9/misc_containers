//created by John Stanco 6.22.18


template<class T>
class linked_list{
private:

	struct node{
		T data;
		node *prev;
		node *next;
		node() {}
		node(const T& data) : data(data), prev(nullptr), next(nullptr) {};
	};

	size_t len;
	node *head;
	node *tail;
	node *iter;

	int copy_data(const linked_list& second);
	int delete_data();
	int locate(const size_t);
	int remove_at_iter();

public:	

	linked_list() : len(0), head(new node), tail(new node), iter(head){
		head->next = tail;
		tail->prev = head;
	} 
	linked_list(const linked_list<T>&);
	~linked_list();
	linked_list<T>& operator=(const linked_list<T>&);

	T get(const size_t);
	T pop(const size_t);
	int push(const T& datum);
	int insert(const T& datum, const size_t);
	int remove(const size_t);

};


//------------------------- Rule of Three --------------------------//


template <class T>
linked_list<T>::linked_list(const linked_list<T>& other) : len(0), 
head(new node), tail(new node), iter(head){
	head->next = tail;
	tail->prev = head;
	node *tmp = other.head->next;

	for(size_t i = 0; i < other.len; i++){
		push(tmp->data);
		tmp = tmp->next;
	}
}


template<class T>
int
linked_list<T>::delete_data(){
	node *tmp = head;

	for(size_t i = 0; i < len; i++){
		head = head->next;
		iter = head;
		delete iter;
	}
	head = tmp;
	len = 0;
	return 1;
}


template<class T>
linked_list<T>::~linked_list(){
	delete_data();
	delete head;
	delete tail;
}	


template<class T>
int
linked_list<T>::copy_data(const linked_list<T>& other){
	if(len > 0) delete_data();

	node *tmp = other.head->next;

	for(size_t i = 0; i < other.len; i++){
		push(tmp->data);
		tmp = tmp->next;
	}
	return 1;
}


template<class T>
linked_list<T>&
linked_list<T>::operator=(const linked_list<T> &other){
	if(this != &other) copy_data(other);
	return *this;
}


//--------------------------------------------------------------//


template<class T>
T
linked_list<T>::get(const size_t index){
	locate(index);
	return iter->data;
}


template<class T>
int
linked_list<T>::push(const T& datum){
	node *newNode = new node(datum);

	tail->prev->next = newNode;
	newNode->next = tail;
	newNode->prev = tail->prev;
	tail->prev = newNode;

	len++;
	return 1;
}


template<class T>
int
linked_list<T>::locate(const size_t index){
	if(index < 0 || index >= len){
		throw("index out of bounds!");
	}
	iter = head->next;
	for(size_t i = 0; i < index; i++){
		iter = iter->next;
	}
	return 1;
}


template<class T>
int
linked_list<T>::remove_at_iter(){
	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;

	iter->next = nullptr;
	iter->prev = nullptr;

	delete iter;
	len--;
	return 1;
}


template<class T>
T
linked_list<T>::pop(const size_t index){
	locate(index);
	T toRet = iter->data;
	remove_at_iter();
	return toRet;
}


template<class T>
int
linked_list<T>::remove(const size_t index){
	locate(index);
	return remove_at_iter();
}


template<class T>
int
linked_list<T>::insert(const T& data, const size_t index){
	if(index == len) return push(data);
	locate(index);

	node *newNode = new node(data);

	newNode->prev = iter->prev;
	newNode->next = iter;
	newNode->next->prev = newNode;
	newNode->prev->next = newNode;

	len++;
	return 1;
}