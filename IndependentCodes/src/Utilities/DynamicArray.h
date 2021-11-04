#pragma once
#include <cassert>

template<typename T>
class DynamicArray {
public:
	DynamicArray() {
		Resize(2);
	}
	~DynamicArray() {
		clear();
		::operator delete(_data, _capacity * sizeof(T));
	}
	void push_back(const T& value) {
		if(_size >= _capacity) {
			Resize(_capacity + _capacity / 2);
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
	// void add(T&& value) {
	// 	// Todo: Use std::move to reduce copies
	// 	if (_size >= _capacity) {
	// 		Resize(_capacity + _capacity / 2);
	// 	}
	// 	_data[_size++] = std::move(value);
	// }

	size_t Size() const {
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
	void Resize(size_t newCapacity) {
		T* newBlock = static_cast<T*>(::operator new(newCapacity * sizeof(T)));

		if(newCapacity < _size) {
			_size = newCapacity;
		}

		// Todo: Use std::move to reduce copies
		for(size_t i = 0;i<_size;i++) {
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
	};
private:
	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};
