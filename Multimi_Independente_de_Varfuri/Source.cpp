#include <sstream>
#include <fstream>
#include <queue>
#include <unordered_map>

#include "Student.h"
#include "SportsCompetition.h"

void ReadFile(std::vector<SportsCompetition>& sportsCompetitions)
{
	std::string line;
	uint16_t k = 0;
	std::ifstream f("AdjacencyList.txt");

	std::getline(f, line);
	while (!line.empty())
	{
		sportsCompetitions.push_back(SportsCompetition(sportsCompetitions.size(), line));
		std::getline(f, line);
	}

	while (!f.eof())
	{
		std::getline(f, line);
		std::vector<uint16_t> adjacent;
		std::stringstream ss(line);
		std::string element;

		while (std::getline(ss, element, ' '))
			adjacent.push_back(std::stoi(element));

		for (const auto& index : adjacent)
			sportsCompetitions[k].AddEnroll(sportsCompetitions[index]);
		k++;
	}
	std::cout << "The adjacency list was read successfully." << std::endl << std::endl;
}

bool Find(const std::string& name, const std::vector<SportsCompetition>& sportsCompetitions)
{
	for (const auto& sportCompetitions : sportsCompetitions)
		if (sportCompetitions.GetName() == name)
			return true;
	return false;
}

void AddSportsCompetition(std::vector<SportsCompetition>& sportsCompetitions)
{
	std::string name;
	std::cout << "Name: ";
	std::cin >> name;
	while (Find(name, sportsCompetitions))
	{
		std::cout << "This sports competition already exists. Add another: ";
		std::cin >> name;
	}
	std::cout << std::endl;
	sportsCompetitions.push_back(SportsCompetition(sportsCompetitions.size(), name));
}

uint16_t NumberEnrolls(const std::vector<SportsCompetition>& sportsCompetitions)
{
	uint16_t numberEnrolls = 0;
	for (const SportsCompetition& sportsCompetition : sportsCompetitions)
		numberEnrolls += sportsCompetition.GetEnrolleds().size();
	return numberEnrolls;
}

void Verify(uint16_t& idSportsCompetition, const std::vector<SportsCompetition>& sportsCompetitions)
{
	std::cin >> idSportsCompetition;
	idSportsCompetition--;
	while (idSportsCompetition >= sportsCompetitions.size() || idSportsCompetition < 0)
	{
		std::cout << "Invalid sports competition id. Please select a valid id:" << std::endl;
		std::cin >> idSportsCompetition;
		idSportsCompetition--;
	}
}

void Enroll(std::vector<SportsCompetition>& sportsCompetitions)
{
	if (sportsCompetitions.empty())
	{
		std::cout << "There are not enough sports competitions." << std::endl << std::endl;
		return;
	}

	if (NumberEnrolls(sportsCompetitions) == std::pow(sportsCompetitions.size(), 2))
	{
		std::cout << "Enrolls are no longer possible." << std::endl << std::endl;
		return;
	}

	std::cout << std::endl;
	for (const SportsCompetition& sportsCompetition : sportsCompetitions)
		std::cout << sportsCompetition.GetId() + 1 << ". " << sportsCompetition.GetName() << std::endl;

	uint16_t idSportsCompetitionFirst, idSportsCompetitionSecond;
	std::cout << "Select the first sports competition:" << std::endl;
	Verify(idSportsCompetitionFirst, sportsCompetitions);
	std::cout << "Select the second sports competition:" << std::endl;
	Verify(idSportsCompetitionSecond, sportsCompetitions);

	if (idSportsCompetitionFirst != idSportsCompetitionSecond && !sportsCompetitions[idSportsCompetitionFirst].Find(sportsCompetitions[idSportsCompetitionSecond]))
	{
		sportsCompetitions[idSportsCompetitionFirst].AddEnroll(sportsCompetitions[idSportsCompetitionSecond]);
		sportsCompetitions[idSportsCompetitionSecond].AddEnroll(sportsCompetitions[idSportsCompetitionFirst]);
		std::cout << "The enroll was done successfully." << std::endl << std::endl;
	}
	else
		std::cout << "The enrollment already exists." << std::endl << std::endl;
}

void PlanningSportsCompetitions(const std::vector<SportsCompetition>& sportsCompetitions)
{
	std::vector<uint16_t> sportsIndex;
	std::unordered_map<uint16_t, bool> adjacent;
	std::priority_queue<std::pair<uint16_t, uint16_t>, std::vector<std::pair<uint16_t, uint16_t>>, std::greater<std::pair<uint16_t, uint16_t>>> q;

	for (uint16_t i = 0; i < sportsCompetitions.size(); i++)
		q.push(std::make_pair(sportsCompetitions[i].GetEnrolleds().size(), i));

	while (!q.empty())
	{
		auto p = q.top();
		q.pop();
		uint16_t index = p.second;
		if (!adjacent[index])
		{
			sportsIndex.push_back(index);
			for (auto neighbor : sportsCompetitions[index].GetEnrolleds())
				adjacent[neighbor.GetId()] = true;
		}
	}

	std::cout << "The sports competitions that can be organized are: ";
	for (const auto& index : sportsIndex)
		std::cout << sportsCompetitions[index] << " ";
	std::cout << std::endl << std::endl;
}

int main()
{
	uint16_t choice = 0;
	std::vector<SportsCompetition> sportsCompetitions;
	while (choice != 5)
	{
		std::cout << "1. Reads the adjacency list from the text file." << std::endl;
		std::cout << "2. Add a sports competition." << std::endl;
		std::cout << "3. Enroll a student in a sports competition." << std::endl;
		std::cout << "4. Print the sports competitions that can be started." << std::endl;
		std::cout << "5. Exit" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			ReadFile(sportsCompetitions);
			break;
		case 2:
			AddSportsCompetition(sportsCompetitions);
			break;
		case 3:
			Enroll(sportsCompetitions);
			break;
		case 4:
			PlanningSportsCompetitions(sportsCompetitions);
			break;
		}
	}
	return 0;
}