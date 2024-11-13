#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10.2.B/lab_10.2.B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102B
{
	TEST_CLASS(UnitTest102B)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(4, calc_n(1000));
		}
	};
}
