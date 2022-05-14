#include "pch.h"
#include "CppUnitTest.h"
#include "GasStations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDijkstraAlgorithm
{
	TEST_CLASS(TestDijkstraAlgorithm)
	{
	public:
		
		TEST_METHOD(NoPathBetweenTowns)
		{
			std::vector<std::vector<InfInt>> matrix = {
				{0, 0},
				{0, 0} };

			bool gotException = false;

			bool shouldThrowException = true;
			int expectedErrorID = 0;

			try
			{
				DijkstraAlgorithm(matrix);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
				Assert::AreEqual(expectedErrorID, excInfo.excID);
			}

			Assert::AreEqual(shouldThrowException, gotException);
		}

		TEST_METHOD(AmountOfTownsIs1)
		{
			std::vector<std::vector<InfInt>> matrix = { {0} };

			bool gotException = false;
			InfInt result;

			bool shouldThrowException = false;
			InfInt expectedResult = "0";

			try
			{
				result = DijkstraAlgorithm(matrix);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
			}

			Assert::AreEqual(shouldThrowException, gotException);
			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(AmountOfTownsIs2)
		{
			std::vector<std::vector<InfInt>> matrix = {
				{0, 1},
				{0, 0} };

			bool gotException = false;
			InfInt result;

			bool shouldThrowException = false;
			InfInt expectedResult = "1";

			try
			{
				result = DijkstraAlgorithm(matrix);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
			}

			Assert::AreEqual(shouldThrowException, gotException);
			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(AmountOfTownsIs3)
		{
			std::vector<std::vector<InfInt>> matrix = {
				{0, 1, 0},
				{2, 0, 2},
				{0, 0, 0} };

			bool gotException = false;
			InfInt result;

			bool shouldThrowException = false;
			InfInt expectedResult = "3";

			try
			{
				result = DijkstraAlgorithm(matrix);
			}
			catch (ErrorInfo excInfo)
			{
				gotException = true;
			}

			Assert::AreEqual(shouldThrowException, gotException);
			Assert::IsTrue(expectedResult == result);
		}
	};
}
