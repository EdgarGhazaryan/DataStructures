#pragma once

#include "DataStructuresExceptions.h"

#include <queue>

template <typename T>
class ListTree {
	template <typename T1>
	friend std::ostream& operator<<(std::ostream&, const ListTree<T1>&);

public:
	ListTree() : m_size(0), m_root(nullptr) {}
	ListTree(const ListTree<T>&);
	ListTree& operator=(const ListTree<T>&);
	~ListTree();

	bool empty() const { return m_size == 0; }
	int get_size() const { return m_size; }
	const T& find(int) const;
	void insert(const T&, int);
	void remove(int);

private:
	struct BaseNode {
		BaseNode() : m_left(nullptr), m_right(nullptr) {}
		virtual ~BaseNode() {}
		
		bool is_leaf() const { return (m_left == nullptr && m_right == nullptr); }

		BaseNode* m_left;
		BaseNode* m_right;
	};

	struct InnerNode : public BaseNode {
		InnerNode(int i) : BaseNode(), m_info(i) {}

		int m_info;
	};

	template <typename T>
	struct OuterNode : public BaseNode {
		OuterNode(const T& i = T()) : BaseNode(), m_info(i) {}

		T m_info;
	};

	void allocate(const ListTree&);
	void deallocate();
	
private:
	int m_size;
	BaseNode* m_root;
};

template <typename T1>
std::ostream& operator<<(std::ostream& out, const ListTree<T1>& object) {
	if (!object.empty()) {
		std::queue<const ListTree<T1>::BaseNode*> q;
		q.push(object.m_root);
		while (!q.empty()) {
			if (q.front()->is_leaf()) {
				const ListTree<T1>::template OuterNode<T1>* tmp = dynamic_cast<const ListTree<T1>::template OuterNode<T1>*>(q.front());
				out << tmp->m_info << ' ';
			}
			else {
				q.push(q.front()->m_left);
				q.push(q.front()->m_right);
			}
			q.pop();
		}
	}
	return out;
}

template <typename T>
ListTree<T>::ListTree(const ListTree<T>& object) : m_size(object.m_size), m_root(nullptr) {
	allocate(object);
}

template <typename T>
ListTree<T>& ListTree<T>::operator=(const ListTree<T>& object) {
	if (this != &object) {
		m_size = object.m_size;
		deallocate();
		allocate(object);
	}
	return *this;
}

template <typename T>
ListTree<T>::~ListTree() {
	deallocate();
}

template <typename T>
const T& ListTree<T>::find(int index) const {
	if (index <= 0) {
		throw IndexOutOfBoundsException();
	}
	if (m_size == 0) {
		throw IsEmptyException();
	}
	const BaseNode* tmp = m_root;
	const InnerNode* tmpI{};
	while (!tmp->is_leaf()) {
		tmpI = dynamic_cast<const InnerNode*>(tmp);
		if (index > tmpI->m_info) {
			index -= tmpI->m_info;
			tmp = tmp->m_right;
		}
		else {
			tmp = tmp->m_left;
		}
	}
	const OuterNode<T>* result = dynamic_cast<const OuterNode<T>*>(tmp);
	return result->m_info;
}

template <typename T>
void ListTree<T>::insert(const T& element, int index) {
	if (index <= 0) {
		throw IndexOutOfBoundsException();
	}
	if (index > m_size) {
		index = m_size + 1;
	}
	if (m_size == 0) {
		m_root = new OuterNode<T>(element);
		++m_size;
		return;
	}
	BaseNode* tmp = m_root, *tmp_father{};
	InnerNode* tmpI{};
	int i = index;
	while (!tmp->is_leaf()) {
		tmpI = dynamic_cast<InnerNode*>(tmp);
		tmp_father = tmp;
		if (i > tmpI->m_info) {
			i -= tmpI->m_info;
			tmp = tmp->m_right;
		}
		else {
			++tmpI->m_info;
			tmp = tmp->m_left;
		}
	}
	BaseNode* add_in = new InnerNode(1);
	BaseNode* add_out = new OuterNode<T>(element);
	if (tmp_father == nullptr) {
		m_root = add_in;
		if (index == 1) {
			add_in->m_left = add_out;
			add_in->m_right = tmp;
		}
		else {
			add_in->m_left = tmp;
			add_in->m_right = add_out;
		}
		++m_size;
		return;
	}
	if (index == m_size + 1) {
		add_in->m_left = tmp;
		add_in->m_right = add_out;
		tmp_father->m_right = add_in;
	}
	else {
		add_in->m_left = add_out;
		add_in->m_right = tmp;
		if (index == m_size) {
			tmp_father->m_right = add_in;
		}
		else {
			tmp_father->m_left = add_in;
		}
	}
	++m_size;
}

template <typename T>
void ListTree<T>::remove(int index) {
	if (m_size == 0) {
		throw IsEmptyException();
	}
	if (index <= 0) {
		throw IndexOutOfBoundsException();
	}
	if (index > m_size) {
		index = m_size;
	}
	BaseNode* tmp = m_root, * tmp_f{}, * tmp_ff{};
	InnerNode* tmpI{};
	if (m_size == 1) {
		delete m_root;
		--m_size;
		m_root = nullptr;
		return;
	}
	int i = index;
	while (!tmp->is_leaf()) {
		tmpI = dynamic_cast<InnerNode*>(tmp);
		tmp_ff = tmp_f;
		tmp_f = tmp;
		if (i > tmpI->m_info) {
			i -= tmpI->m_info;
			tmp = tmp->m_right;
		}
		else {
			--tmpI->m_info;
			tmp = tmp->m_left;
		}
	}
	if (tmp_ff == nullptr) {
		BaseNode* t = m_root;
		if (index == 1) {
			delete m_root->m_left;
			m_root = m_root->m_right;
		}
		else {
			delete m_root->m_right;
			m_root = m_root->m_left;
		}
		delete t;
		--m_size;
		return;
	}
	if (tmp_f == tmp_ff->m_left) {
		tmp_ff->m_left = (tmp == tmp_f->m_left) ? tmp_f->m_right : tmp_f->m_left;
	}
	else {
		tmp_ff->m_right = (tmp == tmp_f->m_left) ? tmp_f->m_right : tmp_f->m_left;
	}
	delete tmp;
	delete tmp_f;
	--m_size;
}

template <typename T>
void ListTree<T>::allocate(const ListTree& object) {
	if (object.m_size == 0) {
		return;
	}
	std::queue<BaseNode*> real;
	std::queue<BaseNode*> obj;
	obj.push(object.m_root);
	real.push(m_root);
	while (!obj.empty()) {
		if (obj.front()->is_leaf()) {
			real.front() = new OuterNode<T>(obj.front()->m_info);
		}
		else {
			real.front() = new InnerNode(obj.front()->m_info);
			obj.push(obj.front()->m_left);
			real.push(real.front()->m_left);
			obj.push(obj.front()->m_left);
			real.push(real.front()->m_left);
		}
		obj.pop();
		real.pop();
	}
}

template <typename T>
void ListTree<T>::deallocate() {
	if (m_size == 0) {
		return;
	}
	std::queue<BaseNode*> q;
	q.push(m_root);
	while (!q.empty()) {
		if (!q.front()->is_leaf()) {
			q.push(q.front()->m_left);
			q.push(q.front()->m_right);
		}
		delete q.front();
		q.pop();
	}
}