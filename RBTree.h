#pragma once

#include "SearchTree.h"

enum color {

};

template <typename T>
class RBTree : public SearchTree<T> {
public:
	RBTree() : m_root(nullptr), m_size(0) {}
	RBTree(const RBTree<T>&);
	RBTree& operator=(const RBTree<T>&);
	virtual ~RBTree();

	virtual void insert(const T&);
	virtual void remove(const T&);

private:
	template <typename T>
	struct ColoredNode : public BinaryTree::Node<T> {
		ColoredNode(const T& info = T()) : BinaryTree::Node<T>(info), m_father(nullptr), m_color() {}

		BinaryTree::Node<T>* m_father;
		bool m_color;
	};
};