#include "RBTree.h"
#include "Iterator.h"
#include <stdexcept>



template<typename T>
RBTree<T>::RBTree()
{
	reset_list();
	size = 0;
}

template<typename T>
RBTree<T>::~RBTree()
{
	clear();
/*	if (root != nullptr)
	{
		root->Del();
		if (root->next_left != nullptr)
			root->next_left = nullptr;
		if (root->next_right != nullptr)
			root->next_right = nullptr;
		root = nullptr;
	}*/
}
/*
template<typename T>
void RBTree<T>::node::Del()
{
	if (this != nullptr) {
		this->next_left->Del();
		this->next_right->Del();
		free(this);
	}
}
*/

/*template<typename T>
void RBTree<T>::add_first(node *cur)
{

	root = cur;
	cur->parent = nullptr;
	cur->color = 0;
	size++;
}
*/
template<typename T>
void RBTree<T>::add_first(T key, T val)
{

	root = new node(key, val);
	root->parent = nullptr;
	size++;
}
template<typename T>
void RBTree<T>::remove(T key)
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}

	node *p;
	p = root;
	node *y = NULL;
	node *q = NULL;
	int found = 0;
	while (p != NULL && found == 0)
	{
		if (p->key == key)
			found = 1;
		if (found == 0)
		{
			if (p->key < key)
				p = p->next_right;
			else
				p = p->next_left;
		}
	}
	if (found == 0)
	{
		throw out_of_range("error");
	}
	else
	{
		if (p->next_left == nullptr || p->next_right == nullptr)
			y = p;
		else
			y = get_successor(p);
		if (y->next_left != nullptr)
			q = y->next_left;
		else
		{
			if (y->next_right != nullptr)
				q = y->next_right;
			else
				q = nullptr;
		}
		if (q != nullptr)
			q->parent = y->parent;
		if (y->parent == nullptr)
			root = q;
		else
		{
			if (y == y->parent->next_left)
				y->parent->next_left = q;
			else
				y->parent->next_right = q;
		}
		if (y != p)
		{
			p->color = y->color;
			p->key = y->key;
		}
		if (y->color == 'b')
			delfix(q);
	}
}
template<typename T>
void RBTree<T>::delfix(node *p)
{
	node *s;
	while (p != root && p->color == 'b')
	{
		if (p->parent->next_left == p)
		{
			s = p->parent->next_right;
			if (s->color == 'r')
			{
				s->color = 'b';
				p->parent->color = 'r';
				leftrotate(p->parent);
				s = p->parent->next_right;
			}
			if (s->next_right->color == 'b'&&s->next_left->color == 'b')
			{
				s->color = 'r';
				p = p->parent;
			}
			else
			{
				if (s->next_right->color == 'b')
				{
					s->next_left->color == 'b';
					s->color = 'r';
					rightrotate(s);
					s = p->parent->next_right;
				}
				s->color = p->parent->color;
				p->parent->color = 'b';
				s->next_right->color = 'b';
				leftrotate(p->parent);
				p = root;
			}
		}
		else
		{
			s = p->parent->next_left;
			if (s->color == 'r')
			{
				s->color = 'b';
				p->parent->color = 'r';
				rightrotate(p->parent);
				s = p->parent->next_left;
			}
			if (s->next_left->color == 'b'&&s->next_right->color == 'b')
			{
				s->color = 'r';
				p = p->parent;
			}
			else
			{
				if (s->next_left->color == 'b')
				{
					s->next_right->color = 'b';
					s->color = 'r';
					leftrotate(s);
					s = p->parent->next_left;
				}
				s->color = p->parent->color;
				p->parent->color = 'b';
				s->next_left->color = 'b';
				rightrotate(p->parent);
				p = root;
			}
		}
		p->color = 'b';
		root->color = 'b';
	}
}
template<typename T>
T RBTree<T>::find(T key)
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}

	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
		if (it.current_key() == key) return *it;
	throw out_of_range("error");
}

template<typename T>
T RBTree<T>::get_keys()
{

	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}
	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
		cout << it.current_key()<< ' ';
	cout << '\n';
}


template<typename T>
void RBTree<T>::get_value()
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}
	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
		cout << *it << ' ';
	cout << '\n';

	
}

template<typename T>
void RBTree<T>::clear()
{
	while (size > 0)
		remove(root->key);
}

template<typename T>
void RBTree<T>::reset_list()
{
	//	cur = nullptr;
	root = nullptr;
}

template <typename T>
typename RBTree<T>::node* RBTree<T>::get_uncle(node *cur) {
	node *granny = get_grandparent(cur);
	if (granny == nullptr)
		return nullptr; // No grandparent means no uncle
	if (cur->parent == granny->next_left)
		return granny->next_right;
	else
		return granny->next_left;
}

template <typename T>
typename RBTree<T>::node* RBTree<T>::get_grandparent(node *cur) {
	if ((cur != nullptr) && (cur->parent != nullptr))
		return cur->parent->parent;
	else
		return nullptr;
}

template<typename T>
typename RBTree<T>::node * RBTree<T>::get_sibling(node *current)
{
	if (current == current->parent->next_left)
		return current->parent->next_right;
	else
		return current->parent->next_left;
}

template<typename T>
typename RBTree<T>::node * RBTree<T>::get_successor(node *current)
{
	node *successor = NULL;
	if (current->next_left != NULL)
	{
		successor = current->next_left;
		while (successor->next_right != NULL)
			successor = successor->next_right;
	}
	else
	{
		successor = current->next_right;
		while (successor->next_left != NULL)
			successor = successor->next_left;
	}
	return successor;
}


template <typename T>
void RBTree<T>::insert(T key, T value) {

	node *temp, *prev;
	node *current = new node(key, value);
	temp = root;
	prev = nullptr;
	if (root == nullptr)
	{
		root = current;
		current->parent = nullptr;
	}
	else
	{
		while (temp != nullptr)
		{
			prev = temp;
			if (temp->key < current->key)
				temp = temp->next_right;
			else
				temp = temp->next_left;
		}	current->parent = prev;
		if (prev->key < current->key)
			prev->next_right = current;
		else
			prev->next_left = current;
	}
	
	insertfix(current);
	size++;
}

template<typename T>
void RBTree<T>::insertfix(node *current) {
	node *uncle;
	if (root == current)
	{
		current->color = 'b';
		return;
	}
	while (current->parent != nullptr && current->parent->color == 'r')
	{
		node *granny = current->parent->parent;
		if (granny->next_left == current->parent)
		{
			if (granny->next_right != nullptr)
			{
				uncle = granny->next_right;
				if (uncle->color == 'r')
				{
					current->parent->color = 'b';
					uncle->color = 'b';
					granny->color = 'r';
					current = granny;
				}
			}
			else
			{
				if (current->parent->next_right == current)
				{
					current = current->parent;
					leftrotate(current);
				}
				current->parent->color = 'b';
				granny->color = 'r';
				rightrotate(granny);
			}
		}
		else
		{
			if (granny->next_left != nullptr)
			{
				uncle = granny->next_left;
				if (uncle->color == 'r')
				{
					current->parent->color = 'b';
					uncle->color = 'b';
					granny->color = 'r';
					current = granny;
				}
			}
			else
			{
				if (current->parent->next_left == current)
				{
					current = current->parent;
					rightrotate(current);
				}
				current->parent->color = 'b';
				granny->color = 'r';
				leftrotate(granny);
			}
		}
		root->color = 'b';
	}

}

template<typename T>
void RBTree<T>::leftrotate(node *current)
{
	if (current->next_right == nullptr)
		return;
	else
	{
		node *y = current->next_right;
		if (y->next_left != NULL)
		{
			current->next_right = y->next_left;
			y->next_left->parent = current;
		}
		else
			current->next_right = nullptr;
		if (current->parent != nullptr)
			y->parent = current->parent;
		if (current->parent == nullptr)
			root = y;
		else
		{
			if (current == current->parent->next_left)
				current->parent->next_left = y;
			else
				current->parent->next_right = y;
		}
		y->next_left = current;
		current->parent = y;
	}
}

template<typename T>
void RBTree<T>::rightrotate(node *current)
{
	if (current->next_left == nullptr)
		return;
	else
	{
		node *child = current->next_left;
		if (child->next_right != nullptr)
		{
			current->next_left = child->next_right;
			child->next_right->parent = current;
		}
		else
			current->next_left = nullptr;
		if (current->parent != nullptr)
			child->parent = current->parent;
		if (current->parent == nullptr)
			root = child;
		else
		{
			if (current == current->parent->next_left)
				current->parent->next_left = child;
			else
				current->parent->next_right = child;
		}
		child->next_right = current;
		current->parent = child;
	}
}
