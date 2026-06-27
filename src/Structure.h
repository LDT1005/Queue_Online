#pragma once
#include <string>

using namespace std;

// Cấu trúc Đơn Hàng (Dữ liệu lõi cho hệ thống)
struct DonHang {
    string maDonHang;
    string tenKhachHang;
    string ngayTao;     // Định dạng chuẩn: YYYY-MM-DD
    double tongTien;
    int trangThai;      // 0: Chờ duyệt, 1: Đã duyệt, 2: Hủy, 3: Hoàn thành
};

// Cấu trúc Node danh sách liên kết
struct Node {
    DonHang data;
    Node* pNext = nullptr;
};

// Cấu trúc Queue (Chứa các đơn hàng có trạng thái 0)
struct Queue {
    Node* pHead = nullptr;
    Node* pTail = nullptr;
    int size = 0;
};

// Cấu trúc List (Chứa các đơn hàng có trạng thái 1, 2, 3)
struct List {
    Node* pHead = nullptr;
    Node* pTail = nullptr;
    int size = 0;
};