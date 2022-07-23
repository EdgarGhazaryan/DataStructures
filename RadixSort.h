#include "Queue.h"
#include "LinkedQueue.h"
#include <queue>

void RadixSort(int* data, int size) {
	Queue<int> Q[2];
	//LinkedQueue<int> Q[2];
	//std::queue<int> Q[2];
	for (int k = 0; k < sizeof(int) * 8; ++k) {
		for (int i = 0; i < size; ++i) {
			Q[(data[i] >> k) & 1].push(data[i]);
		}
		for (int i = 0, j = 0; j < 2; ++j) {
			while (!Q[j].empty()) {
				data[i++] = Q[j].front();
				Q[j].pop();
			}
		}
	}
}