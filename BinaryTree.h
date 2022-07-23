#pragma once

#include <algorithm>
#include <vector>
#include <queue>
#include <stack>

namespace BinaryTree {
	template <typename T>
	struct Node {
		Node(const T& info = T()) : m_left(nullptr), m_right(nullptr), m_info(info) {}
		Node(Node<T>&) = delete;
		Node<T>& operator=(Node<T>&) = delete;
		virtual ~Node() {}

		Node<T>* m_left;
		Node<T>* m_right;
		T m_info;
	};

	template <typename T>
	struct ExtendedNode : public Node<T> {
		ExtendedNode(const T& info = T()) : Node(info), m_father(nullptr) {}

		ExtendedNode<T>* m_father;
	};

	template <typename T>
	using FuncNode = void (*)(Node<T>*);

	template <typename T>
	using FuncExtendedNode = void (*)(ExtendedNode<T>*);

	template <typename T>
	int height(Node<T>* root) {
		if (root == nullptr || (root->m_left == nullptr && root->m_right == nullptr)) {
			return 0;
		}
		return std::max(height(root->m_left), height(root->m_right)) + 1;
	}

	template <typename T>
	int leaves_count(Node<T>* root) {
		if (root == nullptr) {
			return 0;
		}
		if (root->m_left == nullptr && root->m_right == nullptr) {
			return 1;
		}
		return leaves_count(root->m_left) + leaves_count(root->m_right);
	}

	template <typename T>
	int max_value(Node<T>* root) {
		if (root->m_left == nullptr && root->m_right == nullptr) {
			return root->m_info;
		}
		std::vector<int> max = { root->m_info };
		if (root->m_left != nullptr) {
			max.push_back(max_value(root->m_left));
		}
		if (root->m_right != nullptr) {
			max.push_back(max_value(root->m_right));
		}
		return *std::max_element(max.begin(), max.end());
	}

	template <typename T>
	int points_count(Node<T>* root) {
		if (root == nullptr) {
			return 0;
		}
		if (root->m_left == nullptr && root->m_right == nullptr) {
			return 1;
		}
		return (1 + points_count(root->m_left) + points_count(root->m_right));
	}

	template <typename T>
	bool is_strict(Node<T>* root) {
		if (root == nullptr || (root->m_left == nullptr && root->m_right == nullptr)) {
			return true;
		}
		if (root->m_left == nullptr || root->m_right == nullptr) {
			return false;
		}
		return is_strict(root->m_left) && is_strict(root->m_right);
	}

	template <typename T>
	ExtendedNode<T>* straight_next(ExtendedNode<T>* current) {
		if (current->m_left != nullptr) {
			return current->m_left; 
		}
		if (current->m_right != nullptr) { 
			return current->m_right; 
		}
		while (current->m_father != nullptr && ((current->m_father->m_right == current) || 
			((current->m_father->m_left == current) && (current->m_father->m_right == nullptr)))) {
			current = current->m_father;
		}
		if (current->m_father == nullptr) { 
			return nullptr; 
		}
		return current->m_father->m_right;
	}

	template <typename T>
	void straight_it(ExtendedNode<T>* root, FuncExtendedNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		visit(root);
		ExtendedNode<T>* next = straight_next(root);
		while (next != nullptr) {
			visit(next);
			next = straight_next(next);
		}
	}

	template <typename T>
	void straight_it_st(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		std::stack<Node<T>*> s;
		s.push(root);
		while (!s.empty()) {
			visit(s.top());
			Node<T>* tmp = s.top();
			s.pop();
			if (tmp->m_right != nullptr) {
				s.push(tmp->m_right);
			}
			if (tmp->m_left != nullptr) {
				s.push(tmp->m_left);
			}
		}
	}

	template <typename T>
	void straight_rec(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		visit(root);
		if (root->m_left != nullptr) {
			straight_rec(root->m_left, visit);
		}
		if (root->m_right != nullptr) {
			straight_rec(root->m_right, visit);
		}
	}

	template <typename T>
	ExtendedNode<T>* symetric_next(ExtendedNode<T>* current) {
		if (current->m_right != nullptr) {
			if (current->m_right->m_left != nullptr) {
				current = current->m_right;
				while (current->m_left != nullptr) {
					current = current->m_left;
				}
				return current;
			}
			return current->m_right;
		}
		while (current == current->m_father->m_right) {
			current = current->m_father;
		}
		return current->m_father;
	}

	template <typename T>
	void symetric_it(ExtendedNode<T>* root, FuncExtendedNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		while (root->m_left != nullptr) {
			root = root->m_left;
		}
		visit(root);
		ExtendedNode<T>* next = symetric_next(root);
		while (next != nullptr) {
			visit(next);
			next = symetric_next(next);
		}
	}

	template <typename T>
	void symetric_it_st(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		std::stack<Node<T>*> s;
		Node<T>* tmp = root;
		while (!s.empty() || tmp != nullptr) {
			while (tmp != nullptr) {
				s.push(tmp);
				tmp = tmp->m_left;
			}
			visit(s.top());
			tmp = s.top();
			s.pop();
			tmp = tmp->m_right;
		}
	}

	template <typename T>
	void symetric_rec(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		if (root->m_left != nullptr) {
			symetric_rec(root->m_left, visit);
		}
		visit(root);
		if (root->m_right != nullptr) {
			symetric_rec(root->m_right, visit);
		}
	}

	template <typename T>
	ExtendedNode<T>* reverse_next(ExtendedNode<T>* current) {
		if (current->m_father != nullptr) {
			if (current == current->m_father->m_left && current->m_father->m_right != nullptr) {
				if (current->m_father->m_right->m_left != nullptr) {
					current = current->m_father->m_right;
					while (current->m_left != nullptr) {
						current = current->m_left;
					}
					return current;
				}
				return current->m_father->m_right;
			}
		}
		return current->m_father;
	}

	template <typename T>
	void reverse_it(ExtendedNode<T>* root, FuncExtendedNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		while (root->m_left != nullptr || root->m_right != nullptr) {
			while (root->m_left != nullptr) {
				root = root->m_left;
			}
			if (root->m_right != nullptr) {
				root = root->m_right;
			}
		}
		visit(root);
		ExtendedNode<T>* next = reverse_next(root);
		while (next != nullptr) {
			visit(next);
			next = reverse_next(next);
		}
	}

	template <typename T>
	void reverse_it_st(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) { 
			return; 
		}
		std::stack<Node<T>*> s1, s2;
		s1.push(root);
		Node<T>* tmp;
		while (!s1.empty()) {
			tmp = s1.top();
			s2.push(tmp);
			s1.pop();
			if (tmp->m_left != nullptr) {
				s1.push(tmp->m_left);
			}
			if (tmp->m_right != nullptr) {
				s1.push(tmp->m_right);
			}
		}
		while (!s2.empty()) {
			visit(s2.top());
			s2.pop();
		}
	}

	template <typename T>
	void reverse_rec(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		if (root->m_left != nullptr) {
			reverse_rec(root->m_left, visit);
		}
		if (root->m_right != nullptr) {
			reverse_rec(root->m_right, visit);
		}
		visit(root);
	}

	template <typename T>
	void by_level_it(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		std::queue<Node<T>*> q;
		q.push(root);
		while (!q.empty()) {
			visit(q.front());
			if (q.front()->m_left != nullptr) {
				q.push(q.front()->m_left);
			}
			if (q.front()->m_right != nullptr) {
				q.push(q.front()->m_right);
			}
			q.pop();
		}
	}

	template <typename T>
	void print_i_level(Node<T>* root, int level, FuncNode<T> visit) {
		if (level == 0) {
			visit(root);
			return;
		}
		if (root->m_left != nullptr) {
			print_i_level(root->m_left, level - 1, visit);
		}
		if (root->m_right != nullptr) {
			print_i_level(root->m_right, level - 1, visit);
		}
	}

	template <typename T>
	void by_level_rec(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		int h = BinaryTree::height(root);
		int i = 0;
		while (i <= h) {
			print_i_level(root, i, visit);
			++i;
		}
	}
}