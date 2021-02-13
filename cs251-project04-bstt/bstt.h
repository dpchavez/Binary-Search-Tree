/*
 * Student: Daniela Chavez
 * NetID: dchave29
 * Professors: Joe Hummel && Shannon Reckinger
 * Spring 2020
 * */

/*bstt.h*/

/*Threaded Binary Tree */
#pragma once

#include <iostream>

using namespace std;

template<typename KeyT, typename ValueT>
class bstt
{
private:
  struct NODE /*The creation of a new NODE*/
  {
    KeyT   Key; //This will be the identifier of the Node, maybe like its "NAME"
    ValueT Value; //If we want to get the value of a designated key, then we would want to return that value
    NODE*  Left; //goes to the left of the root
    NODE*  Right; //Goes to the right of the Root
    bool   isThreaded; //checkes if the current noe we are it if its threaded or not
	};

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
  NODE* newNode; //Used as a temp to store root information without altering the root
  
  /*************************************************************************************************/
  /* This is my Destructor Helper. It will help the Destructor is a member function
   *  which destructs or deletes an object.*/
  void destructorHelper(NODE *cur) //We take the current node as a parameter
  {
	  if(cur == nullptr) //If the current node is a null pointer
		  return;        // Then just return
		  
	  destructorHelper(cur->Left); //We call this recursivly
	  if(!cur->isThreaded) //If the current node is not threaded
		  destructorHelper(cur->Right); //We call the decontructor helper for the right node recursivly

	  delete cur; //Delete the current node by default
  }
  
  
  
  /*************************************************************************************************/
  /*This is my Dump Helper. This will help my dump fucntion. This will help my dump fucntion
   * to output the threaded and non threaded nodes*/
 void dumpHelper(NODE* curr, ostream& output)const
 {
	 if (curr == nullptr) //If the current node is null
		 return;          //Then just return
	 
	 else{
		 dumpHelper(curr->Left, output); //Calling the dump helper 
		 if (curr->isThreaded && curr->Right != nullptr) //if the current node is threaded and the nide to the right isnt null
			 output<< "(" << curr->Key <<","<<curr->Value<<","<<curr->Right->Key << ")" << endl; //output key, value, threaded value	 
		 else
		 {  //If the node is not threaded
			 output << "(" << curr->Key <<","<<curr->Value<< ")" << endl; //Print current key and value
			 dumpHelper(curr->Right, output); //calling the dump helper recursively
		 } 
	 }//Closes else statement 
 }//closes function
  
  /*************************************************************************************************/
  /*This is my Copy Helper. This fyunction will be used recursively.
   * Will be used to help my copy contructor by copying an existing tree into a new one*/
  void copy(NODE* &curr, NODE* Other)
  {
	  if(Other == nullptr) //If the existing tree is null
		  return;          // Then just return

	  else{
		  insert(Other->Key, Other->Value); //Useing insert to get all the nodes and values of the existing tree
		  copyHelper(curr->Left, Other->Left); //Copy left nodes from old tree into new tree
		  if (!Other->isThreaded) //If the old tree is not threaded
			  copy(curr->Right, Other->Right); //then copy the right nodes from the pld tree into the new tree
	  } 
  }
 /*************************************************************************************************/

public:

  // default constructor:
  // Creates an empty tree.
  //
  bstt()
  {
    Root = nullptr; //default value for the root
    Size = 0; //default value for the size
  }

/*************************************************************************************************/
  // copy constructor
  // This will copy an existing tree to a new one
  bstt(const bstt& other)
  {
    Root = nullptr; 
	Size = 0;
	copy(this->Root, other.Root); //Using copy helper
  }
/*************************************************************************************************/
/*Destructor... deletes nodes from Tree*/
  virtual ~bstt()
  {
	  destructorHelper(Root); /* Calling the destructor Helper*/
  }
/*************************************************************************************************/
  // operator =
  // Clears "this" tree and then makes a copy of the "other" tree.

  bstt& operator=(const bstt& other)
  {
    destructorHelper(Root); // deletes root
	Root = nullptr; //sets root to null ptr
	Size = 0; //As the root is null, we wet the size to zero
	copy(this->Root, other.Root); // we copy nodes from existing tree to root

    return *this; //returns tree with new nodes
  }
/*************************************************************************************************/
/*Clear Function
 * Clears the contents of the tree, resetting the tree to empty.
 * */
  void clear()
  {
    destructorHelper(Root); //Calls the destructorfunction to delete the Rot
	Root = nullptr; //We set the root to a null pointer
	Size = 0; //We set the size to zero
  }
/*************************************************************************************************/
  
  /*  Size:
   *  Returns the # of nodes in the tree, 0 if empty.
   *  Time complexity:  O(1)
   * */

  int size() const
  {
    return Size; //retuns size of Tree
  }
/*************************************************************************************************/
  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  If the key is found, the corresponding value
  // is returned via the reference parameter.
  //
  // Time complexity:  O(lgN) on average
  //
  bool search(KeyT key, ValueT& value) const
  {
    NODE* cur = Root; //creating cur with the data of Root
	
	while (cur != nullptr) //While cur is not null
	{
		if (key == cur->Key) //If the key is found, then just return
		{
			value = cur->Value; 
			return true;
		}
		
		if (key < cur->Key) //If key is less than the current key
			cur = cur->Left; // our current node will be moved to the node on the left
		
		else 
		{
			if(cur->isThreaded)
				cur = nullptr; //if the current node is threaded, make it a null pointer
			else
				cur = cur->Right; //If cur is not threaded, then assign cur to the node at the right
		}	
	}
		return false; //default
  }
/*************************************************************************************************/

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  // Time complexity:  O(lgN) on average
  //
  void insert(KeyT key, ValueT value)
  {
	NODE*cur = Root; // We create a new node with the root information
	NODE*prev = nullptr; // We create
	
	// 1. Search for key, return if found:
	while(cur!=nullptr) //Looping through the tree
	{
		if (key == cur->Key)
			return;
		else if (key < cur->Key) //If the key we are looking for is less then the key at the current node
		{
			prev = cur; //We set the previous node to current
			cur = cur->Left; //And then we go left
		}
		
		else
		{   //If the key we are looking for is greater than the key at the curent node
			prev = cur; //We set the previous to the current node
			if(cur->isThreaded) //Checking if the current node is threaded
				break; //If its threaded, then break;
				
			cur = cur->Right; //If the node is not threaded, then go right
		}
	} //Closing while loop
	
  /*Now that we have checked if the key exsists or not within the tree:
   * If it doesnt, then we add it to the tree, at the corresponding position*/
  
	NODE *n = new NODE; //Creating a new node that will be inserted into the tree
	n->Key = key; //The key of the new node will be the key that doesnt exist in the tree
	n->Value = value; //We are also giving it the value that was set as a parameter
	n->Left = nullptr; //Creating a left node
	n->Right = nullptr; //Creating a right node
	
	if (prev==nullptr) //If the previous node is nul
	{                  //Then we set the Root to N
		Root= n;       //And then we devlare that it is not threaded
		n->isThreaded = false; //Basically meaning that if its a non existant tree, create a root node
	}
	else if (key < prev->Key) //If the key is smaller than the previouskey
	{
		n->Right = prev; //we assign the node to the right as the prev
		prev->Left = n; //Assigning the previous left node as the current node
		n->isThreaded = true; // n is assign as threaded
	}	
	else
	{
		if (prev->isThreaded) // there is no Right pointer in traditional traversal:
		{
			n->isThreaded = true;  //Setting n as threaded
			prev->isThreaded = false; //previous node as not threaded
			n->Right = prev->Right; //Node to the right is now the previous node to the right
		}
		else //if prev is not threaded
			n->isThreaded = false; //set n as not threaded
		
		prev->Right =n; //previous right node to the right will be the new prev node
				
	}
	// 3. Update size and return:
	Size++;
  }
/*************************************************************************************************/
  //
  // []
  //
  // Returns the value for the given key; if the key is not found,
  // the default value ValueT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  ValueT operator[](KeyT key) const
  {
	NODE* cur = Root;
   
	while (cur != nullptr) //While cur is not null
	{
		if (key == cur->Key) //If the key is found, then just return
			return cur->Value;
		
		if (key < cur->Key) //If key is less than the current key
			cur = cur->Left; // our current node will be moved to the node on the left
		
		else 
		{
			if(cur->isThreaded)
				break;//if the current node is threaded, make it a null pointer
			else{ cur = cur->Right;} //If cur is not threaded, then assign cur to the node at the right
		}	
	}	
	return ValueT{ }; //Returns default value
    
  }
/*************************************************************************************************/

  //
  // ()
  //
  // Finds the key in the tree, and returns the key to the "right".
  // If the right is threaded, this will be the next inorder key.
  // if the right is not threaded, it will be the key of whatever
  // node is immediately to the right.
  //
  // If no such key exists, or there is no key to the "right", the
  // default key value KeyT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  KeyT operator()(KeyT key) const
  {
    NODE* cur = Root; // We get all the information from Root
	while (cur != nullptr) //While the tree is not empty
	{
		if(cur->Key == key && cur->Right != nullptr) //If the current key matches the key we are looking for
			return cur->Right->Key; //And if the node to the right is not null, then return the key to the right
		
		if (cur->Key > key) //If the key we are looking for is less than the key at the current node
			cur = cur->Left; //Go left
		
		else{
			if(cur->isThreaded) //if the current node is threaded
				return KeyT{ }; //We return the default key
				
			cur = cur->Right; //If the node is not threaded, then go right
		}	
	}
    return KeyT{ }; //Returns default key value
  }
/*************************************************************************************************/
  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the 
  // call to begin(), the internal state denotes the first inorder
  // key; this ensure that first call to next() function returns
  // the first inorder key.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  void begin()
  { 
	  newNode= Root; //The node has all the information about the root. We dont want to alter the root
	  if (size() == 0) //If the size is equal to zero
		  return; //Just return  
	  else 
	  {
		  if ( newNode != nullptr) //If the node is not a null pointer
		  {
			  while (newNode->Left != nullptr) //And while the node to the left is not a null pointer
			  {
				  newNode = newNode->Left; // We keep moving the node to the left until we find the smallest value
			  } //closing while loop
		  } //Closing if statement
	  }  //Closing else statement
  }//Closing the begin() function
  
/*************************************************************************************************/
  //
  // next
  //
  // Uses the internal state to return the next inorder key, and 
  // then advances the internal state in anticipation of future
  // calls.  If a key is in fact returned (via the reference 
  // parameter), true is also returned.
  //
  // False is returned when the internal state has reached null,
  // meaning no more keys are available.  This is the end of the
  // inorder traversal.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  bool next(KeyT& key)
  {
    if(newNode == nullptr) //If the node is null
		return false;      //Just return
	if (newNode->isThreaded || newNode->Right == nullptr)
	{   //If the node is treaded or if the node to the right is null
		key = newNode->Key; //Then the key becomes the nodes key
		newNode = newNode->Right; //and the node will be pointing at the right
	}
	
	else
	{ //If the node is not threaded
		key = newNode->Key; //Then we assign the key to the key of that current node
		newNode = newNode->Right; //The node will be pointing to the right
			
		while(newNode->Left != nullptr) //If the node at the left is not null
		{
			newNode = newNode->Left; //Then mode to the left
		}
	}
    return true; //Returining true as a default
  }
/*************************************************************************************************/
  //
  // dump
  // 
  // Dumps the contents of the tree to the output stream, using a
  // recursive inorder traversal.
  //
  void dump(ostream& output) const
  {
    output << "**************************************************" << endl;
    output << "********************* BSTT ***********************" << endl;

    output << "** size: " << this->size() << endl;

    //
    // inorder traversal, with one output per line: either 
    // (key,value) or (key,value,THREAD)
    //
    // (key,value) if the node is not threaded OR thread==nullptr
    // (key,value,THREAD) if the node is threaded and THREAD denotes the next inorder key
    //

    dumpHelper(Root,output);

    output << "**************************************************" << endl;
  }
/*************************************************************************************************/	
};

