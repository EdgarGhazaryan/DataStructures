#pragma once

#include "Heap.h"

template <typename T>
void HeapSort(T* data, int size) {
	Heap<T> h;
	for (int i = 0; i < size; ++i) {
		h.insert(data[i]);
	}
	for (int i = size - 1; i >= 0; --i) {
		data[i] = h.get_max();
		h.remove();
	}
}