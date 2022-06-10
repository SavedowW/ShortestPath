#include "GasStations.h"
#include <fstream>

int main(const int argc, char** argv)
{
	//Выдать ошибку, если входной файл не указан в аргументах командной строки
	if (argc == 1)
	{
		std::cout << "Input file is not defined in arguments.\n";
		return 1;
	}
	//Выдать ошибку, если выходной файл не указан в аргументах командной строки
	if (argc == 2)
	{
		std::cout << "Output file is not defined in arguments.\n";
		return 2;
	}
	//Выдать ошибку, если входной файл невозможно открыть
	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cout << "Cannot open input file. Make sure the path is correct.\n";
		return 3;
	}
	std::ofstream output(argv[2]);
	if (!output.is_open())
	{
		std::cout << "Cannot open output file. Make sure the path is correct and you have write rights.\n";
		input.close();
		return 3;
	}

	std::vector<InfInt> prices;
	std::set<std::pair<int, int>> roads;

	try
	{
		//Считать содержимое файла
		ParseStream(input, prices, roads);
		input.close();

		//Построить матрицу весов графа
		std::vector<std::vector<InfInt>> mat;
		BuildMatrix(prices, roads, mat);
		
		//Решить алгоритм Дейкстры
		auto result = DijkstraAlgorithm(mat);
		
		//Записать длину кратчайшего пути в выходной файл
		output << result;
		
	}
	catch (ErrorInfo err) //Если было выброшено исключение
	{
		if (err.excID == 0) //Если пути нет
		{
			//Записать в выходной файл «Решения не существует»
			output << "No solution";
		}
		else //Иначе
		{
			//Сформировать и вывести информацию об ошибке
			switch (err.excID)
			{
			// Символы кроме цифр и пробелов
			case(1):
				std::cout << "Error in line \"" << err.str << "\"\n";
				std::cout << "Only natural numbers are allowed in input.\n";
				break;

			// В строке 0 или больше 2 чисел
			case(2):
				std::cout << "Error in line \"" << err.str << "\"\n";
				std::cout << "Line can contain only 1 or 2 numbers.\n";
				break;

			// В дорогах только 1 число
			case(3):
				std::cout << "Error in line \"" << err.str << "\"\n";
				std::cout << "Line with road should contain 2 numbers.\n";
				break;

			// Число вне диапазона
			case(4):
				std::cout << "Error in line \"" << err.str << "\", value " << err.value << "\n";
				std::cout << "Value out of range [1.. 2147483647].\n";
				break;

			// Круговая дорога
			case(5):
				std::cout << "Error in line \"" << err.str << "\"\n";
				std::cout << "Road cannot lead to the origin.\n";
				break;

			// Несуществующий город
			case(6):
				std::cout << "Error in value " << err.value << "\n";
				std::cout << "Town was not defined in the prices part.\n";
				break;
			}
		}
	}

	output.close();

}