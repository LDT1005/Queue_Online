#pragma once

#include <iostream>
#include <string>

using namespace std;

struct DonHang
{
    string maDonHang;
    string tenKhachHang;
    string ngayTao;
    double tongTien;
    int trangThai; //0, 1, 2, 3 - chờ duyệt, đã duyệt, hủy, hoàn thành
};

struct Node {
    DonHang data;
    Node* pNext;
};

struct Queue
{
    Node* pHead;
    Node* pTail;
    int size;
};
struct List
{
    Node* pHead;
    Node* pTail;
    int size;
};