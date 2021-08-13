

#include <iostream>


template <class T>
class circularBuffer
{
	circularBuffer() = delete;
public:
	explicit circularBuffer(unsigned short const size){
		data = new T[size];
		total_size_ = size;
		head_ = -1;		
		size_ = 0;
	}
	~circularBuffer()
	{
		delete[] data;
	}
	bool clear() { head_ = -1; size_ = 0; return true; }
	bool empty() { return size_ == 0; }
	bool full() { return size_ == total_size_; }
	unsigned short capacity() { return total_size_; }
	unsigned short size() { return size_; }

	void push(T const item)
	{
		head_ = next_pos();
		data[head_] = item;
		if (size_ < total_size_)size_++;
	}
	T pop()
	{
		
		short pos = first_pos();
		size_--;
		return data[pos];		
	}

	void add(const T *data, unsigned short cntWord)
	{
		for (unsigned short i = 0; i < cntWord; ++i)
		{
			push(data[i]);
		}
	}

	void pop(T *data, unsigned short cntWord)
	{
		if (cntWord > size()) return;
		for (unsigned short i = 0; i < cntWord; ++i)
		{
			data[i] = pop();
		}
	}
private:
	short next_pos()
	{
		return size_ == 0 ? 0 : (head_ + 1) % total_size_;
	}
	short first_pos()
	{
		return size_ == 0 ? 0 : (head_ + total_size_ - size_ + 1) % total_size_;
	}
private:
	T *data;
	unsigned short total_size_;
	unsigned short size_;
	short head_;	

};

typedef union
{
	struct
	{
		int16_t a;
		int16_t b;
	} words;
	unsigned char bytes[4];
} _s;
int main()
{
	circularBuffer<unsigned char> cbuf(5);
	circularBuffer<_s> cbuf2(3);
	_s val;
	_s val2;
	val.words.a = 0x01;
	val.words.b= 0x02;


	cbuf.add(&val.bytes[0], 4);
	cbuf.pop(&val2.bytes[0], 4);

	std::cout << val.words.a << " " << val.words.b << std::endl;
	std::cout << val2.words.a << " " << val2.words.b << std::endl;



	cbuf2.push(val);
	cbuf2.push(val2);

	_s val3;
	for (; !cbuf2.empty();)
	{
		val3 = cbuf2.pop();
		std::cout << val3.words.a << " " << val3.words.b << std::endl;
	}


}


