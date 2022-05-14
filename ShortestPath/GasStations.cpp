#include "GasStations.h"

void ParseStream(std::ifstream& input_, std::vector<InfInt>& prices_, std::vector<std::pair<int, int>>& roads_)
{
	return;
}

/*!
* \Строит матрицу графа
* \param[in] prices_ - цены в городах
* \param[in] roads_ - пары городов, между которыми есть дороги
* \return – матрица графа
*/
std::vector<std::vector<InfInt>> BuildMatrix(const std::vector<InfInt>& prices_, const std::vector<std::pair<int, int>>& roads_)
{
	return std::vector<std::vector<InfInt>>();
}

/*!
* \Находит цену кратчайшего пути с помощью алгоритма Дейкстры
* \param[in] paths_ - матрица графа
* \return – цена кратчайшего пути
*/
InfInt DijkstraAlgorithm(const std::vector<std::vector<InfInt>>& paths_)
{
	return InfInt();
}

/*!
* \Разбивает строку из натуральных чисел на отдельные числа
* \param[in] line_ - входная строка
* \return – вектор отдельных чисел
*/
std::vector<InfInt> ParseLineToInts(const std::string& line_)
{
	return std::vector<InfInt>();
}
