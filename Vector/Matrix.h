#pragma once
#include <chrono> 
#include <random>
#include <iostream>

using namespace std;
using namespace std::chrono;

template <class T>
class TMatrix
{
protected:
	int rows, columns;
	T** matrix;

    void inversion();
public:
    TMatrix() :rows(0), columns(0), matrix(0) {};
	TMatrix(int _r, int _c);
	TMatrix(const TMatrix& rhs);
    TMatrix(int _r, int _c, int a, int b);
	virtual ~TMatrix();

	int get_rows() const;
	int get_columns() const;
	T** get_array() const;

    void set_size(int new_r, int new_c);

    const TMatrix<T> &operator =(const TMatrix<T>& rhs);

    T*& operator [](const int i) const;

    template<class P>
    friend TMatrix<P> operator +(TMatrix<P>& lhs, TMatrix<P>& rhs);

    template <class M>
    friend TMatrix<M> operator -(TMatrix<M>& lhs, TMatrix<M>& rhs);

    template <class E>
    friend bool operator ==(TMatrix<E>& lhs, TMatrix<E>& rhs);

    template <class M>
    friend TMatrix<M> operator *(TMatrix<M>& lhs, TMatrix<M>& rhs);

    template <class M, typename N>
    friend TMatrix<M> operator *(TMatrix<M>& lhs, N rhs);

    template <class D, typename N>
    friend TMatrix<D> operator /(TMatrix<D>& lhs, N rhs);

    template <class I>
    friend istream& operator >>(istream& in, TMatrix<I>& t);

    template <class O>
    friend ostream& operator <<(ostream& out, const TMatrix<O>& t);

    //Dop zadaniya
    virtual void Find(T a);
    virtual void FindAll(T a);

    template <class D>
    friend TMatrix<D> operator /(TMatrix<D>& lhs, TMatrix<D>& rhs);
};

#include "Matrix_imp.h"