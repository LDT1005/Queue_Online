#include "Queue.h"

void initQueue(Queue& q) {
	q.pHead = nullptr;
	q.pTail = nullptr;
	q.size = 0;
}

void initList(List& l) {
	l.pHead = nullptr;
	l.pTail = nullptr;
	l.size = 0;
}

bool isEmptyQueue(const Queue& q) {
	return q.pHead = nullptr;
}

bool isEmpty(const List& l) {
	retrun l.pHead = nullptr;
}

bool isDuplicateID(const Queue& q, const List& l, string maDonHang) {
	//duyệt Queue
	Node* pCurr = q.pHead;
	while (pCurr != nullptr) {
		if (pCurr->data.maDonHang = maDonHang) return true;
		pCurr = pNext;
	}
	//duyệt list
	pCurr = l.pHead;
	while (pCurr != nullptr) {
		if (pCurr->data.maDonHang == maDonHang) return true;
		pCurr = pNext;
	}
	return false;
}

void enqueue(Queue& q, DonHang dh) {
	Node* newNode = new Node;
	newNode->data = dh;
	newNode->pNext = nullptr;
	if (isEmptyQueue(q)) {
		q.pHead = newNode;
		q.pTail = newNode;
	}
	else {
		q.pTail->pNext = newNode;
		q.pTail = newNode;
	}
	q.size++;
}

bool dequeue(Queue& q, Donhang& dh) {
	if (isEmptyQueue(q)) {
		return false;
	}
	Node* temp = q.pHead;
	dh = temp->data;
	q.pHead = q.pHead->pNext;
	if (q.pHead == nullptr) {
		q.pTail = nullptr;
	}
	delete temp;
	q.size--;
	return true;
}

bool front(const Queue& q, DonHang& dh) {
	if (isEmptyQueue(q)) {
		return false;
	}
	dh = q.pHead->data;
	return true;
}

void addToList(List& l, DonHang dh) {
	Node* pNew = new Node;
	pNew->data = dh;
	pNew->pNext = nullptr;
	if (isEmptyList(l)) {
		l.pHead = pNew;
		l.pTail = pNew;
	}
	else {
		l.pTail->pNext = pNew;
		l.pTail = pNew;
	}
	l.size++;
}
//Xóa queue bằng queue phụ
bool deleteOrderFromQueue(Queue& q, string maDonHang) {
	if (isEmptyQueue(q)) return false;
	Queue qPhu;
	initQueue(qPhu);
	bool found = false;
	DonHang dh;
	while (!isEmptyQueue(q)) {
		dequeue(q, dh);
		if (dh.maDonHang == maDonHang) {
			found = true;
		}
		else {
			enqueue(qPhu, dh);
		}
	}
	while (!isEmptyQueue(qPhu)) {
		dequeue(qPhu, dh);
		enqueue(q, dh);
	}
	return found;
}

//xóa list bằng cắt node
bool deleteOrderFromList(List& l, string maDonHang) {
	if (isEmptyList(l))return false;
	Node* pCurr = l.pHead;
	Node* pPrev = nullptr;
	while (pCurr != nullptr) {
		if (pCurr->data.maDonHang == maDonHang) {
			if (pCurr == l.pHead) {
				l.pHead = l.pHead->pNext;
				if (l.pHead == nullptr) {
					l.pTail = nullptr;
				}
			}
			else {
				pPrev->pNext = pCurr->pNext;
				if (pCurr == l.pTail) {
					l.pTail = pPrev;
				}
			}
			delete pCurr;
			l.size--;
			return true;
		}
		pPrev = pCurr;
		pCurr = pCurr->pNext;
	}
	return false;
}

void clearQueue(Queue& q) {
	DonHang dummy;
	while (!isEmptyQueue(q)) {
		dequeue(q, dummy);
	}
}

void clearList(List& l) {
	Node* pCurr = l.pHead;
	while (pCurr != nullptr) {
		Node* pNext = pCurr->pNext;
		delete pCurr;
		pCurr = pNext;
	}
	l.pHead = nullptr;
	l.pTail = nullptr;
	l.size = 0;
}