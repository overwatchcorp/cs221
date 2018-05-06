// Naomi Boss and Jasper Fung
#include "LList.h"

// Default constructor
LList::LList()
{
  myHeadNode = nullptr;
}

// Destructor deallocates all memory allocated by list
LList::~LList()
{
	Node *tmp = myHeadNode;

	while(tmp != nullptr)
	{
		Node *tmpNext = tmp->next;
		delete tmp;
		tmp = tmpNext;
	}
}

// Returns the number of items in the list
int LList::getLength() const
{
	int count = 0;
	Node *tmp = myHeadNode;

	while(tmp != nullptr) {
		count += 1;
		tmp = tmp->next;
	}

	return count;
}

// Returns the string at specified position.  If position is not in the
// range [0, length), returns "".
std::string LList::getElementAt(int position) const
{
	std::string result = "";
	if(position < 0 || position > getLength()){
    	return result;
	}

	Node *tmp = myHeadNode;

	if (tmp == nullptr) {
		return result;
	}


	for(int i= 0; i < position; i++){
		tmp = tmp->next;
	}


  if (tmp != nullptr) {
    result = tmp->data;
  }

  return result;
}

// Inserts specified string at the end of the list
void LList::append(std::string str)
{
  Node *tmp = myHeadNode;

  if(tmp == nullptr){
    tmp = new Node();
    tmp->data = str;
    tmp->next = nullptr;
    myHeadNode = tmp;
  }
  else{
    while(tmp->next != nullptr){
      tmp = tmp->next;
    }
    tmp->next = new Node();
    tmp->next->data = str;
    tmp->next->next = nullptr;
  }

}


// Inserts specified string at position. pos must be in the range [0, length]
// Returns true if str inserted successfully.  Otherwise, returns false.
bool LList::insert(std::string str, int position)
{
  if(position < 0 || position > getLength()){
    return false;
  }

  Node *tmp = myHeadNode;

  if(position == 0) {
    Node *newNode = new Node();
    newNode->next = myHeadNode;
    newNode->data = str;
    myHeadNode = newNode;
    return true;
  }

  if(position == getLength()) {
    append(str);
    return true;
  }

  // move to the position
  int index = 0;
  while (index < position - 1) {
    tmp = tmp->next;
    index += 1;
  }
  Node *prevNext = tmp->next;
  tmp->next = new Node();
  tmp->next->data = str;
  tmp->next->next = prevNext;
  return true;
}

// Removes the specified string and returns true if successful. Returns false
// if specified string could not be removed.
bool LList::remove(std::string str)
{
	Node *tmp = myHeadNode;

  if(tmp == nullptr) { return false; }

  int pos = 0;
	while(tmp != nullptr) {

		if(tmp->data == str) {
      return remove(pos);
		}
    pos += 1;
    tmp = tmp->next;
	}

	return false;

}

// Removes the string at specified position. position must be in the range
// [0, length). Returns true if successful.  Otherwise, returns false.
bool LList::remove(int position)
{
  if((position < 0) || (position >= getLength()) ){
    return false;
  }

  Node *tmp = myHeadNode;

  if(position == 0) {
    myHeadNode = myHeadNode->next;
    return true;
  }

  if(position == getLength()) {
    while (tmp->next->next != nullptr) {
      tmp = tmp->next;
    }
    tmp->next = nullptr;
    return true;
  }

  // move to the position
  int index = 0;
  while (index < position - 1) {
    tmp = tmp->next;
    index += 1;
  }
  Node *prevNextNext = tmp->next->next;
  tmp->next = prevNextNext;
  return true;

  // Node *tmp = myHeadNode;
  // int counter = 0;
  // while(counter < position) {
  // 	tmp = tmp->next;
  // 	counter += 1;
  // }
  // tmp->data = "";
  // return true;

}

// Returns the position of the specified string.  Returns -1 if the specified
// string does not appear in the list.  If the string appears more than
// once in the list, returns its first position.
int LList::find(std::string str) const
{
	int count = 0;
	Node *tmp = myHeadNode;

  if(tmp == nullptr) { return -1; }

	while(tmp != nullptr) {
		if (tmp->data == str) {
			return count;
		}
		count += 1;
		tmp = tmp->next;
	}

    return -1;
}
