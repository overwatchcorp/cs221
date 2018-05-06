#ifndef _LLIST_H_
#define _LLIST_H_

#include <string>

// Each element in chain of nodes for linked list
struct Node{
  std::string data;
  Node *next;
};

// This is a singly linked list.  It stores an ordered collection
// of strings.  Ordering starts at 0.
class LList {
 public:
  // Default constructor
  LList();

  // Destructor deallocates all memory allocated by list
  ~LList();

  // Returns the number of entries in list
  int getLength() const;

  // Returns the string at specified position.  If position is not in the 
  // range [0, length), returns "".
  std::string getElementAt(int position) const;

  // Inserts specified string at the end of the list. 
  void append(std::string str);

  // Inserts specified string at position. pos must be in the range [0, length]
  // Returns true if str inserted successfully.  Otherwise, returns false.
  bool insert(std::string str, int position);

  // Removes the specified string and returns true if successful. Returns false
  // if specified string could not be removed.
  bool remove(std::string str);

  // Removes the string at specified position. position must be in the range 
  // [0, length). Returns true if successful.  Otherwise, returns false.
  bool remove(int position);
  
  // Returns the position of the specified string.  Returns -1 if the specified
  // string does not appear in the list.  If the string appears more than
  // once in the list, returns its first position.
  int find(std::string str) const;

 private:
  Node * myHeadNode;

};

#endif
