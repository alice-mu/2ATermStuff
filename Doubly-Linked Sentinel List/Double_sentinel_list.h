#include <iostream>

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////


// Default constructor for list
// Creates two instances of Double_node--the head and tail nodes
// Head and tail nodes have default values of 0
// Previous pointer of head is the nullptr and next pointer of tail is the nullptr
// List size set to zero
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_size( 0 )
{
	list_head = new Double_node();
	list_tail = new Double_node();

	list_head->next_node = list_tail;
	list_head->previous_node = nullptr;
	list_head->node_value = 0;

	list_tail->next_node = nullptr;
	list_tail->previous_node = list_head;
	list_head->node_value = 0;
}

// Copy constructor
// Takes argument of type Double_sentinel_list pointer
// Returns new list with node values from argument list, in the same order
// Changes to argument list does not affect new list
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_size( 0 )
{
	// Creates a new, empty list
	list_head = new Double_node();
	list_tail = new Double_node();

	list_head->next_node = list_tail;
	list_head->previous_node = nullptr;
	list_head->node_value = 0;

	list_tail->next_node = nullptr;
	list_tail->previous_node = list_head;
	list_head->node_value = 0;

	// Start from first node on the list and add nodes into
	// new_list one-by-one

	Double_node* curr_node = list.list_head->next_node;
	for (int i = 0; i < list.list_size; i++){
		push_back(curr_node->node_value);
		curr_node = curr_node->next_node;
	}
}

// Move constructor
// Takes argument of type Double_sentinel_list pointer
// Returns new list with node values from argument list, in the same order
// Implementation: Creating new, empty list and calling swap with argument list
// Assumes that the destructor will be call upon the completion of the constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_size( 0 )
{
	// Creates a new, empty list
	list_head = new Double_node();
	list_tail = new Double_node();

	list_head->next_node = list_tail;
	list_head->previous_node = nullptr;
	list_head->node_value = 0;

	list_tail->next_node = nullptr;
	list_tail->previous_node = list_head;
	list_head->node_value = 0;

	swap(list);
}


// Deletes all nodes including the head and tail pointers
template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	// Start iteration with two pointers:
	// current node and the next node
	Double_node* curr = list_head;
	for (int i = 0; i < list_size; i++){
		curr = curr->next_node;
		delete curr->previous_node;
	}
	delete curr;
	delete list_tail;
}

// Returns the amount of items in the list
template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;
}

// Returns true if list is empty, false if not
template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
		return (list_size == 0);
}

// Retrieves first object in the list
// Throws underflow of list empty
template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	if (list_size == 0)
		throw underflow();
	else
		return list_head->next_node->node_value;
}

// Retrieves last object in the list
// Throws underflow of list empty
template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	if (list_size == 0)
		throw underflow();
	else
		return list_tail->previous_node->node_value;
}

// Retrieves address of the next pointer of the head sentinel
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	return list_head->next_node;
}

// Returns the address of the tail sentinel
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	return list_tail;
}

// Returns the address of the previous pointer of the tail sentinel
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	return list_tail->previous_node;
}

// Returns the address of the head sentinel
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	return list_head;
}

// Takes argument of Type
// Returns the address of the first node in the list with a node value equal to argument
// Returns end() otherwise
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	Double_node* curr;
	curr = list_head;
	for (int i=0; i < list_size; i++){
		curr = curr->next_node;
		if (curr->node_value == obj)
			return curr;
	}
	return end();
}

// Takes argument of Type
// Returns the number of nodes in list that have a node value equal to argument
template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	int counter = 0;
	Double_node* curr;
	curr = list_head;
	// std::cout << "list size:" << list_size << std::endl;

	for (int i = 0; i < list_size; i++){

		curr = curr->next_node;
		if (curr->node_value == obj)
			counter++;
	}
	return counter;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	swap( rhs );
	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	swap( rhs );
	return *this;
}

// Take argument of Type
// Creates new Double_node instance and makes said new object the first item on the list
// Modifies pointers of the head pointer and first item pointers accordingly
template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	Double_node* new_node = new Double_node();
	new_node->node_value = obj;
	new_node->previous_node = list_head;
	new_node->next_node = list_head->next_node;

	list_head->next_node->previous_node = new_node;
	list_head->next_node = new_node;
	list_size++;
}

// Take argument of Type
// Creates new Double_node instance and makes said new object the last item on the list
// Modifies pointers of the tail pointer and last item pointers accordingly
template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	Double_node* new_node = new Double_node();
	new_node->node_value = obj;
	new_node->next_node = list_tail;
	new_node->previous_node = list_tail->previous_node;

	list_tail->previous_node->next_node = new_node;
	list_tail->previous_node = new_node;
	list_size++;
}

// Delete the first non-sentinel node of the linked list
// Updates the previous and next pointers of other nodes within the list accordingly
// Throws an underflow exception if list is empty
template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	if (list_size == 0)
		throw underflow();
	else {
		Double_node* pop_node = list_head->next_node;
		list_head->next_node = list_head->next_node->next_node;
		list_head->next_node->previous_node = list_head;
		delete pop_node;
		list_size--;
	}
}

// Delete the last non-sentinel node of the linked list
// Updates the previous and next pointers of other nodes within the list accordingly
// Throws an underflow exception if list is empty
template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	if (list_size == 0)
		throw underflow();
	else {
		Double_node* pop_node = list_tail->previous_node;
		list_tail->previous_node = list_tail->previous_node->previous_node;
		list_tail->previous_node->next_node = list_tail;
		delete pop_node;
		list_size--;
	}
}

// Deletes all the nodes in the linked list that have a value equal to the argument value
// Updates the previous and next pointers of other nodes accordingly
// Returns the number of nodes that were deleted
template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	int count = 0;
	Double_node* curr = list_head;

	for (int i=0; i < list_size; i++){
		curr = curr->next_node;
		if (curr->node_value == obj){
			count++;
			curr->previous_node->next_node = curr->next_node;
			curr->next_node->previous_node = curr->previous_node;
			delete curr;
		}
	}
	list_size = list_size - count;
	return count;
}

// Double_node constructor
// Take arguments of and sets values for node_value, previous_node,and next_node
template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( nv ),
previous_node( pn ),
next_node( nn )
{
}

// Returns the value of the current node
template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value;
}

// Returns the pointer to the previous node
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	return previous_node;
}

// Returns the pointer to the next node
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	return next_node;
}


template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}
