#include "book.h"
#include "product.h"
#include "util.h"
#include <string>
#include <sstream>
using namespace std; 

// Constructor
Book::Book(const std::string category, const std::string name, double price,
	int qty, string author, string isbn): Product(category, name, price, qty)
{
	author_ = author;
	isbn_ = isbn;
}

// Returns keywords from name, author, and ISBN
std::set<std::string> Book::keywords() const
{
	set<string> nameset = parseStringToWords(name_);
	set<string> authorset = parseStringToWords(author_);
	// set of keywords from both name and author variables
	set<string> keywords = setUnion(nameset, authorset);
	// insert isbn the way it is
	keywords.insert(isbn_);
	return keywords;
}

// Returns string of book characteristics 
std::string Book::displayString() const
{
	// price and qty variables require conversion from double/int to string
	ostringstream ss1, ss2;
	ss1 << price_;
	ss2 << qty_;
	string p = ss1.str();
	string q = ss2.str();

	string display = "" + name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_
	+ "\n" + p + "\n" + q + " left.";
	return display;
}

// Outputs book characteristics into outfile
void Book::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<
	"\n" << isbn_ << "\n" << author_ << endl;
}

// Returns author
std::string Book::getAuthor() const
{
	return author_;
}

// Returns ISBN
std::string Book::getISBN() const
{
	return isbn_;
}