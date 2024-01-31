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

//searches name conflicts
bool name_lookup(std::string);

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
	
	Error error(0);
	if (!valid_main || invalid_main) {
		error.message(7);					//There is not main()
		exit(0);
	}

	if (!validParentheses(vec)) {
		error.message(7);					//Invalid parentheses
		exit(0);
	}

	read.close();
}

void fill_symbol_table(std::vector<std::pair<std::string, std::list<std::string>*>>& vec)
{
	vec.resize(3);
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
   	 vec[2].second->push_back("main");
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
	std::vector<std::string> vec = tokenizer(str);

	if (vec.size() == 0 || vec.size() > 4) {
		return false;
	}

	for (size_t i = 0; i < vec.size(); ++i) {
		if (i == 0 && vec[i] != "int") {
			return false;
		} else if (i == 1) {
			if (vec[i] == "main(){" && vec.size() == 2) {
				parsed[0] = vec;
				return true;
			} else if (vec[i] != "main()") {
				if (vec[i] != "main") {
					return false;
				}
			} else {
				if (vec.size() == 2) {
					parsed[0] = vec;
					return true;
				}
			}
		} else if (i == 2) {
			if (vec[1] == "main") {
				if (vec[i] != "()") {
					return false;
				} else if (vec[i] == "(){" && vec.size() == 3){
					parsed[0] = vec;
					return true;
				}
			} else if (vec[1] == "main()") {
				if (vec[i] != "{") {
					return false;
				} else {
					if (vec.size() == 3) {
						parsed[0] = vec;
						return true;
					}
				}
			} 
		}
	}
	parsed[0] = vec;
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
	if (vec == parsed[0]) {
		return false;
	}

	Error error(code_line);
	
	if (vec.size() == 1) {
			error.message(1);
			exit(0);
	}

	for (size_t i = 1; i < vec.size(); ++i) {
		if (i == 1) {
			if (vec[i] == ";") {
				error.message(2);				//expected ;
				exit(0);
			} else if (find_in_symTable(vec[i]) == "operator") {
				error.message(6);				//unnamed variable
				exit(0);
			} else if (find_in_symTable(vec[i]) != "X") {		//if string didn't found in symble_table, function returns "X"
				error.message(3);				// name conflict
				exit(0);
			} else if (name_lookup(vec[i])) {		     
				error.message(4);				//Redeclaration
				exit(0);
			} else if (vec.size() == 2) {
				error.message(1);
				exit(0);
			}
		} else if (i == 2) {
			if (vec[i] == ";") {
				if (vec.size() == 3) {
					return true;
				} else {
					error.message(1);
					exit(0);
				}
			} else if (vec[i] == "=") {
				if (vec.size() < 5) {
					error.message(5);			//uninitialized variable
					exit(0);
				} 
			}	
		} else if (i == 4) {
			if (vec[i] != ";") {
				error.message(1);
				exit(0);
			}
		}
	}

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
	for (size_t i = 0; i < symbol_table.size(); ++i) {
		auto it = std::find(symbol_table[i].second->begin(), symbol_table[i].second->end(), str);
		if (it != symbol_table[i].second->end()) {
			return symbol_table[i].first;
		}
	}
	
	//if string did not found in table, function returns "X"
	std::string X = "X";
	return X;
}

bool name_lookup(std::string str)
{
	return false;
}










