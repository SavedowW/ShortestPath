#include "pch.h"
#include "CppUnitTest.h"
#include "GasStations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestParseLineToInts
{

	TEST_CLASS(TestParseLineToInts)
	{
	public:
		
		TEST_METHOD(EmptyString)
		{
			std::string line = "";

			std::vector<InfInt> expectedResult = {};

			std::vector<InfInt> result = ParseLineToInts(line);

			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(OnlySpaces)
		{
			std::string line = "       ";

			std::vector<InfInt> expectedResult = {};

			std::vector<InfInt> result = ParseLineToInts(line);

			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(OnlyOneDigit)
		{
			std::string line = "1";

			std::vector<InfInt> expectedResult = { "1" };

			std::vector<InfInt> result = ParseLineToInts(line);

			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(OneDigitWithSpacesBeforeAndAfter)
		{
			std::string line = "  1    ";

			std::vector<InfInt> expectedResult = { "1" };

			std::vector<InfInt> result = ParseLineToInts(line);

			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(MultidigitNumber)
		{
			std::string line = "123";

			std::vector<InfInt> expectedResult = { "123" };

			std::vector<InfInt> result = ParseLineToInts(line);

			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(TwoMultidigitNumbers)
		{
			std::string line = "123 234";

			std::vector<InfInt> expectedResult = { "123", "234" };

			std::vector<InfInt> result = ParseLineToInts(line);

			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(ThreeMultidigitNumbers)
		{
			std::string line = "12 23 34";

			std::vector<InfInt> expectedResult = { "12", "23", "34" };

			std::vector<InfInt> result = ParseLineToInts(line);

			Assert::IsTrue(expectedResult == result);
		}
	};
}
