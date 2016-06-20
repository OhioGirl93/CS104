#include "mainwindow.h"
#include "database.h"
#include <sstream>
#include <fstream>
#include <string>
#include "msort.h"
#include <cmath>
#include "reviewwindow.h"
#include "cartwindow.h"

//sorts alphabetically
struct AlphabetComp 
{
	bool operator() (Product* x, Product* y){
  		return x->getName() < y->getName();
  	}
};

//sorts by product rating
struct RatingComp
{
	bool operator() (Product* x, Product* y){
  		vector<Review*> reviews = x->getReviews();

  		//if product has no reviews then y is greater or equal
  		if(reviews.size()==0)
  			return false;

  		double xRating = 0.0;
  		double yRating = 0.0;

  		for(unsigned i=0; i<reviews.size(); i++){
  			xRating+=reviews[i]->rating;
  		}
  		//average of all ratings
  		xRating = xRating/reviews.size();

  		//same as above
  		reviews = y->getReviews();

  		for(unsigned i=0; i<reviews.size(); i++){
  			yRating+=reviews[i]->rating;
  		}
  		yRating = yRating/reviews.size();

  		return xRating > yRating;
  	}
};

//sorts by product date
struct DateComp 
{
	bool operator() (Review* x, Review* y){

  		string date1 = x->date;
  		string date2 = y->date;

  		int year1, year2, month1, month2, day1, day2;

  		//parsing the date strings
  		stringstream ss1(date1);
  		stringstream ss2(date2);

  		ss1 >> year1; ss2 >> year2;
  		//if the year is bigger then x is more recent than y
  		if(year1 > year2)
  			return true;
  		else if(year2 > year1) //vice versa
  			return false;

  		//same thing with month
  		ss1 >> month1; ss2 >> month2;
  		if(abs(month1) > abs(month2))
  			return true;
  		else if(abs(month2) > abs(month1))
  			return false;

  		//same thing with day
  		ss1 >> day1; ss2 >> day2;
  		if(abs(day1) > abs(day2))
  			return true;
  		else
  			return false;
  	}
};

MainWindow::MainWindow(DataBase& db)
{
	database = &db;

	setWindowTitle("Amazon");

	overallLayout = new QHBoxLayout();
	//lhs contains all search functions/buttons along with save and exit
	//rhs contains user list, cart functions, and review functions

	lhsLayout = new QVBoxLayout();
	rhsLayout = new QVBoxLayout();
	overallLayout->addLayout(lhsLayout);
	overallLayout->addLayout(rhsLayout);

	searchLabel = new QLabel("Search");
	searchBox = new QLineEdit();
	lhsLayout->addWidget(searchLabel);
	lhsLayout->addWidget(searchBox);

	andButton = new QRadioButton("AND search", this);
	orButton = new QRadioButton("OR search", this);
	searchButton = new QPushButton("Search");
	searchResultsList = new QListWidget();
	lhsLayout->addWidget(andButton);
	lhsLayout->addWidget(orButton);
	lhsLayout->addWidget(searchButton);
	lhsLayout->addWidget(searchResultsList);

	sortAlphaButton = new QPushButton("Sort Alphabetically");
	sortRatingButton = new QPushButton("Sort by Rating");
	lhsLayout->addWidget(sortAlphaButton);
	lhsLayout->addWidget(sortRatingButton);

	saveDBLabel = new QLabel("Enter Database to Save");
	saveDBLine = new QLineEdit();
	saveDBButton = new QPushButton("SAVE DATABASE");
	lhsLayout->addWidget(saveDBLabel);
	lhsLayout->addWidget(saveDBLine);
	lhsLayout->addWidget(saveDBButton);

	exitLabel = new QLabel("Exit Search");
	exitButton = new QPushButton("EXIT");
	lhsLayout->addWidget(exitLabel);
	lhsLayout->addWidget(exitButton);

	usersLabel = new QLabel("Users");
	usersList = new QListWidget();
	rhsLayout->addWidget(usersLabel);
	rhsLayout->addWidget(usersList);

	addToCartButton = new QPushButton("Add to Cart");
	viewCartButton = new QPushButton("View Cart");
	rhsLayout->addWidget(addToCartButton);
	rhsLayout->addWidget(viewCartButton);

	reviewLabel = new QLabel("Reviews");
	reviewsList = new QListWidget();
	writeReviewButton = new QPushButton("Write Review");
	rhsLayout->addWidget(reviewLabel);
	rhsLayout->addWidget(reviewsList);
	rhsLayout->addWidget(writeReviewButton);

	connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
	connect(sortAlphaButton, SIGNAL(clicked()), this, SLOT(sortA()));
	connect(sortRatingButton, SIGNAL(clicked()), this, SLOT(sortR()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(saveDBButton, SIGNAL(clicked()), this, SLOT(save()));
	connect(searchResultsList, SIGNAL(currentRowChanged(int)), this, 
		SLOT(displayReviews()));
	connect(addToCartButton, SIGNAL(clicked()), this, SLOT(addToCart()));
	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(viewCart()));
	connect(writeReviewButton, SIGNAL(clicked()), this, SLOT(writeReview()));

	//display users
	for(unsigned int i=0; i<database->getUsers().size(); i++){
		string username = database->getUsers()[i]->getName();
		QString temp = QString::fromStdString(username);
		usersList->addItem(temp);
	}
	
	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	delete searchLabel;
	delete searchBox;
	delete andButton;
	delete orButton;
	delete searchButton;
	delete searchResultsList;
	delete sortAlphaButton;
	delete sortRatingButton;
	delete saveDBLabel;
	delete saveDBButton;

	delete usersLabel;
	delete usersList;
	delete addToCartButton;
	delete viewCartButton;
	delete reviewLabel;
	delete reviewsList;
	delete writeReviewButton;

	delete lhsLayout;
	delete rhsLayout;

	delete overallLayout;
	
}

//search box function and product list display
void MainWindow::search()
{
	QMessageBox msgBox;
	//checking if search box is empty and if search type was chosen
	if(searchBox->text().isEmpty()){
		msgBox.setText(QString::fromStdString("No search terms entered. Please try again."));
		msgBox.exec();
		return;
	}
	else if(!andButton->isChecked() && !orButton->isChecked()){
		msgBox.setText(QString::fromStdString("Please choose type of search."));
		msgBox.exec();
		return;
	}

	//clear previous searches
	searchResultsList->clear();

	//add search terms to a vector to be searched in database
	string searchTerms = searchBox->text().toStdString();
	vector<string> terms;
	stringstream ss (searchTerms);
	string term;
	ss >> term;
	while(!ss.fail()){
		terms.push_back(term);
		ss >> term;
	}
	int type = 0;
	if(orButton->isChecked())
		type = 1;

	vector<Product*> results = database->search(terms, type);

	//if no results, print message
	if(results.size()==0){
		searchResultsList->addItem(QString::fromStdString("No results were found."));
		searchBox->setText("");
		return;
	}

	//update hits vector
	database->setHits(results);

	//display results on list
	for(unsigned int i=0; i<results.size(); i++){
		string product = results[i]->displayString();
		searchResultsList->addItem(QString::fromStdString(product));
	}
	//clear search box
	searchBox->setText("");

}

//sort alphabetically
void MainWindow::sortA()
{
	vector<Product*> hits = database->getHits();
	//no need to sort 1 hit
	if(hits.size()>1){
		//call mergesort
		AlphabetComp comp;
		mergeSort(hits, comp);
		//clear results and print new results
		searchResultsList->clear();
		for(unsigned int i=0; i<hits.size(); i++){
			QString temp = QString::fromStdString(hits[i]->displayString());
			searchResultsList->addItem(temp);
		}
		//update hits to match reviews
		database->setHits(hits);
	}
}

//same as sortA but with ratings
void MainWindow::sortR()
{
	vector<Product*> hits = database->getHits();
	if(hits.size()>1){
		RatingComp comp;
		mergeSort(hits, comp);
		searchResultsList->clear();
		for(unsigned int i=0; i<hits.size(); i++){
			QString temp = QString::fromStdString(hits[i]->displayString());
			searchResultsList->addItem(temp);
		}
		database->setHits(hits);
	}
}

//save into a new database
void MainWindow::save()
{
	QMessageBox msgBox;
	if(saveDBLine->text().isEmpty()){
		msgBox.setText(QString::fromStdString("Please enter database name."));
		msgBox.exec();
		return;
	}
	//take name entered and create/dump database
	ofstream ofile(saveDBLine->text().toStdString().c_str());
	database->dump(ofile);
	ofile.close();
	msgBox.setText(QString::fromStdString("Saved!"));
	msgBox.exec();

}

//add a product to a user
void MainWindow::addToCart()
{
	QMessageBox msgBox;
	//checking if product/user are selected
	if(searchResultsList->currentRow()<0){
		msgBox.setText(QString::fromStdString("Please select product to add to cart."));
		msgBox.exec();
		return;
	}

	if(usersList->currentRow()<0){
		msgBox.setText(QString::fromStdString("Please select user to add item."));
		msgBox.exec();
		return;
	}

	//the user selected
	User* u = database->getUsers()[usersList->currentRow()];

	//what happened when adding to cart product message
	string m = database->addToCart(u, searchResultsList->currentRow()+1, database->getHits());
	msgBox.setText(QString::fromStdString(m));
	msgBox.exec();
}

//view a user's cart
void MainWindow::viewCart()
{
	//check if user is selected
	if(usersList->currentRow()<0){
		QMessageBox msgBox;
		msgBox.setText(QString::fromStdString("Please select user to view cart."));
		msgBox.exec();
		return;
	}
	//open new cart window
	User* user = database->getUsers()[usersList->currentRow()];
	CartWindow cart(database, user);
	cart.exec();
	//clear previous results
	searchResultsList->clear();
}

//creates a review in a new window for a product
void MainWindow::writeReview()
{
	//check if product is selected
	if(searchResultsList->currentRow()<0){
		QMessageBox msgBox;
		msgBox.setText(QString::fromStdString("Please select product to write a review."));
		msgBox.exec();
		return;
	}
	//open review window
	Product* p = database->getHits()[searchResultsList->currentRow()];
	ReviewWindow newReview(database, p);
	newReview.exec();
	//upate/display new review added
	displayReviews();
}

//display a product's reviews
void MainWindow::displayReviews()
{
	//clear previous product's reviews
	reviewsList->clear();
	DateComp comp;
	//only display when product is clicked
	if(searchResultsList->currentRow()>=0){

		//get and sort the reviews by date
		vector<Review*> currReviews = database->getHits()[searchResultsList->currentRow()]->getReviews();

		//if a product has no reviews
		if(currReviews.size()==0){
			reviewsList->addItem(QString::fromStdString("No reviews."));
		}

		mergeSort(currReviews, comp);

		//add each review to list
		for(unsigned int i=0; i<currReviews.size(); i++){
			
			string review = currReviews[i]->prodName;
			review += "\nRating: ";
			string rating;
			ostringstream convert;
			convert << currReviews[i]->rating;
			rating = convert.str();
			review += rating;
			review += "\nDate Added: ";
			review += currReviews[i]->date;
			review += "\n'";
			review += currReviews[i]->reviewText;
			review += "'";

			reviewsList->addItem(QString::fromStdString(review));
		}
	}
	
}