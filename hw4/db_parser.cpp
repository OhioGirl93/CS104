#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include "db_parser.h"

using namespace std;

DBParser::DBParser()
{
  lineno_ = 1;
  error_ = false;

}
DBParser::~DBParser()
{
  for(map<string, ProductParser*>::iterator it = parsers_.begin();
      it != parsers_.end();
      ++it){
    delete it->second;
  }
}

void DBParser::addProductParser(ProductParser* p)
{
  parsers_.insert(make_pair(p->categoryID(), p));
}

bool DBParser::parse(string db_filename, DataStore& ds)
{
  int numProds = 0;
  int numUsers = 0;
#ifdef DEBUG
  cout << "Starting parsing" << endl;
#endif
  ifstream ifile(db_filename.c_str());
  if(ifile.fail()){
    return true;
  }
  lineno_ = 1;
  string line;
  PState state = INIT;
  while(!ifile.fail() && !error_){
    getline(ifile, line);
#ifdef DEBUG
    cout << "Line: " << line << endl;
#endif
    stringstream ss(line);
    string token;
    if(state == INIT){
      if( ss >> token ){
	if(token == "<products>"){
#ifdef DEBUG
	  cout << "Found product" << endl;
#endif
	  state = PRODUCTS;
	}
      }
    }
    else if( state == PRODUCTS ){
      if( ss >> token) {
	if( token == "</products>" ){
#ifdef DEBUG
	  cout << "Found /product" << endl;
#endif
	  state = FIND_USERS;
	}
	else {
	  Product* p = parseProduct(token, ifile);
	  if(!error_ && p != NULL){
	    ds.addProduct(p);
	    numProds++;
	  }
	}
      }
    }
    else if( state == FIND_USERS){
      if( ss >> token ){
	if(token == "<users>"){
	  state = READ_USERS;
#ifdef DEBUG
	  cout << "Found users" << endl;
#endif
	}
      }
    }
    else if( state == READ_USERS){
      if( ss >> token) {
	if( token == "</users>" ){
#ifdef DEBUG
	  cout << "Found /users" << endl;
#endif
	  state = DONE;
	}
	else {
	  ss.clear();
	  ss.str(line);
	  User* u = parseUser(ss);
	  if(u){
	    ds.addUser(u);
	    numUsers++;
	  }
	}
      }
    }
    
    if(error_){
      cerr << "Parse error on line " << lineno_ << ": " << errorMsg_ << endl;
    }
    lineno_++;
  }
  if(!error_){
    cout << "Successfully parsed " << numProds << " products and " <<
      numUsers << " users." << endl;
  }
  return error_;
}



Product* DBParser::parseProduct(const string& category, 
			    istream& is)
{
  map<string,ProductParser*>::iterator it = parsers_.find(category);
  if(it != parsers_.end()){
    return it->second->parse(category, is, error_, errorMsg_, lineno_);
  }
  else {
    error_ = true;
    string msg = "No product parser available for category: ";
    errorMsg_ =  msg + category;
    return NULL;
  }
}

User* DBParser::parseUser(istream& is)
{
  string username;
  int age;
  double balance;
  int type;
  is >> username;
  if( is.fail() ){
    error_ = true;
    errorMsg_ = "Unable to read username";
  }
  is >> age;
  if( is.fail() ){
    error_ = true;
    errorMsg_ = "Unable to read age";
  }
  is >> balance;
  if( is.fail() ){
    error_ = true;
    errorMsg_ = "Unable to read balance";
  }
  is >> type;
  if( is.fail() ){
    error_ = true;
    errorMsg_ = "Unable to read type";
  }
  if(error_){
    return NULL;
  }
  else {
    return new User(username, age, balance, type);
  }
}


