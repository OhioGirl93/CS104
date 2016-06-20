#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include "database.h"

class UserInfoWindow : public QDialog
{
	Q_OBJECT
public:
	UserInfoWindow(DataBase* db, std::string u, std::string pass, int p);
	~UserInfoWindow();

private slots:
	void finish();

private:

	DataBase* database;

	std::string username;
	std::string spassword;
	int password;

	QVBoxLayout* overallLayout;

	QLabel* confirmInfoLabel;
	QLabel* usernameLabel;
	QLabel* passwordLabel;

	QLabel* ageLabel;
	QSpinBox* ageLine;

	QLabel* creditAmountLabel;
	QSpinBox* creditAmountLine;

	QPushButton* finishButton;

	QPushButton* exitButton;
};