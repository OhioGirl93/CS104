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
	set1 = keywords[terms[0]];
	
	if(type==0){ //if user is looking for the intersection of these terms
		for(unsigned int i=1; i<terms.size();i++){
			set2 = keywords[terms[i]];
			set1 = setIntersection(set1, set2);
		}
		// Loop through set and add to Product vector
		for(set<Product*>::iterator it = set1.begin(); it!=set1.end(); it++){
			results.push_back(*it);
		}
		return results;
	}

	else{ // if user is looking for the union of these terms
		for(unsigned int i=1; i<terms.size();i++){
			set2 = keywords[terms[i]];
			set1 = setUnion(set1, set2);
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
}

// Find user, add desired product to shopping cart
void DataBase::addToCart(string username, int hitnum, vector<Product*> hits)
{
	// Find user
	User* u = NULL;
	for(unsigned int i=0; i<users.size(); i++){
		if(users[i]->getName() == username)
			u = users[i];
	}

	if(u!=NULL){ //checks if user exists
		//if the user has a shopping cart, add to it
		if(shoppingCart.find(u)!=shoppingCart.end()){
			if(hits[hitnum-1]->getQty() > 0){ //check if product is in stock
				deque<Product*> cart = shoppingCart[u];
				cart.push_back(hits[hitnum-1]);
				shoppingCart[u] = cart;
			}
			else
				cout << "This item is sold out." << endl;
		}
		//if the user does not have a cart, create and add
		else{
			if(hits[hitnum-1]->getQty() > 0){
				deque<Product*> cart;
				cart.push_back(hits[hitnum-1]);
				shoppingCart[u] = cart;
			}
			else
				cout << "This item is sold out." << endl;
		}
	}

	else
		cout << "User does not exist." << endl;
	
}

// Display the user's cart
void DataBase::printCart(string username)
{
	// Find user
	User* u = NULL;
	for(unsigned int i=0; i<users.size(); i++){
		if(users[i]->getName() == username)
			u = users[i];
	}

	if(u!=NULL){ //check if user exists
		//if the cart exists, print it out FIFO
		if(shoppingCart.find(u)!=shoppingCart.end()){
			//loop through cart and print out items
			deque<Product*> cart = shoppingCart[u];
			for(unsigned int i=0; i<cart.size(); i++){
				cout << "Item " << (i+1) << endl;
				cout << cart[i]->displayString() << endl;
			}
		}

		else
			cout << "Shopping Cart is empty." << endl;
	}

	else
		cout << "User does not exist." << endl;
	

}

// Purchase and remove items from cart
void DataBase::buyCart(string username)
{
	//Find user
	User* u = NULL;
	for(unsigned int i=0; i<users.size(); i++){
		if(users[i]->getName() == username)
			u = users[i];
	}

	if(u!=NULL){ //check if user exists
		//if the cart exists
		if(shoppingCart.find(u)!=shoppingCart.end()){

			deque<Product*> cart = shoppingCart[u];
			int counter = 0; //keeps track of how many items are analyzed
			int size = cart.size();

			while(counter < size){
				//checks if item is still in stock
				if(cart[0]->getQty() < 1){
					cout <<"'" << cart[0]->getName() << "' is no longer in stock." << endl;
					//temp to store the item
					Product* temp = cart.front();
					//pop and add to back of the cart
					cart.pop_front();
					cart.push_back(temp);
					counter++;
				}
				//check if user has enough money
				else if(u->getBalance() - cart[0]->getPrice() > 0){
					u->deductAmount(cart[0]->getPrice()); //subtract $
					cart[0]->subtractQty(1); //subtract quantity
					cart.pop_front(); //remove from front
					counter++;
				}
				//if user cannot buy item
				else{
					cout << "Could not purchase due to insufficient funds: " 
					<< cart[0]->getName() << endl;
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
		}
		
		else
			cout << "Shopping Cart is empty." << endl;
	}

	else
		cout << "User does not exist." << endl;

}