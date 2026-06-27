#pragma once
#include <iostream>
#include <string>

using namespace std;

// Hợp đồng dữ liệu 1: Cấu trúc Đơn Hàng (Dữ liệu lõi cho Thuật toán)
struct DonHang {
    string maDonHang;
    string tenKhachHang;
    string ngayTao;     // Định dạng chuẩn: YYYY-MM-DD
    double tongTien;
    int trangThai;      // 0: Chờ duyệt, 1: Đã duyệt, 2: Hủy, 3: Hoàn thành
};

// Hợp đồng dữ liệu 2: Cấu trúc Node (Dành cho Queue/List của TV1)
struct Node {
    DonHang data;
    Node* pNext = NULL; // FIX: Ngăn chặn lỗi con trỏ rác
};

// Hợp đồng dữ liệu 3: Cấu trúc Queue (Chứa đơn trạng thái 0)
struct Queue {
    Node* pHead = NULL; // FIX: Khởi tạo an toàn
    Node* pTail = NULL;
    int size = 0;
};

// Hợp đồng dữ liệu 4: Cấu trúc List (Chứa đơn trạng thái 1, 2, 3)
struct List {
    Node* pHead = NULL; // FIX: Khởi tạo an toàn
    Node* pTail = NULL;
    int size = 0;
};