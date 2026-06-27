#include "Algorithms.h"
#include <iostream>
#include <algorithm> // std::swap

// 1. Hàm so sánh 2 đơn hàng (Đã tối ưu Pass-by-Reference)
bool compareOrder(const DonHang& a, const DonHang& b) {
    if (a.ngayTao != b.ngayTao) {
        return a.ngayTao < b.ngayTao;
    }
    return a.maDonHang < b.maDonHang;
}

// 2. Thuật toán Quick Sort
void quickSort(DonHang a[], int left, int right) {
    if (left >= right) return;

    DonHang pivot = a[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (compareOrder(a[i], pivot)) {
            i++;
        }
        while (compareOrder(pivot, a[j])) {
            j--;
        }

        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(a, left, j);
    }
    if (i < right) {
        quickSort(a, i, right);
    }
}

// 3. Thuật toán Tìm kiếm nhị phân (Binary Search)
int binarySearchByDate(DonHang a[], int n, string ngayCanTim) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid].ngayTao == ngayCanTim) {
            return mid; 
        }

        if (a[mid].ngayTao < ngayCanTim) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }

    return -1;
}

// 4. Thuật toán Tìm kiếm tuyến tính (Linear Search - Trả về count)
int linearSearchByDate(DonHang a[], int n, string ngayCanTim) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].ngayTao == ngayCanTim) {
            count++;
        }
    }
    return count;
}

// 5. Luồng nghiệp vụ chính: Tìm kiếm theo ngày
void searchByDate(const Queue& choDuyet, const List& dsDonDaXuLy, string ngayCanTim) {
    int tongSize = choDuyet.size + dsDonDaXuLy.size;
    if (tongSize == 0) {
        cout << "He thong hien tai khong co don hang nao!" << endl;
        return;
    }

    DonHang* a = new DonHang[tongSize];
    int index = 0;

    Node* pQueue = choDuyet.pHead;
    while (pQueue != NULL) {
        a[index++] = pQueue->data;
        pQueue = pQueue->pNext;
    }

    Node* pList = dsDonDaXuLy.pHead;
    while (pList != NULL) {
        a[index++] = pList->data;
        pList = pList->pNext;
    }

    quickSort(a, 0, tongSize - 1);

    int foundIndex = binarySearchByDate(a, tongSize, ngayCanTim);

    if (foundIndex == -1) {
        cout << "Khong tim thay don hang nao trong ngay: " << ngayCanTim << endl;
    } else {
        cout << "--- DANH SACH DON HANG NGAY " << ngayCanTim << " ---" << endl;
        
        int leftScan = foundIndex;
        while (leftScan >= 0 && a[leftScan].ngayTao == ngayCanTim) {
            leftScan--;
        }
        
        int rightScan = foundIndex;
        while (rightScan < tongSize && a[rightScan].ngayTao == ngayCanTim) {
            rightScan++;
        }
        
        int count = 0;
        for (int i = leftScan + 1; i < rightScan; i++) {
            cout << "Ma DH: " << a[i].maDonHang 
                 << " | Khach: " << a[i].tenKhachHang 
                 << " | Tien: " << a[i].tongTien 
                 << " | Trang thai: " << a[i].trangThai << endl;
            count++;
        }
        cout << "=> Tong cong co " << count << " don hang." << endl;
    }

    delete[] a;
}

// 6. Luồng nghiệp vụ chính: Lọc theo trạng thái
void filterByStatus(const Queue& choDuyet, const List& dsDonDaXuLy, int trangThai) {
    if (trangThai < 0 || trangThai > 3) {
        cout << "Loi: Trang thai khong hop le! (Chi chap nhan 0, 1, 2, 3)" << endl;
        return;
    }

    cout << "--- DANH SACH DON HANG TRANG THAI [" << trangThai << "] ---" << endl;
    int count = 0;

    // Duyệt Queue
    Node* pQueue = choDuyet.pHead;
    while (pQueue != NULL) {
        if (pQueue->data.trangThai == trangThai) {
            // Đã bổ sung in Trang thai
            cout << "Ma DH: " << pQueue->data.maDonHang 
                 << " | Khach: " << pQueue->data.tenKhachHang 
                 << " | Ngay: " << pQueue->data.ngayTao
                 << " | Tien: " << pQueue->data.tongTien 
                 << " | Trang thai: " << pQueue->data.trangThai << endl; 
            count++;
        }
        pQueue = pQueue->pNext;
    }

    // Duyệt List
    Node* pList = dsDonDaXuLy.pHead;
    while (pList != NULL) {
        if (pList->data.trangThai == trangThai) {
            // Đã bổ sung in Trang thai
            cout << "Ma DH: " << pList->data.maDonHang 
                 << " | Khach: " << pList->data.tenKhachHang 
                 << " | Ngay: " << pList->data.ngayTao
                 << " | Tien: " << pList->data.tongTien 
                 << " | Trang thai: " << pList->data.trangThai << endl;
            count++;
        }
        pList = pList->pNext;
    }

    if (count == 0) {
        cout << "Khong co don hang nao o trang thai nay." << endl;
    } else {
        cout << "=> Tong cong co " << count << " don hang." << endl;
    }
}