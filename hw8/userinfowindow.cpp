#include "userinfowindow.h"
#include <iostream>
#include <sstream>
using namespace std;

UserInfoWindow::UserInfoWindow(DataBase* db, string u, string pass, int p){
	database = db;

	username = u;
	spassword = pass;
	password = p;

	setWindowTitle("Additional User Information");

	overallLayout = new QVBoxLayout();

	confirmInfoLabel = new QLabel("Please confirm the following information is as desired:");
	string str1 = "Username: " + username;
	usernameLabel = new QLabel(QString::fromStdString(str1));

	string str2 = "Password: " + spassword;
	passwordLabel = new QLabel(QString::fromStdString(str2));

	ageLabel = new QLabel("Enter your age.");
	ageLine = new QSpinBox();
	ageLine->setMaximum(999);

	creditAmountLabel = new QLabel("Enter your credit amount.");
	creditAmountLine = new QSpinBox();
	creditAmountLine->setMaximum(9999);

	finishButton = new QPushButton("FINISH");

	exitButton = new QPushButton("EXIT");

	overallLayout->addWidget(confirmInfoLabel);
	overallLayout->addWidget(usernameLabel);
	overallLayout->addWidget(passwordLabel);
	overallLayout->addWidget(ageLabel);
	overallLayout->addWidget(ageLine);
	overallLayout->addWidget(creditAmountLabel);
	overallLayout->addWidget(creditAmountLine);
	overallLayout->addWidget(finishButton);
	overallLayout->addWidget(exitButton);

	setLayout(overallLayout);

	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(finishButton, SIGNAL(clicked()), this, SLOT(finish()));
}

UserInfoWindow::~UserInfoWindow(){
	delete confirmInfoLabel;
	delete usernameLabel;
	delete passwordLabel;
	delete ageLabel;
	delete ageLine;
	delete creditAmountLabel;
	delete creditAmountLine;
	delete finishButton;
	delete exitButton;
	delete overallLayout;
}

void UserInfoWindow::finish()
{
	User* newUser = new User(username, ageLine->value(), (double)creditAmountLine->value(), 0, password);
	database->addUser(newUser);
	QMessageBox msgBox;
	msgBox.setText(QString::fromStdString("Account successfully created! Please log in!"));
	msgBox.exec();
	close();
}