#ifndef CLASSES_HPP
#define CLASSES_HPP

//Int class
Int::Int(std::string str) {
	try {
		val = std::stoi(str);
	} catch (const std::invalid_argument& e) {
		if (!name_lookup(str)) {
			std::cout << "Invalid argument" << std::endl;
			exit(0);
		} else {
			val = find_val<int>(str);
		}
	} catch (const std::out_of_range& e) {
		std::cerr << "Out of range." << std::endl;	
	}
}

Int::operator int() {
	return val;
}

Int::operator double() {
	return static_cast<double>(val);
}

//Double class
Double::Double (std::string str) {
	try {
		val = std::stoi(str);
	} catch (const std::invalid_argument& e) {
		if (!name_lookup(str)) {
			std::cout << "Invalid argument" << std::endl;
			exit(0);
		} else {
			val = find_val<double>(str);
		}
	} catch (const std::out_of_range& e) {
		std::cerr << "Out of range." << std::endl;
	}
}

Double::operator double() {
	return val;
}

Double::operator int() {
	return static_cast<double> (val);
}

//Error class
	
void Error::message (int r)
{
	switch(r) {
		case 0:
			std::cout << "Error in line " << code_line << ": " 
				  << "Ipp interpreter doesn't support that syntax yet." << std::endl;
			break;
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
		case 9:
			std::cout << "You have syntax error in line " << code_line << ".\nPlease check it." << std::endl;
			break;
		case 10:
			std::cout << "Error in line " << code_line << ".\nYou cann't declare string array!" << std::endl;
			break;
		case 11:
			std::cout << "Error in line " << code_line << ".\nStatic array must have size!" << std::endl;
			break;
		case 12:
			std::cout << "Error in line " << code_line << ".\nVariable declaration not found!" << std::endl;
			break;
		case 13:
			std::cout << "Error in line " << code_line << ".\nExpected \"\"." << std::endl;
			break;
		case 14:
			std::cout << "Error in line " << code_line << ".\nExpected \'\'." << std::endl;
			break;
		case 15:
			std::cout << "Error in line " << code_line << ".\nExpected initializer." << std::endl;
			break;
		case 16:
			std::cout << "Error in line " << code_line << ".\nStrings must initialized at the moment of declaration." << std::endl;
			break;
		case 17:
			std::cout << "Error in line " << code_line << ".\nexpected (condition) { syntax." << std::endl;
			break;
		case 18:
			std::cout << "Error in line " << code_line << ".\nExpected std::cout << syntax." << std::endl;
			break;
		case 19:
			std::cout << "Error in line " << code_line << ".\nExpected std::cin >> syntax." << std::endl;
			break;
		case 20:
			std::cout << "Error in line " << code_line << ".\nExpected primary-expression before ‘;’ token" << std::endl;
			break;
		}
}

#endif
