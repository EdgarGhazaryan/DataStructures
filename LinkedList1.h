#pragma once

#include "DataStructuresExceptions.h"

class LinkedList {
public:
	struct Node {
		int m_info;
		Node* m_next;
		Node* m_previous;

		Node(int info = 0) : m_info(info), m_next(nullptr), m_previous(nullptr) {}
		Node(const Node&) = delete;
		Node& operator=(const Node& object) = delete;
	};

	LinkedList() : m_size(0), m_head(nullptr), m_tail(nullptr), m_current(nullptr) {}
	LinkedList(const int*, int);
	LinkedList(const LinkedList&);
	LinkedList& operator=(const LinkedList&);
	~LinkedList() { deallocate(); }

	bool is_empty() const { return m_size == 0; }
	int size() const { return m_size; }
	void insert(int, Node* = nullptr);
	void remove(Node*);

	Node* head() const;
	Node* current() const;
	Node* next() const;
	Node* previous() const;
	void reset() const { m_current = m_head; }

private:
	void deallocate();

private:
	int m_size;
	Node* m_head;
	Node* m_tail;
	mutable Node* m_current;
};