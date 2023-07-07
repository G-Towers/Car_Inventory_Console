
#ifndef RECORDARRAY_H
#define RECORDARRAY_H

#include "Record.h"

class RecordArray
{
public:
	RecordArray()
	{
		recArr = new Record[MAX_SIZE];
	}

	~RecordArray()
	{
		delete [] recArr;
		recArr = nullptr;
	}

	Record& operator[](int index) 
	{
		if (index < 0 || index >= arrSize) 
		{
			throw std::out_of_range("Index out of range");
		}
		return recArr[index];
	}

	// Member access
	Record* GetRecArr() const { return recArr; }
	void SetRecArr(Record* rec) { recArr = rec; }

	int GetSize() const { return arrSize; }
	void SetSize(int size) { arrSize = size; }
	void IncrementSize() { arrSize++; }

	void ResetRecArr()
	{
		delete [] recArr;
		recArr = new Record[MAX_SIZE];
	}

public:
	Record* recArr;
	int arrSize = 0;
	

};

#endif // !RECORDARRAY_H
