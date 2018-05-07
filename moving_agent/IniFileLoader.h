#pragma once
#include <fstream>
#include <string>

class IniFileLoader
{
	std::ifstream m_file;
	std::string get_next_parameter();
	void remove_comment(std::string &line);
public:
	IniFileLoader(const std::string &filename);
	~IniFileLoader();
	int get_parameter_as_int() { return atoi(get_next_parameter().c_str()); }
	double get_parameter_as_double() { return atof(get_next_parameter().c_str()); }
};

