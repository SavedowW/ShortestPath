#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "InfInt.h"

/*!
	\brief ��������� ��� ���� ���������� � �������

	������ ��� ������ �, ��� �������������, ������ � / ��� �������� � �������
*/
struct ErrorInfo
{
	int excID = 0;
	std::string str = "";
	InfInt value = 0;
};

const InfInt ARGUMENT_UPPER_LIMIT("2147483647");  ///< ������������ ����������� ��� ������� ������

/*!
* �������� ������� ������
* \param[in] input_ - ����� ������� ������
* \param[out] prices_ - ���� � �������
* \param[out] roads_ - ���� �������, ����� �������� ���� ������
*/
void ParseStream(std::ifstream& input_, std::vector<InfInt>& prices_, std::vector<std::pair<int, int>>& roads_);

/*!
* ������ ������� �����
* \param[in] prices_ - ���� � �������
* \param[in] roads_ - ���� �������, ����� �������� ���� ������
* \return � ������� �����
*/
std::vector<std::vector<InfInt>> BuildMatrix(const std::vector<InfInt>& prices_, const std::vector<std::pair<int, int>>& roads_);

/*!
* ������� ���� ����������� ���� � ������� ��������� ��������
* \param[in] paths_ - ������� �����
* \return � ���� ����������� ����
*/
InfInt DijkstraAlgorithm(const std::vector<std::vector<InfInt>>& paths_);

/*!
* ��������� ������ �� ����������� ����� �� ��������� �����
* \param[in] line_ - ������� ������
* \return � ������ ��������� �����
*/
std::vector<InfInt> ParseLineToInts(const std::string& line_);
