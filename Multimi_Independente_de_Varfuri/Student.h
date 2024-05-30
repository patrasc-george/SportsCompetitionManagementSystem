#pragma once
#include <iostream>

class Student
{
public:
	Student(const uint16_t& id, const std::string& name);

	uint16_t GetId() const;
	std::string GetName() const;

private:
	uint16_t id;
	std::string name;
};