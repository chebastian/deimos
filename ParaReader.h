#pragma once
#include <string>
#include <map>
#include <vector>

class ParaReader
{
public:
	ParaReader();
	~ParaReader();

	static ParaReader FromString(const int argc,char* argv[]);
	static ParaReader FromStringWithSwitches(const int argc,char* argv[], std::vector<std::string> switches);
	void AddSwitchWithName(const std::string& name);
	bool HasFlag(const std::string& flag); 
	bool HasSwitch(const std::string& flag);

	void AddKeyValue(const std::string& flag, const std::string& value); 
	std::string GetValue(const std::string& flag); 
	int GetNumber(const std::string& flag);
	int GetNumberOrdefault(const std::string& flag, int def);
private:
	std::map<std::string, std::string>  _keyValues;
	std::vector<std::string> _switches;
};

