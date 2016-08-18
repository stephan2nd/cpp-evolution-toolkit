#ifndef DUMMY_HPP_
#define DUMMY_HPP_

#include <iostream>
#include <string>



using namespace std;

class Dummy
{
friend unsigned int test_dummy(bool verbose);

public:

	Dummy();

	virtual
	~Dummy();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const Dummy& dummy);

private:


};

#endif /* DUMMY_HPP_ */
