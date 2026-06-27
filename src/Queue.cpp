#include "Queue.h"

// Khởi tạo Queue an toàn
void initQueue(Queue& q) {
    q.pHead = nullptr;
    q.pTail = nullptr;
    q.size = 0;
}

// Khởi tạo List an toàn
void initList(List& l) {
    l.pHead = nullptr;
    l.pTail = nullptr;
    l.size = 0;
}

// Kiểm tra Queue rỗng (Sửa toán tử = thành ==)
bool isEmptyQueue(const Queue& q) {
    return q.pHead == nullptr;
}

// Kiểm tra List rỗng (Đồng bộ tên hàm với file .h và sửa = thành ==)
bool isEmptyList(const List& l) {
    return l.pHead == nullptr;
}

// Kiểm tra trùng maDonHang (Đồng bộ tên hàm isDuplicateId chuẩn camelCase, sửa lỗi vòng lặp vô hạn)
bool isDuplicateId(const Queue& q, const List& l, string maDonHang) {
    // Duyệt Queue
    Node* pCurr = q.pHead;
    while (pCurr != nullptr) {
        if (pCurr->data.maDonHang == maDonHang) return true; // Sửa toán tử = thành ==
        pCurr = pCurr->pNext; // Sửa từ pNext thành pCurr->pNext
    }
    
    // Duyệt List
    pCurr = l.pHead;
    while (pCurr != nullptr) {
        if (pCurr->data.maDonHang == maDonHang) return true;
        pCurr = pCurr->pNext; // Sửa từ pNext thành pCurr->pNext
    }
    return false;
}

// Thêm đơn hàng vào cuối Queue (FIFO)
void enqueue(Queue& q, DonHang dh) {
    Node* newNode = new Node;
    newNode->data = dh;
    newNode->pNext = nullptr;
    
    if (isEmptyQueue(q)) {
        q.pHead = newNode;
        q.pTail = newNode;
    }
    else {
        q.pTail->pNext = newNode;
        q.pTail = newNode;
    }
    q.size++;
}

// Lấy đơn hàng ra khỏi đầu Queue (Sửa lỗi sai chính tả kiểu dữ liệu Donhang)
bool dequeue(Queue& q, DonHang& dh) {
    if (isEmptyQueue(q)) {
        return false;
    }
    Node* temp = q.pHead;
    dh = temp->data;
    q.pHead = q.pHead->pNext;
    
    if (q.pHead == nullptr) {
        q.pTail = nullptr;
    }
    delete temp; // Giải phóng vùng nhớ để tránh rò rỉ (Memory Leak)
    q.size--;
    return true;
}

// Xem thông tin đơn đầu Queue nhưng không xóa
bool front(const Queue& q, DonHang& dh) {
    if (isEmptyQueue(q)) {
        return false;
    }
    dh = q.pHead->data;
    return true;
}

// Thêm đơn hàng vào cuối List đơn đã xử lý
void addToList(List& l, DonHang dh) {
    Node* pNew = new Node;
    pNew->data = dh;
    pNew->pNext = nullptr;
    
    if (isEmptyList(l)) {
        l.pHead = pNew;
        l.pTail = pNew;
    }
    else {
        l.pTail->pNext = pNew;
        l.pTail = pNew;
    }
    l.size++;
}

// Xóa đơn trong Queue bằng cơ chế Queue phụ (Bảo toàn nguyên tắc FIFO)
bool deleteOrderFromQueue(Queue& q, string maDonHang) {
    if (isEmptyQueue(q)) return false;
    
    Queue qPhu;
    initQueue(qPhu);
    bool found = false;
    DonHang dh;
    
    // Đổ hết sang Queue phụ, chừa node cần xóa ra
    while (!isEmptyQueue(q)) {
        dequeue(q, dh);
        if (dh.maDonHang == maDonHang) {
            found = true; // Bỏ qua node này (chính là hành động xóa)
        }
        else {
            enqueue(qPhu, dh);
        }
    }
    
    // Đổ ngược dữ liệu từ Queue phụ về lại Queue chính để bảo toàn thứ tự ban đầu
    while (!isEmptyQueue(qPhu)) {
        dequeue(qPhu, dh);
        enqueue(q, dh);
    }
    return found;
}

// Xóa đơn trong List bằng phương pháp cô lập và cắt Node
bool deleteOrderFromList(List& l, string maDonHang) {
    if (isEmptyList(l)) return false;
    
    Node* pCurr = l.pHead;
    Node* pPrev = nullptr;
    
    while (pCurr != nullptr) {
        if (pCurr->data.maDonHang == maDonHang) {
            // Nếu node cần xóa nằm ở ngay đầu danh sách
            if (pCurr == l.pHead) {
                l.pHead = l.pHead->pNext;
                if (l.pHead == nullptr) {
                    l.pTail = nullptr;
                }
            }
            // Nếu node nằm ở giữa hoặc cuối danh sách
            else {
                pPrev->pNext = pCurr->pNext;
                if (pCurr == l.pTail) {
                    l.pTail = pPrev;
                }
            }
            delete pCurr; // Giải phóng bộ nhớ node bị cắt
            l.size--;
            return true;
        }
        pPrev = pCurr;
        pCurr = pCurr->pNext;
    }
    return false;
}

// Giải phóng toàn bộ các Node trong Queue
void clearQueue(Queue& q) {
    Node* pCurr = q.pHead;
    while (pCurr != nullptr) {
        Node* pNext = pCurr->pNext;
        delete pCurr;
        pCurr = pNext;
    }
    q.pHead = nullptr;
    q.pTail = nullptr;
    q.size = 0;
}

// Giải phóng toàn bộ các Node trong List
void clearList(List& l) {
    Node* pCurr = l.pHead;
    while (pCurr != nullptr) {
        Node* pNext = pCurr->pNext;
        delete pCurr;
        pCurr = pNext;
    }
    l.pHead = nullptr;
    l.pTail = nullptr;
    l.size = 0;
}