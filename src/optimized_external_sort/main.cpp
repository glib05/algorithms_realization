#include <iostream>
#include <windows.h>
#include <conio.h>
#include "external_sort.h"
#include "unit_testing_sorting.h"

#define GB 1073741824 // 268 435 456
#define ENTER 13
#define BACKSPACE 8
#define ESCAPE 27


using namespace std;

unsigned long long readNum(const string& var_name);
void doSorting();

int main(int argc, char **argv) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    if (argc == 1){
        doSorting();
    }
    else if (string(argv[1]) == "test"){
        unitTestingSorting();
    }
}

void doSorting(){
    do {
        unsigned long size = readNum("������ ������� �����, �� ������ ������� � ���� \nsize");

        cout<<"\n\n������� ��������� �����\n";
        createFileWithRandomNumbers("A.bin", size);

        cout << "���� �� " << size << " �������� (" << size * sizeof(int)
             << " �����/"<<double(size * sizeof(int))/GB<<"��) �����������. ������� ������ ��������� ����������." << endl;

        auto start_time = chrono::high_resolution_clock::now();

        try {
            ExternalSimpleFileSort("A.bin");
            chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start_time;
            cout << "\n��� ������ ��������� " << elapsed.count() << endl << endl;
            cout << "������� ���� �� �����? \n(��� �������, �������� Enter)" << endl;
            if (getch() == ENTER)
                printFile("A.bin");
        }
        catch (const exception &e) {
            cout << "???????" << e.what();
            getch();
        }
        cout<<"\n\n��� ����� �������� ESCAPE\n"
              "��� ������ ������ �������� ����-��� ���� ������";
    }while(getch() != ESCAPE);
}

unsigned long long readNum(const string& var_name){
    char ch;
    bool exit = false;
    bool correct_input;
    unsigned long long num = 0;

    do {
        system("cls");
        cout << var_name << " = " << num;
        correct_input = false;
        do {
            ch = char(getch());

            if (ch == '1' || ch == '0' || ch == '2' || ch == '3'
                || ch == '4' || ch == '5' || ch == '6' || ch == '7'
                || ch == '8' || ch == '9') {
                correct_input = true;
                num = num*10 + (ch-48);
            }
            else if (ch == BACKSPACE && num != 0){
                correct_input = true;
                num /= 10;
            }
            else if (ch == ENTER && num != 0){
                correct_input = true;
                exit = true;
            }

            if (num != 0)
                if (num > (GB/sizeof(int))*4){
                    system("cls");
                    cout << var_name << " = " << num;
                    cout<<"(����� ��������(������), �������� BACKSPACE ��� ������� ������� �����)";
                    while( getch() != BACKSPACE);
                    correct_input = true;
                    num /= 10;
                }
        }while (!correct_input);
    } while (!exit);

    return num;
}


