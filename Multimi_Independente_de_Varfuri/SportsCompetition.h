#pragma once
#include <iostream>
#include <vector>

class SportsCompetition
{
public:
	SportsCompetition(const uint16_t& id, const std::string& name);

	uint16_t GetId() const;
	std::string GetName() const;
	std::vector<SportsCompetition> GetEnrolleds() const;

	void AddEnroll(const SportsCompetition& sportsCompetition);
	bool Find(const SportsCompetition& sportsCompetition);

	friend std::ostream& operator<<(std::ostream& out, const SportsCompetition& sportsCompetition);
	bool operator==(const SportsCompetition& sportsCompetition) const;

private:
	uint16_t id;
	std::string name;
	std::vector<SportsCompetition> enrolleds;
};