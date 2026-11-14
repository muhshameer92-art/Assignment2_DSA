#pragma once
#include<iostream>
using namespace std;
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
		currentCapacity = vec.currentCapacity < 2 ? 2 : vec.currentCapacity;
		currentSize = vec.currentSize < currentCapacity ? vec.currentSize : currentCapacity;
		pl = new T[currentCapacity];
		for (int i = 0; i < currentSize; i++)
			pl[i] = vec.pl[i];
	}
	vector& operator=(const vector& other) {

		if (this == &other)
			return *this;

		int cap = other.currentCapacity < 2 ? 2 : other.currentCapacity;
		int n = other.currentSize < cap ? other.currentSize : cap;
		T* temp = new T[cap];
		for (int i = 0; i < n; i++)
			temp[i] = other.pl[i];   
		delete[] pl;
		pl = temp;
		currentCapacity = cap;
		currentSize = n;
		return *this;
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
		if (i < 0 || i >= currentSize) {
			cout << "Error!ClubManager>Vector says: \'Out of Range!\'"<<endl;
			return T();
		}
		return pl[i];
	}
	void push_back(T val) {
		if (currentSize == currentCapacity)
			resize();
		pl[currentSize] = val;
		currentSize++;
	}
	void pop_back() {
		if (currentSize == 0)
			return;
		currentSize--;
		
	}
};
