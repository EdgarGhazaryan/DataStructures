#pragma once

#include <iostream>
#include <vector>

class Polynom {
	friend std::ostream& operator<<(std::ostream&, const Polynom&);

public:
	typedef std::vector<std::pair<double, int>> Information;

	Polynom();
	Polynom(const Information&);
	Polynom(const Polynom&);
	Polynom& operator=(const Polynom&);
	~Polynom();

	Polynom& operator+=(const Polynom&);
	Polynom& operator*=(const Polynom&);
	Polynom& operator*=(const double);

	int get_exponent() const { return m_exponent; }

	Polynom& derivative();
	double count_value(double) const;

private:
	struct Node {
		double m_coefficient;
		int m_exponent;
		Node* m_next;

		Node(double coeffecient, int exponent) : m_coefficient(coeffecient), m_exponent(exponent), m_next(nullptr) {}
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
	};

	void deallocate();

	int m_exponent;
	Node* m_head;
};

Polynom operator+(Polynom, const Polynom&);
Polynom operator*(Polynom, const Polynom&);
Polynom operator*(Polynom, const double);