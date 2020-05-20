#include "Vector.h"
template<class T>
inline TVector<T>::~TVector()
{
	if ((this->rows != 0) & (this->columns != 0))
	{
		delete[] this->matrix[0];
		delete[] this->matrix;
		this->rows = 0;
		this->columns = 0;
		//cout << "deleted";
	}
}

template<class T>
TVector<T>::TVector(const std::initializer_list<T>& list)
	: TVector(list.size())
{
	int count = 0;
	for (auto& element : list)
	{
		this->matrix[0][count] = element;
		++count;
	}
}

template<class T>
inline TVector<T>::TVector(int n, int a, int b)
{
	this->matrix = new T * [1];
	this->matrix[0] = new T[n];
	for (int i = 0; i < n; i++)
		this->matrix[0][i] = ((double)rand() / (double)RAND_MAX) * (b - a) + a;

	this->rows = 1;
	this->columns = n;

}

template<class T>
inline T* TVector<T>::get_vector()
{
	return this->matrix;
}

template<class T>
inline T& TVector<T>::operator[](const int i) const
{
	return this->matrix[0][i];
}

template<class T>
const TVector<T>& TVector<T>::operator=(const std::initializer_list<T>& list)
{

	delete[] this->matrix[0];
	delete[] this->matrix;

	this->matrix = new T * [1];
	this->matrix[0] = new T[list.size()];

	this->columns = list.size();

	int count = 0;
	for (auto& element : list)
	{
		this->matrix[0][count] = element;
		++count;
	}

	return *this;
}

template<class T>
inline const TVector<T>& TVector<T>::operator=(const TMatrix<T>& rhs)
{
	if (this == &rhs)
		return *this;

	delete[] this->matrix[0];
	delete[] this->matrix;

	this->rows = 1;
	this->columns = rhs.get_columns();

	this->matrix = new T * [1];

	this->matrix[0] = new T[this->columns];
	for (int i = 0; i < this->columns; i++)
	{
		this->matrix[0][i] = rhs[0][i];
	}

	return *this;
}

template<class P, typename N>
inline TVector<N> operator+(TVector<P>& lhs, TVector<N>& rhs)
{
	if (lhs.rows != rhs.rows || lhs.columns != rhs.columns)
		throw "Vectors aren't equal";

	TVector<N> result(lhs.columns);
	for (int i = 0; i < lhs.columns; i++)
	{
		result[i] = lhs[i] + rhs[i];
	}
	return result;
}

template<class M, typename N>
inline TVector<N> operator-(TVector<M>& lhs, TVector<N>& rhs)
{
	if (lhs.rows != rhs.rows || lhs.columns != rhs.columns)
		throw "Vectors aren't equal";

	TVector<N> result(lhs.columns);
	for (int i = 0; i < lhs.columns; i++)
	{
		result[i] = lhs[i] - rhs[i];
	}
	return result;
}

template<class M, typename N>
inline TVector<M> operator*(TMatrix<M>& lhs, TVector<N>& rhs)
{
	if (lhs.get_columns() != rhs.columns)
		throw "Can't multiply";

	TVector<M> result(lhs.get_rows());
	M t;
	for (int i = 0; i < rhs.columns; i++)
	{
		t = 0;
		for (int j = 0; j < lhs.get_columns(); j++)
			t += lhs[i][j] * rhs[j];
		result[i] = t;
	}
	return result;
}

template<class M, typename N>
inline TMatrix<M> operator*(TVector<M>& lhs, TMatrix<N>& rhs)
{
	if (lhs.rows != rhs.get_rows())
		throw "Can't multiply";

	TMatrix<M> result(lhs.columns, rhs.get_columns());

	for (int i = 0; i < lhs.columns; i++)
		for (int j = 0; j < rhs.get_columns(); j++)
		{
			result[i][j] = lhs[i] * rhs[0][j];
		}
	return result;
}

template<class D, typename N>
inline TVector<D> operator/(TVector<D>& lhs, N rhs)
{
	TVector<D> result(lhs.columns);

	for (int i = 0; i < lhs.columns; i++)
		result[i] = lhs[i] / rhs;

	return result;
}

template<class I>
inline istream& operator>>(istream& in, TVector<I>& t)
{
	for (int i = 0; i < t.columns; i++)
		in >> t[i];

	return in;
}

template<class O>
inline ostream& operator<<(ostream& out, const TVector<O>& t)
{
	for (int i = 0; i < t.columns; i++)
	{
		out << t[i] << endl;
	}
	out << endl;
	return out;
}

template<class T>
inline void TVector<T>::BubbleSort()
{
	auto start = high_resolution_clock::now();

	for (int i = 0; i < this->columns; i++)
	{
		for (int j = i + 1; j < this->columns; j++)
		{
			if (this->matrix[0][i] > this->matrix[0][j])
			{
				T element;
				element = this->matrix[0][i];
				this->matrix[0][i] = this->matrix[0][j];
				this->matrix[0][j] = element;
			}
		}
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by bubble sort: "
		<< duration.count() << " microseconds" << endl;
}

template<class T>
inline void TVector<T>::InsertSort()
{
	int begin;
	int end;
	int middle;
	T value;

	auto start = high_resolution_clock::now();

	for (int i = 1; i < this->columns; ++i)
	{
		value = this->matrix[0][i];
		begin = 0;
		end = i - 1;
		while (begin <= end)
		{
			middle = (begin + end) / 2;
			if (value < this->matrix[0][middle])
			{
				end = middle - 1;
			}
			else
			{
				begin = middle + 1;
			}
		}

		for (int j = i - 1; j >= begin; --j)
		{
			this->matrix[0][j + 1] = this->matrix[0][j];
		}

		this->matrix[0][begin] = value;
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by insertion sort: "
		<< duration.count() << " microseconds" << endl;
}

template<class T>
inline void TVector<T>::qs(int first, int last)
{
	int i = first, j = last;
	T tmp, x = this->matrix[0][(first + last) / 2];

	do {
		while (this->matrix[0][i] < x)
			i++;
		while (this->matrix[0][j] > x)
			j--;

		if (i <= j)
		{
			if (i < j)
			{
				tmp = this->matrix[0][i];
				this->matrix[0][i] = this->matrix[0][j];
				this->matrix[0][j] = tmp;
			}
			i++;
			j--;
		}
	} while (i <= j);

	if (i < last)
		qs(i, last);
	if (first < j)
		qs(first, j);
}

template<class T>
inline void TVector<T>::QuickSort()
{
	auto start = high_resolution_clock::now();

	this->qs(0, this->columns - 1);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by quick sort: "
		<< duration.count() << " microseconds" << endl;
}

template<class T>
inline void TVector<T>::Find(T a)
{
	int k = 0;
	for (int i = 0; i < this->columns; i++)
		if (this->matrix[0][i] == a)
		{
			cout << "Item found at [" << i << "]" << endl;
			k = 1;
		}
	if (k == 0)
		cout << "Item not found" << endl;
}

template<class T>
inline void TVector<T>::FindAll(T a)
{
	int k = 0;
	for (int i = 0; i < this->columns; i++)
		if (this->matrix[0][i] == a)
		{
			cout << "Item found at [" << i << "]" << endl;
			k = 1;
		}
	if (k == 0)
		cout << "item not found" << endl;
}
