#ifndef DATABASE_H
#define DATABASE_H
#include "book.h"
#include "movie.h"
#include "clothing.h"
#include "product.h"
#include "datastore.h"
#include "user.h"
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <fstream>
#include <sstream>
using namespace std;

class DataBase : public DataStore{

public:
	DataBase();
	~DataBase();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	void addToCart(string username, int hitnum, vector<Product*> hits);
	void printCart(string username);
	void buyCart(string username);

private:
	// Contains all products
	vector<Product*> products;

	// Contains all users
	vector<User*> users;

	// Map of all products per keyword
	map<string, set<Product*> > keywords;
	
	// Map of each user's shopping cart
	map<User*, deque<Product*> > shoppingCart;

};
#endif