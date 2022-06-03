#include "GasStations.h"
#include <set>

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
	//������� ���������� ������� � ��������, ������ ���������� �������
	int target = prices_.size();
	int size = target + 1;
	if (target == 0)
		size = 0;
	std::vector<std::vector<InfInt>> a(size);

	for (int i = 0; i < a.size(); ++i)
	{
		a[i].resize(size);
		for (int k = 0; k < a[i].size(); ++k) //��� ������� �������� �������
		{
			//������� ������� ������� ������ 0
			a[i][k] = 0;

			if (i != target && //���� ���� ������ ������ � ������� ������������ � ������ ����� � �������� ����� �� ���������
				(std::find(roads_.begin(), roads_.end(), std::pair<int, int>{i + 1, k + 1}) != roads_.end() ||
				 std::find(roads_.begin(), roads_.end(), std::pair<int, int>{k + 1, i + 1}) != roads_.end())) 
			{
				//������� ������� ������ ���� � ������, �� �������� ���� ������
				a[i][k] = prices_[i];
			}
		}
	}

	//������� ���������� �������
	return a;
}

InfInt DijkstraAlgorithm(const std::vector<std::vector<InfInt>>& paths_)
{
	std::set<int> visited;

	//�������, ��� ����� ���� ������� ����� -1, � � ������� - 0
	std::vector<InfInt> marks(paths_.size(), -1);
	marks[0] = 0;

	//������ ����� ������� � 0-��
	int toProceed = 0;
	while (toProceed != -1) //���� ���� ������, ������� ����� ������
	{
		//�������� ������ �������, ������������� � �������
		std::set<int> neighbours;
		for (int i = 0; i < paths_[toProceed].size(); ++i)
		{
			if (paths_[toProceed][i] > 0 && !visited.contains(i))
				neighbours.insert(i);
		}

		//��� ���� �������� �������
		for (auto& i : neighbours)
		{
			//���������� ����� �����
			InfInt newMark = marks[toProceed] + paths_[toProceed][i];

			//�������� �����, ���� ��� �� ���� �� ����� ����������� ��� ���� ����� ������ ������
			if (marks[i] == -1 || marks[i] > newMark)
				marks[i] = newMark;
		}
		//������� ������� ����� ����������
		visited.insert(toProceed);

		toProceed = -1;
		InfInt minPathLen = -1;
		int townWithMinLen = -1;
		for (auto& i : visited) //��� ���� ���������� �������
		{
			for (int k = 0; k < paths_[i].size(); ++k)
			{
				if (paths_[i][k] != 0 && !visited.contains(k))  //��� ���� �������, ��������� � ���������� 
				{
					if (minPathLen == -1 || paths_[i][k] < minPathLen) //���� ������ �� ������ ������ �����������
					{
						//��������� ���
						minPathLen = paths_[i][k];
						townWithMinLen = k;
					}
				}
			}
		}

		//�������� ������� �����
		toProceed = townWithMinLen;
	}
	
	if (marks[paths_.size() - 1] == -1) //���� �������� ����� �� ��� �������
		//��������� ����������
		throw ErrorInfo{ 0 };
	else //�����
		//������� ���� ���� �� ����
		return marks[paths_.size() - 1];
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
