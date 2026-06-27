#pragma once

#include "Structure.h"

// Khởi tạo an toàn cho Queue và List ban đầu
void initQueue(Queue& q);
void initList(List& l);

// Kiểm tra rỗng (Ngăn chặn lỗi truy xuất vùng nhớ)
bool isEmptyQueue(const Queue& q);
bool isEmptyList(const List& l);

// Kiểm tra tính duy nhất của mã đơn hàng trong toàn bộ hệ thống
bool isDuplicateId(const Queue& q, const List& l, string maDonHang);

// Thao tác với Queue (Dành cho đơn hàng trạng thái 0: Chờ duyệt)
void enqueue(Queue& q, DonHang dh);
bool dequeue(Queue& q, DonHang& dh);
bool front(const Queue& q, DonHang& dh);

// Thao tác với List (Dành cho đơn hàng đã xử lý: trạng thái 1, 2, 3)
void addToList(List& l, DonHang dh);

// Xóa đơn hàng khỏi hệ thống
bool deleteOrderFromQueue(Queue& q, string maDonHang);
bool deleteOrderFromList(List& l, string maDonHang);

// Dọn dẹp, giải phóng toàn bộ bộ nhớ (Chống Memory Leak)
void clearQueue(Queue& q);
void clearList(List& l);