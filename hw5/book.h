#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <set>
#include <iostream>
#include <string>

class Book: public Product{
public:
	Book(const std::string category, const std::string name, double price, int qty,
	std::string author, std:: string isbn);
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;
	std::string getAuthor() const;
	std::string getISBN() const;

private:
	std::string author_;
	std::string isbn_;
};
#endif