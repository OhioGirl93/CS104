#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include <set>
#include <iostream>
#include <string>
using namespace std;

class Movie: public Product{
public:
	Movie(const std::string category, const std::string name, double price, int qty,
	string genre, string rating);

	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;
	std::string getRating() const;
	std::string getGenre() const;

private:
	std::string genre_;
	std::string rating_;
};
#endif