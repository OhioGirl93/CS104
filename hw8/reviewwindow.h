#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QMessageBox>
#include "database.h"
#include "review.h"

class ReviewWindow : public QDialog
{
	Q_OBJECT
public:
	ReviewWindow(DataBase* db, Product* p);
	~ReviewWindow();

private slots:
	void createReview();

private:
	DataBase* database;
	Product* product;

	QHBoxLayout* overallLayout;
	QVBoxLayout* lhsLayout;
	QLabel* reviewLabel;
	QTextEdit* reviewTextBox;

	QVBoxLayout* rhsLayout;
	QLabel* ratingLabel;
	QListWidget* ratingList;
	QLabel* dateLabel;
	QLabel* yearLabel;
	QLabel* monthLabel;
	QLabel* dayLabel;
	QLineEdit* yearLine;
	QLineEdit* monthLine;
	QLineEdit* dayLine;
	QPushButton* submitButton;
	QPushButton* cancelButton;
};