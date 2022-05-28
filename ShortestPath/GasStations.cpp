#include "GasStations.h"

void ParseStream(std::ifstream& input_, std::vector<InfInt>& prices_, std::vector<std::pair<int, int>>& roads_)
{
	std::string line;

	//�������, ��� ����������� ��������� �����
	bool readingPrices = true;

	while (std::getline(input_, line)) //���� �������� ������� ������
	{
		if (std::end(line) != std::find_if(line.begin(), line.end(),
			[](char val)
			{
				return (val < '0' || val > '9') && val != ' ';
			})) //���� � ������ ���� ������� ����� ���� � ��������
			//��������� ��������� ErrorInfo � ��������� ���������� 1
			throw ErrorInfo{ 1, line };

		//������� ����� �� ������
		

		//���� � ������ 0 ��� ������ 2 - � �����
			//��������� ��������� ErrorInfo � ��������� ���������� 2
		//���� ����������� ��������� �����
		{
			//���� � ������ 2 �����
				//�������, ��� ����������� ����
			//�����
			{
				//���� ����� ��������� ��� ���������
					//��������� ��������� ErrorInfo � ��������� ���������� 4
				//��������� ����� ��� ����
			}
		}

		//���� ����������� ����
		{
			//���� � ������ ������ 1 �����
				//��������� ��������� ErrorInfo � ��������� ���������� 3
			//���� ���� �� ����� ��������� ��� ���������
				//��������� ��������� ErrorInfo � ��������� ���������� 4
			//���� ����� �����
				//��������� ��������� ErrorInfo � ��������� ���������� 5
			//���� ����� �� ���� ��� �� ���������
				//��������� �� ��� ���� �������
		}
	}

	//���� ����� ���������� ������� ���� ����� � ������� ���� ���������� ��� + 1
		//��������� ��������� ErrorInfo � ��������� ���������� 6


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

	//�������� ����������� �����
	std::string temp = "";
	
	for (const auto& ch : line_) //��� ������� ������� ������� ������ � ������� �� ����������
	{
		if (ch == ' ') //���� ������ �������� ��������
		{
			if (isNumberEntering) //���� �������� �����
			{
				//�������� ����������� ����� � ������
				res.push_back(InfInt(temp));
				
				//�������� ����������� �����
				temp = "";

				//�������, ��� ����� �� �����������
				isNumberEntering = false;
			}
		}
		else if (ch >= '0' && ch <= '9') //����� ���� ������ �������� ������
		{
			//�������� �� � ������������ ����� ��� ������� ������
			temp += ch;
			
			//�������, ��� ����� �����������
			isNumberEntering = true;
		}
	}

	if (isNumberEntering) //���� ����� �����������
		//�������� ����������� ����� � ������
		res.push_back(InfInt(temp));

	return res;
}
