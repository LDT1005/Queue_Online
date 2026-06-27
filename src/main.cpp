#include <iostream>
#include <string>
#include <limits>

using namespace std;

string NhapChuoiKhongRong(string thongBao) {
    string str;
    while (true) {
        cout << thongBao;
        getline(cin, str);

        while (str.length() > 0 && str[0] == ' ') str.erase(0, 1);

        if (str.empty()) {
            cout << ">> LOI: Thong tin nay khong duoc de trong! Vui long nhap lai.\n";
        }
        else {
            return str;
        }
    }
}

string NhapNgayHopLe() {
    string ngay;
    while (true) {
        cout << "Nhap ngay dat hang (YYYY-MM-DD, vd: 2024-05-10): ";
        getline(cin, ngay);

        if (ngay.length() == 10 && ngay[4] == '-' && ngay[7] == '-') {
            return ngay;
        }
        else {
            cout << ">> LOI: Sai dinh dang ngay! Vui long nhap dung chuan (VD: 2024-05-10).\n";
        }
    }
}

long long NhapTienHopLe() {
    long long tien;
    while (true) {
        cout << "Nhap tong tien (VND): ";
        if (cin >> tien && tien >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return tien;
        }
        else {
            cout << ">> LOI: So tien phai la so duong va khong chua chu cai. Nhap lai!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}

int NhapLuaChonMenu() {
    int luaChon;
    while (true) {
        cout << "Moi ban nhap lua chon (1-9): ";
        if (cin >> luaChon && luaChon >= 1 && luaChon <= 9) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return luaChon;
        }
        else {
            cout << ">> LOI: Vui long nhap 1 con so tu 1 den 9!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


void MenuChinh() {


    int luaChon;
    do {
        cout << "\n=======================================================\n";
        cout << "      QUAN LY DON DAT HANG TRUC TUYEN (QUEUE & LIST)   \n";
        cout << "=======================================================\n";
        cout << "1. Doc du lieu tu file (TV 3)\n";
        cout << "2. Them don hang moi vao Queue (TV 1 & 4)\n";
        cout << "3. Xoa don hang khoi he thong (TV 1)\n";
        cout << "4. Xem danh sach don hang (TV 1)\n";
        cout << "5. Xu ly don hang dau Queue (Duyet/Huy) (TV 1)\n";
        cout << "6. Tim don hang theo ngay (TV 2)\n";
        cout << "7. Loc don hang theo trang thai (TV 2)\n";
        cout << "8. Xem thong ke doanh thu (TV 3)\n";
        cout << "9. Ghi du lieu vao file & Thoat (TV 3)\n";
        cout << "=======================================================\n";

        luaChon = NhapLuaChonMenu(); 

        switch (luaChon) {
        case 1:
            cout << "\n--- BAN CHON: DOC DU LIEU TU FILE ---\n";
            cout << ">> Tinh nang se duoc tich hop boi Thanh vien 3.\n";
            break;

        case 2: {
            cout << "\n--- BAN CHON: THEM DON HANG MOI ---\n";

            string maDH = NhapChuoiKhongRong("Nhap Ma Don Hang (vd: DH001): ");
            string tenKH = NhapChuoiKhongRong("Nhap Ten Khach Hang: ");
            string sdt = NhapChuoiKhongRong("Nhap So Dien Thoai: ");
            string ngayTao = NhapNgayHopLe();
            long long tongTien = NhapTienHopLe();
            string trangThai = "Cho duyet";

            cout << "\n>> Da nhap thanh cong thong tin cho Ma DH: " << maDH << "\n";
            break;
        }

        case 3: {
            cout << "\n--- BAN CHON: XOA DON HANG ---\n";
            string maXoa = NhapChuoiKhongRong("Nhap Ma Don Hang can xoa: ");
            cout << ">> Tinh nang xoa se tich hop boi Thanh vien 1.\n";
            break;
        }

        case 4:
            cout << "\n--- BAN CHON: XEM DANH SACH DON HANG ---\n";

            break;

        case 5:
            cout << "\n--- BAN CHON: XU LY DON HANG DAU QUEUE ---\n";
            break;

        case 6: {
            cout << "\n--- BAN CHON: TIM KIEM DON HANG THEO NGAY ---\n";
            string ngayTim = NhapNgayHopLe(); 
            break;
        }

        case 7:
            cout << "\n--- BAN CHON: LOC DON HANG THEO TRANG THAI ---\n";
            break;

        case 8:
            cout << "\n--- BAN CHON: THONG KE DOANH THU ---\n";
            break;

        case 9:
            cout << "\n--- BAN CHON: GHI FILE VA THOAT ---\n";
            cout << ">> Chuong trinh dang luu du lieu... Tam biet!\n";
            break;
        }
    } while (luaChon != 9);
}

int main() {
    MenuChinh();
    return 0;
}