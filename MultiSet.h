#pragma once

#include "SearchTree.h"
#include "BinaryTree.h"

template <typename T>
class MultiSet {
	template <typename T1>
	friend std::ostream& operator<<(std::ostream&, const MultiSet<T1>&);

public:
	MultiSet(const T*, int);

	MultiSet<T>& operator&=(const MultiSet<T>&);
	MultiSet<T>& operator|=(const MultiSet<T>&);
	MultiSet<T>& operator-=(const MultiSet<T>&);

	bool operator==(const MultiSet<T>&);
	bool operator<(const MultiSet<T>&);

private:
	SearchTree<T> m_tree;
};

template <typename T>
MultiSet<T>& operator&(MultiSet<T> obj1, const MultiSet<T>& obj2) {
	return obj1 &= obj2;
}

template <typename T>
MultiSet<T>& operator|(MultiSet<T> obj1, const MultiSet<T>& obj2) {
	return obj1 |= obj2;
}

template <typename T>
MultiSet<T>& operator-(MultiSet<T> obj1, const MultiSet<T>& obj2) {
	return obj1 -= obj2;
}

template <typename T>
bool operator<=(MultiSet<T> obj1, const MultiSet<T>& obj2) {
	return (obj1 == obj2) || (obj1 < obj2);
}

template <typename T>
bool operator>(MultiSet<T> obj1, const MultiSet<T>& obj2) {
	return !(obj1 <= obj2);
}

template <typename T>
bool operator>=(MultiSet<T> obj1, const MultiSet<T>& obj2) {
	return (obj1 == obj2) || (obj1 > obj2);
}

template <typename T>
bool operator!=(MultiSet<T> obj1, const MultiSet<T>& obj2) {
	return !(obj1 == obj2);
}

template <typename T1>
std::ostream& operator<<(std::ostream& out, const MultiSet<T1>& object) {
	if (!object.m_tree.empty()) {
		std::stack<const BinaryTree::Node<T1>*> st;
		const BinaryTree::Node<T1>* tmp = object.m_tree.straight_first();
		st.push(tmp);
		while (!st.empty()) {
			out << st.top()->m_info << std::endl;
			object.m_tree.straight_next(st);
		}
	}
	return out;
}

template <typename T>
MultiSet<T>::MultiSet(const T* data, int size) {
	for (int i = 0; i < size; ++i) {
		m_tree.insert(data[i]);
	}
}

template <typename T>
MultiSet<T>& MultiSet<T>::operator&=(const MultiSet<T>& object) {
	std::stack<const BinaryTree::Node<T>*> st;
	st.push(m_tree.straight_first());
	while (!st.empty()) {
		if (object.m_tree.find(st.top()->m_info) == nullptr) {
			const T x = st.top()->m_info;
			m_tree.straight_next(st);
			m_tree.remove(x);
			continue;
		}
		m_tree.straight_next(st);
	}
	return *this;
}

template <typename T>
MultiSet<T>& MultiSet<T>::operator|=(const MultiSet<T>& object) {
	std::stack<const BinaryTree::Node<T>*> st;
	st.push(object.m_tree.straight_first());
	while (!st.empty()) {
		m_tree.insert(st.top()->m_info);
		object.m_tree.straight_next(st);
	}
	return *this;
}

template <typename T>
MultiSet<T>& MultiSet<T>::operator-=(const MultiSet<T>& object) {
	std::stack<const BinaryTree::Node<T>*> st;
	st.push(m_tree.straight_first());
	while (!st.empty()) {
		if (object.m_tree.find(st.top()->m_info) != nullptr) {
			const T x = st.top()->m_info;
			m_tree.straight_next(st);
			m_tree.remove(x);
			continue;
		}
		m_tree.straight_next(st);
	}
	return *this;
}

template <typename T>
bool MultiSet<T>::operator==(const MultiSet<T>& object) {
	if (m_tree.get_size() != object.m_tree.get_size()) { return false; }
	std::stack<const BinaryTree::Node<T>*> st;
	st.push(m_tree.straight_first());
	while (!st.empty()) {
		if (object.m_tree.find(st.top()->m_info) == nullptr) {
			return false;
		}
		m_tree.straight_next(st);
	}
	return true;
}

template <typename T>
bool MultiSet<T>::operator<(const MultiSet<T>& object) {
	if (m_tree.get_size() >= object.m_tree.get_size()) { return false; }
	std::stack<const BinaryTree::Node<T>*> st;
	st.push(m_tree.straight_first());
	while (!st.empty()) {
		if (object.m_tree.find(st.top()->m_info) == nullptr) {
			return false;
		}
		m_tree.straight_next(st);
	}
	return true;
}