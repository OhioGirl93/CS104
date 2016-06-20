#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>

/**
 * Implements User functionality and information storage
 */
class User{
 public:
  User();
  User(std::string name, int age, double balance, int type);
  virtual ~User();

  int getAge() const;
  std::string getName() const;
  void deductAmount(double amt);
  double getBalance() const;
  virtual void dump(std::ostream& os);

 private:
  std::string name_;
  int age_;
  double balance_;
  int type_;
};
#endif
