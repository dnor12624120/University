#pragma once

#include <string>
#include <exception>

static const std::string getFileExtension(const std::string& file)
{
	auto location = file.find_last_of(".");
	if (location >= file.size())
	{
		throw std::exception("File has no extension!");
	}
	return file.substr(location + 1);
}