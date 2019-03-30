// Deimos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

char const hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',   'B','C','D','E','F'};

std::string byte_2_str(char byte)
{
	std::string str;
	str.append(&hex[(byte & 0xF0) >> 4], 1);
	str.append(&hex[byte & 0xF], 1);
	return str;
} 

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage Deimos <file_to_read>" << std::endl;
		return 0; 
	}

	auto stream = std::ifstream(argv[1], std::ios::binary | std::ios::ate);
	auto pos = stream.tellg();
	int length = pos;

	std::vector<char> bytes(pos);

	stream.seekg(0, std::ios::beg);
	stream.read(&bytes[0],length);

	int i = 0;
	for (auto b : bytes)
	{
		std::cout << byte_2_str(b) << " ";
		i++;
		if (i % 16 == 0)
			std::cout << std::endl;
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
