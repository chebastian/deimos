#include "ParaReader.h"


ParaReader::ParaReader()
{
	_keyValues = std::map<std::string, std::string>();
}


ParaReader::~ParaReader()
{
} 

bool IsFlag(const std::string& arg)
{
	return arg.find('-') == 0;
}

ParaReader ParaReader::FromString(const int argc, const char* argv[])
{
	auto reader = ParaReader();
	for (int i = 0; i < argc; i++)
	{ 
		if (IsFlag(argv[i]))
		{ 
			reader.AddKeyValue(argv[i],argv[i+1]);
		}
	}

	return reader;
}


void ParaReader::AddKeyValue(const std::string& flag, const std::string& value)
{
	_keyValues[flag] = value;
}

std::string ParaReader::GetValue(const std::string& flag)
{
	return _keyValues[flag];
}

int ParaReader::GetNumber(const std::string& flag)
{
	return std::stoi(GetValue(flag));
}

bool ParaReader::HasFlag(const std::string& flag)
{
	return _keyValues.find(flag) != _keyValues.end();
} 
