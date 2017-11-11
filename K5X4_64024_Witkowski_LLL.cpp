#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <time.h>
#include <boost/multiprecision/cpp_int.hpp>


using namespace boost::multiprecision;
using namespace boost::math;
using namespace std;
 int N = 11;
 int p = 3;
 int q = 97;


long double Iloczyn_Skalarny(vector<long double> &a, vector<long double> &b);
vector <long double> Odejmowanie_Wektora(vector <long double> &a, vector < long double> &b, long double q);
long double max(long double a, long double b);
void show_vector(vector<long double> x);
void show_matrix(vector < vector <long double> > &matrix);
void LLL(vector < vector <long double> > &base);
vector <vector <long double> > Ortogonalizacja(vector<vector<long double> > &base, vector<vector<long double> > &mi);
vector <int> Multi_Polynomials(vector< int> left, vector<int> right, int mod);
bool EqualPolynomials(vector<int> left, vector<int> right);
int congruence(int a, int b, int mod);
vector <int> Scalar_Vector_Multiplication(int scalar, vector<int> &vek);
void CenterLift(vector<int> &vek, int mod);

void show_vector(vector<cpp_int> vector);
int convert(int n, vector<int> &cont);
cpp_int Szybkie_pot(int a, int n);
cpp_int Generuj_BigInteger(int n);

cpp_int Iloczyn_Skalarny(vector<cpp_int> &a, vector<cpp_int> &b);
vector <cpp_int> Odejmowanie_Wektora(vector <cpp_int> &a, vector < cpp_int> &b, cpp_int m);
vector <cpp_int> Generuj_Vector(int rozmiar, int n_bitowa_liczba);
void GL(vector <cpp_int> &v1, vector<cpp_int> &v2);
cpp_int mod(cpp_int a, cpp_int b);
cpp_int boost_round(cpp_int a, cpp_int b);
int main() {
    srand(time(NULL));
	cout << "Matematyka konkretna 2017\nPawel Witkowski, indeks 64024\nK5X4S1\n\n\n" << endl;
	cout << "1. Generuj BigInteger\n2. Algorytm redukcji bazy G-L\n3. Algorytm redukcji bazy LLL" << endl;
	int mode = 0;
	cin >> mode;
	switch (mode) {
	case 1:
	{
		cout << "Podaj rozmiar liczby, w bitach, jaka ma zostac wygenerowana." << endl;
		int size;
		cin >> size;
		cpp_int BigInteger = Generuj_BigInteger(size);
		cout << BigInteger << endl;;
		break;
	}
	case 2: {
		cout << "Czy chcesz wygenerowaæ wektory losowo(1) czy recznie(2)?" << endl;
		int mode2 = 0;
		cin >> mode2;
		vector <cpp_int> v1, v2;
		if (mode2 == 1) {
			cout << "Podaj jakiej wielkosci maja byc liczby w wektorach. Rozmiar podawany w bitach." << endl;
			int size;
			cin >> size;
			v1 = Generuj_Vector(2, size);
			v2 = Generuj_Vector(2, size);
		}
		else if (mode2 == 2) {
			cout << "Pierwszy wektor: " << endl;
			for (int i = 0; i < 2; i++) {
				cpp_int temp;
				cin >> temp;
				v1.push_back(temp);
			}
			for (int i = 0; i < 2; i++) {
				cpp_int temp;
				cin >> temp;
				v2.push_back(temp);
			}

		}
		else {
			cout << "Zly tryb!" << endl;
			break;
		}
		show_vector(v1);
		show_vector(v2);
		GL(v1, v2);
		show_vector(v1);
		show_vector(v2);
		break;
	}
	case 3:

		vector<vector<long double> > matrix;
		cout << "Czy chcesz zredukowac baze(1) czy zlamac NTRU(2)?" << endl;
		int mode2 = 0;
		cin >> mode2;
		if (mode2 == 1) {
            cout << "Podaj rozmiar macierzy" << endl;
            int size;
            cin >> size;
            cout << "Czy chcesz samemu wprowadzic dane(1) czy wygenerowac baze losowo(2)?" << endl;
            int mode3=0;
            cin>>mode3;
            if (mode3==1){
                for (int i = 0; i < size; i++) {
                    vector<long double> temp;
                    cout << i + 1 << " wektor: " << endl;
                    for (int j = 0; j < size; j++) {
                        long double a;
                        cin >> a;
                        temp.push_back(a);
                    }
                    matrix.push_back(temp);
                }
            }else if (mode3==2){
                cout << "Liczby beda z przedzialu <-d,d>, podaj d"<<endl;
                int d;
                cin >> d;
                for (int i = 0; i < size; i++) {
                    vector<long double> temp;
                    for (int j = 0; j < size; j++) {
                        long double a;
                        a = rand()%(2*d) - d;
                        temp.push_back(a);
                    }
                    matrix.push_back(temp);
                }
            }
			show_matrix(matrix);
			LLL(matrix);
			show_matrix(matrix);
		}
		else if (mode2 == 2) {
			vector<int>h, e;
			vector <int> f, g, Fp;
			cout << "Czy chcesz sam wprowadzic N,p,q,h(x),e(x) (1) czy skorzystac z przykladu z zajec(2)?" << endl;
			int mode3 = 0;
			cin >> mode3;
			if (mode3 == 1) {
				cout << "Podaj N" << endl;
				cin >> N;
				cout << "Podaj p" << endl;
				cin >> p;
				cout << "Podaj q" << endl;
				cin >> q;
				cout << "Wprowadz klucz publiczny, wprowadzanie nalezy zaczac od wyrazu wolnego(1,2,1,0,0,0,0,0,0.....)" << endl;
				for (int i = 0; i < N; i++) {
					long double temp;
					cin >> temp;
					h.push_back(temp);
				}
				cout << "Wprowadz szyfrogram, wprowadzanie nalezy zaczac od wyrazu wolnego(1,2,1,0,0,0,0,0,0.....)" << endl;
				for (int i = 0; i < N; i++) {
					long double temp;
					cin >> temp;
					e.push_back(temp);
				}

			}
			else if (mode3 == 2) {
				//Fp = { 1,1,1,0,2,1,1,2,0,1 };
				Fp.push_back(1);
				Fp.push_back(1);
				Fp.push_back(1);
				Fp.push_back(0);
				Fp.push_back(2);
				Fp.push_back(1);
				Fp.push_back(1);
				Fp.push_back(2);
				Fp.push_back(0);
				Fp.push_back(1);
				//e = { 52, 50, 50, 61, 61, 7, 53, 46, 24, 17, 50 };
				e.push_back(52);
				e.push_back(50);
				e.push_back(50);
				e.push_back(61);
				e.push_back(61);
				e.push_back(7);
				e.push_back(53);
				e.push_back(46);
				e.push_back(24);
				e.push_back(17);
				e.push_back(50);
				//h = { 39,9,33,52,58,11,38,6,1,48,41 };
				h.push_back(39);
				h.push_back(9);
				h.push_back(33);
				h.push_back(52);
				h.push_back(58);
				h.push_back(11);
				h.push_back(38);
				h.push_back(6);
				h.push_back(1);
				h.push_back(48);
				h.push_back(41);
			}

			vector <int> solution;

			for (int i = 0; i < 2 * N; i++) {
				vector<long double> a;
				for (int j = 0; j < 2 * N; j++) {
					a.push_back(0);
				}
				matrix.push_back(a);
			}
			int index;
			for (int i = 0; i < 2 * N; i++) {
				for (int j = 0; j < 2 * N; j++) {
					if ((i < N) && (j < N)) {
						if (i == j)matrix[i][j] = 1;
					}
					else if ((i >= N) && (j >= N)) {
						if (i == j) matrix[i][j] = q;
					}
					else if ((i < N) && (j >= N)) {
						index = j - N - i;
						if (index < 0) index += N;
						matrix[i][j] = h[index];
					}
				}
			}
			show_matrix(matrix);
			LLL(matrix);
			show_matrix(matrix);
			cout << endl;

			for (int i = 0; i < N; i++) {
				f.push_back(matrix[0][i]);
				g.push_back(matrix[0][i + N]);
				if (f[i] < 0) f[i] += q;
				if (g[i] < 0)g[i] += q;

			}

			bool flag;
			solution = Multi_Polynomials(f, h, q);
			flag = EqualPolynomials(solution, g);
			if (flag) {
                cout << "Zostalo spelnione f*h = g (modq)" << endl;
				cout << "f: ";
				for (int i = 0; i < N; i++) {
					cout << f[i] << " ";
				}
				cout << endl << "g: ";
				for (int i = 0; i < N; i++) {
					cout << g[i] << " ";

				}
				solution.clear();
				solution = Multi_Polynomials(f, e, q);
				CenterLift(solution, q);

				vector<int> message;
				if (mode3 == 1) {
					cout << "Podaj wielomian odwrotny w Fp dla zadanego wektora f" << endl;
					for (int i = 0; i < N; i++) {
						long double temp;
						cin >> temp;
						Fp.push_back(temp);
					}
				}
				message = Multi_Polynomials(solution, Fp, p);
				CenterLift(message, p);
				cout << endl << "m: ";
				for (int i = 0; i < message.size(); i++) {
					cout << message[i] << " ";
				}
				cout << endl;
			}
		}
		break;

	}
    int stop;
    cin >> stop;
}





long double Iloczyn_Skalarny(vector<long double> &a, vector<long double> &b) {
	long double wynik = 0;
	for (int i = 0; i < a.size(); i++) {
		wynik += a[i] * b[i];
	}
	return wynik;
}
vector <long double> Odejmowanie_Wektora(vector <long double> &a, vector < long double> &b, long double q) {
	vector <long double> c;
	for (int i = 0; i < b.size(); i++) {
		c.push_back(a[i] - q*b[i]);
	}
	return c;
}
long double max(long double a, long double b) {
	if (a > b) return a;
	else return b;
}
void show_vector(vector<long double> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i] << " ";
	}
	cout << endl;
}
void show_matrix(vector < vector <long double> > &matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		show_vector(matrix[i]);
	}
}
void LLL(vector < vector <long double> > &base) {
	vector < vector <long double> > ort;
	vector <vector<long double> > mi;
	vector <long double>k_values;
	for (int i = 0; i < base.size(); i++) {
		vector <long double> temp;
		for (int j = 0; j < base[i].size(); j++) {
			temp.push_back(0);
		}
		mi.push_back(temp);
	}
	int k = 1;
	long double t;
	long double Left_Lovasz, Right_Lovasz;
	int swaps = 0;
	int iterator = 0;
	while (k < base.size()) {
		k_values.push_back(k + 1);
		for (int j = k - 1; j >= 0; j--) {
			ort = Ortogonalizacja(base, mi);
			t = floor(mi[k][j]+ 0.5);
			base[k] = Odejmowanie_Wektora(base[k], base[j], t);
		}

		ort = Ortogonalizacja(base, mi);
		Left_Lovasz = Iloczyn_Skalarny(ort[k], ort[k]);
		Right_Lovasz = 0.75 - pow(mi[k][k - 1], 2);
		Right_Lovasz *= Iloczyn_Skalarny(ort[k - 1], ort[k - 1]);
		if (Left_Lovasz > Right_Lovasz) {
			k++;
		}
		else {
			base[k - 1].swap(base[k]);
			swaps++;
			k = max(k - 1, 1);
		}
		iterator++;
}
	cout << endl;
	cout << "k's : ";
	show_vector(k_values);
	cout << "swaps: " << swaps << endl;
	cout << "iterations: " << iterator << endl;
}
vector <vector <long double> > Ortogonalizacja(vector<vector<long double> > &base, vector<vector<long double> > &mi) {

	vector<vector<long double> >ort;
	for (int i = 0; i < base.size(); i++) {
		vector <long double> temp;
		for (int j = 0; j < base[i].size(); j++) {
			long double val = base[i][j];
			temp.push_back(val);
		}
		ort.push_back(temp);
	}
	for (int i = 0; i < mi.size(); i++) {
		for (int j = 0; j < mi[i].size(); j++) {
			mi[i][j] = 0;
		}
	}
	long double t;
	for (int i = 1; i < base.size(); i++) {
		for (int l = 0; l <= i - 1; l++) {
			t = Iloczyn_Skalarny(ort[i], ort[l]) / Iloczyn_Skalarny(ort[l], ort[l]);
			ort[i] = Odejmowanie_Wektora(ort[i], ort[l], t);
			mi[i][l] = t;

		}

	}
	return ort;
}
vector < int> Multi_Polynomials(vector< int> left, vector< int> right, int mod) {
	vector < int> solution;
	for (int i = 0; i < left.size(); i++) {
		solution.push_back(0);
	}
	int temp;
	for (int i = 0; i < left.size(); i++){
		for (int j = 0; j < right.size(); j++) {
			temp = left[i] * right[j];

			temp %=mod;
			if (temp < 0) temp += mod;
			solution[(i + j) % N] = (solution[(i + j) % N]+temp)%mod;

		}
	}
	return solution;
}
bool EqualPolynomials(vector<int> left, vector<int> right) {
	if (left.size() != right.size())return false;
	else {
		for (int i = 0; i < left.size(); i++) {
			if (left[i] != right[i]) return false;
		}
	}
	return true;
}
int congruence(int a, int b, int mod) {
	if (b < 0)	b+=mod;
	if (a < 0)	a+= mod;
	int variable=1;
	while (1) {
		if (((variable*a) % mod) == b) {
			return variable;
		}
		else variable++;
	}

}
vector <int> Scalar_Vector_Multiplication(int scalar, vector<int> &vek) {
	vector <int> temp;
	for (int i = 0; i < vek.size(); i++) {
		temp.push_back(scalar*vek[i]);
	}
	return temp;
}
void CenterLift(vector<int> &vek, int mod) {
	for (int i = 0; i < vek.size(); i++) {
		if (vek[i] > (mod/2)) vek[i] -= mod;
	}
}


void show_vector(vector<cpp_int> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i] << " ";
	}
	cout << endl;
}
int convert(int n, vector<int> &cont) {
	int reszta = n % 2;
	if (n > 1) convert((int)(n / 2), cont);
	cont.push_back(reszta);
	return reszta;
}
cpp_int Szybkie_pot(int a, int n) {
	cpp_int value = 1;
	cpp_int temp = a;
	vector<int>cont;
	convert(n, cont);
	for (int i = cont.size() - 1; i >= 0; i--) {
		if (cont[i] != 0)
			value *= temp;
		temp *= temp;
	}
	return value;
}
cpp_int Generuj_BigInteger(int n) {
	cpp_int BigInt = 0, y;
	cpp_int Iterations = n / 16;
	short x;
	if (Iterations == 0) {
		x = rand();
		return x;
	}
	else {
		for (int i = 1; i <= Iterations; i++) {
			x = rand();
			y = Szybkie_pot(2, 15) | x;
			BigInt |= (y << (n - (16 * i)));
		}
		short rd = rand() % 2;
		if (rd == 1) BigInt *= (-1);
		return BigInt;
	}
}
vector <cpp_int> Generuj_Vector(int rozmiar, int n_bitowa_liczba) {
	vector <cpp_int> a;
	for (int i = 0; i < rozmiar; i++) {
		a.push_back(Generuj_BigInteger(n_bitowa_liczba));
	}
	return a;
}
cpp_int Iloczyn_Skalarny(vector<cpp_int> &a, vector<cpp_int> &b) {
	cpp_int wynik = 0;
	for (int i = 0; i < a.size(); i++) {
		wynik += a[i] * b[i];
	}
	return wynik;
}
vector <cpp_int> Odejmowanie_Wektora(vector <cpp_int> &a, vector < cpp_int> &b, cpp_int m) {
	vector <cpp_int> c;
	cpp_int d;
	for (int i = 0; i < b.size(); i++) {
		d = a[i] - m*b[i];
		c.push_back(d);
	}
	return c;
}
void GL(vector <cpp_int> &v1, vector<cpp_int> &v2) {
	cpp_int m;
	do {
		if (Iloczyn_Skalarny(v2, v2) < Iloczyn_Skalarny(v1, v1)) v1.swap(v2);
		m = boost_round(Iloczyn_Skalarny(v1, v2), Iloczyn_Skalarny(v1, v1));
		v2 = Odejmowanie_Wektora(v2, v1, m);
	} while (m != 0);
}

cpp_int mod(cpp_int a, cpp_int b) {
	cpp_int integer;
	cpp_int rem;
	integer = a / b;

	if (((a <0) ^ (b<0))&(integer <= 0)) integer--;

	rem = a - (b * integer);
	return rem;
}
cpp_int boost_round(cpp_int a, cpp_int b) {
	cpp_int integer;
	cpp_int rem;
	short sign = 1;
	if ((a < 0) ^ (b < 0)) sign = 0;
	integer = a / b;
	if (a < 0) a *= (-1);
	if (b < 0) b *= (-1);

	if (sign == 1) {
		rem = mod(a, b);
		if (2 * rem > b) integer++;
	}
	else {
		while (a > b) {
			a -= b;
		}
		if (mod(a, b) != 0)
			if (2 * a >= b) integer--;
	}

	return integer;
}
