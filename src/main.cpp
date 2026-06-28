#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "Structure.h"
#include "Queue.h"
#include "DataProcess.h"
#include "Algorithms.h"

using namespace std;

string trimString(const string& str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

string NhapChuoiKhongRong(string thongBao)
{
    string str;
    while (true)
    {
        cout << thongBao;
        getline(cin, str);

        str = trimString(str);

        if (str.empty())
        {
            cout << ">> LOI: Thong tin nay khong duoc de trong! Vui long nhap lai.\n";
        }
        else
        {
            return str;
        }
    }
}

string NhapNgayHopLe()
{
    string ngay;
    while (true)
    {
        cout << "Nhap ngay dat hang (YYYY-MM-DD): ";
        getline(cin, ngay);
        ngay = trimString(ngay);

        bool hopLe = true;

        if (ngay.length() == 10 && ngay[4] == '-' && ngay[7] == '-')
        {
            for (int i = 0; i < 10; i++)
            {
                if (i != 4 && i != 7)
                {
                    if (ngay[i] < '0' || ngay[i] > '9')
                    {
                        hopLe = false;
                    }
                }
            }

            if (hopLe)
            {
                int month = stoi(ngay.substr(5, 2));
                int day = stoi(ngay.substr(8, 2));

                if (month < 1 || month > 12)
                {
                    hopLe = false;
                }

                if (day < 1 || day > 31)
                {
                    hopLe = false;
                }
            }
        }
        else
        {
            hopLe = false;
        }

        if (hopLe)
        {
            return ngay;
        }
        else
        {
            cout << ">> LOI: Sai dinh dang hoac ngay khong ton tai! Vui long nhap dung (VD: 2026-05-10).\n";
        }
    }
}

long long NhapTienHopLe()
{
    long long tien;

    while (true)
    {
        cout << "Nhap tong tien(VND): ";

        if (cin >> tien && tien > 0)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return tien;
        }
        else
        {
            cout << ">> LOI: So tien phai la so duong (> 0) va khong chua chu cai. Nhap lai!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int NhapLuaChonMenu()
{
    int luaChon;

    while (true)
    {
        cout << " Nhap lua chon (0-9): ";

        if (cin >> luaChon && luaChon >= 0 && luaChon <= 9)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return luaChon;
        }
        else
        {
            cout << ">> Vui long nhap 1 con so tu 0 den 9!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int NhapTrangThai(string thongBao, int minVal, int maxVal)
{
    int tt;

    while (true)
    {
        cout << thongBao;

        if (cin >> tt && tt >= minVal && tt <= maxVal)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return tt;
        }
        else
        {
            cout << ">> LOI: Gia tri khong hop le! Vui long nhap tu " << minVal << " den " << maxVal << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void MenuChinh(Queue& choDuyet, List& dsDonDaXuLy)
{
    int luaChon;

    do
    {
        cout << "\n=======================================================\n";
        cout << "      QUAN LY DON DAT HANG TRUC TUYEN    \n";
        cout << "=======================================================\n";
        cout << "1. Doc du lieu tu file\n";
        cout << "2. Them don hang moi vao Queue\n";
        cout << "3. Xoa don hang khoi he thong\n";
        cout << "4. Xem danh sach don hang\n";
        cout << "5. Xu ly don hang dau Queue (Duyet/Huy/Hoan thanh)\n";
        cout << "6. Tim don hang theo ngay tao\n";
        cout << "7. Loc don hang theo trang thai\n";
        cout << "8. Xem thong ke doanh thu\n";
        cout << "9. Ghi du lieu vao file\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "=======================================================\n";

        luaChon = NhapLuaChonMenu();

        switch (luaChon)
        {
        case 1:
        {
            cout << "\n--- DOC DU LIEU TU FILE ---\n";
            string filename = NhapChuoiKhongRong("Nhap ten file de doc: ");
            readFile(filename, choDuyet, dsDonDaXuLy);
            break;
        }

        case 2:
        {
            cout << "\n--- THEM DON HANG MOI ---\n";
            string maDH = NhapChuoiKhongRong("Nhap Ma Don Hang (vd: DH001): ");

            if (isDuplicateId(choDuyet, dsDonDaXuLy, maDH))
            {
                cout << ">> Ma don hang '" << maDH << "' da ton tai trong he thong! Vui long them don khac.\n";
                break;
            }

            string tenKH = NhapChuoiKhongRong("Nhap Ten Khach Hang: ");
            string ngayTao = NhapNgayHopLe();
            long long tongTien = NhapTienHopLe();

            DonHang dh;
            dh.maDonHang = maDH;
            dh.tenKhachHang = tenKH;
            dh.ngayTao = ngayTao;
            dh.tongTien = static_cast<double>(tongTien);
            dh.trangThai = 0;

            enqueue(choDuyet, dh);

            cout << "\n>> Da dua don hang '" << maDH << "' vao Queue cho phe duyet thanh cong!\n";
            break;
        }

        case 3:
        {
            cout << "\n--- XOA DON HANG ---\n";
            string maXoa = NhapChuoiKhongRong("Nhap Ma Don Hang can xoa: ");

            if (deleteOrderFromQueue(choDuyet, maXoa))
            {
                cout << ">> Da xoa thanh cong don hang '" << maXoa << "' khoi Queue cho duyet!\n";
            }
            else if (deleteOrderFromList(dsDonDaXuLy, maXoa))
            {
                cout << ">> Da xoa thanh cong don hang '" << maXoa << "' khoi List da xu ly!\n";
            }
            else
            {
                cout << ">> Khong tim thay don hang co ma '" << maXoa << "' trong he thong!\n";
            }

            break;
        }

        case 4:
        {
            cout << "\n--- XEM DANH SACH DON HANG ---\n";
            displayAllOrders(choDuyet, dsDonDaXuLy);
            break;
        }

        case 5:
        {
            cout << "\n--- XU LY DON HANG DAU QUEUE ---\n";

            DonHang dhFront;

            if (front(choDuyet, dhFront))
            {
                cout << "Thong tin don hang dang cho xu ly:\n";
                cout << " - Ma DH    : " << dhFront.maDonHang << "\n";
                cout << " - Khach    : " << dhFront.tenKhachHang << "\n";
                cout << " - Tong tien: " << fixed << setprecision(0) << dhFront.tongTien << " VND\n";

                int chonTT = NhapTrangThai("Chon thao tac (1: Duyet, 2: Huy, 3: Hoan thanh, 0: Bo qua): ", 0, 3);

                if (chonTT == 0)
                {
                    cout << ">> Da huy thao tac. Don hang van duoc giu nguyen.\n";
                }
                else
                {
                    DonHang dhDaLay;
                    dequeue(choDuyet, dhDaLay);

                    dhDaLay.trangThai = chonTT;
                    addToList(dsDonDaXuLy, dhDaLay);

                    cout << ">> Da cap nhat trang thai don hang '" << dhDaLay.maDonHang << "' va chuyen vao danh sach da xu ly.\n";
                }
            }
            else
            {
                cout << ">> Hien tai khong co don hang nao dang cho duyet!\n";
            }

            break;
        }

        case 6:
        {
            cout << "\n--- TIM KIEM DON HANG THEO NGAY ---\n";
            string ngayTim = NhapNgayHopLe();
            searchByDate(choDuyet, dsDonDaXuLy, ngayTim);
            break;
        }

        case 7:
        {
            cout << "\n--- LOC DON HANG THEO TRANG THAI ---\n";
            cout << "Goi y trang thai: 0 (Cho duyet), 1 (Da duyet), 2 (Huy), 3 (Hoan thanh)\n";

            int ttLoc = NhapTrangThai("Nhap trang thai can loc (0-3): ", 0, 3);
            filterByStatus(choDuyet, dsDonDaXuLy, ttLoc);

            break;
        }

        case 8:
        {
            cout << "\n--- THONG KE DOANH THU ---\n";
            calculateStatistics(choDuyet, dsDonDaXuLy);
            break;
        }

        case 9:
        {
            cout << "\n--- GHI DU LIEU VAO FILE ---\n";
            string filename = NhapChuoiKhongRong("Nhap ten file de ghi: ");

            bool ghiThanhCong = writeFile(filename, choDuyet, dsDonDaXuLy);

            if (ghiThanhCong)
            {
                cout << ">> Ghi file thanh cong. Du lieu da duoc cap nhat vao file.\n";
            }
            else
            {
                cout << ">> Ghi file that bai. Du lieu trong RAM van duoc giu nguyen.\n";
            }

            break;
        }

        case 0:
        {
            clearQueue(choDuyet);
            clearList(dsDonDaXuLy);

            cout << ">> Da don dep RAM.\n";
            break;
        }
        }

    } while (luaChon != 0);
}

int main()
{
    Queue choDuyet;
    List dsDonDaXuLy;

    initQueue(choDuyet);
    initList(dsDonDaXuLy);

    MenuChinh(choDuyet, dsDonDaXuLy);

    return 0;
}