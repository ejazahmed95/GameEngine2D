#pragma once
#include <cassert>

template<typename T>
class DynamicArray {
public:
	DynamicArray() {
		resize(2);
	}
	~DynamicArray() {
		clear();
		::operator delete(_data, _capacity * sizeof(T));
	}
	DynamicArray(const DynamicArray& other) = delete;
	DynamicArray& operator=(const DynamicArray& other) = delete;

	void push_back(const T& value) {
		if(_size >= _capacity) {
			resize(_capacity + _capacity / 2);
		}
		_data[_size++] = value;
	}

	void pop_back() {
		if (_size == 0) return;
		_size--;
		_data[_size].~T();
	}

	void clear() {
		for(size_t i=0;i<_size;i++) {
			_data[i].~T();
		}
		_size = 0;
	}

	size_t size() const {
		return _size;
	}
	const T& operator[](size_t index) const {
		if (index >= _size) {
			assert(false);
		}
		return _data[index];
	}

	T& operator[](size_t index) {
		if (index >= _size) {
			assert(false);
		}
		return _data[index];
	}
private:
	void resize(size_t newCapacity) { // Capacity can only be more than size
		T* newBlock = static_cast<T*>(::operator new(newCapacity * sizeof(T)));
		assert(newBlock);
		if(newCapacity < _size) {
			return;
		}
		
		for(size_t i = 0;i<newCapacity && i<_size;i++) {
			newBlock[i] = _data[i];
		}

		// Calling destructor for previous data
		for (size_t i = 0; i < _size; i++) {
			_data[i].~T();
		}
		// Freeing the memory
		::operator delete(_data, _capacity * sizeof(T));

		_data = newBlock;
		_capacity = newCapacity;
	}
private:
	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};
