#include "database.h"
#include "book.h"
#include "movie.h"
#include "clothing.h"
#include "product.h"
#include "datastore.h"
#include "user.h"
#include "util.h"
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include "review.h"

using namespace std;

// Constructor/Destructor
DataBase::DataBase() { }

DataBase::~DataBase()
{
	for(unsigned int i=0; i<products.size(); i++){
		delete products[i];
	}

	for(unsigned int i=0; i<users.size(); i++){
		delete users[i];
	}

}

// Adds product into the database
void DataBase::addProduct(Product* p)
{
	// Add product to list of products
	products.push_back(p);

	// loop through keywords, adding the Product to the map at each keyword
	set<string> prodKeys = p->keywords();
	for(set<string>::iterator it = prodKeys.begin(); it!=prodKeys.end(); it++){
		if(keywords.find(*it)==keywords.end()){ //if it does not exist
			set<Product*> set; //create a new set for the keyword
			set.insert(p);
			keywords[*it] = set;
		}
		else{ //if it does exist
			set<Product*> set = keywords[*it];
			set.insert(p);
			keywords[*it] = set;
		}
	}
}

// Add users to the list of users
void DataBase::addUser(User* u)
{
	users.push_back(u);
}

// Search for terms entered and return corresponding products
std::vector<Product*> DataBase::search(std::vector<std::string>& terms, int type)
{
	vector<Product*> results;
	set<Product*> set1, set2;

	if(type==0){ //if user is looking for the intersection of these terms

		if(terms.size()>1){
			set1 = keywords[terms[0]];
		}
		else{
			if(keywords.find(terms[0])==keywords.end())
				return results;
			else{
				results.push_back(*(keywords[terms[0]].begin()));
				return results;
			}
		}

		for(unsigned int i=1; i<terms.size();i++){
			if(keywords.find(terms[i])!=keywords.end()){
				set2 = keywords[terms[i]];
				set1 = setIntersection(set1, set2);
			}
		}
		// Loop through set and add to Product vector
		for(set<Product*>::iterator it = set1.begin(); it!=set1.end(); it++){
			results.push_back(*it);
		}
		return results;
		
	}

	else{ // if user is looking for the union of these terms
		for(unsigned int i=0; i<terms.size();i++){
			if(keywords.find(terms[i])!=keywords.end()){
				set2 = keywords[terms[i]];
				set1 = setUnion(set1, set2);
			}
		}
		// Loop through and add to Product vector
		for(set<Product*>::iterator it = set1.begin(); it!=set1.end(); it++){
			results.push_back(*it);
		}

		return results;
	}
}

// Print out database of products and users
void DataBase::dump(std::ostream& ofile)
{
	ofile << "<products>" << endl;

	for(unsigned int i=0; i<products.size(); i++){
		products[i]->dump(ofile);
	}

	ofile << "</products>" << endl;
	ofile << "<users>" << endl;

	for(unsigned int i=0; i<users.size(); i++){
		users[i]->dump(ofile);
	}

	ofile << "</users>" << endl;

	ofile << "<reviews>" << endl;
	for(unsigned int i=0; i<products.size(); i++){
		for(unsigned int j=0; j<products[i]->getReviews().size(); j++){
			ofile << products[i]->getReviews()[j]->prodName << endl;
			ofile << products[i]->getReviews()[j]->rating << " " << 
			products[i]->getReviews()[j]->date << " " << 
			products[i]->getReviews()[j]->reviewText << endl;
		}
	}
	ofile << "</reviews>" << endl;
}

// Find user, add desired product to shopping cart, returns string of what happened
string DataBase::addToCart(User* u, int hitnum, vector<Product*> hits)
{
	string message = "Unable to add item to cart.";
	//if the user has a shopping cart, add to it
	if(shoppingCart.find(u)!=shoppingCart.end()){
		if(hits[hitnum-1]->getQty() > 0){ //check if product is in stock
			deque<Product*> cart = shoppingCart[u];
			cart.push_back(hits[hitnum-1]);
			shoppingCart[u] = cart;
			message = "You have successfully added this item to your cart.";
		}
		else
			message = "This item is sold out.";
	}
	//if the user does not have a cart, create and add
	else{
		if(hits[hitnum-1]->getQty() > 0){
			deque<Product*> cart;
			cart.push_back(hits[hitnum-1]);
			shoppingCart[u] = cart;
			message = "You have successfully added this item to your cart.";
		}
		else
			message = "This item is sold out.";
	}
	return message;
}

// Purchase and remove items from cart, return string of what happened
string DataBase::buyAll(User* u)
{
	string message = "Summary:";
	deque<Product*> cart = shoppingCart[u];
	int counter = 0; //keeps track of how many items are analyzed
	int size = cart.size();

	while(counter < size){
		//checks if item is still in stock
		if(cart[0]->getQty() < 1){
			message += "\n'" + cart[0]->getName() + "' is no longer in stock.";
			//temp to store the item
			Product* temp = cart.front();
			//pop and add to back of the cart
			cart.pop_front();
			cart.push_back(temp);
			counter++;
		}
		//check if user has enough money
		else if(u->getBalance() - cart[0]->getPrice() > 0){
			message += "\nYou have successfully bought: " 
			+ cart[0]->getName();
			u->deductAmount(cart[0]->getPrice()); //subtract $
			cart[0]->subtractQty(1); //subtract quantity
			cart.pop_front(); //remove from front
			counter++;
		}
		//if user cannot buy item
		else{
			message += "\nCould not purchase due to insufficient funds: " 
			+ cart[0]->getName();
			//temp to store the item
			Product* temp = cart.front();
			//pop and add to back of the cart
			cart.pop_front();
			cart.push_back(temp);
			counter++;
		}
	}
	//update shopping cart for this user
	shoppingCart[u] = cart;

	return message;
}

vector<Product*> DataBase::getProducts()
{
	return products;
}

vector<User*> DataBase::getUsers()
{
	return users;
}

//adds review to its product
void DataBase::addReview(Review* r)
{
	for(unsigned int i=0; i<products.size(); i++){
		if(r->prodName==products[i]->getName())
			products[i]->newReview(r);
	}
}

//get/set search results
vector<Product*> DataBase::getHits()
{
	return hits;
}

void DataBase::setHits(vector<Product*> h)
{
	hits = h;
}

//get/set shopping cart
map<User*, deque<Product*> > DataBase::getCart()
{
	return shoppingCart;
}

void DataBase::setCart(User* u, deque<Product*> d)
{
	shoppingCart[u] = d;
}

// Purchase and remove items from cart
string DataBase::buySingle(User* u, int cartnum)
{
	string message = "Summary:";
	deque<Product*> cart = shoppingCart[u];

	//switches front item with desired item and pops front to remove after bought
	if(cartnum!=0){
		Product* front = cart[0];
		cart[0] = cart[cartnum];
		cart[cartnum]= front;
	}

	//checks if item is still in stock
	if(cart[0]->getQty() < 1){
		message += "\n'" + cart[0]->getName() + "' is no longer in stock.";
		//pop and add to back of the cart
		cart.pop_front();
	}
	//check if user has enough money
	else if(u->getBalance() - cart[0]->getPrice() > 0){
		message += "\nYou have successfully bought: " 
		+ cart[0]->getName();
		u->deductAmount(cart[0]->getPrice()); //subtract $
		cart[0]->subtractQty(1); //subtract quantity
		cart.pop_front(); //remove from front
	}
	//if user cannot buy item
	else{
		message += "\nCould not purchase due to insufficient funds: " 
		+ cart[0]->getName();
	}
	//update shopping cart for this user
	shoppingCart[u] = cart;

	return message;
}
