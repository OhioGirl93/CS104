#ifndef HEAP_H
#define HEAP_H
#include <vector>

#include <stdexcept>

template <typename T, typename Comparator >
class Heap
{
 public:
  // Constructs an m_ary heap for any m >= 2
  Heap(int m, Comparator c);

  // Destructor as needed
  ~Heap();

  // Adds an item
  void push(const T& item);

  // returns the element at the top of the heap 
  // max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  // returns true if the heap is empty
  bool empty() const;

 private:
    std::vector<T> heapVec;

    void heapify (int index);
    Comparator comp;
    int m_ary;

};

// handles the case of calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // exceptions handle the case of trying to access the top of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If heap has at least 1 item, return the top element
  return heapVec[0];
}

// handles the case of calling pop on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }

  heapVec[0] = heapVec.back();
  heapVec.pop_back();
  heapify(0);

}

template <typename T, typename Comparator>
void Heap<T,Comparator>::heapify (int index){

  if(index > heapVec.size())
    return;

  //index of the left child
  int leftChild = m_ary*index+1;

  if(leftChild > heapVec.size())
    return;

  //biggest/smallest of all the childs
  int topChild = leftChild;

  //if leftChild is not a leaf node
  if(m_ary*leftChild+1 < heapVec.size()){ //checks if leftchild has children
    // loop through index's children, finding the "top" child
     for(int i=leftChild; i<leftChild+m_ary; i++){
      if(comp(heapVec[i], heapVec[topChild]))
        topChild = i;
     }
  }
  // if leftChild is a leaf node, but more leaf nodes on other nodes
  else if(leftChild+m_ary < heapVec.size()){
    // loop through leaves until end
    for(int i=leftChild; i<leftChild+m_ary; i++){
      if(comp(heapVec[i], heapVec[topChild]))
        topChild = i;
    }
  }
  // if leftChild and other leaf nodes are on same node
  else{
    // loop through leaves until end
    for(int i=leftChild; i<heapVec.size(); i++){
      if(comp(heapVec[i], heapVec[topChild]))
        topChild = i;
    }
  }

  if(!comp(heapVec[index], heapVec[topChild])){
    T temp = heapVec[index];
    heapVec[index] = heapVec[topChild];
    heapVec[topChild] = temp;
    heapify(topChild);
  }
}

template <typename T, typename Comparator>
Heap<T,Comparator>::Heap(int m, Comparator c){
  comp = c;
  m_ary = m;
}

template <typename T, typename Comparator>
Heap<T,Comparator>::~Heap(){
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item){

  heapVec.push_back(item);

  if(heapVec.size()>1){
    int loc = heapVec.size()-1;
    int parent = (loc-1)/m_ary;

    while(parent >=0 && comp(heapVec[loc], heapVec[parent])){
      T temp = heapVec[parent];
      heapVec[parent] = heapVec[loc];
      heapVec[loc] = temp;
      loc = parent;
      parent = (loc-1)/m_ary;
    }
  }
  
}

template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const{
  return heapVec.size()==0;
}

#endif

