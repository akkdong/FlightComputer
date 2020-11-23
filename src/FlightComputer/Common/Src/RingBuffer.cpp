// RingBuffer.cpp
//

#include <stdint.h>
#include "RingBuffer.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////
//

RingBuffer::RingBuffer()
	: mData(0), mSize(0), mHead(0), mTail(0)
{
}

RingBuffer::RingBuffer(uint8_t * data, uint16_t size)
	: mData(data), mSize(size), mHead(0), mTail(0)
{
}

void RingBuffer::init(uint8_t * data, uint16_t size)
{
	mData = data;
	mSize = size;

	mHead = mTail = 0;
}

int32_t RingBuffer::getBufferCount()
{
	return mSize;
}

int32_t RingBuffer::getDataCount()
{
	return (mHead - mTail) & (mSize - 1);
}

int32_t RingBuffer::isFull()
{
	return ((mHead + 1) & (mSize - 1)) == mTail ? 1 : 0;
}

int32_t	RingBuffer::isEmpty()
{
	return (mHead == mTail) ? 1 : 0;
}

int32_t RingBuffer::push(uint8_t data)
{
	if (isFull())
		return -1;

	mData[mHead] = data;
	mHead = (mHead + 1) & (mSize -1);

	return 0;
}

int32_t RingBuffer::pushBack(uint8_t data)
{
	if (isFull())
		return -1;

	mTail = (mTail == 0) ? (mSize - 1) : (mTail - 1);
	mData[mTail] = data;

	return 0;
}

int32_t RingBuffer::pop()
{
	if (isEmpty())
		return -1;

	int32_t ch = mData[mTail];
	mTail = (mTail + 1) & (mSize -1);

	return ch;
}

int32_t RingBuffer::peek()
{
	if (isEmpty())
		return -1;

	return mData[mTail];
}

void RingBuffer::empty()
{
	mHead = mTail = 0;
}

