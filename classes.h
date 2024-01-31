//abstract class Type
class Type {};

//types that inherits from Type class

class Integer : public Type {};


class Error {
public:
	Error() = delete;
	Error(const Error&) = delete;
	Error(const Error&&) = delete;
	Error(size_t line) : code_line{line} {}
	
	void message (int r)
	{
		switch(r) {
			case 1:
				std::cout << "Error in line " << code_line << ": " 
					  << "Expected \";\" operator." << std::endl;
				break;
			case 2:
				std::cout << "Error in line " << code_line << ":\n" 
						  << "Declaration does not declare anything." << std::endl;
				break;
			case 3:
				std::cout << "Error in line " << code_line << ":" << "\n"
					      << "You cann't use C++ identifiers or keywords for variable identification." << std::endl;
				break;
			case 4:
				std::cout << "Redeclaration in line " << code_line << ".";
				break;
			case 5:
				std::cout << "Error in line " << code_line << ": " 
					      << "Expected primary initializer." << std::endl;
				break;
			case 6:
				std::cout << "Error in line " << code_line << ":" << "\n"
					      << "You cann't declare variable without identification." << std::endl;
				break;
			case 7:
				std::cout << "I haven't found the main(). I don't know where to start execution of the program." << std::endl;
				break;
			case 8:
				std::cout << "You have syntax error! Check parentheses!" << std::endl;
				break;
		}
	}
private:  
	size_t code_line;	
};
