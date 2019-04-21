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
		throw out_of_range("no this element");
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
			current->data = successor->data;
		}
		if (successor->color == 0)
			delfix(temp);
	}
	size--;
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
/*template <typename T, typename T2 >
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
*/

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

template<typename T, typename T2>
void RBTree<T, T2>::delfix(node *fixable)
{

	node *sibling;
	while (fixable != root && fixable->color == 0)
	{
		if (fixable->parent->next_left == fixable)
		{
			sibling = fixable->parent->next_right;
			if (sibling->color == 1) //sibling is red. In this case, we change the colors of the ancestor and the sibling, and
									//then make a rotation to the left around the ancestor, making the grandfather of fixable.
			{
				sibling->color = 0;
				fixable->parent->color = 1;
				leftrotate(fixable->parent);
				sibling = fixable->parent->next_right;
			}
			if (sibling->next_right->color == 0 && sibling->next_left->color == 0) //In this case, we repaint sibling to red.
			{
				sibling->color = 1;
				fixable = fixable->parent;
			}
			else
			{
				if (sibling->next_right->color == 0) //In this case, we rotate the tree to the right around sibling. 
					//Thus, the left descendant S becomes his father and his new brother N. 
				//	After that, we change the colors of S and his new father. 
				{
					sibling->next_left->color == 0;
					sibling->color = 1;
					rightrotate(sibling);
					sibling = fixable->parent->next_right;
				}
				sibling->color = fixable->parent->color;
				fixable->parent->color = 0;
				sibling->next_right->color = 0;
				leftrotate(fixable->parent);
				fixable = root;
			}
		}
		else
		{
			sibling = fixable->parent->next_left;
			if (sibling->color == 1)
			{
				sibling->color = 0;
				fixable->parent->color = 1;
				rightrotate(fixable->parent);
				sibling = fixable->parent->next_left;
			}
			if (sibling->next_left->color == 0 && sibling->next_right->color == 0)
			{
				sibling->color = 1;
				fixable = fixable->parent;
			}
			else
			{
				if (sibling->next_left->color == 0)
				{
					sibling->next_right->color = 0;
					sibling->color = 1;
					leftrotate(sibling);
					sibling = fixable->parent->next_left;
				}
				sibling->color = fixable->parent->color;
				fixable->parent->color = 0;
				sibling->next_left->color = 0;
				rightrotate(fixable->parent);
				fixable = root;
			}
		}
		fixable->color = 0;
		root->color = 0;
	}
}

template <typename T, typename T2 >
void RBTree<T,T2>::insertfix(node *current) {
	node *uncle;
	//0 - black
	//1 - red
	//The current node  at the root of the tree.
	if (root == current)
	{
		current->color = 0;
		return;
	}
	while (current->parent != nullptr && current->parent->color == 1)
	{
		node *granny = current->parent->parent; // get grandfather of the current node
		if (granny->next_left == current->parent) // If both the parent and uncle are red, then both of them 
												  //can be repainted black and the grandfather will turn red.(right side)
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
				if (current->parent->next_right == current) //The parent is red, but the uncle is black. Also, the current node is the 
															//right descendant, and in turn the left descendant of its ancestor.
															//In this case, a tree can be rotated, which changes the roles of the current node and its ancestor.
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
			if (granny->next_left != nullptr)// If both the parent and uncle are red, then both of them 
												  //can be repainted black and the grandfather will turn red.(left side)
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
				if (current->parent->next_left == current) //The parent is red, but the uncle is black, the current node is the left descendant and the 
															//left descendant. In this case, the tree is rotated by. 
															//The result is a tree in which the former parent is now the parent of both the current node and the former grandfather.
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
