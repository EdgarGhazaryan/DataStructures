#pragma once

#include "DataStructuresExceptions.h"

template <typename T>
class LinkedQueue {
public:
	LinkedQueue() : m_size(0), m_front(nullptr), m_rear(nullptr) {}
	LinkedQueue(const LinkedQueue<T>&);
	LinkedQueue<T>& operator=(const LinkedQueue<T>&);
	~LinkedQueue() { deallocate(); }

	bool empty() const { return m_size == 0; }
	int size() const { return m_size; }
	T& front();
	const T& front() const;
	void push(const T&);
	void pop();

private: 
	template <typename T>
	struct Node {
		T m_info;
		Node<T>* m_next;

		Node(const T& info = T()) : m_info(info), m_next(nullptr) {}
		Node(const Node<T>&) = delete;
		Node<T>& operator=(const Node<T>& object) = delete;
	};

	void deallocate();

private:
	int m_size;
	Node<T>* m_front;
	Node<T>* m_rear;
};

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& object) : m_size(object.m_size), m_front(nullptr), m_rear(nullptr) {
	const Node<T>* current = object.m_front;
	Node<T>* tmp1 = nullptr;
	while (current != nullptr) {
		Node<T>* tmp = new Node<T>(current->m_info);
		if (current == object.m_front) {
			m_front = tmp;
		}
		if (tmp1 != nullptr) {
			tmp1->m_next = tmp;
		}
		tmp1 = tmp;
		current = current->m_next;
	}
	m_rear = tmp1;
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& object) {
	if (this != &object) {
		deallocate();
		m_size = object.m_size;
		const Node<T>* current = object.m_front;
		Node<T>* tmp1 = nullptr;
		while (current != nullptr) {
			Node<T>* tmp = new Node(current->m_info);
			if (current == object.m_front) {
				m_front = tmp;
			}
			if (tmp1 != nullptr) {
				tmp1->m_next = tmp;
			}
			tmp1 = tmp;
			current = current->m_next;
		}
		m_rear = tmp1;
	}
	return *this;
}

template <typename T>
T& LinkedQueue<T>::front() {
	if (m_size != 0) {
		return m_front->m_info;
	}
	throw IsEmptyException;
}

template <typename T>
const T& LinkedQueue<T>::front() const {
	if (m_size != 0) {
		return m_front->m_info;
	}
	throw IsEmptyException;
}

template <typename T>
void LinkedQueue<T>::push(const T& element) {
	Node<T>* tmp = new Node<T>(element);
	(m_size == 0) ? m_front = tmp : m_rear->m_next = tmp;
	m_rear = tmp;
	++m_size;
}

template <typename T>
void LinkedQueue<T>::pop() {
	if (m_size != 0) {
		Node<T>* tmp = m_front->m_next;
		delete m_front;
		m_front = tmp;
		--m_size;
		return;
	}
	throw IsEmptyException;
}

template <typename T>
void LinkedQueue<T>::deallocate() {
	if (m_size != 0) {
		Node<T>* DeleteAfter = m_front->m_next;
		while (m_size != 0) {
			delete m_front;
			m_front = DeleteAfter;
			DeleteAfter = DeleteAfter->m_next;
			--m_size;
		}
	}
}