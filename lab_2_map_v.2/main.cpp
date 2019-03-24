#include "map.cpp"
#include "Iterator.h"
#include <conio.h>
#include <iostream>
#include <string>

void main()
{
	RBTree<int,char> map;
	map.insert(2, 'a');
	map.insert(4, 'k');
	map.insert(4, 'b');
	map.insert(1, 'u');
	map.insert(9, 'j');
	map.find(4);
	/*List.insert(2, 1);  //     2
	List.insert(4, 2);  //   1   4
	List.insert(3, 3);  // 0    3  9
	List.insert(1, 4);
	List.insert(9, 4);
	List.insert(0, 7);
	List.insert(2, 8);
	List.insert(3, 8);
	List.insert(0, 8);
	List.insert(1, 8);
	List.remove(2);*/
	/*List.insert(13, 'a');
	List.insert(9, 'b');
	List.insert(12, 'c');
	List.insert(14, 'd');
	List.insert(7, 'f');
	List.insert(11, 'g');
	List.insert(23, 'h');
	List.insert(19, 'i');
	List.insert(1, 'j');
	List.insert(4, 'k');
	List.insert(6, 'l');*/

	map.get_value();
	_getch();
	//return;
}