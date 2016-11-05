#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

/*****************************************
* UW User ID:  z388wang
* Submitted for ECE 250
* Semester of Submission:  (Fall) 20NN
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#include "Exception.h"
#include "ece250.h"
using namespace std;
enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class LinearHashTable {
private:
	int count;
	int power;
	int array_size;
	int initialsize;
	T *array;
	state *occupied;


public:
	LinearHashTable(int = 5);
	~LinearHashTable();
	int size() const;
	int capacity() const;
	double load_factor() const;
	bool empty() const;
	bool member(T const &) const;
	T bin(int) const;


	void insert(T const &);
	bool remove(T const &);
	void clear();
	void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable(int m) :
	array_size(1 << power),power(m) {
	array = new T[array_size];
	occupied = new state[array_size];
	count = 0;
	initialsize = array_size;
	for (int i = 0; i < array_size; i++)
	{
		occupied[i] = EMPTY;
	}
	
}

template<typename T >
LinearHashTable<T >::~LinearHashTable() {
	delete[]array;
	delete[]occupied;
}

template<typename T >
int LinearHashTable<T >::size() const {
	
	return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {
	
	return array_size;
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
	double loadfactor = (double)count / (double)array_size;
	return loadfactor;
}

template<typename T >
bool LinearHashTable<T >::empty() const {
	if (count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template<typename T >
bool LinearHashTable<T >::member(T const &obj) const {
	int position;
	position = fmod(obj, array_size);
	if (position < 0)
	{
		position = position + array_size;
	}
	int time = array_size;
		if (occupied[position] == EMPTY || occupied[position] == DELETED)
		{
			return false;
		}
		else if (occupied[position] == OCCUPIED)
		{
			while (array[position] != obj && time > 0)
			{
				time--;
				position = (position + 1) % array_size;
			}
				if (array[position] == obj)
				{
					return true;
				}
				else
				{
					return false;
				}
			
		}
	}


template<typename T >
T LinearHashTable<T >::bin(int n) const {
	
	return array[n];
}

template<typename T >
void LinearHashTable<T >::insert(T const &obj) {
	int position;
	position = fmod(obj, array_size);
	if (position < 0)
	{
		position = position + array_size;
	}
	double load = load_factor();
		if (load <= 0.75)
		{
			if (occupied[position] == EMPTY)
			{
				occupied[position] = OCCUPIED;
				array[position] = obj;
				count++;
			}
			else 
			{
				while (occupied[position] == OCCUPIED)
				{
					
					position = (position + 1) % array_size;
				}
				occupied[position] = OCCUPIED;
				array[position] = obj;
				count++;
			}
		}
		else
		{
			int newarray_size;
			newarray_size = 2 * array_size;
			int index;
			T *newarray;
			state *newoccupied;
			newarray = new T[newarray_size];
			newoccupied = new state[newarray_size];
			for (int i = 0; i < newarray_size; i++)
			{
				newoccupied[i] = EMPTY;
			}
			for (int i = 0; i < array_size; i++)
			{
				if (occupied[i] == OCCUPIED)
				{
					index = fmod(array[i], newarray_size);

					if (index < 0)
					{
						index = index + newarray_size;
					}
					while (newoccupied[index] == OCCUPIED)
					{
						index = (index + 1) % newarray_size;
					}
					newarray[index] = array[i];
					newoccupied[index] = OCCUPIED;
				}
			}
			
			delete[]array;
			delete[]occupied;

			array = newarray;
			occupied = newoccupied;
			array_size = newarray_size;
			

			int position2 = 0;
			position2 = fmod(obj, array_size);
			if (position2 < 0)
			{
				position2 = position2 + array_size;
			}
			while (occupied[position2] == OCCUPIED)
			{
				position2 = (position2 + 1) % array_size;
			}
			array[position2] = obj;
			occupied[position2] = OCCUPIED;
			count++;

		}
}

template<typename T >
bool LinearHashTable<T >::remove(T const &obj) {
	int position2;
	position2 = fmod(obj, array_size);
	if (position2 < 0)
	{
		position2 = position2 + array_size;
	}
	int time = array_size - 1;
	double load = load_factor();
	if (load <= 0.25 && array_size > initialsize)
	{
		int newarray_size = array_size / 2;
		int index;
		T *newarray;
		state *newoccupied;
		newarray = new T[newarray_size];
		newoccupied = new state[newarray_size];
		for (int i = 0; i < newarray_size; i++)
		{
			newoccupied[i] = EMPTY;
		}
		for (int i = 0; i < array_size; i++)
		{
			if (occupied[i] == OCCUPIED)
			{
				index = fmod(array[i], newarray_size); 
				if (index < 0)
				{
					index = index + newarray_size;
				}
				while (newoccupied[index] == OCCUPIED)
				{
					index = (index + 1) % newarray_size;
				}
				newarray[index] = array[i];
				newoccupied[index] = OCCUPIED;
			}
		}
		delete[]array;
		delete[]occupied;

		array = newarray;
		occupied = newoccupied;
		array_size = newarray_size;

	

		int position3;
		position3 = fmod(obj, array_size); 
		if (position3 < 0)
		{
			position3 = position3 + array_size;
		}
		   
			while (array[position3] != obj || occupied[position3] != OCCUPIED)
			{
				position3 = (position3 + 1) % array_size;
			}

		occupied[position3] = DELETED;
		array[position3] = '/n';
		count--;
		return true;
		
	}
	
	if (occupied[position2] == EMPTY)  
	{
		return false;
	}
		if(occupied[position2] == DELETED)
		{
			while (occupied[position2] != OCCUPIED)
			{
				position2 = (position2 + 1) % array_size;
			}
		}
	
   if (occupied[position2] == OCCUPIED)
	{
		while (array[position2] != obj && time > 0)
		{
			time--;
			position2 = (position2 + 1) % array_size;
		}
		if (array[position2] == obj)
		{
			occupied[position2] = DELETED;
			array[position2] = '/n';
			count--;
			return true;
		}
		else
		{
			return false;
		}
	}

  
}

template<typename T >
void LinearHashTable<T >::clear() {
	for (int i = 0; i < array_size; i++)
	{
		occupied[i] = EMPTY;
		array[i] = '/n';
	}
	count = 0;
}

template<typename T >
void LinearHashTable<T >::print() const {
	for (int i = 0; i < array_size; i++)
	{
		cout << array[i] << "  " << occupied[i] << endl;
	}

}

#endif