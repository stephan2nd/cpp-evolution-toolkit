#include "Dummy.hpp"

#include <sstream>



Dummy::Dummy()
{ }



Dummy::~Dummy()
{ }



string
Dummy::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine();
	return ss.str();
}
	


string
Dummy::toLine(void) const
{
	return "";
}
	


ostream&
operator<<(ostream& os, const Dummy& dummy)
{
	return os << dummy.toLine();
}









