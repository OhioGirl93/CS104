#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "database.h"

using namespace std;

/* Prototypes */
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please specify a database file" << endl;
  }

  // Declare your derived DataStore object here 
  DataBase ds;

  // Instantiate the parser
  DBParser parser;

  // Instantiate the individual7 product parsers we want
  parser.addProductParser(new ProductBookParser);
  parser.addProductParser(new ProductClothingParser);
  parser.addProductParser(new ProductMovieParser);

  // Now parse the database to populate the DataStore
  if( parser.parse(argv[1], ds) ){
    cerr << "Error parsing!" << endl;
    return 1;
  }

  // Menu
  cout << "=====================================" << endl;
  cout << "Menu: " << endl;
  cout << "  AND term term ...                  " << endl;
  cout << "  OR term term ...                   " << endl;
  cout << "  ADD username search_hit_number     " << endl;
  cout << "  VIEWCART username                  " << endl;
  cout << "  BUYCART username                   " << endl;
  cout << "  QUIT new_db_filename               " << endl;
  cout << "====================================" << endl;

  vector<Product*> hits; //products that come up in search
  bool done = false;

  while(!done){
    cout << "\nEnter search terms: " << endl;
    string line;
    getline(cin,line);
    stringstream ss(line);
    string cmd;
    if((ss >> cmd)){

      //User enters AND command
      if( cmd == "AND" ){
	      string term;
      	vector<string> terms;
      	while(ss >> term){
      	  term = convToLower(term);
      	  terms.push_back(term);
      	}
        hits = ds.search(terms, 0);
        displayProducts(hits);
      }

      //User enters OR command
      else if ( cmd == "OR" ){
      	string term;
      	vector<string> terms;
      	while(ss >> term){
      	  term = convToLower(term);
      	  terms.push_back(term);
      	}
      	hits = ds.search(terms, 1);
      	displayProducts(hits);
      }

      //User enters QUIT command
      else if ( cmd == "QUIT" ){
      	string filename;
      	if(ss >> filename){
      	  ofstream ofile(filename.c_str());
      	  ds.dump(ofile);
      	  ofile.close();
      	}
        done = true;
      }

      //User enters ADD command
      else if ( cmd == "ADD" ){
        string name;
        int hit;
        if(ss >> name){
          if(ss >> hit){
            ds.addToCart(name, hit, hits);
          }
        }
      }

      //User enters VIEWCART command
      else if ( cmd == "VIEWCART" ){
        string name;
        if(ss >> name)
          ds.printCart(name);
      }

      //User enters BUYCART command
      else if ( cmd == "BUYCART" ){
        string name;
        if(ss >> name)
          ds.buyCart(name);
      }
    }
  }
  
  return 0;
}
 
// Prints products on screen
void displayProducts(vector<Product*>& hits)
{
  int resultNo = 1;
  for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it){
    cout << "Hit " << setw(3) << resultNo << endl;
    cout << (*it)->displayString() << endl;
    cout << endl;
    resultNo++;
  }
}
