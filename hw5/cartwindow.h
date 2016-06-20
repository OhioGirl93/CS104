#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QString>
#include <string>
#include <deque>
#include "database.h"

class CartWindow : public QDialog
{
	Q_OBJECT
public:
	CartWindow(DataBase* db, User* u);
	~CartWindow();

private slots:
	void buy();
	void buyAll();
	void remove();

private:
	DataBase* database;
	User* user;
	deque<Product*> cart;
	QHBoxLayout* overallLayout;

	QVBoxLayout* lhsLayout;
	QLabel* shoppingCartLabel;
	QListWidget* shoppingCartList;

	QVBoxLayout* rhsLayout;
	QPushButton* buyButton;
	QPushButton* buyAllButton;
	QPushButton* removeButton;
	QPushButton* exitButton;
};
