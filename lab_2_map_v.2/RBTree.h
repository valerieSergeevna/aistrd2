#pragma once
#include <iostream>
#include "Iterator.h"

using namespace std;


template <class item> class stack
{
	item *Stack; int size_;
public:
	stack(int maxt) : Stack(new item[maxt]), size_(0) {};
	~stack();
	bool empty() const { return size_ == 0; }
	int size() const { return size_; }
	void push(item & item) { Stack[size_++] = item; }
	item top() const { return Stack[size_ - 1]; }
	void pop() { if (size_) --size_; }
};



// ������� ����������� �����
template <class item>
stack<item>::~stack()
{
	free(Stack); // ������� ����
}

template <class item> class queue
{
	item *Queue; int head, tail, size_, Max;
public:
	queue(int maxQ) : head(0), tail(0), Max(maxQ), size_(0), Queue(new item[maxQ + 1]) {}
	~queue();
	bool empty() const { return (head % Max) == tail; }
	int size() const { return size_; }
	void push(item & item) { Queue[tail++] = item; tail %= Max; ++size_; }
	item front() const { return Queue[head % Max]; }
	void pop() { head++; head %= Max; --size_; }
};

template <class item>
queue<item>::~queue()
{
	free(Queue);
}

template <typename T>
class RBTree
{
private:

	class node
	{

	public:
		node(T key, T data, node * next1 = nullptr, node * next2 = nullptr) {
			this->data = data;
			this->next_left = next1;
			this->next_right = next2;
			this->key = key;
			this->height = 0;
			this->parent = nullptr;
			this->color = 'r';

		};
		char color;
		T key, data;
		node * next_right, *next_left, *parent;
		unsigned int height;
		void Del();
		~node();

	};

	node * root;
	size_t size;
public:
	RBTree();
	~RBTree();
	class TreeIterator : public Iterator<T> {
	protected:
		node *current;
		TreeIterator(node* root) : current(root) { }

	public:
		bool operator==(const nullptr_t) const override { return current == nullptr; }
		bool operator!=(const nullptr_t) const override { return !operator==(nullptr); }
		T operator*() const override { return current->data; }
		T current_key() { return current->key; }
		char current_color() { return current->color; }

	};

	class DftIterator : public TreeIterator {
	private:
		stack<node*> nodes;
	public:
		DftIterator(node *root, size_t size) : TreeIterator(root), nodes(size) {}
		void operator++(T) override;
	};

	class BftIterator : public TreeIterator {
	private:
		queue<node*> nodes;
	public:
		BftIterator(node *root, size_t size) : TreeIterator(root), nodes(size) {}
		void operator++(T) override;
	};

	//mode* remove(int);
	void reset_list();
	
	node *get_uncle(node*);
	node* get_grandparent(node *);
	node* get_sibling(node *);
	node *get_successor(node *);

	//void add_first(node*);
	void add_first(T, T);
	void remove(T);
	void delfix(node*);
	T find(T);

	T get_keys();
	T get_colors();
	void get_value();
	void clear();
	void insert(T,T);
	void insertfix(node *t);
	void leftrotate(node *);
	void rightrotate(node *);

	DftIterator create_dft_iterator() { return DftIterator(root, size); }
	BftIterator create_bft_iterator() { return BftIterator(root, size); }
};

template<typename T>
void RBTree<T>::DftIterator::operator++(T)
{
	if (this->current->next_right != nullptr)
		nodes.push(this->current->next_right);
	if (this->current->next_left)
		this->current = this->current->next_left;
	else {
		if (nodes.size() > 0) {
			this->current = nodes.top();
			nodes.pop();
		}
		else
			this->current = nullptr;
	}
}

template<typename T>
void RBTree<T>::BftIterator::operator++(T)
{
	if (this->current->next_left != nullptr)
		nodes.push(this->current->next_left);
	if (this->current->next_right != nullptr)
		nodes.push(this->current->next_right);
	if (nodes.size() > 0) {
		this->current = nodes.front();
		nodes.pop();
	}
	else
		this->current = nullptr;
}

