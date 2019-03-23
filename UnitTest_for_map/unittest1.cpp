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
				check = !it.current_color() ? 0 : 1;
				Assert::AreEqual(0, check);
			}
		}

	};
}