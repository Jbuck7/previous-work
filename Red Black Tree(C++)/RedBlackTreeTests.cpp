#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	assert(rbt.ToInfixString() == "");
	
	cout << "Simple Constructor Test PASSED!"<< endl << endl;
}


void TestInsertFirstNode(){
	cout << "Testing Inserting First Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "Inserting First Node Test PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Inserting Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30); 
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "Inserting Second Node Test PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Inserting Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Left Right
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
}

void TestInsertFourthNode(){
	cout << "Testing Inserting Fourth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10);
	rbt->Insert(25);
	rbt->Insert(20); // Inserting between third and fifth
	assert(rbt->ToPrefixString() == " B15  B10  B25  R20  R30 ");
	delete rbt;
	
	cout << "Inserting Fourth Node Test PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Inserting Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	
	cout << "Inserting Fifth Node Test PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);
	
	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "ToString Methods Test PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insertions..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(12);
	rbt->Insert(11);
	rbt->Insert(15);
	rbt->Insert(5);
	rbt->Insert(13);
	rbt->Insert(7);
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(12);
	rbt->Insert(10);
	rbt->Insert(8);
	delete rbt;
	
	cout << "Random Insertions Test PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);
	

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);
	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "Copy Constructor Test PASSED!" << endl << endl;
}

void TestContains(){
	cout << "Testing Contains..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	assert(rbt->Contains(40));
	rbt->Insert(22);
	assert(rbt->Contains(22));
	rbt->Insert(15);
	assert(rbt->Contains(15));
	rbt->Insert(31);
	assert(rbt->Contains(31));
	rbt->Insert(55);
	assert(rbt->Contains(55));
	rbt->Insert(12);
	assert(rbt->Contains(12));
	rbt->Insert(17);
	assert(rbt->Contains(17));
	rbt->Insert(29);
	assert(rbt->Contains(29));
	rbt->Insert(34);
	assert(rbt->Contains(34));
	delete rbt;
	
	cout << "Contains Test PASSED!" << endl << endl;
}

void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	assert(rbt->GetMax()==55);
	assert(rbt->GetMin()==12);

	delete rbt;
	cout << "Get Minimum and Get Maximum Test PASSED!" << endl << endl;
}

int main(){

	
	TestSimpleConstructor();
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
