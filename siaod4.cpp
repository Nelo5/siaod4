// siaod4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<fstream>
#include <iostream>
#include <string>
using namespace std;

int get2word(string s) {
	if (s == "") { return 10000000000000; }
	int l = s.find(" ");
	int r = s.find(" ", l + 1);
	return stoi(s.substr(l + 1, r - l ));
}

void partition(string file1, string file2, string file3, int size) {
	ifstream A(file1);
	ofstream B(file2);
	ofstream C(file3);
	int counter = 0;
	string s = "";
	while (getline(A, s)) {
		if (counter/size % 2 == 0) {
			B<<s<<endl;
			cout << "b";
		}
		else {
			C<<s<<endl;
			cout << "c";
		}
		counter++;
	}
	A.close();
	B.close();
	C.close();
}

void merge(string file1, string file2, string file3, int size) {
	ofstream A(file1);
	ifstream B(file2);
	ifstream C(file3);
	string s1 = "";
	string s2 = "";
	int counter1 = 0;
	int counter2 = 0;
	getline(B, s1);
	getline(C, s2);
	while (!B.eof() || !C.eof()) {
		if (counter1 == size && counter2 < size) {
			A << s2 << endl;
			counter2++;
			if (!C.eof() && counter2<size) {getline(C, s2);
			}
			else { counter2 = size; }
		}
		else if (counter2 == size && counter1 < size) {
			A << s1 << endl;
			counter1++;
			if (!B.eof() && counter1 < size) {
				getline(B, s1);
			}
			else { counter1 = size; }
			
		}
		else if (counter2 < size && counter1 < size) {

			if (get2word(s1) < get2word(s2)) {
				A << s1 << endl;
				counter1++;
				if (counter1<size) { getline(B, s1); }
			}
			else {
				A << s2 << endl;
				counter2++;
				if (counter2 < size) { getline(C, s2); }
			}
		}
		else if (counter2 == size && counter1 == size) {
			getline(C, s2);
			getline(B, s1);
			if (!B.eof()) { counter1 = 0;}
			if (!C.eof()) { counter2 = 0;};
		}
	}
}


int main()
{
	for (int i = 1; i < 35; i *= 2) {
		partition("C:\\Users\\user\\Desktop\\A.txt", "C:\\Users\\user\\Desktop\\B.txt", "C:\\Users\\user\\Desktop\\C.txt", i);
		merge("C:\\Users\\user\\Desktop\\A.txt", "C:\\Users\\user\\Desktop\\B.txt", "C:\\Users\\user\\Desktop\\C.txt", i);
	}

}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
