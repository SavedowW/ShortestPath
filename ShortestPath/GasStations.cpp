#include "GasStations.h"
#include <set>

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
	//Создать квадратную матрицу с размером, равным количеству городов
	int target = prices_.size();
	int size = target + 1;
	if (target == 0)
		size = 0;
	std::vector<std::vector<InfInt>> a(size);

	for (int i = 0; i < a.size(); ++i)
	{
		a[i].resize(size);
		for (int k = 0; k < a[i].size(); ++k) //Для каждого элемента матрицы
		{
			//Считать элемент матрицы равным 0
			a[i][k] = 0;

			if (i != target && //Если пара номера строки и столбца присутствует в списке дорог и исходный город не конечныйц
				(std::find(roads_.begin(), roads_.end(), std::pair<int, int>{i + 1, k + 1}) != roads_.end() ||
				 std::find(roads_.begin(), roads_.end(), std::pair<int, int>{k + 1, i + 1}) != roads_.end())) 
			{
				//Считать элемент равным цене в городе, из которого идет дорога
				a[i][k] = prices_[i];
			}
		}
	}

	//Вернуть полученную матрицу
	return a;
}

InfInt DijkstraAlgorithm(const std::vector<std::vector<InfInt>>& paths_)
{
	std::set<int> visited;

	//Считать, что метки всех городов равны -1, и у первого - 0
	std::vector<InfInt> marks(paths_.size(), -1);
	marks[0] = 0;

	//Начать обход городов с 0-го
	int toProceed = 0;
	while (toProceed != -1) //Пока есть города, которые можно обойти
	{
		//Получить список городов, соседствующих с текущим
		std::set<int> neighbours;
		for (int i = 0; i < paths_[toProceed].size(); ++i)
		{
			if (paths_[toProceed][i] > 0 && !visited.contains(i))
				neighbours.insert(i);
		}

		//Для всех соседних городов
		for (auto& i : neighbours)
		{
			//Рассчитать новую метку
			InfInt newMark = marks[toProceed] + paths_[toProceed][i];

			//Обновить метку, если она не была до этого установлена или если новая меньше старой
			if (marks[i] == -1 || marks[i] > newMark)
				marks[i] = newMark;
		}
		//Считать текущий город посещенным
		visited.insert(toProceed);

		toProceed = -1;
		InfInt minPathLen = -1;
		int townWithMinLen = -1;
		for (auto& i : visited) //Для всех посещенных городов
		{
			for (int k = 0; k < paths_[i].size(); ++k)
			{
				if (paths_[i][k] != 0 && !visited.contains(k))  //Для всех городов, связанных с посещенным 
				{
					if (minPathLen == -1 || paths_[i][k] < minPathLen) //Если дорога до города меньше сохраненной
					{
						//Сохранить его
						minPathLen = paths_[i][k];
						townWithMinLen = k;
					}
				}
			}
		}

		//Обновить текущий город
		toProceed = townWithMinLen;
	}
	
	if (marks[paths_.size() - 1] == -1) //Если конечный город не был обойден
		//Выбросить исключение
		throw ErrorInfo{ 0 };
	else //Иначе
		//Вернуть цену пути до него
		return marks[paths_.size() - 1];
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
