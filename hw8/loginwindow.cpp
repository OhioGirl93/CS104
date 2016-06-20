#include "loginwindow.h"
#include "mainwindow.h"
#include "userinfowindow.h"
#include <iostream>
#include <algorithm>
#include <string> 
#include <math.h>
using namespace std;

LoginWindow::LoginWindow(DataBase* db){

	setWindowTitle("Amazon Login");

	database = db;

	overallLayout = new QVBoxLayout();

	existingUserLabel = new QLabel("Existing User Login");
	usernameLabel = new QLabel("Username:");
	usernameLine = new QLineEdit();
	overallLayout->addWidget(existingUserLabel);
	overallLayout->addWidget(usernameLabel);
	overallLayout->addWidget(usernameLine);

	passwordLabel = new QLabel("Password:");
	passwordLine = new QLineEdit();
	loginButton = new QPushButton("LOGIN");
	overallLayout->addWidget(passwordLabel);
	overallLayout->addWidget(passwordLine);
	overallLayout->addWidget(loginButton);

	newUserLabel = new QLabel("New User? Create an Account!");
	newUsernameLabel = new QLabel("New Username:");
	newUsernameLine = new QLineEdit();

	newPasswordLabel = new QLabel("New Password:");
	newPasswordLine = new QLineEdit();

	newPasswordLabel2 = new QLabel("Confirm Password:");
	newPasswordLine2 = new QLineEdit();

	createUserButton = new QPushButton("CREATE NEW ACCOUNT");
	overallLayout->addWidget(newUserLabel);
	overallLayout->addWidget(newUsernameLabel);
	overallLayout->addWidget(newUsernameLine);
	overallLayout->addWidget(newPasswordLabel);
	overallLayout->addWidget(newPasswordLine);
	overallLayout->addWidget(newPasswordLabel2);
	overallLayout->addWidget(newPasswordLine2);
	overallLayout->addWidget(createUserButton);

	QPushButton* exitButton = new QPushButton("EXIT");
	overallLayout->addWidget(exitButton);
	setLayout(overallLayout);

	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));
	connect(createUserButton, SIGNAL(clicked()), this, SLOT(createUser()));

}

LoginWindow::~LoginWindow()
{
	qDeleteAll(this->children());
}

int LoginWindow::hashfunction(string p)
{
	long long int p1 = 0;
	for(unsigned int i=0; i<p.length(); i++){
		p1 += (long long)pow(128, i) * (long long)p[p.length()-i-1];
	}

	unsigned int array [4];

	array[3] = p1%65521;
	p1 /= (long long)65521;

	array[2] = p1%65521;
	p1 /= (long long)65521;

	array[1] = p1%65521;
	p1 /= (long long)65521;

	array[0] = p1%65521;
	p1 /= (long long)65521;

	unsigned int hashpass = ((45912*array[0]) + (35511*array[1]) + (65169*array[2]) + (4625*array[3])) % 65521;

	return hashpass;
}

void LoginWindow::login()
{
	QMessageBox msgBox;
	if(usernameLine->text().isEmpty()){
		msgBox.setText(QString::fromStdString("No Username entered. Please try again."));
		msgBox.exec();
		return;
	}
	if(passwordLine->text().isEmpty()){
		msgBox.setText(QString::fromStdString("No Password entered. Please try again."));
		msgBox.exec();
		return;
	}
	string u = usernameLine->text().toStdString();
	int pass = hashfunction(passwordLine->text().toStdString());
	bool found = false;
	User* user = NULL;
	for(unsigned int i=0; i<database->getUsers().size(); i++){
		if(database->getUsers()[i]->getName()==u){
			found = true;
			user = database->getUsers()[i];
			if(database->getUsers()[i]->getPassword()!=pass){
				msgBox.setText(QString::fromStdString(
					"Password is incorrect. Please try again.\n*Note: Please include all capital letters"));
				msgBox.exec();
				return;
			}
		}
	}
	if(!found && user==NULL){
		msgBox.setText(QString::fromStdString(
			"Username was not found. Please try again.\n*Note: Disregard all capital letters"));
		msgBox.exec();
		return;
	}

	close();
	MainWindow mw(*database, *user);
	mw.exec();
	show();

	usernameLine->setText("");
	passwordLine->setText("");
}

void LoginWindow::createUser()
{
	QMessageBox msgBox;
	if(newUsernameLine->text().isEmpty()){
		msgBox.setText(QString::fromStdString("No Username entered. Please try again."));
		msgBox.exec();
		return;
	}

	string username = newUsernameLine->text().toStdString();
	transform(username.begin(), username.end(), username.begin(), ::tolower);

	for(unsigned int i=0; i<database->getUsers().size(); i++){
		if(database->getUsers()[i]->getName()==username){
			msgBox.setText(QString::fromStdString("Username already exists. Please try again."));
			msgBox.exec();
			return;
		}
	}

	if(newPasswordLine->text().isEmpty()){
		msgBox.setText(QString::fromStdString("No Password entered. Please try again."));
		msgBox.exec();
		return;
	}

	if(newPasswordLine2->text().isEmpty()){
		msgBox.setText(QString::fromStdString("Please confirm password."));
		msgBox.exec();
		return;
	}

	string p1 = newPasswordLine->text().toStdString();
	string p2 = newPasswordLine2->text().toStdString();

	if(p1.length()>8){
		msgBox.setText(QString::fromStdString("Password can only be 8 characters long."));
		msgBox.exec();
		return;
	}

	for(unsigned int i=0; i<p1.length(); i++){
		if(p1[i]==' '){
			msgBox.setText(QString::fromStdString("Password cannot have any whitespace."));
			msgBox.exec();
			return;
		}
	}

	if(p1!=p2){
		msgBox.setText(QString::fromStdString("Passwords do not match. Please try again."));
		msgBox.exec();
		return;
	}

	msgBox.setText(
	QString::fromStdString("Account created!\nPlease enter additional information to complete registration."));
	msgBox.exec();

	int hpass = hashfunction(p1);

	UserInfoWindow ui (database, username, p1, hpass);
	ui.exec();

	newUsernameLine->setText("");
	newPasswordLine->setText("");
	newPasswordLine2->setText("");
}