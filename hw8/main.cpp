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
#include "cartwindow.h"
#include "reviewwindow.h"
#include "loginwindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char* argv[])
{
  //Parse database file
  if(argc < 2){
    cerr << "Please specify a database file" << endl;
  }

 //Derived DataStore object
  DataBase ds;

  // Instantiate the parser
  DBParser parser;

  // Instantiate the individual product parsers we want
  parser.addProductParser(new ProductBookParser);
  parser.addProductParser(new ProductClothingParser);
  parser.addProductParser(new ProductMovieParser);

  // Now parse the database to populate the DataStore
  if( parser.parse(argv[1], ds) ){
    cerr << "Error parsing!" << endl;
    return 1;
  }

  //open app and display main window
  QApplication app(argc, argv);

  LoginWindow login(&ds);
  login.show();
  
  return app.exec();
}