#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include "database.h"

class LoginWindow : public QDialog
{
	Q_OBJECT
public:
	LoginWindow(DataBase* db);
	~LoginWindow();

private slots:
	void login();
	void createUser();

private:
	DataBase* database;

	QVBoxLayout* overallLayout;

	QLabel* existingUserLabel;
	QLabel* usernameLabel;
	QLineEdit* usernameLine;
	
	QLabel* passwordLabel;
	QLineEdit* passwordLine;
	QPushButton* loginButton;

	QLabel* newUserLabel;
	QLabel* newUsernameLabel;
	QLineEdit* newUsernameLine;

	QLabel* newPasswordLabel;
	QLineEdit* newPasswordLine;

	QLabel* newPasswordLabel2;
	QLineEdit* newPasswordLine2;

	QPushButton* createUserButton;
	QPushButton* exitButton;

	int hashfunction(std::string p);
};