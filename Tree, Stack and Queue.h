#pragma once
#include <iostream>

using namespace std;

//Iterator class
class Iterator {
public:
	virtual int next() = 0;
	virtual bool has_next() = 0;
};

//Stack class
class Stack {
private:
	class node_stack {
	public:
		int value;
		node_stack* prev;
	};

public:
	size_t size;
	node_stack* top;

	//constructor 
	Stack() {
		top = NULL;
		size = 0;
	}

	//destructor 
	~Stack() {
		while (!Empty())
			pop();
	}
	
	//push the last node
	void push(int value) {
		node_stack* st_point = top;
		top = new node_stack;
		top->value = value;
		top->prev = st_point;
		size++;
	}

	//return the last element of the stack and delete from the stack
	int pop() {
		if (Empty())
			throw std::invalid_argument("The stack is empty");
		else {
			int last_value = top->value;
			node_stack* st_point = top->prev;
			delete top;
			top = st_point;
			size--;
			return last_value;
		}
	}

	//stack is empty
	bool Empty() {
		bool empty = false;
		if (size == 0) {
			empty = true;
		}
		return empty;
	}
};

//Queue class
class Queue {

private:
	//node of the queue
	class qu_node {
	public:
		int value;
		qu_node* next;
	};
	qu_node* head;
	qu_node* end;
	int size;

public:

	//constructor 
	Queue() {
		head = NULL;
		end = head;
		size = 0;
	}

	//destructor 
	~Queue() {
		while (size > 0) {
			pop();
		}
	}

	//insert elem
	void push(int value) {
		if (size == 0) {
			head = new qu_node;
			head->value = value;
			end = head;
		}
		else {
			end = end->next = new qu_node;
			end->value = value;
		}
		size++;
	}

	//return the first elem of the queue and delete them
	int pop() {
		if (Empty())
			throw std::out_of_range::out_of_range("The queue is empty");
		else {
			int top_value = head->value;
			qu_node* qu_point = head->next;
			delete head;
			head = qu_point;
			size--;
			return top_value;
		}
	}

	//queue is empty
	bool Empty() {
		bool empty = false;
		if (size == 0) {
			empty = true;
		}
		return empty;
	}
};


//Tree class
class tree {

private:

	class node {
	public:
		int elem = 0;
		node* left, * right;
	};

public:
	size_t size;
	node* tail;
	node* root;//pointer to the begin

	Iterator* create_dft_iterator();
	Iterator* create_bft_iterator();

	//Iterator subclass in the tree class for the stack
	class TreeIterator_stack : public Iterator {
	public:
		bool has_next() override;
		int next() override;

		//Constructor for the iterator
		TreeIterator_stack(node* root) {
			current = root;
			stack.push(current->elem);
		}

	private:
		bool check = false;
		Stack stack;
		node* root;
		node* current;
	};

	//Iterator subclass in the tree class for the queue
	class TreeIterator_queue : public Iterator {
	public:
		bool has_next() override;
		int next() override;

		//Constructor for the iterator1
		TreeIterator_queue(node* root) {
			current = root;
			queue.push(current->elem);
		}
	private:
		Queue queue;
		node* current;
		node* root;
		bool check = false;

	};


	//Constructor with parameter
	tree(int elem) {
		node* current = new node;
		current->elem = elem;
		current->left = current->right = NULL;
		root = current;
		tail = current;
		size = 1;
	}

	//Constructor without parameter
	tree() {
		root = NULL;
		tail = NULL;
		size = 0;
	}

	//Destructor 
	~tree() {
		while (size != 0) {
			remove(root->elem);
		}
	}

	//Inserting an element into the tree
	void insert(int elem)
	{
		if (root == NULL) {
			node* current = new node;
			current->elem = elem;
			current->left = current->right = NULL;
			root = current;
			tail = current;
			size++;
		}
		else {
			node* current = tail;
			if (elem < current->elem)
			{
				if (current->left != NULL) {
					current = current->left;
					tail = current;
					insert(elem);
				}
				else
				{
					current->left = new node;
					current = current->left;
					current->left = NULL;
					current->right = NULL;
					current->elem = elem;
					tail = root;
					size++;
				}
			}

			if (elem > current->elem)
			{
				if (current->right != NULL) {
					current = current->right;
					tail = current;
					insert(elem);
				}
				else
				{
					current->right = new node;
					current = current->right;
					current->left = NULL;
					current->right = NULL;
					current->elem = elem;
					tail = root;
					size++;
				}
			}
		}
		tail = root;
	}

	//Finding an element in the tree
	bool contains(int elem) {
		bool Existence = false;
		if (root == NULL) {
			throw invalid_argument("Tree is empty");
		}
		else {
			node* current = tail;
			if (elem == current->elem) {
				Existence = true;
				tail = root;
				return Existence;
			}
			else {
				if ((elem < current->elem) && (current->left != NULL)) {
					current = current->left;
					tail = current;
					if (elem == current->elem) {
						Existence = true;
						tail = root;
						return Existence;
					}
					if ((current->left == NULL) && (current->right == NULL)) {
						tail = root;
						return Existence;
					}
					else contains(elem);
				}
				if ((elem > current->elem) && (current->right != NULL)) {
					current = current->right;
					tail = current;
					if (elem == current->elem) {
						Existence = true;
						tail = root;
						return Existence;
					}
					if ((current->left == NULL) && (current->right == NULL)) {
						tail = root;
						return Existence;
					}
					else contains(elem);
				}
				else {
					tail = root;
					return Existence;
				}
			}
		}
	}

	//Removing an item from the tree
	void remove(int elem) {
		if (root == NULL) {
			throw invalid_argument("List is empty");
		}
		else {
			//If an element has no leaves or both
			node* current = tail;
			if (elem == current->elem) {
				if ((current->left == NULL) && (current->right == NULL)) { //If an item has no leaves
					current = NULL;
					tail = root;
					size--;
					return;
				}
				else {
					if ((root->right == NULL) && (root->left != NULL)) {
						node* dopcurrent = root;
						root = root->left;
						size--;
						tail = root;
						delete dopcurrent;
						return;
					}
					node* dopcurrent = current;
					node* remove_elem = current;
					dopcurrent = dopcurrent->right;
					int min_elem = dopcurrent->elem;
					while (dopcurrent->left != NULL) {
						current = dopcurrent;
						dopcurrent = dopcurrent->left;
						if (dopcurrent->left == NULL) {
							min_elem = dopcurrent->elem;
							break;
						}
					}
					if ((root->right == NULL) && (root->left == NULL)) {
						delete root;
						root = NULL;
						size--;
						return;
					}

					if (current == root) {
						current->elem = dopcurrent->elem;
						current->right = dopcurrent->right;
						dopcurrent->right = NULL;
						tail = root;
						size--;
						return;
					}
					if ((dopcurrent->right != NULL) && (dopcurrent->left == NULL)) {
						current->left = dopcurrent->right;
						delete dopcurrent->right;
						current->left->right = NULL;
						remove_elem->elem = min_elem;
						tail = root;
						size--;
						return;
					}
					else {
						remove_elem->elem = min_elem;
						delete dopcurrent;
						current->left = NULL;
						tail = root;
						size--;
						return;
					}
				}
			}
			else {
				if ((elem == root->elem) && (root->right == NULL)) {
					current = root;
					root = root->left;
					delete current;
					size--;
					return;
				}
				if ((elem == root->elem) && (root->left == NULL)) {
					current = root;
					root = root->right;
					delete current;
					size--;
					return;
				}

				if (current->left != NULL) {
					if (elem == current->left->elem) {
						if ((current->left->left == NULL) && (current->left->right != NULL)) {
							node* dopcurrent = current->left;
							current->left = dopcurrent->right;
							delete dopcurrent;
							tail = root;
							size--;
							return;
						}
						if ((current->left->left != NULL) && (current->left->right == NULL)) {
							node* dopcurrent = current->left;
							current->left = dopcurrent->left;
							delete dopcurrent;
							tail = root;
							size--;
							return;
						}
					}
				}
				if (current->right != NULL) {
					if (elem == current->right->elem) {
						if ((current->right->left == NULL) && (current->right->right != NULL)) {
							node* dopcurrent = current->right;
							current->right = dopcurrent->right;
							delete dopcurrent;
							tail = root;
							size--;
							return;
						}
						if ((current->right->left != NULL) && (current->right->right == NULL)) {
							node* dopcurrent = current->right;
							current->right = dopcurrent->left;
							delete dopcurrent;
							tail = root;
							size--;
							return;
						}
					}
				}
				if ((current->right == NULL) && (current->left == NULL)) {
					throw invalid_argument("Element doesn't exist");
				}
				if (elem > current->elem) {
					current = current->right;
					tail = current;
				}
				if (elem < current->elem) {
					current = current->left;
					tail = current;
				}
				remove(elem);
			}
		}
	}
};


//Stack
Iterator* tree::create_dft_iterator() {
	return new TreeIterator_stack(root);
}

int tree::TreeIterator_stack::next() {
	if (!has_next()) {
		throw out_of_range("No more elements");
	}
	else {
		int temp = stack.pop();
		if (check == false) {
			root = current;
			check = true;
		}
		current = root;
		while (current->elem != temp) {
			if (temp < current->elem) {
				current = current->left;
			}
			if (temp > current->elem) {
				current = current->right;
			}
		}

		if (current->right != NULL) {
			stack.push(current->right->elem);
		}
		if (current->left != NULL) {
			stack.push(current->left->elem);
		}

		return temp;
	}
}
bool tree::TreeIterator_stack::has_next() {
	return !stack.Empty();
}

//Queue
Iterator* tree::create_bft_iterator() {
	return new TreeIterator_queue(root);
}
int tree::TreeIterator_queue::next() {
	if (!has_next()) {
		throw out_of_range("No more elements");
	}
	else {
		int temp = queue.pop();
		if (check == false) {
			root = current;
			check = true;
		}
		current = root;
		while (current->elem != temp) {
			if (temp < current->elem) {
				current = current->left;
			}
			if (temp > current->elem) {
				current = current->right;
			}
		}
		if (current->left != NULL) {
			queue.push(current->left->elem);
		}
		if (current->right != NULL) {
			queue.push(current->right->elem);
		}
		return temp;
	}
}
bool tree::TreeIterator_queue::has_next() {
	return !queue.Empty();
}