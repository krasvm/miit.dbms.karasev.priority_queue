#include <stdlib.h>

class PriorityQueue_int{
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

		int& getValue() {
			return _value;
		}

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
	size_t _size=0;
	
	/*
	* Массив элементов очереди
	*/
	ItemWrapper_int * _items=NULL;
	
	/*
	* Служебная (приватная) процедура для изменения размера очереди
	*/
	virtual void _resizeItems(size_t newSize);
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
	* Публичные методы класса
	*/
	virtual void push(unsigned int priority, int& value);
	virtual int less();
	virtual int top();
};