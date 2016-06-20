#include "movie.h"
#include "product.h"
#include "util.h"
#include <string>
#include <sstream>
using namespace std; 

// Constructor
Movie::Movie(const std::string category, const std::string name, double price,
	int qty, string genre, string rating): Product(category, name, price, qty)
{
	genre_ = genre;
	rating_ = rating;
}

// Returns keywords from name and genre
std::set<std::string> Movie::keywords() const
{
	//set of keywords from name variable
	set<string> keywords = parseStringToWords(name_);
	keywords.insert(convToLower(genre_)); //not parsing genre
	return keywords;
}

// Returns string of movie characteristics
std::string Movie::displayString() const
{
	//convert to string
	ostringstream ss1, ss2;
	ss1 << price_;
	ss2 << qty_;
	string p = ss1.str();
	string q = ss2.str();

	string display = "" + name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_
	+ "\n" + p + "\n" + q + " left.";
	return display;
}

// Outputs movie characteristics into outfile
void Movie::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<
	"\n" << rating_ << "\n" << genre_ << endl;
}

// Returns genre
std::string Movie::getGenre() const
{
	return genre_;
}

// Returns rating
std::string Movie::getRating() const
{
	return rating_;
}