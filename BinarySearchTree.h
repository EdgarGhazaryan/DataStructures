#pragma once

#include "BinaryTree.h"
#include "DataStructuresExceptions.h"

#include <algorithm>

template <typename T>
class SearchTree {
public:
	SearchTree() : m_root(nullptr), m_size(0) {}
	SearchTree(const SearchTree<T>&);
	SearchTree<T>& operator=(const SearchTree<T>&);
	virtual ~SearchTree();

	bool empty() const { return m_size == 0; }
	int get_size() const { return m_size; }
	BinaryTree::Node<T>* find(const T&);
	const BinaryTree::Node<T>* find(const T&) const;

	virtual void insert(const T&);
	virtual void remove(const T&);

	const BinaryTree::Node<T>* straight_first() const { return m_root; }
	void straight_next(std::stack<const BinaryTree::Node<T>*>&) const;

private:
	void allocate(const SearchTree<T>&);
	void allocate_help(BinaryTree::Node<T>*, BinaryTree::Node<T>*);
	void deallocate(BinaryTree::Node<T>*);

	BinaryTree::Node<T>* symetric_next(BinaryTree::Node<T>*);

	BinaryTree::Node<T>* find_father(const T&);
	BinaryTree::Node<T>* child_search(BinaryTree::Node<T>*, const T&);
	void delete_node(BinaryTree::Node<T>*, BinaryTree::Node<T>*);

protected:
	BinaryTree::Node<T>* m_root;
	int m_size;
};

template <typename T>
SearchTree<T>::SearchTree(const SearchTree<T>& object) : m_root(nullptr), m_size(0) {
	allocate(object);
}

template <typename T>
SearchTree<T>& SearchTree<T>::operator=(const SearchTree<T>& object) {
	if (this != &object) {
		m_size = 0;
		deallocate(m_root);
		allocate(object);
	}
	return *this;
}

template <typename T>
SearchTree<T>::~SearchTree() {
	deallocate(m_root);
}

template <typename T>
BinaryTree::Node<T>* SearchTree<T>::find(const T& element) {
	if (m_root == nullptr) {
		return nullptr;
	}
	BinaryTree::Node<T>* ptr = m_root;
	while (ptr != nullptr && ptr->m_info != element) {
		if (element < ptr->m_info) {
			ptr = ptr->m_left;
		}
		else {
			ptr = ptr->m_right;
		}
	}
	return ptr;
}

template <typename T>
const BinaryTree::Node<T>* SearchTree<T>::find(const T& element) const {
	if (m_root == nullptr) {
		return nullptr;
	}
	const BinaryTree::Node<T>* ptr = m_root;
	while (ptr != nullptr && ptr->m_info != element) {
		if (element < ptr->m_info) {
			ptr = ptr->m_left;
		}
		else {
			ptr = ptr->m_right;
		}
	}
	return ptr;
}

template <typename T>
void SearchTree<T>::insert(const T& element) {
	BinaryTree::Node<T>* tmp = m_root, * tmp_parent{};
	while (tmp != nullptr) {
		tmp_parent = tmp;
		tmp = (element < tmp->m_info) ? tmp->m_left : tmp->m_right;
	}
	if (tmp_parent == nullptr) {
		m_root = new BinaryTree::Node<T>(element);
	}
	else {
		if (element < tmp_parent->m_info) {
			tmp_parent->m_left = new BinaryTree::Node<T>(element);
		}
		else {
			tmp_parent->m_right = new BinaryTree::Node<T>(element);
		}
	}
	++m_size;
}

template <typename T>
void SearchTree<T>::remove(const T& element) {
	BinaryTree::Node<T>* father = find_father(element);
	BinaryTree::Node<T>* child = child_search(father, element);
	if (child == nullptr) {
		throw IsEmptyException;
	}
	if (child->m_left != nullptr && child->m_right != nullptr) {
		father = symetric_next(child);
		child = child_search(father, element);
	}
	delete_node(father, child);
	--m_size;
}

template <typename T>
void SearchTree<T>::straight_next(std::stack<const BinaryTree::Node<T>*>& s) const {
	const BinaryTree::Node<T>* tmp = s.top();
	s.pop();
	if (tmp->m_right != nullptr) {
		s.push(tmp->m_right);
	}
	if (tmp->m_left != nullptr) {
		s.push(tmp->m_left);
	}
}

template <typename T>
void SearchTree<T>::allocate(const SearchTree<T>& object) {
	if (!object.empty()) {
		m_root = new BinaryTree::Node<T>(object.m_root->m_info);
		allocate_help(m_root, object.m_root);
	}
}

template <typename T>
void SearchTree<T>::allocate_help(BinaryTree::Node<T>* real, BinaryTree::Node<T>* object) {
	if (object->m_left != nullptr) {
		real->m_left = new BinaryTree::Node<T>(object->m_left->m_info);
		allocate_help(real->m_left, object->m_left);
	}
	if (object->m_right != nullptr) {
		real->m_right = new BinaryTree::Node<T>(object->m_right->m_info);
		allocate_help(real->m_right, object->m_right);
	}
}

template <typename T>
void SearchTree<T>::deallocate(BinaryTree::Node<T>* root) {
	if (root == nullptr) {
		return;
	}
	BinaryTree::Node<T>* left = root->m_left;
	BinaryTree::Node<T>* right = root->m_right;
	delete root;
	if (left != nullptr) {
		deallocate(left);
	}
	if (right != nullptr) {
		deallocate(right);
	}
}

template <typename T>
BinaryTree::Node<T>* SearchTree<T>::symetric_next(BinaryTree::Node<T>* current) {
	BinaryTree::Node<T>* to_remove = current;
	BinaryTree::Node<T>* curr_father = current;
	current = current->m_right;
	while (current->m_left != nullptr) {
		curr_father = current;
		current = current->m_left;
	}
	std::swap(current->m_info, to_remove->m_info);
	return curr_father;
}

template <typename T>
BinaryTree::Node<T>* SearchTree<T>::find_father(const T& element) {
	if (m_root == nullptr) {
		return nullptr;
	}
	BinaryTree::Node<T>* pointer = m_root;
	BinaryTree::Node<T>* pointer1 = m_root;
	while (pointer != nullptr && pointer->m_info != element) {
		pointer1 = pointer;
		if (pointer->m_info > element) {
			pointer = pointer->m_left;
		}
		else {
			pointer = pointer->m_right;
		}
	}
	return (pointer == nullptr) ? nullptr : pointer1;
}

template <typename T>
BinaryTree::Node<T>* SearchTree<T>::child_search(BinaryTree::Node<T>* father, const T& element) {
	if (father == nullptr) { 
		return nullptr; 
	}
	if (father == m_root && ((father->m_left == nullptr && father->m_right == nullptr) || father->m_info == element)) {
		return father;
	}
	if (father->m_left != nullptr && father->m_left->m_info == element) { 
		return father->m_left;
	}
	return father->m_right;
}

template <typename T>
void SearchTree<T>::delete_node(BinaryTree::Node<T>* father, BinaryTree::Node<T>* child) {
	if (child->m_left == nullptr && child->m_right == nullptr) {
		if (child == m_root) {
			m_root = nullptr;
			delete child;
			return;
		}
		if (child == father->m_left) {
			father->m_left = nullptr;
		}
		if (child == father->m_right) {
			father->m_right = nullptr;
		}
	}
	else {
		if (child == m_root) {
			m_root = (m_root->m_left != nullptr) ? m_root->m_left : m_root->m_right;
			delete child;
			return;
		}
		if (father->m_left == child) {
			father->m_left = (child->m_left != nullptr) ? child->m_left : child->m_right;
		}
		if (father->m_right == child) {
			father->m_right = (child->m_left != nullptr) ? child->m_left : child->m_right;
		}
	}
	delete child;
}
