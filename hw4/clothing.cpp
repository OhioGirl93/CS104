#include "clothing.h"
#include "product.h"
#include "util.h"
#include <string>
#include <sstream>
using namespace std; 

// Constructor
Clothing::Clothing(const std::string category, const std::string name, double price,
	int qty, string size, string brand): Product(category, name, price, qty)
{
	size_ = size;
	brand_ = brand;
}

// Returns keywords from name and brand
std::set<std::string> Clothing::keywords() const
{
	set<string> nameset = parseStringToWords(name_);
	set<string> brandset = parseStringToWords(brand_);
	// set of keywords from name and brand variables
	set<string> keywords = setUnion(nameset, brandset);
	return keywords;
}

// Returns a string of clothing characteristics
std::string Clothing::displayString() const
{
	// convert price/qty to string variables
	ostringstream ss1, ss2;
	ss1 << price_;
	ss2 << qty_;
	string p = ss1.str();
	string q = ss2.str();

	string display = "" + name_ + "\n" + "Size: " + size_ + " Brand: " + brand_
	+ "\n" + p + "\n" + q + " left.";
	return display;
}

// Outputs clothing characteristics into outfile
void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<
	"\n" << brand_ << "\n" << size_ << endl;
}

// Returns size
std::string Clothing::getSize() const
{
	return size_;
}

// Returns brand
std::string Clothing::getBrand() const
{
	return brand_;
}