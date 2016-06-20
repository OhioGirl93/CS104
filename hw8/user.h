#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <set>

class Product;
/**
 * Implements User functionality and information storage
 */
class User{
 public:
  User();
  User(std::string name, int age, double balance, int type, int password);
  virtual ~User();

  int getAge() const;
  std::string getName() const;
  void deductAmount(double amt);
  double getBalance() const;
  int getPassword() const;
  virtual void dump(std::ostream& os);
  std::set<Product*> getReviewedList();
  void addToReviewedList(Product* p);

 private:
  std::set<Product*> reviewedList;
  std::string name_;
  int age_;
  double balance_;
  int type_;
  int password_;
};
#endif
