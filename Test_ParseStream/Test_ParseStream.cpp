#include "pch.h"
#include "CppUnitTest.h"
#include "GasStations.h"

const std::string TESTS_PATH = "T:\\cppStuff\\ShortestPath\\ParseStreamTestFiles";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestParseStream
{

	TEST_CLASS(TestParseStream)
	{
	public:
		
		TEST_METHOD(EmptyInputStream)
		{
			std::ifstream input(TESTS_PATH + "\\test_1.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = false;
			std::vector<InfInt> expectedPrices = {};
			std::vector<std::pair<int, int>> expectedRoads = {};

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
			Assert::IsTrue(expectedPrices == resultPrices);
			Assert::IsTrue(expectedRoads == resultRoads);
		}

		TEST_METHOD(SymbolsExceptDigitsAndSpaces)
		{
			std::ifstream input(TESTS_PATH + "\\test_2.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = true;
			int expectedCode = 1;
			std::string expectedStr = "Nine";

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
				Assert::AreEqual(expectedCode, excInfo.excID);
				Assert::AreEqual(expectedStr, excInfo.str);
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
		}

		TEST_METHOD(LineHas0Numbers)
		{
			std::ifstream input(TESTS_PATH + "\\test_3.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = true;
			int expectedCode = 2;
			std::string expectedStr = "";

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
				Assert::AreEqual(expectedCode, excInfo.excID);
				Assert::AreEqual(expectedStr, excInfo.str);
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
		}

		TEST_METHOD(LineHas3Numbers)
		{
			std::ifstream input(TESTS_PATH + "\\test_4.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = true;
			int expectedCode = 2;
			std::string expectedStr = "1 2 3";

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
				Assert::AreEqual(expectedCode, excInfo.excID);
				Assert::AreEqual(expectedStr, excInfo.str);
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
		}

		TEST_METHOD(PathOfASingleTown)
		{
			std::ifstream input(TESTS_PATH + "\\test_5.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = true;
			int expectedCode = 3;
			std::string expectedStr = "2";

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
				Assert::AreEqual(expectedCode, excInfo.excID);
				Assert::AreEqual(expectedStr, excInfo.str);
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
		}
		
		TEST_METHOD(OneOfNumbersIsOutOfRange)
		{
			std::ifstream input(TESTS_PATH + "\\test_6.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = true;
			int expectedCode = 4;
			std::string expectedStr = "0";
			InfInt expectedOperand = 0;

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
				Assert::AreEqual(expectedCode, excInfo.excID);
				Assert::AreEqual(expectedStr, excInfo.str);
				Assert::IsTrue(expectedOperand == excInfo.value);
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
		}
		
		TEST_METHOD(OneOfPathsIsLoop)
		{
			std::ifstream input(TESTS_PATH + "\\test_7.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = true;
			int expectedCode = 5;
			std::string expectedStr = "1 1";

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
				Assert::AreEqual(expectedCode, excInfo.excID);
				Assert::AreEqual(expectedStr, excInfo.str);
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
		}
		
		TEST_METHOD(RoadsHaveNonexistentTown)
		{
			std::ifstream input(TESTS_PATH + "\\test_8.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = true;
			int expectedCode = 2;
			std::string expectedStr = "2 9";
			InfInt expectedOperand = 9;

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
				Assert::AreEqual(expectedCode, excInfo.excID);
				Assert::AreEqual(expectedStr, excInfo.str);
				Assert::IsTrue(expectedOperand == excInfo.value);
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
		}
		
		TEST_METHOD(SinglePriceAndRoad)
		{
			std::ifstream input(TESTS_PATH + "\\test_9.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = false;
			std::vector<InfInt> expectedPrices = { 1 };
			std::vector<std::pair<int, int>> expectedRoads = { {1, 2} };

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
			Assert::IsTrue(expectedPrices == resultPrices);
			Assert::IsTrue(expectedRoads == resultRoads);
		}
		
		TEST_METHOD(TwoLinesWithPrices)
		{
			std::ifstream input(TESTS_PATH + "\\test_10.txt");

			Assert::IsTrue(input.is_open());

			bool gotException = false;

			bool shouldThrowException = false;
			std::vector<InfInt> expectedPrices = {1, 99};
			std::vector<std::pair<int, int>> expectedRoads = { {1, 2}, {2, 3}, {1, 3} };

			std::vector<InfInt> resultPrices = {};
			std::vector<std::pair<int, int>> resultRoads = {};

			try
			{
				ParseStream(input, resultPrices, resultRoads);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
			}

			input.close();
			Assert::AreEqual(shouldThrowException, gotException);
			Assert::IsTrue(expectedPrices == resultPrices);
			Assert::IsTrue(expectedRoads == resultRoads);
		}
	};
}
