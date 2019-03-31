#pragma once
#include <string>
#include <map>
class ParaReader
{
public:
	ParaReader();
	~ParaReader();

	static ParaReader FromString(const int argc,const char* argv[]);
	bool HasFlag(const std::string& flag); 

	void AddKeyValue(const std::string& flag, const std::string& value); 
	std::string GetValue(const std::string& flag);

	int GetNumber(const std::string& flag);
private:
	std::map<std::string, std::string>  _keyValues;
};

