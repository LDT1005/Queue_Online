#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>

#include "Structure.h"
#include "Queue.h"
#include "Algorithms.h"
#include "DataProcess.h"

using namespace std;
using namespace std::chrono;

bool isLeapYear(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }

    if (year % 100 == 0)
    {
        return false;
    }

    return year % 4 == 0;
}

bool isValidDate(const string& date)
{
    if (date.length() != 10)
    {
        return false;
    }

    if (date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
        {
            continue;
        }

        if (date[i] < '0' || date[i] > '9')
        {
            return false;
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year <= 0)
    {
        return false;
    }

    if (month < 1 || month > 12)
    {
        return false;
    }

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(year))
    {
        daysInMonth[2] = 29;
    }

    if (day < 1 || day > daysInMonth[month])
    {
        return false;
    }

    return true;
}

string inputDate()
{
    string date;

    do
    {
        cout << "Nhap ngay can do hieu nang (YYYY-MM-DD): ";
        cin >> date;

        if (!isValidDate(date))
        {
            cout << "Ngay khong hop le. Vui long nhap lai dung dinh dang YYYY-MM-DD!" << endl;
        }

    } while (!isValidDate(date));

    return date;
}

void copyAllOrders(const Queue& q, const List& l, DonHang a[])
{
    int index = 0;

    Node* pQueue = q.pHead;
    while (pQueue != nullptr)
    {
        a[index++] = pQueue->data;
        pQueue = pQueue->pNext;
    }

    Node* pList = l.pHead;
    while (pList != nullptr)
    {
        a[index++] = pList->data;
        pList = pList->pNext;
    }
}

void copyFirstN(DonHang source[], DonHang dest[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = source[i];
    }
}

int countAfterBinarySearch(DonHang a[], int n, int foundIndex, const string& ngayCanTim)
{
    if (foundIndex == -1)
    {
        return 0;
    }

    int left = foundIndex;
    while (left >= 0 && a[left].ngayTao == ngayCanTim)
    {
        left--;
    }

    int right = foundIndex;
    while (right < n && a[right].ngayTao == ngayCanTim)
    {
        right++;
    }

    return right - left - 1;
}

int main()
{
    Queue choDuyet;
    List dsDonDaXuLy;

    initQueue(choDuyet);
    initList(dsDonDaXuLy);

    string filename = "TestData_Nhom08.txt";

    readFile(filename, choDuyet, dsDonDaXuLy);

    int totalSize = choDuyet.size + dsDonDaXuLy.size;

    if (totalSize == 0)
    {
        cout << "Khong co du lieu de do hieu nang!" << endl;
        clearQueue(choDuyet);
        clearList(dsDonDaXuLy);
        return 0;
    }

    string ngayCanTim = inputDate();

    DonHang* allData = new DonHang[totalSize];
    copyAllOrders(choDuyet, dsDonDaXuLy, allData);

    int sizes[] = {100, 1000, 10000};
    int numberOfSizes = 3;

    cout << fixed << setprecision(4);

    cout << endl;
    cout << "=== BANG DO HIEU NANG ===" << endl;
    cout << "File du lieu: " << filename << endl;
    cout << "Ngay can tim: " << ngayCanTim << endl;
    cout << "Tong so dong doc duoc: " << totalSize << endl;
    cout << endl;

    cout << left << setw(18) << "Kich thuoc"
         << setw(26) << "Tim tuyen tinh (ms)"
         << setw(34) << "QuickSort + BinarySearch (ms)"
         << setw(18) << "So don tim thay" << endl;

    cout << string(96, '-') << endl;

    for (int i = 0; i < numberOfSizes; i++)
    {
        int n = sizes[i];

        if (n > totalSize)
        {
            continue;
        }

        auto startLinear = high_resolution_clock::now();
        int linearCount = linearSearchByDate(allData, n, ngayCanTim);
        auto endLinear = high_resolution_clock::now();

        double linearTime = duration<double, milli>(endLinear - startLinear).count();

        DonHang* temp = new DonHang[n];
        copyFirstN(allData, temp, n);

        auto startBinary = high_resolution_clock::now();

        quickSort(temp, 0, n - 1);

        int foundIndex = binarySearchByDate(temp, n, ngayCanTim);
        int binaryCount = countAfterBinarySearch(temp, n, foundIndex, ngayCanTim);

        auto endBinary = high_resolution_clock::now();

        double binaryTime = duration<double, milli>(endBinary - startBinary).count();

        cout << left << setw(18) << n
             << setw(26) << linearTime
             << setw(34) << binaryTime
             << setw(18) << binaryCount << endl;

        if (linearCount != binaryCount)
        {
            cout << "Canh bao: Ket qua 2 cach tim khong khop!" << endl;
        }

        delete[] temp;
    }

    delete[] allData;

    clearQueue(choDuyet);
    clearList(dsDonDaXuLy);

    return 0;
}