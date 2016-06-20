#ifndef SETINT_H
#define SETINT_H
#include "llistint.h"

class SetInt {
 public:
  /**
   * Default constructor - default to a list of capacity = 10
   */
  SetInt();

  /**
   * Destructor
   */
  ~SetInt();

  /**
   * Returns the current number of items in the list 
   */
  int size() const;

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val into the set, do nothing if val already exists
   */
  void insert(const int& val);

  /**
   * Removes the value at index, pos
   */
  void remove(const int& val);

  /**
   * Returns true if the item is in the set
   */
  bool exists(const int& val) const;

  /**
   * Return a pointer to the first item
   *  and support future calls to next()
   */
  int const* first();

  /**
   * Return a pointer to the next item
   *  after the previous call to next
   *  and NULL if you reach the end
   */
  int const* next();

  /**
   * Returns another (new) set that contains
   * the union of this set and "other"
   */
  SetInt setUnion(const SetInt& other) const;

  /**
   * Returns another (new) set that contains
   * the intersection of this set and "other"
   */
  SetInt setIntersection(const SetInt& other) const;

  SetInt operator|(const SetInt& other) const;

  SetInt operator&(const SetInt& other) const;


 private:
  LListInt list_;
  int size_;
  int position;

  /**
   * Declare other members here
   */

};

#endif
