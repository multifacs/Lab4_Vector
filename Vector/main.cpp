#include "Matrix.h"
#include "Vector.h"

int main()
{
	srand(time(NULL));

	cout << "-- Creating a 3x3 matrix and testing = and the copy constructor --" << endl;
	TMatrix<int> m(3,3);
	TMatrix<int> l(m);
	cout << l << endl;
	m = l;
	cout << m;
	if (l == m)
		cout << "Matrices are equal, successful" << endl;
	else
		cout << "Matrices aren't equal" << endl;

	cout << endl << "Type in a 3x3 matrix: " << endl;
	//cin >> m;

	m.set_size(2, 2);
	cout << endl << "Shrinked!" << endl << m << endl;
	m = m * 5;
	cout << "Multiplied by " << 5 << endl << m << endl;


	cout << "-- Testing vectors --" << endl;

	TVector<int> ah(5);
	ah[0] = 15;
	cout << ah;

	TVector<int> bleh{ 1, 2, 3, 4 };
	ah = { 10, 20, 30, 40 };

	bleh = bleh + ah;
	cout << bleh;

	if (bleh == l)
		cout << "Vectors are equal" << endl;
	else
		cout << "Vectors aren't equal" << endl;


	cout << endl << "-- Adding and multiplicating matrices --" << endl;
	int n = 1;
	for (int i = 1; i < 4; i++)
	{
		cout << n << " and " << n * 2 << " elements: " << endl;
		TMatrix<int> RandM(n, n * 2, 1, 100);
		TMatrix<int> RandN(n, n * 2, 1, 100);

		RandM + RandN;

		TMatrix<int> RandO(n * 2, n, 1, 100);
		RandM* RandO;

		cout << endl;

		n = n * 10;
	}


	cout << "-- Sorting vectors --" << endl;
	n = 10;
	for (int i = 1; i < 5; i++)
	{
		TVector<double> ah(n, 1, 100);
		TVector<double> bh(ah);

		cout << ah.get_columns() << " elements" << endl;

		ah.BubbleSort();
		ah = bh;

		ah.InsertSort();
		ah = bh;

		ah.QuickSort();

		ah.~TVector();
		bh.~TVector();

		cout << endl;

		n = n * 10;
	}


	cout << "Testing Find() and FindAll()" << endl;
	TVector<int> Vec = { 1, 2, 3, 4, 5, 2, 2, 2, 2 };
	Vec.Find(0);

	cout << "Item 2: " << endl;
	Vec.FindAll(2);
	cout << endl;

	//TMatrix<int> R(100, 100, 1, 100);
	//R.FindAll(50);

	TMatrix<double> A(3, 3);
	TMatrix<double> I(3, 3);
	cin >> A >> I;
	cout << A / I;

	return 0;
}