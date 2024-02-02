#ifndef FUNCTION_H
#define FUNCTION_H

#include <stack>
#include <algorithm>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------DEFINITIONS------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
//void preinterpret(char* fileName)
//void fill_symbol_table(std::vector<std::pair<std::string, std::list<std::string>*>>& vec)
//std::vector<std::string> tokenizer(std::string str);
//void is_valid(std::vector<std::string> vec, size_t code_line)
//void interpret (std::vector<std::string> vec)

//----------------------------------------------------------------------------------------------------------------------

//function checks wheter code has main() or not
//preinterpret calls has_main
bool has_main (std::string str);

//checks wheter parentheses valid or not
bool validParentheses(std::vector<char>& vec);

//-----------------------------------------------------------------------------------------------------------------------

//functions check whether declarations valid or not
void declarations(std::vector<std::string> vec, size_t code_line);

bool int_declaration(std::vector<std::string> vec, size_t code_line);
bool none_int_declaration(std::vector<std::string> vec, size_t code_line);
bool string_declaration(std::vector<std::string> vec, size_t code_line);
bool arr_declaration(std::vector<std::string> vec, size_t code_line);

//------------------------------------------------------------------------------------------------------------------------

//functions execute valid declerations 
void exe_int_declaration(std::vector<std::string> vec);
void exe_char_declaration(std::vector<std::string> vec);
void exe_bool_declaration(std::vector<std::string> vec);
void exe_float_declaration(std::vector<std::string> vec);
void exe_double_declaration(std::vector<std::string> vec);
void exe_string_declaration(std::vector<std::string> vec);

//--------------------------------------------------------------------------------------------------------------------------
//checks and executes all operations
void operations(std::vector<std::string> vec, size_t code_line);

//---------------------------------------------------------------------------------------------------------------------------

//checks and executes difinitions
void definitions (std::vector<std::string> vec, size_t code_line);
bool valid_definition (std::vector<std::string> vec, size_t code_line);

//-------------------------------------------------------------------------------------------------------------------------
//searches in symbol table given string 
//and if find it, return its identification
std::string find_in_symTable(std::string str);

//searches name conflicts
bool name_lookup(const std::string& str);

//searches in parsed map whether it contains given string or not
bool is_contains(const std::string& str);

//searches in type_maps given variable name
//and returns its value
template <typename T>
T find_val(std::string str);

#endif





