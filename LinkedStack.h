#pragma once

#include "DataStructuresExceptions.h"

template <typename T>
class LinkedStack {
public:
	LinkedStack() : m_size(0), m_top(nullptr) {}
	LinkedStack(const LinkedStack<T>&);
	LinkedStack<T>& operator=(const LinkedStack<T>&);
	~LinkedStack() { deallocate(); }

	bool is_empty() const { return m_size == 0; }
	int size() const { return m_size; }
	T& top();
	const T& top() const;
	void push(const T&);
	void pop();

private:
	template <typename T>
	struct Node {
		T m_info;
		Node<T>* m_previous;

		Node(const T& info = T()) : m_info(info), m_previous(nullptr) {}
		Node(const Node<T>&) = delete;
		Node<T>& operator=(const Node<T>&) = delete;
	};

	void deallocate();

private:
	int m_size;
	Node<T>* m_top;
};

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& object) : m_size(object.m_size), m_top(nullptr) {
	const Node<T>* current = object.m_top;
	Node<T>* tmp1 = nullptr;
	while (current != nullptr) {
		Node<T>* tmp = new Node<T>(current->m_info);
		if (current == object.m_top) {
			m_top = tmp;
		}
		if (tmp1 != nullptr) {
			tmp1->m_previous = tmp;
		}
		tmp1 = tmp;
		current = current->m_previous;
	}
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& object) {
	if (this != &object) {
		deallocate();
		m_size = object.m_size;
		const Node<T>* current = object.m_top;
		Node<T>* tmp1 = nullptr;
		while (current != nullptr) {
			Node<T>* tmp = new Node<T>(current->m_info);
			if (current == object.m_top) {
				m_top = tmp;
			}
			if (tmp1 != nullptr) {
				tmp1->m_previous = tmp;
			}
			tmp1 = tmp;
			current = current->m_previous;
		}
	}
	return *this;
}

template <typename T>
T& LinkedStack<T>::top() {
	if (m_size != 0) {
		return m_top->m_info;
	}
	throw IsEmptyException;
}

template <typename T>
const T& LinkedStack<T>::top() const {
	if (m_size != 0) {
		return m_top->m_info;
	}
	throw IsEmptyException;
}

template <typename T>
void LinkedStack<T>::push(const T& element) {
	Node<T>* tmp = new Node<T>(element);
	tmp->m_previous = m_top;
	m_top = tmp;
	++m_size;
}

template <typename T>
void LinkedStack<T>::pop() {
	if (m_size != 0) {
		Node<T>* tmp = m_top->m_previous;
		delete m_top;
		m_top = tmp;
		--m_size;
		return;
	}
	throw IsEmptyException;
}

template <typename T>
void LinkedStack<T>::deallocate() {
	if (m_size != 0) {
		Node<T>* DeleteAfter = m_top->m_previous;
		while (m_size != 0) {
			delete m_top;
			m_top = DeleteAfter;
			DeleteAfter = DeleteAfter->m_previous;
			--m_size;
		}
	}
}