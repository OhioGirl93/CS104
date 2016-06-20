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
#include "util.h"
#include "heap.h"

class MainWindow : public QDialog
{
	Q_OBJECT
public:
	MainWindow(DataBase& db, User& u);
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
	User* mainUser;

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

	QVBoxLayout* rhsLayout;

	QLabel* usersLabel;
	QPushButton* signOutButton;

	QLabel* balanceLabel;

	QPushButton* addToCartButton;
	QPushButton* viewCartButton;
	QLabel* reviewLabel;
	QListWidget* reviewsList;
	QPushButton* writeReviewButton;

	QLabel* recommendation;

	std::string makeRec();
	double basicSim(User* u1, User* u2);
	double refinedSim(User* u1, User* u2);

};