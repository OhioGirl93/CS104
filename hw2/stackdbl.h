#ifndef STACKDBL_H
#define STACKDBL_H
#include "llistdbl.h"

class StackDbl {
 public:
  //Constructor/Destructor
  StackDbl();
  ~StackDbl();

  /**
   * Returns true if the stack is empty, false otherwise
   */
  bool empty() const;

  /**
   * Pushes a new value, val, onto the top of the stack
   */
  void push(const double& val);

  /**
   * Returns the top value on the stack
   */
  double const &  top() const;

  /**
   * Removes the top element on the stack
   */
  void pop();

 private:
  /** 
   * Single data member of the Stack.
   * We use composition to implement this Stack 
   */
  LListDbl list_;
};
#endif
