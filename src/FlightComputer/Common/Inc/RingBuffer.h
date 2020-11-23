// RingBuffer.h
//

#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

///////////////////////////////////////////////////////////////////////////////////////////////////////
//

class RingBuffer
{
public:
	RingBuffer();
	RingBuffer(uint8_t * data, uint16_t size);

public:
	void				init(uint8_t * data, uint16_t size);

	int32_t				getBufferCount();
	int32_t				getDataCount();

	int32_t				isFull();
	int32_t				isEmpty();

	int32_t				push(uint8_t data);
	int32_t				pushBack(uint8_t data);
	int32_t				pop();
	int32_t				peek();

	void				empty();

private:
	volatile uint8_t *	mData;
	volatile uint16_t	mSize;

	volatile uint16_t	mHead;
	volatile uint16_t	mTail;
};

#endif // __RINGBUFFER_H__
