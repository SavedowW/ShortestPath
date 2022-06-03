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
		auto numbers = ParseLineToInts(line);

		if (numbers.size() > 2 || numbers.size() == 0) //���� � ������ 0 ��� ������ 2 - � �����
			throw ErrorInfo{ 2, line }; //��������� ��������� ErrorInfo � ��������� ���������� 2
		if (readingPrices) //���� ����������� ��������� �����
		{
			if (numbers.size() == 2) //���� � ������ 2 �����
				//�������, ��� ����������� ����
				readingPrices = false;
			else //�����
			{
				if (numbers[0] > ARGUMENT_UPPER_LIMIT || numbers[0] < 1) //���� ����� ��������� ��� ���������
					//��������� ��������� ErrorInfo � ��������� ���������� 4
					throw ErrorInfo{4, line, numbers[0]};

				//��������� ����� ��� ����
				prices_.push_back(numbers[0]);
			}
		}

		if (!readingPrices) //���� ����������� ����
		{
			if (numbers.size() == 1) //���� � ������ ������ 1 �����
				throw ErrorInfo{3, line}; //��������� ��������� ErrorInfo � ��������� ���������� 3

			for (auto& elem : numbers)
				if (numbers[0] > ARGUMENT_UPPER_LIMIT || numbers[0] < 1) //���� ���� �� ����� ��������� ��� ���������
					throw ErrorInfo{ 4, line, elem }; //��������� ��������� ErrorInfo � ��������� ���������� 4

			if (numbers[0] == numbers[1]) //���� ����� �����
				//��������� ��������� ErrorInfo � ��������� ���������� 5
				throw ErrorInfo{5, line};

			//���� ����� �� ���� ��� �� ���������
			if (!(std::find(roads_.begin(), roads_.end(), std::pair<int, int>(numbers[0].toInt(), numbers[1].toInt())) != roads_.end()) &&
				!(std::find(roads_.begin(), roads_.end(), std::pair<int, int>(numbers[1].toInt(), numbers[0].toInt())) != roads_.end()))
				//��������� �� ��� ���� �������
				roads_.push_back({numbers[0].toInt(), numbers[1].toInt()});
		}
	}

	//���� ����� ���������� ������� ���� ����� � ������� ���� ���������� ��� + 1
	for (auto& elem : roads_)
		if (elem.first > prices_.size() + 1)
			//��������� ��������� ErrorInfo � ��������� ���������� 6
			throw ErrorInfo{6, "", elem.first};
		else if (elem.second > prices_.size() + 1)
			//��������� ��������� ErrorInfo � ��������� ���������� 6
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
