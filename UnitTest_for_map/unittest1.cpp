#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab_2_map_v.2/map.cpp"

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
			map.insert(2, 1); 
			map.insert(4, 2);  
			map.insert(3, 3);  
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
			map.insert(3, 3);  
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
				Assert::AreEqual(*it, check[i++]);
			}
		}

		TEST_METHOD(test_remove_int_char)
		{
			RBTree<int, char> map;
			map.insert(2, 'a');
			map.insert(4, 'k');
			map.insert(3, 'b');
			map.insert(1, 'u');
			map.insert(9, 'j');
			map.remove(3);
			int i = 0;
			char check[4] = { 'a','u','k','j' };
			auto it = map.create_bft_iterator();
			for (; it != nullptr; it++)
			{
				Assert::AreEqual(*it, check[i++]);
			}
		}

		TEST_METHOD(test_remove_int_char_color)
		{
			RBTree<int, char> map;
			map.insert(2, 'a');
			map.insert(4, 'k');
			map.insert(3, 'b');
			map.insert(1, 'u');
			map.insert(9, 'j');
			map.remove(3);
			int i = 0;
			bool check[4] = { 0,1,0,1 };
			auto it = map.create_bft_iterator();
			for (; it != nullptr; it++)
			{
				Assert::AreEqual(it.current_color(), check[i++]);
			}
		}

		TEST_METHOD(test_remove_int_char_exception)
		{
			RBTree<int, char> map;
			map.insert(2, 'a');
			map.insert(4, 'k');
			map.insert(3, 'b');
			map.insert(1, 'u');
			map.insert(9, 'j');
			try {
				map.remove(0); 
			}
			catch (const std::out_of_range& error)
			{
				Assert::AreEqual("no this element", error.what());
			}
			
		}

		TEST_METHOD(test_remove_int_char_none__exception)
		{
			RBTree<int, char> map;
			try {
				map.remove(0);
			}
			catch (const std::out_of_range& error)
			{
				Assert::AreEqual("error", error.what());
			}

		}

		TEST_METHOD(find_int_1)
		{
			RBTree<int, int> map;
			map.insert(2, 1);
			map.insert(4, 2);
			map.insert(3, 3);
			map.insert(1, 4);
			map.insert(9, 4);
			Assert::AreEqual(3, map.find(3));
		}

		TEST_METHOD(find_int_2)
		{
			RBTree<int, int> map;
			map.insert(2, 1);
			map.insert(4, 2);
			map.insert(1, 3);
			map.insert(1, 4);
			map.insert(9, 4);
			Assert::AreEqual(3, map.find(1));
		}

		TEST_METHOD(find_int_exception)
		{
			RBTree<int, int> map;
			map.insert(2, 1);
			map.insert(4, 2);
			map.insert(1, 3);
			map.insert(1, 4);
			map.insert(9, 4);
			try { map.find(0); }
			catch (const std::out_of_range& error) { Assert::AreEqual("error", error.what()); }
		}


		TEST_METHOD(find_int_exception_2)
		{
			RBTree<int, int> map;
			try { map.find(0); }
			catch (const std::out_of_range& error) { Assert::AreEqual("error", error.what()); }
		}
		
		TEST_METHOD(get_keys_exception)
		{
			RBTree<int, int> map;
			try { map.get_keys(); }
			catch (const std::out_of_range& error) { Assert::AreEqual("error", error.what()); }
		}

		TEST_METHOD(get_value_exception)
		{
			RBTree<int, int> map;
			try { map.get_value(); }
			catch (const std::out_of_range& error) { Assert::AreEqual("error", error.what()); }
		}

		TEST_METHOD(find_char)
		{
			RBTree<int, char> map;
			map.insert(2, 'a');
			map.insert(4, 'k');
			map.insert(4, 'b');
			map.insert(1, 'u');
			map.insert(9, 'j');
			Assert::AreEqual('b', map.find(4));
		}
		
	};
}