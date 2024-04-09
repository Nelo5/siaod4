// siaod4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <chrono> 
using namespace std;

string get2word(string s) {
	if (s == "") { return "";}
	int l = s.find(" ");
	int r = s.find(" ", l + 1);
	return s.substr(l + 1, r - l);
}

void quick_sort(string* a, int first, int last) {
	int i = first;
	int j = last;
	string pivot = get2word(a[(i + j) / 2]);
	while (i <= j) {
		while (get2word(a[i]).compare(pivot)<0) { i++; }
		while (get2word(a[j]).compare(pivot) > 0) { j--; }
		if (i <= j) {
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	if (last > i) {quick_sort(a, i, last);}
	if (first < j) {quick_sort(a, first, j);}
}


void partition(string file1, string file2, string file3, int size, int &lenB, int &lenC) {
	ifstream A(file1);
	ofstream B(file2);
	ofstream C(file3);
	int counter = 0;
	string s = "";
	while (getline(A, s)) {
		if ((counter/size) % 2 == 0) {
			B<<s<<endl;
			lenB++;
		}
		else {
			C << s << endl;
			lenC++;
		}
		counter++;
	}
	A.close();
	B.close();
	C.close();
}

void merge(string file1, string file2, string file3, int size, int& lenB, int& lenC) {
	ofstream A(file1);
	ifstream B(file2);
	ifstream C(file3);
	string s1 = "";
	string s2 = "";
	int counter1 = 0;
	int counter2 = 0;
	getline(B, s1);
	getline(C, s2);
	while (lenB + lenC > 0) {
		if (lenB == 0) {
			A << s2 << endl;
			lenC--;
			getline(C, s2);
		}
		else if (lenC == 0) {
			A << s1 << endl;
			lenB--;
			getline(B, s1);
		}
		else if (counter1 == size && counter2 < size) {
			A << s2 << endl;
			counter2++;
			lenC--;
			getline(C, s2);
		}
		else if (counter2 == size && counter1 < size) {
			A << s1 << endl;
			counter1++;
			lenB--;
			getline(B, s1);
		}
		else if (counter2 == size && counter1 == size) {
			counter1 = 0;
			counter2 = 0;
		}
		else if (counter1 < size && counter2 < size) {
			if (get2word(s1).compare (get2word(s2))<0) {
				A << s1 << endl;
				counter1++;
				lenB--;
				getline(B, s1);
			}
			else {
				A << s2 << endl;
				counter2++;
				lenC--;
				getline(C, s2);
			}
		}
	}
	A.close();
	B.close();
	C.close();
}


void prenatural_partition(string file1, string file2, string file3, int size) {
	fstream A(file1, ios::in);
	fstream B(file2, ios::out);
	fstream C(file3, ios::out);
	string* buff = new string[size];
	int counter = 0;
	bool Bf = true;
	bool Cf = false;
	string s = "";
	while (getline(A, s)) {
		if (counter % size < size) {
			buff[counter % size] = s;
			if (counter % size == size - 1 || A.rdstate()) {
				quick_sort(buff, 0, counter % (size));
				for (int i = 0; i <= counter%size; i++) {
					if (Bf) { B << buff[i] << endl; }
					if (Cf) { C << buff[i] << endl; }
				}
				swap(Bf, Cf);
			}
		}
		counter++;
	}
	A.close();
	B.close();
	C.close();
	A.open(file1, ios::out);
	B.open(file2, ios::in);
	C.open(file3, ios::in);
	getline(B, s);
	A << s;
	while (getline(B, s)) { A << endl << s; }
	while (getline(C, s)) { A << endl << s; }
	A.close();
	B.close();
	C.close();
}

void natural_partition(string file1, string file2, string file3, int& lenB, int& lenC){
	fstream A(file1, ios::in );
	fstream B(file2, ios::out);
	fstream C(file3, ios::out);
	string cur = "";
	string prev = "";
	bool Bf = true;
	bool Cf = false;
	while (getline(A, cur)) {
		if (get2word(cur).compare(get2word(prev))<0) {
			swap(Bf, Cf);
		}
		if (Cf) { C << cur << endl; lenC++; }
		if (Bf) { B << cur << endl; lenB++; }
		prev = cur;
	}
	A.close();
	B.close();
	C.close();
}

void natural_merge(string file1, string file2, string file3, int& lenB, int& lenC) {
	fstream A(file1, ios::out);
	fstream B(file2, ios::in);
	fstream C(file3, ios::in);
	string cur1 = "";
	string prev1 = "";
	string cur2 = "";
	string prev2 = "";
	bool Bf = true;
	bool Cf = true;
	getline(B, cur1);
	getline(C, cur2);
	while (lenB + lenC > 0) {
		if (get2word(cur1).compare(get2word(prev1)) < 0) { Bf = false; }
		if (get2word(cur2).compare(get2word(prev2)) < 0) { Cf = false; }
		if (!Bf && !Cf) { Bf = true; Cf = true; prev1 = ""; prev2 = ""; }
		if (lenB == 0) {
			A << cur2 << endl;
			lenC--;
			getline(C, cur2);
		}
		else if (lenC == 0) {
			A << cur1 << endl;
			lenB--;
			getline(B, cur1);
		}
		else if (Bf && Cf) {
			if (get2word(cur1).compare(get2word(cur2))<0) {
				A << cur1 << endl;
				lenB--;
				prev1 = cur1;
				getline(B, cur1);
			}
			else {
				A << cur2 << endl;
				lenC--;
				prev2 = cur2;
				getline(C, cur2);
			}
		}
		else if (Bf) {
			A << cur1 << endl;
			lenB--;
			prev1 = cur1;
			getline(B, cur1);
		}
		else if (Cf) {
			A << cur2 << endl;
			lenC--;
			prev2 = cur2;
			getline(C, cur2);
		}
	}
	A.close();
	B.close();
	C.close();
}

void mergeSort(string file1, string file2, string file3) {
	auto start = chrono::system_clock::now();
	int lenB = 0;
	int lenC = 0;
	int size = 1;
	while (true) {
		partition(file1, file2, file3, size, lenB, lenC);
		if (lenC == 0) {
			merge(file1, file2, file3, size, lenB, lenC);
			auto end = chrono::system_clock::now();
			cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " - ms\n";
			return;
		}
		merge(file1, file2, file3, size, lenB, lenC);
		size *= 2;
	}
}

void naturalMergeSort(string file1, string file2, string file3, int size) {
	auto start = chrono::system_clock::now();
	int lenB = 0;
	int lenC = 0;
	prenatural_partition(file1, file2, file3, size);
	while (true) {
		natural_partition(file1, file2, file3, lenB, lenC);
		if (lenC == 0) {
			natural_merge(file1, file2, file3, lenB, lenC);
			auto end = chrono::system_clock::now();
			cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " - ms\n";
			return;
		}
		natural_merge(file1, file2, file3, lenB, lenC);
	}

}


int main()
{
	string A = "C:\\Users\\user\\Desktop\\A.txt";
	string B = "C:\\Users\\user\\Desktop\\B.txt";
	string C = "C:\\Users\\user\\Desktop\\C.txt";
	//mergeSort(A, B, C);
	naturalMergeSort(A, B, C, 36);
	
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
