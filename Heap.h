#pragma once

#include <algorithm>
#include "DataStructuresExceptions.h"

template <typename T>
class Heap {
public:
	Heap();
	Heap(const Heap<T>&);
	Heap<T>& operator=(const Heap<T>&);
	~Heap();

	bool empty() const { return m_size == 0; }
	int size() const { return m_size; }
	const T& get_max() const;
	void insert(const T&);
	void remove();

private:
	void allocate(const T* = nullptr);
	void deallocate();

private:
	static const int MAX_SIZE = 20;

	int m_size;
	int m_max_size;
	T* m_data;
};

template <typename T>
Heap<T>::Heap() : m_size(0), m_max_size(MAX_SIZE), m_data(nullptr) {
	allocate();
}

template <typename T>
Heap<T>::Heap(const Heap<T>& object): m_size(object.m_size), m_max_size(object.m_max_size),	m_data(nullptr) {
	allocate(object.data);
}

template <typename T>
Heap<T>& Heap<T>::operator=(const Heap<T>& object) {
	if (this != &object) {
		m_size = object.m_size;
		m_max_size = object.m_max_size;
		deallocate();
		allocate(object.m_data);
	}
	return *this;
}

template <typename T>
Heap<T>::~Heap() {
	deallocate();
}

template <typename T>
const T& Heap<T>::get_max() const {
	if (m_size != 0) {
		return m_data[1];
	}
	throw IsEmptyException;
}

template <typename T>
void Heap<T>::insert(const T& element) {
	if (m_size + 1 == m_max_size) {
		m_max_size *= 2;
		T* tmp = new T[m_max_size];
		for (int i = 1; i < m_size + 1; ++i) {
			tmp[i] = m_data[i];
		}
		delete[] m_data;
		m_data = tmp;
	}
	m_data[++m_size] = element;
	int i = m_size;
	while (i != 1 && m_data[i] > m_data[i / 2]) {
		std::swap(m_data[i], m_data[i / 2]);
		i /= 2;
	}
}

template <typename T>
void Heap<T>::remove() {
	if (m_size == 0) {
		throw IsEmptyException;
	}
	m_data[1] = m_data[m_size--];
	int current = 1, child = 2 * current;
	while (child <= m_size) {
		if (child + 1 <= m_size && m_data[child] < m_data[child + 1]) {
			++child;
		}
		if (m_data[current] < m_data[child]) {
			std::swap(m_data[current], m_data[child]);
			current = child;
			child = 2 * current;
		}
		else {
			break;
		}
	}
}

template <typename T>
void Heap<T>::allocate(const T* data) {
	m_data = new T[m_max_size]{};
	for (int i = 1; i < m_size + 1; ++i) {
		m_data[i] = data[i];
	}
}

template <typename T>
void Heap<T>::deallocate() {
	delete[] m_data;
}