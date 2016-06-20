#include "reviewwindow.h"

ReviewWindow::ReviewWindow(DataBase* db, Product* p){
	database = db;
	product = p;

	setWindowTitle("Write a Review");

	overallLayout = new QHBoxLayout();

	lhsLayout = new QVBoxLayout();
	rhsLayout = new QVBoxLayout();
	overallLayout->addLayout(lhsLayout);
	overallLayout->addLayout(rhsLayout);

	reviewLabel = new QLabel("Write a review here");
	reviewTextBox = new QTextEdit();
	lhsLayout->addWidget(reviewLabel);
	lhsLayout->addWidget(reviewTextBox);

	ratingLabel = new QLabel("Rating (1-5)");
	ratingList = new QListWidget();
	dateLabel = new QLabel("Enter date:");
	dayLabel = new QLabel("Day (DD)");
	dayLine = new QLineEdit();
	monthLabel = new QLabel("Month (MM)");
	monthLine = new QLineEdit();
	yearLabel = new QLabel("Year (YYYY)");
	yearLine = new QLineEdit();
	submitButton = new QPushButton("SUBMIT");
	cancelButton = new QPushButton("CANCEL");

	rhsLayout->addWidget(ratingLabel);
	rhsLayout->addWidget(ratingList);
	rhsLayout->addWidget(dateLabel);
	rhsLayout->addWidget(monthLabel);
	rhsLayout->addWidget(monthLine);
	rhsLayout->addWidget(dayLabel);
	rhsLayout->addWidget(dayLine);
	rhsLayout->addWidget(yearLabel);
	rhsLayout->addWidget(yearLine);
	rhsLayout->addWidget(submitButton);
	rhsLayout->addWidget(cancelButton);

	ratingList->addItem(QString::fromStdString("1"));
	ratingList->addItem(QString::fromStdString("2"));
	ratingList->addItem(QString::fromStdString("3"));
	ratingList->addItem(QString::fromStdString("4"));
	ratingList->addItem(QString::fromStdString("5"));

	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(submitButton, SIGNAL(clicked()), this, SLOT(createReview()));

	setLayout(overallLayout);

}

ReviewWindow::~ReviewWindow(){
	delete reviewLabel;
	delete reviewTextBox;

	delete ratingLabel;
	delete ratingList;
	delete dateLabel;
	delete yearLabel;
	delete monthLabel;
	delete dayLabel;
	delete yearLine;
	delete monthLine;
	delete dayLine;
	delete submitButton;
	delete cancelButton;

	delete lhsLayout;
	delete rhsLayout;

	delete overallLayout;

}

void ReviewWindow::createReview(){
	//message box for errors invalid fields
	QMessageBox msgBox;

	//check if date fields are empty
	if(yearLine->text().isEmpty() || monthLine->text().isEmpty() 
		|| dayLine->text().isEmpty()){
		msgBox.setText(QString::fromStdString("You have not entered a valid date."));
		msgBox.exec();
		return;
	}

	//check if rating was selected
	if(ratingList->currentRow()<0){
		msgBox.setText(QString::fromStdString("You have not selected a rating."));
		msgBox.exec();
		return;
	}

	//check if a review was written
	if(reviewTextBox->toPlainText().isEmpty()){
		msgBox.setText(QString::fromStdString("You did not write a review."));
		msgBox.exec();
		return;
	}

	//checking if month field is valid
	string month = monthLine->text().toStdString();

	if(month.length()!=2){
		msgBox.setText(QString::fromStdString("Invalid month"));
		msgBox.exec();
		return;
	}
	//looking for any non-integers
	//does not work if non-integer comes after starting integer
	stringstream ssm(month);
	int m;
	ssm>>m;
	if(ssm.fail()){
		msgBox.setText(QString::fromStdString("Invalid month"));
		msgBox.exec();
		return;
	}

	//check if day field is valid
    string day = dayLine->text().toStdString();

	if(day.length()!=2){
		msgBox.setText(QString::fromStdString("Invalid day"));
		msgBox.exec();
		return;
	}

	stringstream ssd(day);
	int d;
	ssd>>d;
	if(ssd.fail()){
		msgBox.setText(QString::fromStdString("Invalid day"));
		msgBox.exec();
		return;
	}

	//check if year field is valid
	string year = yearLine->text().toStdString();
	if(year.length()!=4){
		msgBox.setText(QString::fromStdString("Invalid year"));
		msgBox.exec();
		return;
	}

	stringstream ssy(year);
	int y;
	ssy>>y;
	if(ssy.fail()){
		msgBox.setText(QString::fromStdString("Invalid year"));
		msgBox.exec();
		return;
	}

	string date = year + "-" + month + "-" + day;

	//creating new review
	Review* newReview = new Review();
	newReview->prodName = product->getName();
	newReview->rating = ratingList->currentRow()+1;
	newReview->date = date;
	newReview->reviewText = reviewTextBox->toPlainText().toStdString();

	//adding to product
	product->newReview(newReview);
	//close the review window
	this->close();
	
}