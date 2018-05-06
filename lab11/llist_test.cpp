// Naomi Boss and Jasper Fung
#include <iostream>
#include <cassert>
#include <vector>
#include "LList.h"

// Checks if the the contents of the specified list are in
// the same order as the contents of the vector.  Returns true
// if the list and vector contents match.  Otherwise, returns false.
bool isCorrect(const LList &list, std::vector<std::string> entries)
{
  if(list.getLength() != int(entries.size())){
    return false;
  }

  for(unsigned int i = 0; i < entries.size(); i++){
    if( list.getElementAt(i) != entries[i]){
      return false;
    }
  }
  return true;

}

// Returns an empty dynamically allocated llist
LList* createEmptyList()
{
  LList *result = new LList();
  return result;
}

// Returns a dynamically allocated list with one entry
LList* createSingletonList()
{
  LList *result = new LList();

  result->append("apple");

  return result;
}

// Returns a dynamically allocated list with three entries
LList* createThreeEntryList()
{

  LList *result = new LList();

  result->append("apple");
  result->append("banana");
  result->append("cherry");

  return result;

}

// Tests LList::getLength() method
void testGetLength()
{
  LList *emptyList = createEmptyList();
  assert(emptyList->getLength() == 0);
  delete emptyList;

  LList *singleList = createSingletonList();
  assert(singleList->getLength() == 1);
  delete singleList;

  LList *threeList = createThreeEntryList();
  assert(threeList->getLength() == 3);
  delete threeList;

}

// Tests LList::operator[] method
void testOperatorIndex()
{
  LList *emptyList = createEmptyList();
  assert(emptyList->getElementAt(0) == "");
  assert(emptyList->getElementAt(1) == "");
  assert(emptyList->getElementAt(-1) == "");
  delete emptyList;

  LList *singleList = createSingletonList();
  assert(singleList->getElementAt(0) == "apple");
  assert(singleList->getElementAt(1) == "");
  assert(singleList->getElementAt(-1) == "");
  delete singleList;

  LList *threeList = createThreeEntryList();
  assert(threeList->getElementAt(0) == "apple");
  assert(threeList->getElementAt(1) == "banana");
  assert(threeList->getElementAt(2) == "cherry");
  assert(threeList->getElementAt(3) == "");
  assert(threeList->getElementAt(-1) == "");
  delete threeList;

}

// Tests LList::append(str)
void testAppend()
{
  // Make sure empty list is indeed empty
  std::vector<std::string> emptyV;
  LList *emptyList = createEmptyList();
  assert(isCorrect(*emptyList, emptyV));

  // Make sure adding to empty list works
  std::vector<std::string> oneV;
  oneV.push_back("apple");
  emptyList->append("apple");
  assert(isCorrect(*emptyList, oneV));
  delete emptyList;

  // Make sure adding to non-empty list works
  std::vector<std::string> threeV;
  threeV.push_back("apple");
  threeV.push_back("banana");
  threeV.push_back("cherry");
  LList *threeList = createThreeEntryList();
  assert(isCorrect(*threeList, threeV));
  threeList->append("date");
  threeV.push_back("date");
  assert(isCorrect(*threeList, threeV));
  delete threeList;


}

// Tests LList::insert(str, pos)
void testInsert()
{

  // Make sure empty list is indeed empty
  std::vector<std::string> emptyV;
  LList *emptyList = createEmptyList();
  assert(isCorrect(*emptyList, emptyV));

  // Make sure adding to empty list works
  std::vector<std::string> oneV;
  oneV.push_back("apple");
  assert(emptyList->insert("apple", -1) == false);
  assert(emptyList->insert("apple", 1) == false);
  assert(emptyList->insert("apple", 0));
  assert(isCorrect(*emptyList, oneV));
  delete emptyList;

  // Make sure inserting at end of non-empty list works
  std::vector<std::string> twoV;
  twoV.push_back("apple");
  twoV.push_back("banana");
  LList *singleList = createSingletonList();
  assert(singleList->insert("banana", -1) == false);
  assert(singleList->insert("banana", 2) == false);
  assert(singleList->insert("banana", 1));  // insert at pos=1
  assert(isCorrect(*singleList, twoV));
  delete singleList;

  // Make sure inserting at front of non-empty list works
  singleList = createSingletonList();
  assert(singleList->insert("banana", 0));  // insert at pos=0
  twoV.clear();
  twoV.push_back("banana");
  twoV.push_back("apple");
  assert(isCorrect(*singleList, twoV));
  delete singleList;

  // Make sure adding to middle of non-empty list works
  std::vector<std::string> fourV;
  fourV.push_back("apple");
  fourV.push_back("banana");
  fourV.push_back("kiwi");
  fourV.push_back("cherry");
  LList *threeList = createThreeEntryList();
  assert(threeList->insert("kiwi", 2));
  assert(isCorrect(*threeList, fourV));
  delete threeList;

}

void testRemoveEntry()
{
  // Remove from empty list
  std::vector<std::string> emptyV;
  LList *emptyList = createEmptyList();
  assert(emptyList->remove("apple") == false);
  assert(isCorrect(*emptyList, emptyV));

  // Remove non-resident string from non-empty list
  std::vector<std::string> twoV;
  twoV.push_back("apple");
  LList *singleList = createSingletonList();
  assert(singleList->remove("eitan we got you!! LOL :P BET YOU FLY A CESSNA") == false);
  assert(isCorrect(*singleList, twoV));
  delete singleList;

  // Remove from front of non-empty list
  LList *threeList = createThreeEntryList();
  std::vector<std::string> twoV2;
  twoV2.push_back("banana");
  twoV2.push_back("cherry");
  assert(threeList->remove("apple"));
  assert(isCorrect(*threeList, twoV2));  // make sure hasn't changed
  delete threeList;

  // Remove from middle of non-empty list
  LList *threeList2 = createThreeEntryList();
  std::vector<std::string> twoV3;
  twoV3.push_back("apple");
  twoV3.push_back("cherry");
  assert(threeList2->remove("banana"));
  assert(isCorrect(*threeList2, twoV3));  // make sure hasn't changed
  delete threeList2;

  // Remove from end of non-empty list
  LList *threeList3 = createThreeEntryList();
  std::vector<std::string> twoV8;
  twoV8.push_back("apple");
  twoV8.push_back("banana");
  assert(threeList3->remove("cherry"));
  assert(isCorrect(*threeList3, twoV8));  // make sure hasn't changed
  delete threeList3;
}

// Tests LList::remove(str, pos)
void testRemovePosition()
{
  // Remove from empty list
  std::vector<std::string> emptyV;
  LList *emptyList = createEmptyList();
  assert(emptyList->remove(0) == false);
  assert(isCorrect(*emptyList, emptyV));
  // Remove at non-valid position from non-empty list
  std::vector<std::string> twoV;
  twoV.push_back("apple");
  LList *singleList = createSingletonList();
  assert(singleList->remove(2147483646) == false);
  assert(isCorrect(*singleList, twoV));
  delete singleList;
  // Remove from front of non-empty list
  LList *threeList = createThreeEntryList();
  std::vector<std::string> twoV2;
  twoV2.push_back("banana");
  twoV2.push_back("cherry");
  assert(threeList->remove(0));
  assert(isCorrect(*threeList, twoV2));  // make sure hasn't changed
  delete threeList;
  // Remove from middle of non-empty list
  LList *threeList2 = createThreeEntryList();
  std::vector<std::string> twoV3;
  twoV3.push_back("apple");
  twoV3.push_back("cherry");
  assert(threeList2->remove(1));
  assert(isCorrect(*threeList2, twoV3));  // make sure hasn't changed
  delete threeList2;
  // Remove from middle of non-empty list
   LList *threeList3 = createThreeEntryList();
  std::vector<std::string> twoV8;
  twoV8.push_back("apple");
  twoV8.push_back("banana");
  assert(threeList3->remove(2));
  assert(isCorrect(*threeList3, twoV8));  // make sure hasn't changed
  delete threeList3;
}

void testFind()
{
  // Get position of something in a non-empty list
  std::vector<std::string> emptyV;
  LList *emptyList = createEmptyList();
  assert(emptyList->find("apple") == -1);

  // Get position of non-resident string in a non-empty list
  std::vector<std::string> threeV;
  threeV.push_back("apple");
  threeV.push_back("banana");
  threeV.push_back("cherry");
  LList *threeList = createThreeEntryList();
  assert(threeList->find("date") == -1);
  assert(isCorrect(*threeList, threeV));  // make sure hasn't changed
  delete threeList;

  // Get position of resident string at beginning of a non-empty list
  threeList = createThreeEntryList();
  assert(threeList->find("apple") == 0);
  assert(isCorrect(*threeList, threeV));  // make sure hasn't changed
  delete threeList;

  // Get position of resident string at middle of a non-empty list
  threeList = createThreeEntryList();
  assert(threeList->find("banana") == 1);
  assert(isCorrect(*threeList, threeV));  // make sure hasn't changed
  delete threeList;

  // Get position of resident string at end of a non-empty list
  threeList = createThreeEntryList();
  assert(threeList->find("cherry") == 2);
  assert(isCorrect(*threeList, threeV));  // make sure hasn't changed
  delete threeList;

}

int main()
{
  testGetLength();
  testOperatorIndex();
  testAppend();
  testInsert();
  testRemoveEntry();
  testRemovePosition();
  testFind();
  std::cout << "all tests passed 🎉" << std::endl;
}
