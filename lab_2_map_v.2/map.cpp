#include "map.h"
#include "Iterator.h"
#include <stdexcept>


template <typename T, typename T2 >
RBTree<T,T2>::RBTree()
{
	reset_list();
	size = 0;
}

template <typename T, typename T2 >
RBTree<T,T2>::~RBTree()
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
template <typename T, typename T2 >
void RBTree<T,T2>::add_first(T key, T2 val)
{

	root = new node(key, val);
	root->parent = nullptr;
	size++;
}
template <typename T, typename T2 >
void RBTree<T,T2>::remove(T key)
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}

	node *current;
	current = root;
	node *successor = nullptr;
	node *temp = nullptr;
	int found = 0;
	while (current != nullptr && found == 0)
	{
		if (current->key == key)
			found = 1;
		if (found == 0)
		{
			if (current->key < key)
				current = current->next_right;
			else
				current = current->next_left;
		}
	}
	if (found == 0)
	{
		throw out_of_range("error");
	}
	else
	{
		if (current->next_left == nullptr || current->next_right == nullptr)
			successor = current;
		else
			successor = get_successor(current);
		if (successor->next_left != nullptr)
			temp = successor->next_left;
		else
		{
			if (successor->next_right != nullptr)
				temp = successor->next_right;
			else
				temp = nullptr;
		}
		if (temp != nullptr)
			temp->parent = successor->parent;
		if (successor->parent == nullptr)
			root = temp;
		else
		{
			if (successor == successor->parent->next_left)
				successor->parent->next_left = temp;
			else
				successor->parent->next_right = temp;
		}
		if (successor != current)
		{
			current->color = successor->color;
			current->key = successor->key;
		}
		if (successor->color == 0)
			delfix(temp);
	}
	size--;
}
template <typename T, typename T2 >
void RBTree<T,T2>::delfix(node *removable)
{
	node *sibling;
	while (removable != root && removable->color == 0)
	{
		if (removable->parent->next_left == removable)
		{
			sibling = removable->parent->next_right;
			if (sibling->color == 1)
			{
				sibling->color = 0;
				removable->parent->color = 1;
				leftrotate(removable->parent);
				sibling = removable->parent->next_right;
			}
			if (sibling->next_right->color == 0&& sibling->next_left->color == 0)
			{
				sibling->color = 1;
				removable = removable->parent;
			}
			else
			{
				if (sibling->next_right->color == 0)
				{
					sibling->next_left->color == 0;
					sibling->color = 1;
					rightrotate(sibling);
					sibling = removable->parent->next_right;
				}
				sibling->color = removable->parent->color;
				removable->parent->color = 0;
				sibling->next_right->color = 0;
				leftrotate(removable->parent);
				removable = root;
			}
		}
		else
		{
			sibling = removable->parent->next_left;
			if (sibling->color == 1)
			{
				sibling->color = 0;
				removable->parent->color = 1;
				rightrotate(removable->parent);
				sibling = removable->parent->next_left;
			}
			if (sibling->next_left->color == 0&& sibling->next_right->color == 0)
			{
				sibling->color = 1;
				removable = removable->parent;
			}
			else
			{
				if (sibling->next_left->color == 0)
				{
					sibling->next_right->color = 0;
					sibling->color = 1;
					leftrotate(sibling);
					sibling = removable->parent->next_left;
				}
				sibling->color = removable->parent->color;
				removable->parent->color = 0;
				sibling->next_left->color = 0;
				rightrotate(removable->parent);
				removable = root;
			}
		}
		removable->color = 0;
		root->color = 0;
	}
}
template <typename T, typename T2 >
T2 RBTree<T,T2>::find(T key)
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

template <typename T, typename T2 >
void RBTree<T,T2>::get_keys()
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


template <typename T, typename T2 >
void RBTree<T,T2>::get_value()
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}
	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
		cout << *it << '-' << it.current_key() << ' ' << it.current_color() << ' ';
	cout << '\n';

	
}

template <typename T, typename T2 >
void RBTree<T,T2>::clear()
{
	while (size > 0)
		remove(root->key);
}

template <typename T, typename T2 >
void RBTree<T,T2>::reset_list()
{
	//	cur = nullptr;
	root = nullptr;
}

/*template <typename T>
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
*/
template <typename T, typename T2 >
typename RBTree<T,T2>::node * RBTree<T,T2>::get_successor(node *current)
{
	node *successor = nullptr;
	if (current->next_left != nullptr)
	{
		successor = current->next_left;
		while (successor->next_right != nullptr)
			successor = successor->next_right;
	}
	else
	{
		successor = current->next_right;
		while (successor->next_left != nullptr)
			successor = successor->next_left;
	}
	return successor;
}


template <typename T, typename T2 >
void RBTree<T,T2>::insert(T key, T2 value) {

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
		}	
		current->parent = prev;
		if (prev->key < current->key)
			prev->next_right = current;
		else
			prev->next_left = current;
	}
	
	insertfix(current);
	size++;
}

template <typename T, typename T2 >
void RBTree<T,T2>::insertfix(node *current) {
	node *uncle;
	if (root == current)
	{
		current->color = 0;
		return;
	}
	while (current->parent != nullptr && current->parent->color == 1)
	{
		node *granny = current->parent->parent;
		if (granny->next_left == current->parent)
		{
			if (granny->next_right != nullptr)
			{
				uncle = granny->next_right;
				if (uncle->color == 1)
				{
					current->parent->color = 0;
					uncle->color = 0;
					granny->color = 1;
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
				current->parent->color = 0;
				granny->color = 1;
				rightrotate(granny);
			}
		}
		else
		{
			if (granny->next_left != nullptr)
			{
				uncle = granny->next_left;
				if (uncle->color == 1)
				{
					current->parent->color = 0;
					uncle->color = 0;
					granny->color = 1;
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
				current->parent->color = 0;
				granny->color = 1;
				leftrotate(granny);
			}
		}
		root->color = 0;
	}

}

template <typename T, typename T2 >
void RBTree<T,T2>::leftrotate(node *current)
{
	if (current->next_right == nullptr)
		return;
	else
	{
		node *child = current->next_right;
		if (child->next_left != nullptr)
		{
			current->next_right = child->next_left;
			child->next_left->parent = current;
		}
		else
			current->next_right = nullptr;
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
		child->next_left = current;
		current->parent = child;
	}
}

template <typename T, typename T2 >
void RBTree<T,T2>::rightrotate(node *current)
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
