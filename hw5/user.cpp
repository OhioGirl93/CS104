#include "user.h"
using namespace std;

User::User() : name_("unknown"), age_(0), balance_(0.0), type_(1)
{

}
User::User(std::string name, int age, double balance, int type) : 
  name_(name), age_(age), balance_(balance), type_(type)
{

}

User::~User()
{

}

double User::getBalance() const
{
  return balance_;
}

int User::getAge() const
{
  return age_;
}

std::string User::getName() const
{
  return name_;
}

void User::deductAmount(double amt)
{
  balance_ -= amt;
}

void User::dump(std::ostream& os)
{
  os << name_ << " " << age_ << " " << balance_ << " " << type_ << endl;
}