#include "pch.h"
#include "CppUnitTest.h"
#include "GasStations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBuildMatrix
{

	TEST_CLASS(TestBuildMatrix)
	{
	public:
		
		TEST_METHOD(EmptyVectors)
		{
			std::vector<InfInt> prices;
			std::vector<std::pair<int, int>> roads;

			std::vector<std::vector<InfInt>> expectedResult = {};

			std::vector<std::vector<InfInt>> result = BuildMatrix(prices, roads);

			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(AmountOfTownsIs2)
		{
			std::vector<InfInt> prices = {1};
			std::vector<std::pair<int, int>> roads = { {1, 2} };

			std::vector<std::vector<InfInt>> expectedResult = {
				{0, 1},
				{0, 0} };

			std::vector<std::vector<InfInt>> result = BuildMatrix(prices, roads);

			Assert::IsTrue(expectedResult == result);
		}

		TEST_METHOD(AmountOfTownsIs3)
		{
			std::vector<InfInt> prices = { 1, 2 };
			std::vector<std::pair<int, int>> roads = { {1, 2}, {2, 3} };

			std::vector<std::vector<InfInt>> expectedResult = {
				{0, 1, 0},
				{2, 0, 2},
				{0, 0, 0} };

			std::vector<std::vector<InfInt>> result = BuildMatrix(prices, roads);

			Assert::IsTrue(expectedResult == result);
		}
	};
}
