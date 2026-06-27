#pragma once
#include "Structure.h"

//Khởi tạo queue đầu

void initQueue(Queue& q);
void initList(List& l);

//check empty
bool isEmptyQueue(const Queue& q);
bool isEmptyList(const List& l);

//check trùng maDonHang
bool isDuplicateId(const Queue& q, const List& l, string maDonHang);

//thao tác queue
void enqueue(Queue& q, DonHang dh);
bool dequeue(Queue& q, DonHang& dh);
bool front(const Queue& q, DonHang& dh);

//thao tác list
void addToList(List& l, DonHang dh);

//xóa đơn
bool deleteOrderFromQueue(Queue& q, string maDonHang);
bool deleteOrderFromList(List& l, string maDonHang);

//clear bộ nhớ
void clearQueue(Queue& q);
void clearList(List& l);