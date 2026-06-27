#include "DataProcess.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

// Hàm bổ trợ ẩn: Loại bỏ khoảng trắng thừa ở 2 đầu chuỗi
static string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Hàm bổ trợ ẩn: Kiểm tra tính hợp lệ của ngày tháng (YYYY-MM-DD)
static bool isValidDateInFile(const string& ngay) {
    if (ngay.length() != 10 || ngay[4] != '-' || ngay[7] != '-') return false;
    
    // Kiểm tra định dạng số
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7) {
            if (ngay[i] < '0' || ngay[i] > '9') return false;
        }
    }
    
    // Kiểm tra tính logic cơ bản của tháng và ngày
    int month = stoi(ngay.substr(5, 2));
    int day = stoi(ngay.substr(8, 2));
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    return true;
}

// 1. Hàm đọc dữ liệu từ file .txt
void readFile(string filename, Queue& choDuyet, List& dsDonDaXuLy) {
    ifstream file(filename);
    
    // Kiem tra an toan: Neu file khong ton tai, giu nguyen du lieu cu tren RAM
    if (!file.is_open()) {
        cout << ">> LOI: Khong the mo file '" << filename << "'. Kiem tra lai ten file!" << endl;
        return;
    }

    // CHI XOA RAM KHI CHAC CHAN DA MO FILE THANH CONG
    clearQueue(choDuyet);
    clearList(dsDonDaXuLy);

    string line;
    int lineCount = 0;
    int successCount = 0;

    while (getline(file, line)) {
        lineCount++;
        if (trim(line).empty()) continue; 

        stringstream ss(line);
        string maDH, tenKH, ngayTao, giaTienStr, trangThaiStr;

        if (getline(ss, maDH, '|') &&
            getline(ss, tenKH, '|') &&
            getline(ss, ngayTao, '|') &&
            getline(ss, giaTienStr, '|') &&
            getline(ss, trangThaiStr, '|')) {

            maDH = trim(maDH);
            tenKH = trim(tenKH);
            ngayTao = trim(ngayTao);
            giaTienStr = trim(giaTienStr);
            trangThaiStr = trim(trangThaiStr);

            // Kiem tra format va gia tri logic cua ngay
            if (!isValidDateInFile(ngayTao)) {
                cout << ">> LOI [Dong " << lineCount << "]: Sai dinh dang hoac gia tri ngay YYYY-MM-DD. Bo qua!" << endl;
                continue;
            }

            try {
                size_t posTien, posTT;
                double tongTien = stod(giaTienStr, &posTien);
                int trangThai = stoi(trangThaiStr, &posTT);

                // Kiem tra chuoi chua ky tu rac
                if (posTien != giaTienStr.length() || posTT != trangThaiStr.length()) {
                    throw invalid_argument("Chuoi chua ky tu rac");
                }

                if (tongTien <= 0) {
                    cout << ">> LOI [Dong " << lineCount << "]: Tong tien phai lon hon 0. Bo qua!" << endl;
                    continue;
                }

                if (trangThai < 0 || trangThai > 3) {
                    cout << ">> LOI [Dong " << lineCount << "]: Trang thai " << trangThai << " khong hop le. Bo qua!" << endl;
                    continue;
                }

                if (isDuplicateId(choDuyet, dsDonDaXuLy, maDH)) {
                    cout << ">> CANH BAO [Dong " << lineCount << "]: Ma don '" << maDH << "' da ton tai. Bo qua!" << endl;
                    continue;
                }

                DonHang dh;
                dh.maDonHang = maDH;
                dh.tenKhachHang = tenKH;
                dh.ngayTao = ngayTao;
                dh.tongTien = tongTien;
                dh.trangThai = trangThai;

                if (dh.trangThai == 0) {
                    enqueue(choDuyet, dh);
                } else {
                    addToList(dsDonDaXuLy, dh);
                }
                successCount++;
            }
            catch (const exception& e) {
                cout << ">> LOI PARSING [Dong " << lineCount << "]: Sai kieu so tien hoac trang thai. Bo qua!" << endl;
            }
        } else {
            cout << ">> LOI [Dong " << lineCount << "]: Khong du 5 truong du lieu theo dinh dang |. Bo qua!" << endl;
        }
    }

    file.close();
    cout << "=> Doc file hoan tat. Nap thanh cong: " << successCount << " / " << lineCount << " dong du lieu." << endl;
}

// 2. Hàm ghi dữ liệu ra file .txt
bool writeFile(string filename, const Queue& choDuyet, const List& dsDonDaXuLy) {
    ofstream file(filename, ios::out | ios::trunc);
    
    if (!file.is_open()) {
        cout << ">> LOI NGHIEM TRONG: Khong the mo file '" << filename << "' de ghi du lieu!" << endl;
        cout << ">> He thong giu nguyen du lieu hien tai tren RAM de dam bao an toan." << endl;
        return false; 
    }

    Node* pQueue = choDuyet.pHead;
    while (pQueue != nullptr) {
        file << pQueue->data.maDonHang << "|"
             << pQueue->data.tenKhachHang << "|"
             << pQueue->data.ngayTao << "|"
             << fixed << setprecision(0) << pQueue->data.tongTien << "|" 
             << pQueue->data.trangThai << "\n";
        pQueue = pQueue->pNext;
    }

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
    return true; 
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

    Node* pQueue = choDuyet.pHead;
    while (pQueue != nullptr) {
        cout << left << setw(12) << pQueue->data.maDonHang
             << setw(25) << pQueue->data.tenKhachHang
             << setw(15) << pQueue->data.ngayTao
             << setw(18) << fixed << setprecision(0) << pQueue->data.tongTien;
        cout << "0 (Cho phe duyet)" << endl;
        pQueue = pQueue->pNext;
    }

    Node* pList = dsDonDaXuLy.pHead;
    while (pList != nullptr) {
        cout << left << setw(12) << pList->data.maDonHang
             << setw(25) << pList->data.tenKhachHang
             << setw(15) << pList->data.ngayTao
             << setw(18) << fixed << setprecision(0) << pList->data.tongTien;
        
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

    Node* pQueue = choDuyet.pHead;
    while (pQueue != nullptr) {
        tongGiaTri += pQueue->data.tongTien;
        if (pQueue->data.trangThai == 0) count0++;
        pQueue = pQueue->pNext;
    }

    Node* pList = dsDonDaXuLy.pHead;
    while (pList != nullptr) {
        tongGiaTri += pList->data.tongTien;
        
        if (pList->data.trangThai == 1) count1++;
        else if (pList->data.trangThai == 2) count2++;
        else if (pList->data.trangThai == 3) {
            count3++;
            doanhThuThucTe += pList->data.tongTien; 
        }
        pList = pList->pNext;
    }

    cout << "\nBAO CAO THONG KE HE THONG\n";
    cout << " 1. SO LUONG DON HANG THEO TRANG THAI:\n";
    cout << "    - [Trang thai 0] Cho phe duyet : " << count0 << " don hang.\n";
    cout << "    - [Trang thai 1] Da phe duyet  : " << count1 << " don hang.\n";
    cout << "    - [Trang thai 2] Da Huy bo     : " << count2 << " don hang.\n";
    cout << "    - [Trang thai 3] Da Hoan thanh : " << count3 << " don hang.\n";
    cout << "    => TONG SO DON HANG HE THONG   : " << (count0 + count1 + count2 + count3) << " don hang.\n";
    cout << " -------------------------------------------------------------------------------------\n";
    cout << " 2. CHI SO DOANH THU & GIA TRI DU AN:\n";
    cout << "    - TONG GIA TRI TAT CA DON HANG : " << fixed << setprecision(0) << tongGiaTri << " VND\n";
    cout << "    - DOANH THU THUC TE (Trang thai 3): " << fixed << setprecision(0) << doanhThuThucTe << " VND\n";
    cout << "=======================================================================================\n";
}