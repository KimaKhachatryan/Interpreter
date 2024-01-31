#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <list>


//fakes symbol table
std::vector<std::pair<std::string, std::list<std::string>*>> symbol_table;

//parsed map collects code file lines, where size_t is line number, vector is tokenized string expresing minimal meaning
std::map<size_t, std::vector<std::string>> parsed;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////FUNCTION_DECLERATIONS/////////////////////////////////////////////////////

//before interpretation checks () [] {} symbols and presence if main() 
void preinterpret(char* fileName);

//fills symbol_table
void fill_symbol_table (std::vector<std::pair<std::string, std::list<std::string>*>>& vec);

//splits the string into tokens
std::vector<std::string> tokenizer(std::string str);

//checks whether the tokenized string is valid or not
//if there is any syntax error, function prints error message and interapts the program execution
//else does nothing
void is_valid(std::vector<std::string> vec, size_t code_line); 

//interprets and executes the line
void interpret(std::vector<std::string> vec);

#include "classes.h"
#include "functions.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////MAIN//////////////////////////////////////////////////////////////////

int main (int args, char* argv[])
{
	
	preinterpret(argv[1]);

	size_t code_line = 1;
	std::ifstream read;	
	std::string str;

	fill_symbol_table(symbol_table);

	read.open(argv[1]);
	if (!read.is_open()) {
		std::cout << "Something is wrong...((" << std::endl;
		std::cout << "Did you follow the correct command syntax?" << "\n" 
				  << "In the command line you should write ./Ipp "<< "\"" << "YourFileName" << "\"" 
				  << std::endl;
		exit(0); 
	}

	while (!read.eof()) {
		std::getline(read, str);
		if (str.size() == 0) {
			++code_line;
			continue;
		}
		
		parsed[code_line] = tokenizer(str);
	
		is_valid(parsed[code_line], code_line);
//		interpret(parsed[code_line]);
		++code_line;
	}

	read.close();

	return 0;
}


