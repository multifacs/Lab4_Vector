#include "Matrix.h"
#include "Vector.h"

int main()
{
	TMatrix<int> m(3,3);
	TMatrix<int> l;
	l = m;
	if (l == m)
		cout << "yes" << endl;
	cout << l << endl;
	cin >> m;
	m.set_size(3, 3);
	cout << m << endl;
	l = m;
	m = l * 5;
	cout << m << endl;
	TVector<int> ah(5);
	ah[0] = 15;

	TVector<int> bleh{ 1, 2, 3 };

	bleh = { 1, 2, 3, 4 };
	ah = { 10, 20, 30, 40 };

	bleh = bleh + ah;

	cout << bleh;

	if (bleh == l)
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	TVector<int> bruh = { 10, 15, 30 };
	TVector<double> ah = {2.0, 5.0, 6.0};

	cout << bruh + ah;

	return 0;
}