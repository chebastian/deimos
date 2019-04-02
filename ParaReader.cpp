#include "ParaReader.h"


ParaReader::ParaReader()
{
	_keyValues = std::map<std::string, std::string>();
	_switches = std::vector<std::string>();
}


ParaReader::~ParaReader()
{
} 

bool IsFlag(const std::string& arg)
{
	return arg.find('-') == 0;
}

ParaReader ParaReader::FromString(const int argc, char* argv[])
{
	auto reader = ParaReader();
	for (int i = 0; i < argc; i++)
	{ 
		if (IsFlag(argv[i]))
		{ 
			if (reader.HasSwitch(argv[i]))
			{ 
				reader.AddKeyValue(argv[i], "");
			}
			else
				reader.AddKeyValue(argv[i],argv[i+1]);
		}
	}

	return reader;
}

ParaReader ParaReader::FromStringWithSwitches(const int argc, char* argv[], std::vector<std::string> switches)
{
	auto reader = ParaReader();
	for (auto sw : switches)
		reader.AddSwitchWithName(sw);

	for (int i = 0; i < argc; i++)
	{ 
		if (IsFlag(argv[i]))
		{ 
			if (reader.HasSwitch(argv[i]))
			{ 
				reader.AddKeyValue(argv[i], "");
			}
			else if(i+1 < argc)
			{ 
				reader.AddKeyValue(argv[i],argv[i+1]); 
			}
		}
	}

	return reader;

}

void ParaReader::AddSwitchWithName(const std::string& name)
{
	if (std::find(std::begin(_switches), std::end(_switches),name) != std::end(_switches))
	{ 
		return;
	}

	_switches.push_back(name);
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

int ParaReader::GetNumberOrdefault(const std::string& flag, int def)
{
	if (_keyValues.find(flag) != _keyValues.end())
		return std::stoi( _keyValues[flag] );

	return def;
}

bool ParaReader::HasFlag(const std::string& flag)
{
	return _keyValues.find(flag) != _keyValues.end();
}
bool ParaReader::HasSwitch(const std::string& flag)
{
	return std::find(std::begin(_switches), std::end(_switches), flag) != std::end(_switches);
}

