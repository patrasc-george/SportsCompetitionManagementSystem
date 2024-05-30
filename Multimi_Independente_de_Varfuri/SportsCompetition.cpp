#include "SportsCompetition.h"

SportsCompetition::SportsCompetition(const uint16_t& id, const std::string& name) : id(id), name(name)
{}

uint16_t SportsCompetition::GetId() const
{
	return id;
}

std::string SportsCompetition::GetName() const
{
	return name;
}

std::vector<SportsCompetition> SportsCompetition::GetEnrolleds() const
{
	return enrolleds;
}

void SportsCompetition::AddEnroll(const SportsCompetition& sportsCompetition)
{
	enrolleds.push_back(sportsCompetition);
}

bool SportsCompetition::Find(const SportsCompetition& sportsCompetition)
{
	for (const auto& enrolled : enrolleds)
		if (enrolled == sportsCompetition)
			return true;
	return false;
}

std::ostream& operator<<(std::ostream& out, const SportsCompetition& sportsCompetition)
{
	out << sportsCompetition.GetName();
	return out;
}

bool SportsCompetition::operator==(const SportsCompetition& sportsCompetition) const
{
	return id == sportsCompetition.id;
}
