#include "cartwindow.h"
#include <iostream>
using namespace std;

CartWindow::CartWindow(DataBase* db, User* u)
{
	setWindowTitle("Shopping Cart");

	database = db;
	user = u;

	overallLayout = new QHBoxLayout();

	//lhs is the list of products in the the cart
	//rhs are the buy/buy all/remove/exit buttons

	lhsLayout = new QVBoxLayout();
	rhsLayout = new QVBoxLayout();
	overallLayout->addLayout(lhsLayout);
	overallLayout->addLayout(rhsLayout);

	shoppingCartLabel = new QLabel("Shopping Cart");
	shoppingCartList = new QListWidget();
	lhsLayout->addWidget(shoppingCartLabel);
	lhsLayout->addWidget(shoppingCartList);

	buyButton = new QPushButton("BUY");
	removeButton = new QPushButton("REMOVE");
	buyAllButton = new QPushButton("BUY ALL");
	exitButton = new QPushButton("EXIT");
	rhsLayout->addWidget(buyButton);
	rhsLayout->addWidget(removeButton);
	rhsLayout->addWidget(buyAllButton);
	rhsLayout->addWidget(exitButton);

	cart = database->getCart()[user];

	//display all the products in cart
	for(unsigned int i=0; i<cart.size(); i++){
		string p = cart[i]->displayString();
		QString temp = QString::fromStdString(p);
		shoppingCartList->addItem(temp);
	}

	connect(buyButton, SIGNAL(clicked()), this, SLOT(buy()));
	connect(buyAllButton, SIGNAL(clicked()), this, SLOT(buyAll()));
	connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

	setLayout(overallLayout);
}

CartWindow::~CartWindow()
{
	delete shoppingCartLabel;
	delete shoppingCartList;
	delete buyButton;
	delete buyAllButton;
	delete removeButton;
	delete exitButton;
	delete rhsLayout;
	delete lhsLayout;
	delete overallLayout;
}

//buys all products, skipping over ones the user cannot afford/out of stock
void CartWindow::buyAll()
{
	QMessageBox msgBox;
	//check if cart is empty
	if(cart.size()==0){
		msgBox.setText(QString::fromStdString("Shopping cart is empty."));
		msgBox.exec();
	}
	else{
		//summary of what was bought/skipped/removed from cart
		string message = database->buyAll(user);
		msgBox.setText(QString::fromStdString(message));
		msgBox.exec();

		//display updated list
		shoppingCartList -> clear();
		cart = database->getCart()[user];
		for(unsigned int i=0; i<cart.size(); i++){
			string p = cart[i]->displayString();
			QString temp = QString::fromStdString(p);
			shoppingCartList->addItem(temp);
		}
	}
}

//removes selected item from cart
void CartWindow::remove()
{
	QMessageBox msgBox;
	//check if product is selected
	if(shoppingCartList->currentRow()<0){
		msgBox.setText(QString::fromStdString("Please select item to remove."));
		msgBox.exec();
		return;
	}

	//switches selected item with first item and then pops the front to delete
	if(cart.size()>1){
		Product* temp = cart[0];
		cart[0] = cart[shoppingCartList->currentRow()];
		cart[shoppingCartList->currentRow()] = temp;
	}	

	cart.pop_front();
	database->setCart(user, cart);

	msgBox.setText(QString::fromStdString("You have removed this item."));
	msgBox.exec();

	//display updated list
	shoppingCartList -> clear();
	cart = database->getCart()[user];
	for(unsigned int i=0; i<cart.size(); i++){
		string p = cart[i]->displayString();
		QString temp = QString::fromStdString(p);
		shoppingCartList->addItem(temp);
	}
}

//buys a single selected item
void CartWindow::buy()
{
	QMessageBox msgBox;
	//checks if item was bought
	if(shoppingCartList->currentRow()<0){
		msgBox.setText(QString::fromStdString("Please select item to buy."));
		msgBox.exec();
		return;
	}
	//summary of trying to buy the item
	string message = database->buySingle(user, shoppingCartList->currentRow());
	msgBox.setText(QString::fromStdString(message));
	msgBox.exec();

	//displayed updated cart
	shoppingCartList -> clear();
	cart = database->getCart()[user];
	for(unsigned int i=0; i<cart.size(); i++){
		QString temp = QString::fromStdString(cart[i]->displayString());
		shoppingCartList->addItem(temp);
	}
}