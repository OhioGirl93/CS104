#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QString>
#include <QMessageBox>
#include <string>
#include <vector>
#include "database.h"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(DataBase& db);
	~MainWindow();

private slots:
	void search();
	void sortA();
	void sortR();
	void save();
	void addToCart();
	void viewCart();
	void writeReview();
	void displayReviews();

private:
	DataBase* database;

	QHBoxLayout* overallLayout;

	QVBoxLayout* lhsLayout;
	QLabel* searchLabel;
	QLineEdit* searchBox;
	QPushButton* searchButton;
	QRadioButton* andButton;
	QRadioButton* orButton;
	QListWidget* searchResultsList;
	QPushButton* sortAlphaButton;
	QPushButton* sortRatingButton;
	QLabel* saveDBLabel;
	QPushButton* saveDBButton;
	QLineEdit* saveDBLine;
	QLabel* exitLabel;
	QPushButton* exitButton;


	QVBoxLayout* rhsLayout;
	QLabel* usersLabel;
	QListWidget* usersList;
	QPushButton* addToCartButton;
	QPushButton* viewCartButton;
	QLabel* reviewLabel;
	QListWidget* reviewsList;
	QPushButton* writeReviewButton;

};