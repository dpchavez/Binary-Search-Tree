/*test01.cpp*/

//
// Unit tests for threaded binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) empty tree") 
{
	bstt<int, int>  tree;
	bstt<int, int> tree2;
	int key = 0;
	REQUIRE(tree.size() == 0);
	REQUIRE(tree2.size() == 0);
	
	tree.insert(1,2);
	tree.insert(3,8);
	tree.insert(5,1);
	tree.insert(20,3);
	tree.insert(29,100);
	tree.insert(30,100);
	tree.insert(70,100);
	tree.insert(50,100);
	
	tree2 = tree;
	
	REQUIRE(tree2.size() == 8);
	cout <<"--------------TREE 1 DUMP ----------------------"<< endl;
	tree.dump(cout);
	
	cout <<"--------------TREE 2 DUMP ----------------------"<< endl;
	tree2.dump(cout);
	
	tree.begin();
    while (tree.next(key))
	{
		cout << key << endl;
	}
		
	

}
