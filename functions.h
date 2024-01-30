#include <stack>
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
bool char_declaration(std::vector<std::string> vec, size_t code_line);
bool bool_declaration(std::vector<std::string> vec, size_t code_line);
bool float_declaration(std::vector<std::string> vec, size_t code_line);
bool double_declaration(std::vector<std::string> vec, size_t code_line);
bool string_declaration(std::vector<std::string> vec, size_t code_line);

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
void difinitions (std::vector<std::string> vec, size_t code_line);

//-------------------------------------------------------------------------------------------------------------------------
//searches in symbol table given string 
//and if find it, return its identification
std::string find_in_symTable(std::string str);

//---------------------------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void preinterpret(char* fileName)
{
	std::ifstream read;	
	std::string str;
	std::vector<char> vec;
	int index = 0;
	bool valid_main = false;
	bool invalid_main = false;
	
	read.open(fileName);
	if (!read.is_open()) {
		std::cout << "Something is wrong...((" << std::endl;
		std::cout << "Did you follow the correct syntax?" << "\n" 
				  << "In the command line you should write ./Ipp "<< "\"" << "YourFileName" << "\"" 
				  << std::endl;
		exit(0); 
	}

	while (!read.eof()) {
		std::getline(read, str);
		if (str.size() == 0) {
			continue;
		}

		if (has_main(str)) {
			if (!valid_main) {
				valid_main = true;
			} else {
				invalid_main = true;
			}
		}

		while (str[index] != '\0') {
			if (str[index] == '{' || str[index] == '}' || str[index] == '[' || str[index] == ']' || str[index] == '(' || str[index] == ')') {
				vec.push_back(str[index]);	
			}
			
			++index;
		}
		index = 0;
	}

	if (!valid_main || invalid_main) {
		std::cout << "I haven't found the main(). I don't know where to start execution of the program." << std::endl;
		exit(0);
	}
	
	if (!validParentheses(vec)) {
		std::cout << "You have syntax error! Check parentheses!" << std::endl;
		exit(0);
	}

	read.close();
}

void fill_symbol_table(std::vector<std::pair<std::string, std::list<std::string>*>>& vec)
{
	vec[0].first = "typeID";
    	vec[0].second = new std::list<std::string>();

   	 vec[1].first = "operator";
   	 vec[1].second = new std::list<std::string>();

   	 vec[2].first = "keyword";
   	 vec[2].second = new std::list<std::string>();

  
   	 vec[0].second->push_back("bool");
   	 vec[0].second->push_back("char");
   	 vec[0].second->push_back("int");
   	 vec[0].second->push_back("float");
   	 vec[0].second->push_back("double");
   	 vec[0].second->push_back("string");
		
   	 vec[1].second->push_back("+");
   	 vec[1].second->push_back("-");
   	 vec[1].second->push_back("/");
   	 vec[1].second->push_back("*");
   	 vec[1].second->push_back("++");
   	 vec[1].second->push_back("--");
   	 vec[1].second->push_back("+=");
   	 vec[1].second->push_back("-=");
   	 vec[1].second->push_back("!");
   	 vec[1].second->push_back("==");
   	 vec[1].second->push_back("!=");
   	 vec[1].second->push_back(">");
   	 vec[1].second->push_back("<");
   	 vec[1].second->push_back(">=");
   	 vec[1].second->push_back("<=");
   	 vec[1].second->push_back("&&");
   	 vec[1].second->push_back("||");
   	 vec[1].second->push_back("(");
   	 vec[1].second->push_back(")");
   	 vec[1].second->push_back("{");
   	 vec[1].second->push_back("}");
   	 vec[1].second->push_back("[");
   	 vec[1].second->push_back("]");

   	 vec[2].second->push_back("if");
   	 vec[2].second->push_back("while");
}

std::vector<std::string> tokenizer(std::string str)
{
	std::vector<std::string> vec;
	std::string tokens;
	std::stringstream ss(str);

	while (ss >> tokens) {
		vec.push_back (tokens);
	}

	return vec;
}

void is_valid(std::vector<std::string> vec, size_t code_line)
{
	if (find_in_symTable(vec[0]) == "typeID") {
		declarations(vec, code_line);
	} else if (find_in_symTable(vec[0]) == "keyword") {
		operations(vec, code_line);
	} else {
		difinitions(vec, code_line);
	}
}

void interpret (std::vector<std::string> vec)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool has_main(std::string str)
{
	std::stringstream ss(str);
	std::vector<std::string> vec;
	std::string token;
	while (ss >> token) {
		vec.push_back(token);
	}

	if (vec.size() == 0 || vec.size() > 4) {
		return false;
	}

	for (size_t i = 0; i < vec.size(); ++i) {
		if (i == 0 && vec[i] != "int") {
			return false;
		} else if (i == 1) {
			if (vec[i] == "main(){" && vec.size() == 2) {
				return true;
			} else if (vec[i] != "main()") {
				if (vec[i] != "main") {
					return false;
				}
			} else {
				if (vec.size() == 2) {
					return true;
				}
			}
		} else if (i == 2) {
			if (vec[1] == "main") {
				if (vec[i] != "()") {
					return false;
				} else if (vec[i] == "(){" && vec.size() == 3){
					return true;
				}
			} else if (vec[1] == "main()") {
				if (vec[i] != "{") {
					return false;
				} else {
					if (vec.size() == 3) {
						return true;
					}
				}
			} 
		}
	}
	return true;
} 

bool validParentheses(std::vector<char>& vec)
{
	if (vec.size() % 2 != 0) {
            return false; 
        }

        std::stack<char> st;

        for (int i = 0; i < vec.size(); ++i) 
        {
            if (vec[i] == '(' || vec[i] == '{' || vec[i] == '[') 
            {
                st.push(vec[i]);
            } 
            else 
            {
                if (st.empty()) 
                {
                    return false;
                }

                char top = st.top();

                if ((vec[i] == ')' && top == '(') || (vec[i] == '}' && top == '{') || (vec[i] == ']' && top == '[')) {
                    st.pop();
                }
                
                else 
                {
                    return false; 
                }
            }
        }

        return st.empty(); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void declarations(std::vector<std::string> vec, size_t code_line)
{
	if (vec[0] == "int") {
		if (int_declaration(vec, code_line)) {
			exe_int_declaration(vec);
		}
	} else if (vec[0] == "char") {
		if (char_declaration(vec, code_line)) {
			exe_char_declaration(vec);
		}
	} else if (vec[0] == "bool") {
		if (bool_declaration(vec, code_line)) {
			exe_bool_declaration(vec);
		}
	} else if (vec[0] == "float") {	
		if (float_declaration(vec, code_line)) {
			exe_float_declaration(vec);
		}
	} else if (vec[0] == "double") {
		if (double_declaration(vec, code_line)) {
			exe_double_declaration(vec);
		}
	} else if (vec[0] == "string") {
		if (string_declaration(vec, code_line)) {
			exe_string_declaration(vec);
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool int_declaration(std::vector<std::string> vec, size_t code_line)
{
	return true;
}

bool bool_declaration(std::vector<std::string> vec, size_t code_line)
{
	return true;
}

bool char_declaration(std::vector<std::string> vec, size_t code_line)
{
	return true;
}

bool float_declaration(std::vector<std::string> vec, size_t code_line)
{
	return true;
}

bool double_declaration(std::vector<std::string> vec, size_t code_line)
{
	return true;
}

bool string_declaration(std::vector<std::string> vec, size_t code_line)
{
	return true;
}

//--------------------------------------------------------------------------------------------------------------------------------------

void exe_int_declaration(std::vector<std::string> vec)
{
}

void exe_bool_declaration(std::vector<std::string> vec)
{
}

void exe_char_declaration(std::vector<std::string> vec)
{
}

void exe_float_declaration(std::vector<std::string> vec)
{
}

void exe_double_declaration(std::vector<std::string> vec)
{
}

void exe_string_declaration(std::vector<std::string> vec)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void operations(std::vector<std::string> vec, size_t code_line)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void difinitions (std::vector<std::string> vec, size_t code_line)
{

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string find_in_symTable(std::string str)
{
	return std::string();
}












