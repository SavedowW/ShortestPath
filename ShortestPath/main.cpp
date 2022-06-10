#include "GasStations.h"
#include <fstream>

int main(const int argc, char** argv)
{
	//������ ������, ���� ������� ���� �� ������ � ���������� ��������� ������
	if (argc == 1)
	{
		std::cout << "Input file is not defined in arguments.\n";
		return 1;
	}
	//������ ������, ���� �������� ���� �� ������ � ���������� ��������� ������
	if (argc == 2)
	{
		std::cout << "Output file is not defined in arguments.\n";
		return 2;
	}
	//������ ������, ���� ������� ���� ���������� �������
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
		//������� ���������� �����
		ParseStream(input, prices, roads);
		input.close();

		//��������� ������� ����� �����
		std::vector<std::vector<InfInt>> mat;
		BuildMatrix(prices, roads, mat);
		
		//������ �������� ��������
		auto result = DijkstraAlgorithm(mat);
		
		//�������� ����� ����������� ���� � �������� ����
		output << result;
		
	}
	catch (ErrorInfo err) //���� ���� ��������� ����������
	{
		if (err.excID == 0) //���� ���� ���
		{
			//�������� � �������� ���� �������� �� ����������
			output << "No solution";
		}
		else //�����
		{
			//������������ � ������� ���������� �� ������
			switch (err.excID)
			{
			// ������� ����� ���� � ��������
			case(1):
				std::cout << "Error in line \"" << err.str << "\"\n";
				std::cout << "Only natural numbers are allowed in input.\n";
				break;

			// � ������ 0 ��� ������ 2 �����
			case(2):
				std::cout << "Error in line \"" << err.str << "\"\n";
				std::cout << "Line can contain only 1 or 2 numbers.\n";
				break;

			// � ������� ������ 1 �����
			case(3):
				std::cout << "Error in line \"" << err.str << "\"\n";
				std::cout << "Line with road should contain 2 numbers.\n";
				break;

			// ����� ��� ���������
			case(4):
				std::cout << "Error in line \"" << err.str << "\", value " << err.value << "\n";
				std::cout << "Value out of range [1.. 2147483647].\n";
				break;

			// �������� ������
			case(5):
				std::cout << "Error in line \"" << err.str << "\"\n";
				std::cout << "Road cannot lead to the origin.\n";
				break;

			// �������������� �����
			case(6):
				std::cout << "Error in value " << err.value << "\n";
				std::cout << "Town was not defined in the prices part.\n";
				break;
			}
		}
	}

	output.close();

}