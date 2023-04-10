#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>

template<typename T>
class myArray {
	private:
		int _size;
		int _capacity;
		T* _data;
	public:
		class iterator{
			private:
				T* _ptr;
			public:
				iterator(T* ptr) : _ptr(ptr) {}
				iterator(const iterator& it) : _ptr(it._ptr) {}
				iterator& operator++(){
					_ptr++;
					return *this;
				}
				iterator operator++(int){
					iterator tmp = *this;
					++(*this);
					return tmp;
				}
				bool operator==(const iterator& other) const{
					return _ptr == other._ptr;
				}
				bool operator!=(const iterator& other) const{
					return _ptr != other._ptr;
				}
				T& operator*(){
					return *_ptr;
				}
		};
		class reverse_iterator{
			private:
				T* _ptr;
			public:
				reverse_iterator(T* ptr) : _ptr(ptr) {}
				reverse_iterator(const reverse_iterator& rit) : _ptr(rit._ptr) {}
				reverse_iterator& operator++(){
					_ptr--;
					return *this;
				}
				reverse_iterator operator++(int){
					reverse_iterator tmp = *this;
					--(*this);
					return tmp;
				}
				bool operator==(const reverse_iterator& other) const{
					return _ptr == other._ptr;
				}
				bool operator!=(const reverse_iterator& other) const{
					return _ptr != other._ptr;
				}
				T& operator*() {
					return *_ptr;
				}
		};
		myArray(int capacity = 1) : _size(0), _capacity(capacity), _data(new T[_capacity]){};
		myArray(const myArray& other) : _size(other._size), _capacity(other._capacity), _data(new T[other._capacity]){ // copy constructor
			for (int i = 0; i < _size; ++i){
				_data[i] = other._data[i];
			}
		}
		myArray(myArray&& other) noexcept : _size(other._size), _capacity(other._capacity), _data(other._data){ // move constructor
			other._size = 0;
			other._capacity = 0;
			other._data = nullptr;
		}
    ~myArray(){
      delete[] _data;
    };
		myArray& operator=(const myArray& other){ // copy assignment
			if (this != &other){
				delete[] _data;
				_size = other._size;
				_capacity = other._capacity;
				_data = new T[_capacity];
				for (int i = 0; i < _size; ++i){
					_data[i] = other._data[i];
				}
			}
			return *this;
		}
		myArray& operator=(myArray&& other) noexcept { // move assignment
			if (this != &other){
				delete[] _data;
				_size = other._size;
				_capacity = other._capacity;
				_data = other._data;
				other._size = 0;
				other._capacity = 0;
				other._data = nullptr;
			}
			return *this;
		}
		T& operator[](int idx) const{ // index operator
			return _data[idx];
		}
		int size() const{
			return _size;
		}
		int capacity() const{
			return _capacity;
		}
		void push_back(const T value){
			if (_size == _capacity){
				resize(2*_capacity);
			}
			_data[_size] = value;
			++_size;
		}
		iterator begin(){
			return iterator(_data);
		}
		iterator end(){
			return iterator(_data+_size);
		}
		reverse_iterator rbegin(){
			return reverse_iterator(_data+_size-1);
		}
		reverse_iterator rend(){
			return reverse_iterator(_data-1);
		}
		bool operator==(const myArray& other) const{
			if (_size != other._size){
				return false;
			}
			for (int i = 0; i < _size; ++i){
				if (_data[i] != other._data[i]){
					return false;
				}
			}
			return true;
		}
		void resize(int new_capacity){
			T* new_data = new T[new_capacity];
			for (int i = 0; i < _size; ++i){
				new_data[i] = std::move(_data[i]);
			}
			delete _data;
			_data = new_data;
			_capacity = new_capacity;
		}
		void clear(){
			_size = 0;
			_capacity = 1;
		}
		void pop_back(){
			--_size;
		}
};

#endif
