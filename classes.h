#ifndef CLASSES_H
#define CLASSES_H


class Int {
public:
	Int () {}
	Int(std::string str);

	operator int();
	operator double();

private:
	int val;
};

class Double {
public:
	Double () {}
	Double (std::string str);

	operator double();

	operator int();
private:
	double val;

};


class Error {
public:
	Error() = delete;
	Error(const Error&) = delete;
	Error(const Error&&) = delete;
	Error(size_t line) : code_line{line} {}
	
	void message (int r);
private:  
	size_t code_line;	
};

#endif
