#pragma once
#include "Structure.h"
#include <string>

using namespace std;

// Hàm so sánh 2 đơn hàng (Ưu tiên: ngayTao -> maDonHang)
// Sử dụng tham chiếu hằng (const &) để tránh copy dữ liệu gây chậm Quick Sort
bool compareOrder(const DonHang& a, const DonHang& b);

// Thuật toán sắp xếp Quick Sort (Sắp xếp tăng dần theo ngày tạo)
void quickSort(DonHang a[], int left, int right);

// Thuật toán Tìm kiếm nhị phân theo Ngày tạo
int binarySearchByDate(DonHang a[], int n, string ngayCanTim);

// Tìm kiếm tuyến tính theo ngày tạo, TRẢ VỀ SỐ LƯỢNG đơn hàng tìm thấy.
// Hàm này phục vụ riêng cho chức năng đo lường hiệu năng của Thành viên 5.
int linearSearchByDate(DonHang a[], int n, string ngayCanTim);

// Luồng nghiệp vụ chính: Tìm kiếm đơn hàng theo ngày tạo trong toàn hệ thống
void searchByDate(const Queue& choDuyet, const List& dsDonDaXuLy, string ngayCanTim);

// Luồng nghiệp vụ chính: Lọc đơn hàng theo trạng thái
void filterByStatus(const Queue& choDuyet, const List& dsDonDaXuLy, int trangThai);