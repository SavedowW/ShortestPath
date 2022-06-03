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
		auto numbers = ParseLineToInts(line);

		if (numbers.size() > 2 || numbers.size() == 0) //Если в строке 0 или больше 2 - х чисел
			throw ErrorInfo{ 2, line }; //Заполнить структуру ErrorInfo и выбросить исключение 2
		if (readingPrices) //Если считываются одиночные числа
		{
			if (numbers.size() == 2) //Если в строке 2 числа
				//Считать, что считываются пары
				readingPrices = false;
			else //Иначе
			{
				if (numbers[0] > ARGUMENT_UPPER_LIMIT || numbers[0] < 1) //Если число находится вне диапазона
					//Заполнить структуру ErrorInfo и выбросить исключение 4
					throw ErrorInfo{4, line, numbers[0]};

				//Сохранить число как цену
				prices_.push_back(numbers[0]);
			}
		}

		if (!readingPrices) //Если считываются пары
		{
			if (numbers.size() == 1) //Если в строке только 1 число
				throw ErrorInfo{3, line}; //Заполнить структуру ErrorInfo и выбросить исключение 3

			for (auto& elem : numbers)
				if (numbers[0] > ARGUMENT_UPPER_LIMIT || numbers[0] < 1) //Если одно из чисел находится вне диапазона
					throw ErrorInfo{ 4, line, elem }; //Заполнить структуру ErrorInfo и выбросить исключение 4

			if (numbers[0] == numbers[1]) //Если числа равны
				//Заполнить структуру ErrorInfo и выбросить исключение 5
				throw ErrorInfo{5, line};

			//Если такая же пара еще не сохранена
			if (!(std::find(roads_.begin(), roads_.end(), std::pair<int, int>(numbers[0].toInt(), numbers[1].toInt())) != roads_.end()) &&
				!(std::find(roads_.begin(), roads_.end(), std::pair<int, int>(numbers[1].toInt(), numbers[0].toInt())) != roads_.end()))
				//Сохранить их как пару городов
				roads_.push_back({numbers[0].toInt(), numbers[1].toInt()});
		}
	}

	//Если среди записанных городов есть город с номером выше количества цен + 1
	for (auto& elem : roads_)
		if (elem.first > prices_.size() + 1)
			//Заполнить структуру ErrorInfo и выбросить исключение 6
			throw ErrorInfo{6, "", elem.first};
		else if (elem.second > prices_.size() + 1)
			//Заполнить структуру ErrorInfo и выбросить исключение 6
			throw ErrorInfo{6, "", elem.second};
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
