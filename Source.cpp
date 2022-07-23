#include <iostream>

#include "DataStructuresExceptions.h"
#include "Queue.h"
#include "Stack.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "LinkedList.h"
#include "Polynom.h"
#include "BinaryTree.h"
#include "Heap.h"
#include "HeapSort.h"
#include <string>
#include "SearchTree.h"
#include "MultiSet.h"
#include "ListTree.h"

class A{
public:
	virtual ~A() {}

protected:
	int m_x;
};

class B :public A {
public: 
	B(int a) : A(), x(a) {}
	int x;
};

int main() {
	ListTree<int> a;
	try {
		a.insert(1, 1);
		a.insert(2, 1);
		a.insert(3, 3);
		a.insert(4, 3);
		a.insert(5, 5);
		a.remove(1);
	}
	catch (const IndexOutOfBoundsException& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const IsEmptyException& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << a;

	return 0;
}