#pragma once
#include "Matrix.h"

template <class T>
class TVector :public TMatrix<T>
{
public:
	TVector() :TMatrix<T>() {}
	TVector(int _size) :TMatrix<T>(1, _size) {}
	TVector(const TVector& t) : TMatrix<T>(t) {}
	~TVector() {}
	TVector(const std::initializer_list<T>& list);

	const TVector<T>& operator=(const std::initializer_list<T>& list);
	
	const TVector<T>& operator =(const TMatrix<T>& rhs);

	template<class P, typename N>
	friend TVector<N> operator +(TVector<P>& lhs, TVector<N>& rhs);

	template <class M, typename N>
	friend TVector<N> operator -(TVector<M>& lhs, TVector<N>& rhs);

	template <class D, typename N>
	friend TVector<D> operator /(TVector<D>& lhs, N rhs);

	template <class M, typename N>
	friend TVector<M> operator *(TMatrix<M>& lhs, TVector<N>& rhs);

	template <class M, typename N>
	friend TMatrix<M> operator *(TVector<M>& lhs, TMatrix<N>& rhs);
	
	T* get_vector();
	T& operator [](const int i) const;

	template <class I>
	friend istream& operator >>(istream& in, TVector<I>& t);

	template <class O>
	friend ostream& operator <<(ostream& out, const TVector<O>& t);
};

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