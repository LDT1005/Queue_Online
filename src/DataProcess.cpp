#include "DataProcess.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

// Hàm bổ trợ ẩn: Loại bỏ khoảng trắng thừa và ký tự ngắt dòng ẩn (\r, \n) ở cuối chuỗi
static string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// 1. Hàm đọc dữ liệu từ file .txt
void readFile(string filename, Queue& choDuyet, List& dsDonDaXuLy) {
    // BƯỚC 1: Bắt buộc giải phóng toàn bộ dữ liệu cũ trong RAM trước khi nạp file mới
    clearQueue(choDuyet);
    clearList(dsDonDaXuLy);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Loi: Khong the mo file '" << filename << "' de doc dữ lieu!" << endl;
        return;
    }

    string line;
    int lineCount = 0;
    int successCount = 0;

    // BƯỚC 2: Đọc tuần tự từng dòng
    while (getline(file, line)) {
        lineCount++;
        if (trim(line).empty()) continue; // Bỏ qua dòng trống

        stringstream ss(line);
        string maDH, tenKH, ngayTao, giaTienStr, trangThaiStr;

        // Tách chuỗi theo ký tự gạch đứng '|'
        if (getline(ss, maDH, '|') &&
            getline(ss, tenKH, '|') &&
            getline(ss, ngayTao, '|') &&
            getline(ss, giaTienStr, '|') &&
            getline(ss, trangThaiStr, '|')) {

            // Làm sạch dữ liệu các trường
            maDH = trim(maDH);
            tenKH = trim(tenKH);
            ngayTao = trim(ngayTao);
            giaTienStr = trim(giaTienStr);
            trangThaiStr = trim(trangThaiStr);

            try {
                double tongTien = stod(giaTienStr);
                int trangThai = stoi(trangThaiStr);

                // Kiểm tra tính hợp lệ của trạng thái
                if (trangThai < 0 || trangThai > 3) {
                    cout << "Loi [Dong " << lineCount << "]: Trang thai " << trangThai << " khong hop le (Chi nhan 0->3). Bo qua bản ghi!" << endl;
                    continue;
                }

                // Kiểm tra tính duy nhất của mã đơn hàng trong toàn bộ hệ thống
                // Lưu ý: Tên hàm gốc trong file Queue.cpp của TV1 bị sai hoa thường (isDuplicateID), ta gọi đúng theo file của TV1.
                if (isDuplicateId(choDuyet, dsDonDaXuLy, maDH)) {
                    cout << "Canh bao [Dong " << lineCount << "]: Ma don hang '" << maDH << "' da ton tai trong he thong. Bo qua dong nay!" << endl;
                    continue;
                }

                // Đóng gói dữ liệu vào struct DonHang
                DonHang dh;
                dh.maDonHang = maDH;
                dh.tenKhachHang = tenKH;
                dh.ngayTao = ngayTao;
                dh.tongTien = tongTien;
                dh.trangThai = trangThai;

                // Phân luồng đổ dữ liệu vào cấu trúc tương ứng
                if (dh.trangThai == 0) {
                    enqueue(choDuyet, dh);
                } else {
                    addToList(dsDonDaXuLy, dh);
                }
                successCount++;
            }
            catch (const exception& e) {
                cout << "Loi Parsing [Dong " << lineCount << "]: Sai dinh dang kieu so (Tong tien/Trang thai). Bo qua bản ghi!" << endl;
            }
        } else {
            cout << "Loi [Dong " << lineCount << "]: Khong du 5 truong du lieu theo dinh dang chuẩn. Bo qua!" << endl;
        }
    }

    file.close();
    cout << "=> Doc file hoan tat. Nap thanh cong: " << successCount << " / " << lineCount << " dong dữ lieu." << endl;
}

// 2. Hàm ghi dữ liệu ra file .txt
void writeFile(string filename, const Queue& choDuyet, const List& dsDonDaXuLy) {
    // Mở file ở chế độ ghi đè (ios::trunc), tuyệt đối không dùng ios::app
    ofstream file(filename, ios::out | ios::trunc);
    
    // Kiểm tra an toàn: Nếu mở file thất bại (bị khóa, lỗi quyền), giữ nguyên RAM, báo lỗi, không tắt app
    if (!file.is_open()) {
        cout << "Loi nghiem trong: Khong the mo file '" << filename << "' de ghi dữ lieu!" << endl;
        cout << "He thong giữ nguyen du lieu hien tai tren RAM de dam bao an toan." << endl;
        return;
    }

    // Ghi dữ liệu từ Queue choDuyet trước (Các đơn chờ duyệt - trạng thái 0)
    Node* pQueue = choDuyet.pHead;
    while (pQueue != nullptr) {
        file << pQueue->data.maDonHang << "|"
             << pQueue->data.tenKhachHang << "|"
             << pQueue->data.ngayTao << "|"
             << fixed << setprecision(0) << pQueue->data.tongTien << "|" // Tránh xuất dạng số e+
             << pQueue->data.trangThai << "\n";
        pQueue = pQueue->pNext;
    }

    // Ghi tiếp dữ liệu từ List dsDonDaXuLy (Các đơn trạng thái 1, 2, 3)
    Node* pList = dsDonDaXuLy.pHead;
    while (pList != nullptr) {
        file << pList->data.maDonHang << "|"
             << pList->data.tenKhachHang << "|"
             << pList->data.ngayTao << "|"
             << fixed << setprecision(0) << pList->data.tongTien << "|"
             << pList->data.trangThai << "\n";
        pList = pList->pNext;
    }

    file.close();
    cout << "=> Ghi va dong bo du lieu ra file '" << filename << "' thanh cong!" << endl;
}

// 3. Hàm hiển thị toàn bộ danh sách đơn hàng
void displayAllOrders(const Queue& choDuyet, const List& dsDonDaXuLy) {
    int tongSize = choDuyet.size + dsDonDaXuLy.size;
    if (tongSize == 0) {
        cout << "He thong trong, khong co don hang nao de hien thi!" << endl;
        return;
    }

    cout << "\nDANH SACH ALL DON HANG\n";
    cout << left << setw(12) << "Ma Don" 
         << setw(25) << "Ten Khach Hang" 
         << setw(15) << "Ngay Tao" 
         << setw(18) << "Tong Tien (VND)" 
         << "Trang Thai" << endl;
    cout << "----------------------------------------------------------------------------------------------------------\n";

    // In các đơn trong Queue chờ duyệt trước
    Node* pQueue = choDuyet.pHead;
    while (pQueue != nullptr) {
        cout << left << setw(12) << pQueue->data.maDonHang
             << setw(25) << pQueue->data.tenKhachHang
             << setw(15) << pQueue->data.ngayTao
             << setw(18) << fixed << setprecision(0) << pQueue->data.tongTien;
        cout << "0 (Cho phe duyet)" << endl;
        pQueue = pQueue->pNext;
    }

    // In tiếp các đơn đã xử lý trong List
    Node* pList = dsDonDaXuLy.pHead;
    while (pList != nullptr) {
        cout << left << setw(12) << pList->data.maDonHang
             << setw(25) << pList->data.tenKhachHang
             << setw(15) << pList->data.ngayTao
             << setw(18) << fixed << setprecision(0) << pList->data.tongTien;
        
        // Hiện text trực quan theo mã trạng thái
        if (pList->data.trangThai == 1) cout << "1 (Da duyet)";
        else if (pList->data.trangThai == 2) cout << "2 (Huy)";
        else if (pList->data.trangThai == 3) cout << "3 (Hoan thanh)";
        
        cout << endl;
        pList = pList->pNext;
    }
    cout << "==========================================================================================================\n";
    cout << "=> Tong cong: " << tongSize << " don hang dang luu tru tren RAM.\n";
}

// 4. Hàm thống kê dữ liệu
void calculateStatistics(const Queue& choDuyet, const List& dsDonDaXuLy) {
    double tongGiaTri = 0;
    double doanhThuThucTe = 0;
    int count0 = 0, count1 = 0, count2 = 0, count3 = 0;

    // Duyệt qua Queue chờ phê duyệt
    Node* pQueue = choDuyet.pHead;
    while (pQueue != nullptr) {
        tongGiaTri += pQueue->data.tongTien;
        if (pQueue->data.trangThai == 0) count0++;
        pQueue = pQueue->pNext;
    }

    // Duyệt qua List đã xử lý
    Node* pList = dsDonDaXuLy.pHead;
    while (pList != nullptr) {
        tongGiaTri += pList->data.tongTien;
        
        if (pList->data.trangThai == 1) count1++;
        else if (pList->data.trangThai == 2) count2++;
        else if (pList->data.trangThai == 3) {
            count3++;
            doanhThuThucTe += pList->data.tongTien; // Doanh thu thực tế chỉ tính đơn "Hoàn thành"
        }
        pList = pList->pNext;
    }

    // Xuất báo cáo thống kê ra màn hình Console
    cout << "\nBAO CAO THONG KE HE THONG\n";
    cout << " 1. SỐ LƯỢNG ĐƠN HÀNG THEO TRẠNG THÁI:\n";
    cout << "    - [Trang thai 0] Cho phe duyet : " << count0 << " don hang.\n";
    cout << "    - [Trang thai 1] Da phe duyet  : " << count1 << " don hang.\n";
    cout << "    - [Trang thai 2] Da Huy bo     : " << count2 << " don hang.\n";
    cout << "    - [Trang thai 3] Da Hoan thanh : " << count3 << " don hang.\n";
         cout << "    => TONG SO DON HANG HE THONG   : " << (count0 + count1 + count2 + count3) << " don hang.\n";
    cout << " -------------------------------------------------------------------------------------\n";
    cout << " 2. CHỈ SỐ DOANH THU & GIÁ TRỊ DỰ ÁN:\n";
    cout << "    - TONG GIA TRI TAT CA DON HANG : " << fixed << setprecision(0) << tongGiaTri << " VND\n";
    cout << "    - DOANH THU THỰC TẾ (Trang thai 3): " << fixed << setprecision(0) << doanhThuThucTe << " VND\n";
    cout << "=======================================================================================\n";
}