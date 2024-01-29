#include <stack>

void fill_symbol_table(std::vector<std::pair<std::string, std::list<std::string>*>>& vec)
{
	vec[0].first = "type";
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
	std::stringstream ss;

	while (ss >> tokens) {
		vec.push_back (tokens);
	}

	return vec;
}

void is_valid(std::vector<std::string> vec)
{
}


void interpret (std::vector<std::string> vec)
{
}

void preinterpret(char* fileName)
{
	std::ifstream read;	
	std::string str;
	std::vector<char> vec;
	int index = 0;
	
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
		
		while (str[index] != '\0') {
			if (str[index] == '{' || str[index] == '}' || str[index] == '[' || str[index] == ']' || str[index] == '(' || str[index] == ')') {
				vec.push_back(str[index]);	
			}
			
			++index;
		}
		index = 0;
	}
	
	if (!validParentheses(vec)) {
		std::cout << "You have syntax error! Check parentheses!" << std::endl;
		exit(0);
	}

	read.close();
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













