// Deimos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <codecvt>
#include "ParaReader.h"
#include <exception>
#include <Windows.h>
#include <sstream>
#include <iterator>
#include <algorithm>

#define ulong unsigned long

char const hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',   'B','C','D','E','F'};

std::string byte_2_str(char byte)
{
	std::string str;
	str.append(&hex[(byte & 0xF0) >> 4], 1);
	str.append(&hex[byte & 0xF], 1);
	return str;
} 

void PrintBytes(std::ifstream* stream, ulong start, ulong sz)
{

	std::vector<char> bytes(sz); 
	stream->seekg(start, std::ios::beg);
	stream->read(&bytes[0],sz);

	int i = 0;
	for (auto b : bytes)
	{
		std::cout << byte_2_str(b) << " ";
		i++;
		if (i % 16 == 0)
			std::cout << std::endl;
	}
}

void PrintAsAscii(std::ifstream* stream, ulong start, ulong sz)
{
	std::vector<char> bytes(sz); 
	stream->seekg(start, std::ios::beg);
	stream->read(&bytes[0],sz);

	int i = 0;
	for (auto b : bytes)
	{
		std::cout << b;
		i++;
		if (i % 16 == 0)
			std::cout << std::endl;
	} 
}

void PrintAsWideChar(std::ifstream* stream, ulong start, ulong sz)
{
	std::vector<char> bytes(sz); 
	stream->seekg(start, std::ios::beg);
	stream->read(&bytes[0],sz); 

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter; 

	try {
		auto str = converter.from_bytes(bytes.data(),bytes.data() + bytes.size()); 
		std::wcout << str;
	}
	catch(std::exception e)
	{
		std::cout << "Could not convert to WideChar utf8" << std::endl; 
	}
}

void PrintAsUnicode(std::ifstream* stream, ulong start, ulong sz)
{
	std::vector<char> bytes(sz); 
	stream->seekg(start, std::ios::beg);
	stream->read(&bytes[0],sz); 

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter; 
	try {
		auto str = converter.from_bytes(bytes.data(), bytes.data() + bytes.size());
		std::wcout << str;
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
}

void MakeUnicodeFile(const std::string& filename)
{ 
	auto stream = std::ofstream(filename);
	char bytes[] = { 0xFF, 0xFE };
	stream.write(bytes,2);
	stream.close();
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage Deimos <file_to_read>" << std::endl;
		return 0; 
	}

	std::vector<std::string> switches = { "-a", "-ansi", "-unicode", "-utf8", "-utf16" };
	auto reader = ParaReader::FromStringWithSwitches(argc, argv, switches);

	auto stream = std::ifstream(argv[1], std::ios::binary | std::ios::ate);
	auto pos = stream.tellg();
	int length = pos;

	int start = reader.GetNumberOrdefault("-s", 0);
	int end = reader.GetNumberOrdefault("-l", length-start);

	PrintBytes(&stream, start, end);
	std::cout << std::endl;

	if(reader.HasFlag("-a") || reader.HasFlag("-ansi"))
		PrintAsAscii(&stream, start, end);
	if (reader.HasFlag("-unicode"))
	{
		std::cout << std::endl;
		PrintAsWideChar(&stream, start, end);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
