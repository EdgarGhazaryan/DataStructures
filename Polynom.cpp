#include "Polynom.h"

#include <cmath>
#include <algorithm>

std::ostream& operator<<(std::ostream& out, const Polynom& object) {
	Polynom::Node* ptr = object.m_head->m_next;
	while (ptr != object.m_head) {
		if (ptr->m_coefficient != 1) {
			out << ptr->m_coefficient;
		}
		out << "x^" << ptr->m_exponent;
		if (ptr->m_next != object.m_head) {
			out << " + ";
		}
		ptr = ptr->m_next;
	}
	out << std::endl;
	return out;
}

Polynom::Polynom() : m_exponent(-1), m_head(nullptr) {
	m_head = new Node(0, -1);
	m_head->m_next = m_head;
}

Polynom::Polynom(const Information& object) : m_exponent(-1), m_head(nullptr) {
	m_head = new Node(0, -1);
	m_head->m_next = m_head;
	Node* previous = m_head, * tmp{nullptr};
	for (unsigned int i = 0; i < object.size(); ++i) {
		tmp = new Node(object[i].first, object[i].second);
		previous->m_next = tmp;
		previous = previous->m_next;
	}
	if (tmp != nullptr) {
		tmp->m_next = m_head;
		m_exponent = object[0].second;
	}
}

Polynom::Polynom(const Polynom& object) : m_exponent(object.m_exponent), m_head(nullptr) {
	const Node* current = object.m_head->m_next;
	m_head = new Node(0, -1);
	m_head->m_next = m_head;
	Node* prev = m_head, * tmp{ nullptr };
	while (current != object.m_head) {
		tmp = new Node(current->m_coefficient, current->m_exponent);
		prev->m_next = tmp;
		prev = tmp;
		current = current->m_next;
	}
	if (tmp != nullptr) {
		tmp->m_next = m_head;
	}
}

Polynom& Polynom::operator=(const Polynom& object) {
	if (this != &object) {
		deallocate();
		m_exponent = object.m_exponent;
		const Node* current = object.m_head->m_next;
		m_head = new Node(0, -1);
		m_head->m_next = m_head;
		Node* prev = m_head, * tmp{ nullptr };
		while (current != object.m_head) {
			tmp = new Node(current->m_coefficient, current->m_exponent);
			prev->m_next = tmp;
			prev = tmp;
			current = current->m_next;
		}
		if (tmp != nullptr) {
			tmp->m_next = m_head;
		}
	}
	return *this;
}

Polynom::~Polynom() {
	deallocate();
}

Polynom& Polynom::operator+=(const Polynom& object) {
	Node* previous = m_head, * this_current = m_head->m_next;
	const Node* object_current = object.m_head->m_next;
	while (object_current != object.m_head) {
		if (this_current->m_exponent == object_current->m_exponent) {
			this_current->m_coefficient += object_current->m_coefficient;
			if (this_current->m_coefficient == 0) {
				previous->m_next = this_current->m_next;
				delete this_current;
				this_current = previous;
			}
			previous = this_current;
			this_current = this_current->m_next;
			object_current = object_current->m_next;
		}
		else if (this_current->m_exponent < object_current->m_exponent) {
			Node* tmp = new Node(object_current->m_coefficient, object_current->m_exponent);
			tmp->m_next = this_current;
			previous->m_next = tmp;
			previous = tmp;
			object_current = object_current->m_next;
		}
		else {
			previous = this_current;
			this_current = this_current->m_next;
		}
	}
	m_exponent = m_head->m_next->m_exponent;
	return *this;
}

Polynom& Polynom::operator*=(const Polynom& object) {
	Polynom y;
	const Node* pointer1 = object.m_head->m_next;
	Node* pointer2 = m_head->m_next;
	while (pointer1 != object.m_head) {
		Polynom x;
		Node* pointer3 = x.m_head;
		while (pointer2 != m_head) {
			double coefficient = pointer1->m_coefficient * pointer2->m_coefficient;
			int exponent = pointer1->m_exponent + pointer2->m_exponent;
			Node* tmp = new Node(coefficient, exponent);
			tmp->m_next = x.m_head;
			pointer3->m_next = tmp;
			pointer3 = tmp;
			pointer2 = pointer2->m_next;
		}
		y += x;
		pointer1 = pointer1->m_next;
		pointer2 = m_head->m_next;
	}
	m_exponent = y.m_exponent;
	return *this = y;
}

Polynom& Polynom::operator*=(const double value) {
	Node* current = m_head->m_next;
	while (current != m_head) {
		current->m_coefficient *= value;
		current = current->m_next;
	}
	return *this;
}

Polynom& Polynom::derivative() {
	Node* current = m_head->m_next;
	Node* prev = m_head;
	while (current != m_head) {
		if (current->m_exponent == 0) {
			delete current;
			prev->m_next = m_head;
			break;
		}
		current->m_coefficient *= current->m_exponent--;
		prev = current;
		current = current->m_next;
	}
	--m_exponent;
	return *this;
}

double Polynom::count_value(double value) const {
	double result = 0;
	Node* current = m_head->m_next;
	while (current != m_head) {
		result += pow(value, current->m_exponent) * current->m_coefficient;
		current = current->m_next;
	}
	return result;
}

void Polynom::deallocate() {
	Node* prev = m_head->m_next, *Delete = m_head->m_next;
	while (prev != m_head) {
		prev = prev->m_next;
		delete Delete;
		Delete = prev;
	}
	delete m_head;
}

Polynom operator+(Polynom P1, const Polynom& P2) {
	return P1 += P2;
}

Polynom operator*(Polynom P1, const Polynom& P2) {
	return P1 *= P2;
}

Polynom operator*(Polynom P1, const double value) {
	return P1 *= value;
}