#ifndef MYARRAY_H
#define MYARRAY_H

#include <stdexcept>
#include <initializer_list>

template<typename T>
class myArray {
	private:
		size_t _size;
		size_t _capacity;
		T* _data;
	public:
		class iterator{
			private:
				T* _ptr;
			public:
				explicit iterator(T* ptr) : _ptr(ptr) {}
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
				explicit reverse_iterator(T* ptr) : _ptr(ptr) {}
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
		explicit myArray(int capacity = 1) : _size(0), _capacity(capacity), _data(new T[_capacity]){};

                myArray(std::initializer_list<T> il) : _size (il.size()), _capacity(_size), _data(new T[_size]) {
                                iterator pointer = begin();
                                for (const T& i : il){
                                        *pointer++ = i;
                                }
                }

		myArray(const myArray& other) : _size(other._size), _capacity(other._capacity), _data(new T[other._capacity]){ // copy constructor
			for (int i = 0; i < _capacity; ++i){
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
				for (int i = 0; i < _capacity; ++i){
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
		T& operator[](size_t idx) const{ // index operator
                        if (idx >= _capacity){
                            throw std::out_of_range("Out of range");
                        }
			return _data[idx];
		}
		size_t size() const{
			return _size;
		}
		size_t capacity() const{
			return _capacity;
		}
		void push_back(T value){
			if (_size == _capacity){
				resize(std::max(2 * _capacity, 1ULL));
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
			_size = _size > new_capacity ? new_capacity : _size;
			for (int i = 0; i < _size; ++i){
				new_data[i] = std::move(_data[i]);
			}
			delete[] _data;
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
		void reverse(){
			for (int i = 0; i < _size/2; ++i){
				std::swap(_data[i],_data[_size-i-1]);
			}
		}

                int find(T value){
                        for (int i = 0; i < _size; ++i){
                                if (_data[i] == value){
                                        return i;
                                }
                        }
                        return -1;
                }
};

#endif
