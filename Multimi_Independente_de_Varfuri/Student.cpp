#include "Student.h"

Student::Student(const uint16_t& id, const std::string& name) : id(id), name(name)
{}

uint16_t Student::GetId() const
{
	return id;
}

std::string Student::GetName() const
{
	return name;
}