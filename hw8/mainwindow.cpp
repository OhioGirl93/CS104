#include "mainwindow.h"
#include "database.h"
#include <sstream>
#include <fstream>
#include <string>
#include "msort.h"
#include <cmath>
#include "reviewwindow.h"
#include "cartwindow.h"

using namespace std;

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

struct DJNode
{
	DJNode(double d, User* u, bool c){
		distance = d;
		curr = u;
		checked = c;
	}

	double distance;
	User* curr;
	bool checked;
};

struct DJComp
{
	bool operator() (DJNode* x, DJNode* y){
		return (x->distance) < (y->distance);
	}
};

MainWindow::MainWindow(DataBase& db, User& u)
{
	database = &db;
	mainUser = &u;

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
	recommendation = new QLabel(QString::fromStdString(makeRec()));

	searchResultsList = new QListWidget();
	lhsLayout->addWidget(andButton);
	lhsLayout->addWidget(orButton);
	lhsLayout->addWidget(searchButton);
	lhsLayout->addWidget(recommendation);
	lhsLayout->addWidget(searchResultsList);

	addToCartButton = new QPushButton("Add to Cart");
	lhsLayout->addWidget(addToCartButton);

	sortAlphaButton = new QPushButton("Sort Alphabetically");
	sortRatingButton = new QPushButton("Sort by Rating");
	lhsLayout->addWidget(sortAlphaButton);
	lhsLayout->addWidget(sortRatingButton);

	//RHS
	usersLabel = new QLabel(QString::fromStdString("Signed in as: " + mainUser->getName()));
	rhsLayout->addWidget(usersLabel);

	stringstream ss;
	ss << mainUser->getBalance();
	string balance = "Balance: $" + ss.str();
	balanceLabel = new QLabel(QString::fromStdString(balance));
	rhsLayout->addWidget(balanceLabel);

	viewCartButton = new QPushButton("View Cart");
	rhsLayout->addWidget(viewCartButton);

	signOutButton = new QPushButton("SIGN OUT");
	rhsLayout->addWidget(signOutButton);

	reviewLabel = new QLabel("Reviews");
	reviewsList = new QListWidget();
	writeReviewButton = new QPushButton("Write Review");
	rhsLayout->addWidget(reviewLabel);
	rhsLayout->addWidget(reviewsList);
	rhsLayout->addWidget(writeReviewButton);

	saveDBLabel = new QLabel("Enter Database to Save");
	saveDBLine = new QLineEdit();
	saveDBButton = new QPushButton("SAVE DATABASE");
	rhsLayout->addWidget(saveDBLabel);
	rhsLayout->addWidget(saveDBLine);
	rhsLayout->addWidget(saveDBButton);

	connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
	connect(sortAlphaButton, SIGNAL(clicked()), this, SLOT(sortA()));
	connect(sortRatingButton, SIGNAL(clicked()), this, SLOT(sortR()));
	connect(signOutButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(saveDBButton, SIGNAL(clicked()), this, SLOT(save()));
	connect(searchResultsList, SIGNAL(currentRowChanged(int)), this, 
		SLOT(displayReviews()));
	connect(addToCartButton, SIGNAL(clicked()), this, SLOT(addToCart()));
	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(viewCart()));
	connect(writeReviewButton, SIGNAL(clicked()), this, SLOT(writeReview()));
	
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
	delete balanceLabel;
	delete signOutButton;
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

	//what happened when adding to cart product message
	string m = database->addToCart(mainUser, searchResultsList->currentRow()+1, database->getHits());
	msgBox.setText(QString::fromStdString(m));
	msgBox.exec();
}

//view a user's cart
void MainWindow::viewCart()
{
	CartWindow cart(database, mainUser);
	cart.exec();
	//clear previous results
	searchResultsList->clear();
	stringstream ss;
	ss << mainUser->getBalance();
	string b = "Balance: $" + ss.str();
	balanceLabel->setText(QString::fromStdString(b));
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
			review += "\nUser: ";
			review += currReviews[i]->username;
			review += "\nDate Added: ";
			review += currReviews[i]->date;
			review += "\n'";
			review += currReviews[i]->reviewText;
			review += "'";

			reviewsList->addItem(QString::fromStdString(review));
		}
	}
}

std::string MainWindow::makeRec()
{
	std::string rec = "Recommendation:\nNo products to recommend";

	if(mainUser->getReviewedList().size()==database->getProducts().size() || mainUser->getReviewedList().size()==0){
		return rec;
	}

	set<Product*> reviewed = mainUser->getReviewedList();
	Product* highestProd = NULL;
	double interestingness = -1.0;

	for(unsigned int i=0; i<database->getProducts().size(); i++){
		if(reviewed.find(database->getProducts()[i])==reviewed.end()){
			set<User*> u = database->getProducts()[i]->getReviewedUsers();
			double rp = 0.0;
			double w = 0.0;
			for(set<User*>::iterator it = u.begin(); it!=u.end(); ++it){
				double sim = refinedSim(mainUser, (*it));
				int rating = 0;
				for(unsigned int j = 0; j<database->getProducts()[i]->getReviews().size(); j++){
					if(database->getProducts()[i]->getReviews()[j]->username == (*it)->getName()){
						rating = database->getProducts()[i]->getReviews()[j]->rating;
					}
				}
				rp += (1.0-sim)*rating;
				w += 1.0-sim;
			}

			if(rp==0 || w==0){
				if(interestingness<0.0){
					highestProd = database->getProducts()[i];
					interestingness = 0.0;
				}
				cout << "      INTERESTINGNESS of " << database->getProducts()[i]->getName() << ": " << rp/w << endl;
			}
			else{
				cout << "RP: " << rp << "\n" <<"W: "<< w << endl;
				if(interestingness<(rp/w)){
					highestProd = database->getProducts()[i];
					interestingness = rp/w;
				}
				cout << "      INTERESTINGNESS of " << database->getProducts()[i]->getName() << ": " << rp/w << endl;

			}
		}
	}

	if(highestProd!=NULL)
		rec = "Recommendation:\n" + highestProd->getName();

	return rec;
}

double MainWindow::basicSim(User* u1, User* u2)
{
	set<Product*> setU = setIntersection(u1->getReviewedList(), u2->getReviewedList());
	//if nothing in commong, bS = 1.0
	if(setU.size()==0){
		return 1.0;
	}
	else{
		double b = 10.5;
		//Go through set all products that MainUser and CurrentUser have in common
		for(set<Product*>::iterator it = setU.begin(); it!=setU.end(); ++it){

			int mainUserRating = 0;
			int currUserRating = 0;

			// Loop through the reviews of each product
			for(unsigned int i=0; i<(*it)->getReviews().size(); i++){

				//if the review was by MainUser, save the rating
				if((*it)->getReviews()[i]->username==u1->getName())
					mainUserRating = (*it)->getReviews()[i]->rating;

				//if the review was by CurrUser, save the rating
				if((*it)->getReviews()[i]->username==u2->getName())
					currUserRating = (*it)->getReviews()[i]->rating;
			}
			//set the bS
			b = (double)abs(mainUserRating - currUserRating)/(double)4;
		}
		//cout << "BASIC " << u1->getName() << " to " << u2->getName() << ": " << b << endl;
		return b;
	}
}

double MainWindow::refinedSim(User* u1, User* u2)
{
	DJComp comp;
	Heap<DJNode*, DJComp> heap (2, comp);
	DJNode* start = new DJNode(0.0, u1, true);
	heap.push(start);

	vector<DJNode*> nodes;

	for(unsigned int i=0; i<database->getUsers().size(); i++){
		if(database->getUsers()[i]!=u1){
			DJNode* newUser = new DJNode(5.5, database->getUsers()[i], false);
			heap.push(newUser);
			nodes.push_back(newUser);
		}
	}

	while(!heap.empty()){

		DJNode* min = heap.top();
		min->checked = true;
		heap.pop();

		for(unsigned int i=0; i<nodes.size(); i++){
			double bSim = basicSim(min->curr, nodes[i]->curr);
			//&& nodes[i]->curr!=u2
			if(nodes[i]->checked==false && min->distance+bSim < nodes[i]->distance){
				nodes[i]->distance = min->distance + bSim;
			}

			while(!heap.empty()){
				heap.pop();
			}

			for(unsigned int j=0; j<nodes.size(); j++){
				if(nodes[j]->checked==false)
					heap.push(nodes[j]);
			}
		}
	}

	double finalSim = 5.5;

	for(unsigned int i=0; i<nodes.size(); i++){
		if(nodes[i]->curr==u2){
			finalSim = nodes[i]->distance;
		}
	}

	cout << "   REFINED: " <<u1->getName() << " to " << u2->getName() << ": " << finalSim << endl;

	return finalSim;
}