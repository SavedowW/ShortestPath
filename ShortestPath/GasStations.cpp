#include "GasStations.h"

void ParseStream(std::ifstream& input_, std::vector<InfInt>& prices_, std::vector<std::pair<int, int>>& roads_)
{
	std::string line;

	//Считать, что считываются одиночные числа
	bool readingPrices = true;

	while (std::getline(input_, line)) //Пока возможно считать строку
	{
		if (std::end(line) != std::find_if(line.begin(), line.end(),
			[](char val)
			{
				return (val < '0' || val > '9') && val != ' ';
			})) //Если в строке есть символы кроме цифр и пробелов
			//Заполнить структуру ErrorInfo и выбросить исключение 1
			throw ErrorInfo{ 1, line };

		//Считать числа из строки
		

		//Если в строке 0 или больше 2 - х чисел
			//Заполнить структуру ErrorInfo и выбросить исключение 2
		//Если считываются одиночные числа
		{
			//Если в строке 2 числа
				//Считать, что считываются пары
			//Иначе
			{
				//Если число находится вне диапазона
					//Заполнить структуру ErrorInfo и выбросить исключение 4
				//Сохранить число как цену
			}
		}

		//Если считываются пары
		{
			//Если в строке только 1 число
				//Заполнить структуру ErrorInfo и выбросить исключение 3
			//Если одно из чисел находится вне диапазона
				//Заполнить структуру ErrorInfo и выбросить исключение 4
			//Если числа равны
				//Заполнить структуру ErrorInfo и выбросить исключение 5
			//Если такая же пара еще не сохранена
				//Сохранить их как пару городов
		}
	}

	//Если среди записанных городов есть город с номером выше количества цен + 1
		//Заполнить структуру ErrorInfo и выбросить исключение 6


}

std::vector<std::vector<InfInt>> BuildMatrix(const std::vector<InfInt>& prices_, const std::vector<std::pair<int, int>>& roads_)
{
	return std::vector<std::vector<InfInt>>();
}

InfInt DijkstraAlgorithm(const std::vector<std::vector<InfInt>>& paths_)
{
	return InfInt();
}

std::vector<InfInt> ParseLineToInts(const std::string& line_)
{
	std::vector<InfInt> res;
	bool isNumberEntering = false;

	//Обнулить считываемое число
	std::string temp = "";
	
	for (const auto& ch : line_) //Для каждого символа входной строки с первого до последнего
	{
		if (ch == ' ') //Если символ является пробелом
		{
			if (isNumberEntering) //Если вводится число
			{
				//Добавить считываемое число в вектор
				res.push_back(InfInt(temp));
				
				//Обнулить считываемое число
				temp = "";

				//Считать, что число не считывается
				isNumberEntering = false;
			}
		}
		else if (ch >= '0' && ch <= '9') //Иначе если символ является цифрой
		{
			//Добавить ее к считываемому числу как младший разряд
			temp += ch;
			
			//Считать, что число считывается
			isNumberEntering = true;
		}
	}

	if (isNumberEntering) //Если число считывается
		//Добавить считываемое число в вектор
		res.push_back(InfInt(temp));

	return res;
}
