#include "LinkedList.h"
#include "DataStructuresExceptions.h"

LinkedList::LinkedList(const int* data, int size) : m_size(size), m_head(nullptr), m_tail(nullptr), m_current(nullptr) {
	Node* tmp = new Node(data[0]);
	m_head = tmp;
	m_current = m_head;
	for (int i = 1; i < size; ++i) {
		Node* tmp1 = new Node(data[i]);
		tmp->m_next = tmp1;
		tmp1->m_previous = tmp;
		tmp = tmp1;
	}
	tmp->m_next = m_head;
	m_tail = tmp;
	m_head->m_previous = m_tail;
}

LinkedList::LinkedList(const LinkedList& object) : m_size(object.m_size), m_head(nullptr), m_tail(nullptr), m_current(nullptr) {
	if (object.m_size != 0) {
		int size = m_size - 1;
		Node* tmp = new Node(object.m_head->m_info);
		m_head = tmp;
		Node* current = object.m_head->m_next;
		while (size != 0) {
			Node* tmp1 = new Node(current->m_info);
			tmp->m_next = tmp1;
			tmp1->m_previous = tmp;
			tmp = tmp1;
			current = current->m_next;
			--size;
		}
	}
}

LinkedList& LinkedList::operator=(const LinkedList& object) {
	if (this != &object && object.m_size != 0) {
		deallocate();
		m_size = object.m_size;
		int size = m_size - 1;
		Node* tmp = new Node(object.m_head->m_info);
		m_head = tmp;
		Node* current = object.m_head->m_next;
		while (size != 0) {
			Node* tmp1 = new Node(current->m_info);
			tmp->m_next = tmp1;
			tmp1->m_previous = tmp;
			tmp = tmp1;
			current = current->m_next;
			--size;
		}
	}
	return *this;
}

void LinkedList::insert(int element, Node* before) {
	Node* tmp = new Node(element);
	if (before == nullptr) {
		tmp->m_next = m_head;
		tmp->m_previous = m_tail;
		m_tail->m_next = tmp;
		m_head->m_previous = tmp;
		m_head = tmp;
		++m_size;
		return;
	}
	if (before == m_tail) {
		before->m_next = tmp;
		tmp->m_previous = before;
		tmp->m_next = m_head;
		m_head->m_next = tmp;
		m_tail = tmp;
		++m_size;
		return;
	}
	tmp->m_next = before->m_next;
	before->m_next->m_previous = tmp;
	before->m_next = tmp;
	tmp->m_previous = before;
	++m_size;
}

void LinkedList::remove(Node* object) {
	if (m_size == 0) {
		//throw IsEmptyException;
		//? mb try to remove from not empty List, but the object is abset
	}
	if (object == m_head) {
		m_tail->m_next = m_head->m_next;
		m_head = m_head->m_next;
		m_head->m_previous = m_tail;
		m_current = m_head;
		delete object;
		--m_size;
		return;
	}
	if (object == m_tail) {
		m_tail->m_previous->m_next = m_head;
		m_tail = m_tail->m_previous;
		m_head->m_previous = m_tail;
		delete object;
		--m_size;
		return;
	}
	if (object == m_current) {
		m_current = m_head;
	}
	object->m_previous = object->m_next;
	object->m_next = object->m_previous;
	delete object;
	--m_size;
}

void LinkedList::deallocate() {
	if (m_size != 0) {
		Node* DeleteAfter = m_head->m_next;
		while (m_size != 0) {
			delete m_head;
			m_head = DeleteAfter;
			DeleteAfter = (m_size == 1) ? nullptr : DeleteAfter->m_next;
			--m_size;
		}
	}
}