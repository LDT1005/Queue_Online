#pragma once
#include "Structure.h"
#include "Queue.h"
#include <string>

using namespace std;

// 1. Hàm đọc dữ liệu từ file .txt vào hệ thống (Xóa RAM cũ trước khi nạp)
void readFile(string filename, Queue& choDuyet, List& dsDonDaXuLy);

// 2. Hàm ghi toàn bộ dữ liệu từ RAM ra file .txt (Ghi đè hoàn toàn)
void writeFile(string filename, const Queue& choDuyet, const List& dsDonDaXuLy);

// 3. Hàm hiển thị tất cả đơn hàng hiện có trong hệ thống dưới dạng bảng
void displayAllOrders(const Queue& choDuyet, const List& dsDonDaXuLy);

// 4. Hàm tính toán và hiển thị số liệu thống kê doanh thu, số lượng trạng thái
void calculateStatistics(const Queue& choDuyet, const List& dsDonDaXuLy);