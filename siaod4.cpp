// siaod4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<fstream>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string get2word(string s) {
	if (s == "") { return "";}
	int l = s.find(" ");
	int r = s.find(" ", l + 1);
	return s.substr(l + 1, r - l);
}

bool compare_strings(string str1, string str2) {
	for (int i = 0; i < min(str1.length(), str2.length()); i++) {
		if (tolower(str2[i]) < tolower(str1[i])) {
			return false;
		}
		else if (tolower(str2[i]) > tolower(str1[i])) {
			return true;
		}
	}
	return true;
}
void print_array(string* a,int n) {
	for (int i = 0; i < n;i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
void quick_sort(string* a, int first, int last) {
	int i = first;
	int j = last;
	string pivot = get2word(a[(i + j) / 2]);
	cout << pivot << endl;
	while (i <= j) {
		//print_array(a, j - i+1);
		while (get2word(a[i]).compare(pivot)<0) { i++; }
		while (get2word(a[j]).compare(pivot) > 0) { j--; }
		if (i <= j) {
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	//print_array(a, last-first);
	if (last > i) {
		quick_sort(a, i, last);
	}
	if (first < j) {
		quick_sort(a, first, j+1);
	}
}


void partition(string file1, string file2, string file3, int size, int &lenB, int &lenC) {
	ifstream A(file1);
	ofstream B(file2);
	ofstream C(file3);
	int counter = 0;
	string s = "";
	while (getline(A, s)) {
		if ((counter/size) % 2 == 0) {
			cout << s<<endl;
			B<<s<<endl;
			lenB++;
		}
		else {
			C << s << endl;
			cout << s << endl;
			lenC++;
		}
		counter++;
	}
	cout << counter<<endl;
}

void merge(string file1, string file2, string file3, int size, int& lenB, int& lenC) {
	ofstream A(file1);
	ifstream B(file2);
	ifstream C(file3);
	string s1 = "";
	string s2 = "";
	int counter1 = 0;
	int counter2 = 0;
	if (lenB > 0) { getline(B, s1); }
	if (lenC > 0) { getline(C, s2); }
	while (lenB + lenC > 0) {
		if (counter1 == size && counter2 < size) {
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
			if (compare_strings(get2word(s1), get2word(s2))) {
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
}


void natural_partition(string file1, string file2, string file3, int size, int& lenB, int& lenC) {
	ifstream A(file1);
	ofstream B(file2);
	ofstream C(file3);
	string* buff = new string[size+1];
	int counter = 0;
	string s = "";
	while (getline(A, s)) {
		if (counter % (2*size) < size) {
			buff[counter % (size)] = s;
			if (counter % (size) == size-1 || A.eof()) {
				quick_sort(buff, 0, counter % (size));
				for (int i = 0; i < counter % (size);i++) {
					cout << buff[i] << endl;
					B << buff[i] << endl;
				}
			}
		}
		else if (counter % (2 * size) < 2*size) {
			buff[counter % (size)] = s;
			if (counter % (size) == size - 1 || A.eof()) {
				quick_sort(buff, 0, counter % (size));
				for (int i = 0; i < counter % (size); i++) {
					cout << buff[i] << endl;
					C << buff[i] << endl;
				}
			}
		}
		counter++;
	}
	cout << counter << endl;
}


int main()
{
	int lenB = 0;
	int lenC = 0;
	string A = "C:\\Users\\user\\Desktop\\A.txt";
	string B = "C:\\Users\\user\\Desktop\\B.txt";
	string C = "C:\\Users\\user\\Desktop\\C.txt";
	string* arr = new string[6]{" Vergil "," 2 ", " Light ", " 1 "," Acheron "};
	quick_sort(arr, 0, 4);
	cout << arr[0] << endl;
	print_array(arr, 5);
	//natural_partition(A, B, C, 3, lenB, lenC);
	//for (int i = 0; i <= log2(35) ; i++) {
	//	partition(A, B, C, pow(2.,i),lenB,lenC);
	//	merge(A, B, C, pow(2., i),lenB,lenC);
	//}
	//partition(A, B, C, 1);
	//merge(A, B, C, 1);
	//cout << counterB<<endl;
	//cout << counterC<<endl;
	//A.close();
	//merge("C:\\Users\\user\\Desktop\\A.txt", "C:\\Users\\user\\Desktop\\B.txt", "C:\\Users\\user\\Desktop\\C.txt", i);

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
