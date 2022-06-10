#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "InfInt.h"
#include <set>
#include <list>

struct ErrorInfo
{
	int excID = 0;
	std::string str = "";
	InfInt value = 0;
};

const InfInt ARGUMENT_UPPER_LIMIT("2147483647");

/*!
* \Считывет входные данные
* \param[in] input_ - поток входных данныъ
* \param[out] prices_ - цены в городах
* \param[out] roads_ - пары городов, между которыми есть дороги
*/
void ParseStream(std::ifstream& input_, std::vector<InfInt>& prices_, std::set<std::pair<int, int>>& roads_);

/*!
* \Строит матрицу графа
* \param[in] prices_ - цены в городах
* \param[in] roads_ - пары городов, между которыми есть дороги
* \return – матрица графа
*/
std::vector<std::vector<InfInt>> BuildMatrix(const std::vector<InfInt>& prices_, const std::set<std::pair<int, int>>& roads_);

/*!
* \Находит цену кратчайшего пути с помощью алгоритма Дейкстры
* \param[in] paths_ - матрица графа
* \return – цена кратчайшего пути
*/
InfInt DijkstraAlgorithm(const std::vector<std::vector<InfInt>>& paths_);

/*!
* \Разбивает строку из натуральных чисел на отдельные числа
* \param[in] line_ - входная строка
* \return – вектор отдельных чисел
*/
std::vector<InfInt> ParseLineToInts(const std::string& line_);
