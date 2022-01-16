#pragma once
#include <stdio.h>
#include <string>
#include <stdexcept>

class PriorityQueue_int{
	public:
    class ItemWrapper_int{
		/*
		* Ссылка на очередь
		*/
		PriorityQueue_int* _queue;
		/*
		* Приоритет
		*/
		unsigned int _priority;
		/*
		* Значение
		*/
		int _value;
	public:
		/*
		* Деструктор класса
		*/
		virtual ~ItemWrapper_int() {}
		/*
		* Конструкторы класса
		*/
		ItemWrapper_int(PriorityQueue_int* queue, unsigned int priority, int& value) : _queue(queue), _priority(priority), _value(value) {}
		/*
		* Геттер для приватного значение _priority
		*/
		unsigned int getPriority() {
			return _priority;
		}
		/*
		* Геттер для приватного значение _value
		*/
		int& getValue() {
			return _value;
		}
		/*
		* Сеттер для приватного значение _value
		*/
		void setValue(int& value) {
			_value=value;
		}

		ItemWrapper_int operator =(ItemWrapper_int other) {
			_queue = other._queue;
			_priority = other._priority;
			_value = other._value;
			return other;
		}
    };
	private:
	size_t _size=0;
	
	/*
	* Массив элементов очереди
	*/
	ItemWrapper_int * _items=NULL;
	
	/*
	* Служебная (приватная) процедура для изменения размера очереди
	*/
	void _resizeItems(size_t newSize) {
		if (_size == newSize) {
			return;
		}
		if (newSize == 0) {
			free(_items);
			_items = NULL;
			_size = 0;
		}
		ItemWrapper_int* newItems = (ItemWrapper_int*)calloc(sizeof(ItemWrapper_int), newSize);
		size_t minSize = _size > newSize ? newSize : _size;
		for (size_t counter = 0; counter < minSize; counter++) {
			newItems[counter] = _items[counter];
		}
		free(_items);
		_items = newItems;
		_size = newSize;
	}
    public:
	/*
	* Деструктор класса
	*/
	virtual ~PriorityQueue_int() {
		free(_items);
	}
	
	/*
	* Конструкторы класса
	*/
	PriorityQueue_int(PriorityQueue_int&){}
	PriorityQueue_int();

	/*
	* Метод формирования строчного представления ОчередиСПриоритетом
	*/
	operator std::string() const {
		std::string buffer="[";
		for(auto counter=0;counter<_size;counter++){
			if(counter>0){
				buffer+=", ";
			}
			auto iterator=_items[counter];
			buffer+=std::to_string(iterator.getValue());
		}
		buffer+="]";
		return buffer;
	}

	/*
	* Публичные методы класса
	*/
	void push(unsigned int priority, int value) {
		_resizeItems(_size + 1);
		size_t offset, shiftOffset;
		ItemWrapper_int newItem(this, priority, value);
		/*
		* Определяем смещение (offset) куда воткнуть наше значение в соответствии с приоритетом
		*/
		for (offset = 0; offset < _size-1; offset++) {
			if (_items[offset].getPriority() < priority) {
				break;
			}
		}
		/*
		* Сдвигаем все элементы начиная с offset дальше по нашей очереди
		*/
		if (_size > 1) {
			for (shiftOffset = _size; shiftOffset-- > offset;) {
				_items[shiftOffset] = _items[shiftOffset - 1];
			}
		}
		/*
		* Устанавливаем новое значение в классе-обёртке на определённое место
		*/
		_items[offset] = newItem;
	}
	/*
	* Выталкивание из очереди элементы с наименьшим приоритетом
	*/
	int less() {
		if (_size == 0) {
			throw std::runtime_error("trying to extract value from empty queue");
		}
		int value = _items[_size - 1].getValue();
		_resizeItems(_size - 1);
		return value;
	}
	/*
	* Выталкивание из очереди элементы с наивысшим приоритетом
	*/
	int top() {
		if (_size == 0) {
			throw std::runtime_error("trying to extract value from empty queue");
		}
		int value = _items[0].getValue();
		if (_size > 1) {
			for (size_t counter = 1; counter++; counter<_size) {
				_items[counter - 1] = _items[counter];
			}
		}
		_resizeItems(_size - 1);
		return value;
	}
};