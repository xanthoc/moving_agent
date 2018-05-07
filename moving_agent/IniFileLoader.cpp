#include "stdafx.h"
#include "IniFileLoader.h"


IniFileLoader::IniFileLoader(const std::string &filename)
{
	m_file.open(filename.c_str());
}


IniFileLoader::~IniFileLoader()
{
	// "closing file" is not necessary by RAII
}


void IniFileLoader::remove_comment(std::string &line) {
	size_t idx = line.find("//");
	if (idx == std::string::npos) return;
	else line = line.substr(0, idx);
}

std::string IniFileLoader::get_next_parameter() {
	std::string res;
	while (std::getline(m_file, res)) {
		remove_comment(res);
		if (res.length() == 0) continue;
		size_t idx = res.find(" ");
		if (idx == std::string::npos || idx==0) throw std::runtime_error("bad file");
		idx = res.find_first_not_of(" ", idx);
		if (idx == std::string::npos) throw std::runtime_error("bad file");
		return res.substr(idx);
	}
	throw std::runtime_error("file read error");
}

