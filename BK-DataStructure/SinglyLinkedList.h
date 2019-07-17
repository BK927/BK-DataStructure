#pragma once
#include <cassert>

#include "BaseContainer.h"

namespace bkDS
{
	template<typename T>
	class ListNode
	{
	public:
		ListNode<T>(T& data, ListNode<T>* next = nullptr);
		T data;
		ListNode<T>* next;
	};

	template<typename T>
	inline ListNode<T>::ListNode(T& data, ListNode<T>* next) : data(data), next(next)
	{
	}

	template<typename T>
	class SinglyLinkedList : BaseContainer
	{
	public:
		SinglyLinkedList();
		SinglyLinkedList(T& data);
		SinglyLinkedList(const SinglyLinkedList<T>& rhs);
		~SinglyLinkedList();

		SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& rhs);
		SinglyLinkedList<T> operator+(const SinglyLinkedList<T>& rhs);
		void operator+=(const SinglyLinkedList<T>& rhs);

		T& GetHead();
		T& GetTail();
		T& GetCurrent();
		bool Next();
		void PushBack(T& data);
		void AddFirst(T& data);
		void RemoveFirst();
		void RemoveLast();
		void Clear();

	private:
		ListNode<T>* mCurrent;
		ListNode<T>* mHead;
		ListNode<T>* mTail;
	};

	template<typename T>
	SinglyLinkedList<T>::SinglyLinkedList() : mHead(nullptr), mTail(nullptr), mCurrent(nullptr)
	{
	}

	template<typename T>
	SinglyLinkedList<T>::SinglyLinkedList(T& data)
	{
		mHead = new ListNode<T>(data);
		mTail = mHead;
		mCurrent = mHead;
	}

	template<typename T>
	SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& rhs) : mHead(nullptr), mTail(nullptr)
	{
		ListNode<T>* cursor = rhs.mHead;
		while (!(cursor == nullptr))
		{
			PushBack(cursor->data);
			cursor = cursor->next;
		}
		mCurrent == mHead;

		assert(mSize == rhs.mSize);
	}

	template<typename T>
	SinglyLinkedList<T>::~SinglyLinkedList()
	{
		Clear();
	}

	template<typename T>
	SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& rhs)
	{
		if (mSize > rhs.mSize)
		{
			for (unsigned int i = 0; i < mSize - rhs.mSize; i++)
			{
				RemoveFirst();
			}
			assert(mSize == rhs.mSize);
		}

		ListNode<T>* thisCursor = mHead;
		ListNode<T>* rhsCursor = rhs.mHead;

		for (unsigned int i = 0; i < mSize; i++)
		{
			thisCursor->data = rhsCursor->data;
			thisCursor = rhsCursor->next;
			rhsCursor = rhsCursor->next;
		}
		assert(thisCursor == nullptr);

		while (!(rhsCursor == nullptr))
		{
			PushBack(rhsCursor->data);
			rhsCursor = rhsCursor->next;
		}

		assert(mSize == rhs.mSize);
		mCurrent == mHead;

		return *this;
	}

	template<typename T>
	SinglyLinkedList<T> SinglyLinkedList<T>::operator+(const SinglyLinkedList<T>& rhs)
	{
		SinglyLinkedList<T> sum = SinglyLinkedList<T>();

		ListNode<T>* cursor = mHead;
		while (!(cursor == nullptr))
		{
			sum.PushBack(cursor->data);
			cursor = cursor->next;
		}

		assert(sum.mSize == mSize);

		ListNode<T>* cursor = rhs.mHead;
		while (!(cursor == nullptr))
		{
			sum.PushBack(cursor->data);
			cursor = cursor->next;
		}

		assert(sum.mSize == mSize + rhs.mSize);

		return sum;
	}

	template<typename T>
	void SinglyLinkedList<T>::operator+=(const SinglyLinkedList<T>& rhs)
	{
		ListNode<T>* cursor = rhs.mHead;
		while (!(cursor == nullptr))
		{
			PushBack(cursor->data);
			cursor = cursor->next;
		}
	}

	template<typename T>
	inline T& SinglyLinkedList<T>::GetHead()
	{
		return mHead->data;
	}

	template<typename T>
	inline T& SinglyLinkedList<T>::GetTail()
	{
		return mTail->data;
	}

	template<typename T>
	inline T& SinglyLinkedList<T>::GetCurrent()
	{
		return mCurrent->data;
	}

	template<typename T>
	void SinglyLinkedList<T>::PushBack(T& data)
	{
		if (mTail == nullptr)
		{
			assert(IsEmpty());
			assert(mHead == nullptr);
			mTail = new ListNode<T>(data);
			mHead = mTail;
			mCurrent = mHead;
		}
		else
		{
			mTail->next = new ListNode<T>(data);
			mTail = mTail->next;
		}
		mSize++;
	}

	template<typename T>
	void SinglyLinkedList<T>::AddFirst(T& data)
	{
		mHead = new ListNode<T>(data, mHead);

		if (mTail == nullptr)
		{
			assert(IsEmpty());
			mTail = mHead;
			mCurrent = mHead;
		}

		mSize++;
	}

	template<typename T>
	void SinglyLinkedList<T>::RemoveFirst()
	{
		if (mHead == nullptr)
		{
			assert(IsEmpty());
			assert(mTail == nullptr);
			return;
		}

		if (mHead == mTail)
		{
			assert(mSize == 1);
			assert(mHead->next == nullptr);
			assert(mTail->next == nullptr);
			delete mHead;
			mHead = nullptr;
			mTail = nullptr;
			mCurrent = nullptr;
			mSize--;
			return;
		}

		ListNode<T>* temp = mHead;
		mHead = mHead->next;
		if (mCurrent == temp)
		{
			mCurrent = mHead;
		}
		delete temp;
		mSize--;
	}

	template<typename T>
	void SinglyLinkedList<T>::RemoveLast()
	{
		if (mTail == nullptr)
		{
			assert(IsEmpty());
			assert(mHead == nullptr);
			return;
		}

		if (mHead == mTail)
		{
			assert(mSize == 1);
			assert(mHead->next == nullptr);
			assert(mTail->next == nullptr);
			delete mHead;
			mHead = nullptr;
			mTail = nullptr;
			mCurrent = nullptr;
			mSize--;
			return;
		}

		ListNode<T>* cursor = mHead;
		while (!(cursor->next == mTail))
		{
			cursor = cursor->next;
		}

		if (mCurrent == mTail)
		{
			mCurrent = cursor;
		}

		delete mTail;
		cursor->next == nullptr;
		mTail = cursor;
		mSize--;
	}

	template<typename T>
	void SinglyLinkedList<T>::Clear()
	{
		ListNode<T>* cursor = mHead;
		while (!(cursor == nullptr))
		{
			ListNode<T>* temp = cursor;
			cursor = cursor->next;
			delete temp;
			mSize--;
		}
		mHead = nullptr;
		mTail = nullptr;
		mCurrent = nullptr;
		assert(IsEmpty());
	}

}