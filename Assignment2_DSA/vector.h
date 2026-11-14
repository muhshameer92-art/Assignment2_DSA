#pragma once
template<class T>
class vector {
	T* pl;
	int currentCapacity;
	int currentSize;
	void resize() {
		T* temp = new T [currentCapacity * 2];
		for (int i = 0; i < currentSize; i++) {
			temp[i] = pl[i];
		}
		delete[]pl;
		pl = temp;
		currentCapacity *= 2;
	}
public:
	vector() {
		currentCapacity = 2;
		pl = new T [currentCapacity];
		currentSize = 0;
	}
	vector(const vector& vec) {
		currentSize = vec.size();
		currentCapacity = vec.capacity();
		for (int i = 0; i < vec.size(); i++) {
			*this->at(i) = vec.at(i);
		}
	}
	~vector() {
		delete[]pl;
	}
	int size() const {
		return currentSize;
	}
	int capacity() const {
		return currentCapacity;
	}
	T at(int i) const {
		if (i < 0 || i >= currentSize)
			return NULL;
		return pl[i];
	}
	void push_back(T val) {
		if (currentSize == currentCapacity)
			resize();
		pl[currentSize] = val;
		currentSize++;
	}
	void pop_back() {
		T* temp = new T [currentCapacity];
		currentSize--;
		for (int i = 0; i < currentSize; i++) {
			temp[i] = pl[i];
		}
		delete[]pl;
		pl = temp;
	}
};
