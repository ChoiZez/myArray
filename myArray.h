#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>

template<typename T>
class myArray {
	private:
		int _size;
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
					++(*this);
					return tmp;
				}
				bool operator==(const reverse_iterator& other) const{
					return _ptr == other._ptr;
				}
				bool operator!=(const reverse_iterator& other) const{
					return *this != other;
				}
				T& operator*() {
					return *_ptr;
				}
		};
		myArray(int size) : _size(size), _data(new T[_size]){};
		myArray(const myArray& other) : _size(other._size), _data(new T[_size]){ // copy constructor
			std::cout << "Copy";
			for (int i = 0; i < _size; ++i){
				_data[i] = other._data[i];
			}
		}
		myArray(myArray&& other) noexcept : _size(other._size), _data(other._data){ // move constructor
			std::cout << "Move";
			other._size = 0;
			other._data = nullptr;
		}
		myArray& operator=(const myArray& other){ // copy assignment
			if (this != &other){
				delete[] _data;
				_size = other._size;
				_data = new T[_size];
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
				_data = other._data;
				other._size = 0;
				other._data = nullptr;
			}
			return *this;
		}
		T& operator[](int idx){ // index operator
			return _data[idx];
		}
		int size() const{
			return _size;
		}
		iterator begin(){
			return iterator(_data);
		}
		iterator end(){
			return iterator(_data+_size);
		}
		reverse_iterator rbegin(){
			return reverse_iterator(_data);
		}
		reverse_iterator rend(){
			return reverse_iterator(_data+_size);
		}
		~myArray(){
			delete[] _data;
		};
};

#endif
