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
#include "review.h"
#include "splaytree.h"
#include <utility>

class DataBase : public DataStore{

public:
	DataBase();
	~DataBase();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	std::string addToCart(User* u, int hitnum, std::vector<Product*> hits);
	std::string buyAll(User* u);
	std::string buySingle(User* u, int cartnum);
	void addReview(Review* r);
	std::vector<Product*> getProducts();
	std::vector<User*> getUsers();
	std::vector<Product*> getHits();
	std::map<User*, std::deque<Product*> > getCart();
	void setHits(std::vector<Product*> h);
	void setCart(User* u, std::deque<Product*> d);
	

private:
	// Contains all products
	std::vector<Product*> products;

	// Contains all users
	std::vector<User*> users;

	// Map of all products per keyword

	SplayTree<std::string, std::set<Product*> > keywords;
	//std::map<std::string, std::set<Product*> > keywords;
	
	// Map of each user's shopping cart
	std::map<User*, std::deque<Product*> > shoppingCart;

	//Search results
	std::vector<Product*> hits;

};
#endif