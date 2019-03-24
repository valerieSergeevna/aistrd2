#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab_2_map_v.2/map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_for_map
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(tree_root_color)
		{
			RBTree<int, int> map;
			map.insert(2, 1);
			int check;
			auto it = map.create_bft_iterator();
			for (; it != nullptr; it++)
			{
			//	check = !it.current_color() ? 0 : 1;
				Assert::IsFalse(it.current_color());
			}
		}

		TEST_METHOD(insert_int_)
		{
			RBTree<int, int> map;
			map.insert(2, 1);  //     2
			map.insert(4, 2);  //   1   4
			map.insert(3, 3);  // 0    3  9
			map.insert(1, 4);
			map.insert(9, 4);
			int i = 0;
			int check[5] = { 3,1,2,4,4 };
			auto it = map.create_bft_iterator();
			for (; it != nullptr; it++)
			{
				//	check = !it.current_color() ? 0 : 1;
				Assert::AreEqual(*it, check[i++]);
			}
		}
		TEST_METHOD(test_insert_int_color)
		{
			RBTree<int, int> map;
			map.insert(2, 1);  //     2
			map.insert(4, 2);  //   1   4
			map.insert(3, 3);  // 0    3  9
			map.insert(1, 4);
			map.insert(9, 4);
			int i = 0;
			bool check[5] = { 0,0,0,1,1 };
			auto it = map.create_bft_iterator();
			for (; it != nullptr; it++)
			{
				//	check = !it.current_color() ? 0 : 1;
				Assert::AreEqual(it.current_color(), check[i++]);
			}
		}
			TEST_METHOD(test_insert_int_char)
			{
				RBTree<int, char> map;
				map.insert(2, 'a');  
				map.insert(4, 'k'); 
				map.insert(3, 'b');  
				map.insert(1, 'u');
				map.insert(9, 'j');
				int i = 0;
				char check[5] = { 'b','a','k','u','j' };
				auto it = map.create_bft_iterator();
				for (; it != nullptr; it++)
				{
					//	check = !it.current_color() ? 0 : 1;
					Assert::AreEqual(*it, check[i++]);
				}
		}
	};
}