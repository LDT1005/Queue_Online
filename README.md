
# 📦 CourseProject_NhomXX - Hệ thống Quản lý Đơn đặt hàng Trực tuyến

![C++](https://img.shields.io/badge/C++-11-blue.svg)
![Build](https://img.shields.io/badge/build-in%20progress-yellow.svg)
![Status](https://img.shields.io/badge/status-developing-orange.svg)

## 📌 1. Giới thiệu Dự án

Dự án **Quản lý Đơn đặt hàng Trực tuyến** là một C++ Console Application được thiết kế nhằm mô phỏng hệ thống xử lý luồng đơn hàng trong thương mại điện tử.

Hệ thống áp dụng các cấu trúc dữ liệu và thuật toán đã học trong môn Cấu trúc dữ liệu & Giải thuật, đặc biệt sử dụng **Queue (Hàng đợi)** để xử lý đơn hàng chờ duyệt theo nguyên tắc **FIFO (First In, First Out)**.

---

## 🏗️ 2. Kiến trúc & Cấu trúc Dữ liệu

Hệ thống vận hành dựa trên 2 luồng dữ liệu song song trong bộ nhớ RAM và đồng bộ với tệp ngoại vi `.txt`:

- **Queue `choDuyet`**: Chứa các đơn hàng có trạng thái `0` - Chờ phê duyệt. Dữ liệu được thêm vào cuối Queue và xử lý từ đầu Queue theo nguyên tắc FIFO.
- **Linked List `dsDonDaXuLy`**: Chứa các đơn hàng đã được xử lý với trạng thái `1` - Đã duyệt, `2` - Hủy, `3` - Hoàn thành.
- **Mảng động**: Được cấp phát tạm thời bằng `new` và giải phóng bằng `delete[]`, dùng trong chức năng tìm kiếm theo ngày tạo.
- **Quick Sort & Binary Search**: Dùng để sắp xếp và tìm kiếm đơn hàng theo ngày tạo.

---

## 🚀 3. Các Chức năng Chính

1. **Đọc dữ liệu từ file**: Nạp dữ liệu từ file `.txt`, kiểm tra định dạng, trạng thái hợp lệ và mã đơn hàng không được trùng.
2. **Thêm đơn hàng mới**: Kiểm tra dữ liệu đầu vào và thêm đơn mới vào cuối Queue chờ duyệt.
3. **Xóa đơn hàng**: Xóa đơn trong Queue bằng Queue phụ để bảo toàn FIFO; xóa đơn trong List bằng thao tác duyệt và cắt Node.
4. **Xem danh sách đơn hàng**: Hiển thị toàn bộ đơn hàng trong Queue và List.
5. **Xử lý đơn hàng đầu Queue**: Xem trước đơn đầu Queue bằng thao tác Peek/Front, kiểm tra trạng thái nhập hợp lệ, sau đó mới Dequeue và chuyển sang List.
6. **Tìm đơn theo ngày tạo**: Gom dữ liệu sang mảng động, sắp xếp bằng Quick Sort, tìm bằng Binary Search và quét hai chiều để lấy toàn bộ đơn cùng ngày. Quick Sort có độ phức tạp trung bình `O(n log n)`, xấu nhất `O(n²)`.
7. **Lọc đơn theo trạng thái**: Hiển thị danh sách đơn hàng theo trạng thái `0`, `1`, `2`, `3`.
8. **Xem thống kê**: Thống kê tổng số đơn, tổng giá trị đơn hàng và doanh thu thực tế từ đơn hoàn thành.
9. **Ghi file và thoát**: Ghi đè dữ liệu từ RAM xuống file `.txt`, kiểm tra mở file thành công trước khi ghi.

---

## 📂 4. Cấu trúc Thư mục

```text
CourseProject_NhomXX/
├── src/
│   ├── Structure.h
│   ├── Queue.h
│   ├── Queue.cpp
│   ├── Algorithms.h
│   ├── Algorithms.cpp
│   ├── DataProcess.h
│   ├── DataProcess.cpp
│   └── main.cpp
│
├── data/
│   ├── DemoData_NhomXX.txt
│   ├── TestData_100.txt
│   ├── TestData_1000.txt
│   └── TestData_10000.txt
│
├── docs/
│   ├── Report_NhomXX.docx
│   └── Report_NhomXX.pdf
│
├── screenshots/
│   ├── menu.png
│   ├── add-order.png
│   ├── process-order.png
│   ├── search-by-date.png
│   └── statistics.png
│
├── build/
├── README.md
└── .gitignore

```

---

## ⚙️ 5. Hướng dẫn Biên dịch (Compile)

> **Lưu ý quan trọng:** Hệ thống sử dụng cú pháp khởi tạo giá trị mặc định trong struct (`int size = 0;`), do đó bắt buộc phải sử dụng chuẩn **C++11** trở lên để biên dịch.

Mở Terminal/Command Prompt tại thư mục gốc của project và chạy lệnh sau:

```bash
g++ -std=c++11 src/main.cpp src/Queue.cpp src/Algorithms.cpp src/DataProcess.cpp -o build/app

```

---

## 🖥️ 6. Hướng dẫn Chạy Chương trình (Run)

**Đối với hệ điều hành Windows:**

```cmd
.\build\app.exe

```

**Đối với hệ điều hành macOS / Linux:**

```bash
./build/app

```

---

## 🗄️ 7. Định dạng File Dữ liệu Ngoại vi (.txt)

Chương trình đọc và ghi file văn bản theo định dạng quy chuẩn, các trường được phân tách bằng ký tự gạch đứng `|`.

**Định dạng chuẩn:**
`maDonHang|tenKhachHang|ngayTao|tongTien|trangThai`

*Quy ước trạng thái:*

* `0`: Chờ duyệt
* `1`: Đã duyệt
* `2`: Hủy
* `3`: Hoàn thành

**Ví dụ nội dung file (`data/DemoData_NhomXX.txt`):**

```text
DH001|Nguyen Van A|2026-06-15|150000|0
DH002|Tran Thi B|2026-06-16|250000|3
DH003|Le Van C|2026-06-17|120000|1

```

---

## 👥 8. Thành viên Nhóm & Phân công

| Thành viên | Nhiệm vụ Code C++ | Nhiệm vụ Báo cáo & Khác | Phối hợp quan trọng |
| --- | --- | --- | --- |
| **TV1** | `Structure.h`, `Queue.h`, `Queue.cpp` (Cấu trúc nền tảng, Tạo/Xóa/Xem) | Viết Chương 1 & 2, Vẽ sơ đồ luồng dữ liệu | Thống nhất dữ liệu trả về cho TV2 và TV3. Cung cấp API cho TV4. |
| **TV2** | `Algorithms.h`, `Algorithms.cpp` (Tìm kiếm, Quick Sort) | Viết Chương 3 (Thuật toán & Big-O) | Đảm bảo tính đúng đắn thuật toán để TV5 đo thời gian. |
| **TV3** | `DataProcess.h`, `DataProcess.cpp` (Đọc/Ghi file, xử lý thống kê) | Chuẩn bị dữ liệu Test, viết hướng dẫn lưu file | Thống nhất format file `.txt`. Phối hợp với TV4 và TV1. |
| **TV4** | `main.cpp` (Menu, Validation dữ liệu đầu vào) | Viết Bảng Test Cases, chụp ảnh màn hình | Gọi API xử lý và bắt lỗi nhập liệu toàn hệ thống. |
| **TV5** | Chèn `<chrono>` đo thời gian, giải phóng mảng động `delete[]` | Tổng hợp Word, định dạng format, đóng gói | Cập nhật số liệu hiệu năng tìm kiếm tuyến tính vs nhị phân. |