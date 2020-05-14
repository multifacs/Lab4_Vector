#pragma once
#include <iostream>

using namespace std;

template <class T>
class TMatrix
{
protected:
	int rows, columns;
	T** matrix;
public:
    TMatrix() :rows(0), columns(0), matrix(0) {};
	TMatrix(int _r, int _c);
	TMatrix(const TMatrix& rhs);
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

};

template<class T>
inline TMatrix<T>::TMatrix(int _r, int _c)
{
    matrix = new T*[_r];
    for (int i = 0; i < _r; i++)
    {
        matrix[i] = new T[_c];
        for (int j = 0; j < _c; j++)
            matrix[i][j] = 0;
    }

    rows = _r;
    columns = _c;
}

template<class T>
inline TMatrix<T>::TMatrix(const TMatrix& rhs)
{
    matrix = new T * [rhs.rows];
    for (int i = 0; i < rhs.rows; i++)
    {
        matrix[i] = new T[rhs.columns];
        for (int j = 0; j < rhs.columns; j++)
            matrix[i][j] = rhs[i][j];
    }
    rows = rhs.rows;
    columns = rhs.columns;

}

template<class T>
inline TMatrix<T>::~TMatrix()
{
    for (int i = 0; i < rows; i++) delete[] matrix[i];
    delete[] matrix;
}

template<class T>
inline int TMatrix<T>::get_rows() const
{
    return rows;
}

template<class T>
inline int TMatrix<T>::get_columns() const
{
    return columns;
}

template<class T>
inline T** TMatrix<T>::get_array() const
{
    return matrix;
}

template<class T>
const TMatrix<T> &TMatrix<T>::operator=(const TMatrix<T>& rhs)
{
    if (this == &rhs)
        return *this;

    for (int i = 0; i < rows; i++) delete[] matrix[i];
    delete[] matrix;

    rows = rhs.rows;
    columns = rhs.columns;

    matrix = new T * [rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new T[columns];
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = rhs[i][j];
        }
    }
    return *this;
}

template<class T>
inline T*& TMatrix<T>::operator[](const int i) const
{
    if (i > rows || i < 0)
        throw length_error("Incorrect index");

    return matrix[i];
}

template<class P>
inline TMatrix<P> operator+(TMatrix<P>& lhs, TMatrix<P>& rhs)
{
    if (lhs.rows != rhs.rows || lhs.columns != rhs.columns)
        throw "Matrices aren't equal";

    TMatrix<P> result(lhs.rows, lhs.columns);
    for (int i = 0; i < lhs.rows; i++)
    {
        for (int j = 0; j < lhs.columns; j++)
        {
            result[i][j] = lhs[i][j] + rhs[i][j];
        }
    }
    return result;
}

template<class M>
inline TMatrix<M> operator-(TMatrix<M>& lhs, TMatrix<M>& rhs)
{
    if (lhs.rows != rhs.rows || lhs.columns != rhs.columns)
        throw "Matrices aren't equal";

    TMatrix<M> result(lhs.rows, lhs.columns);
    for (int i = 0; i < lhs.rows; i++)
    {
        for (int j = 0; j < lhs.columns; j++)
        {
            result[i][j] = lhs[i][j] - rhs[i][j];
        }
    }
    return result;
}

template<class E>
inline bool operator==(TMatrix<E>& lhs, TMatrix<E>& rhs)
{
    if (lhs.rows != rhs.rows || lhs.columns != rhs.columns)
    {
        return false;
    }
    else {
        for (int i = 0; i < lhs.rows; i++)
        {
            for (int j = 0; j < lhs.columns; j++)
            {
                if (lhs[i][j] != rhs[i][j]) return false;
            }
        }
    }
    return true;
}

template<class M>
inline TMatrix<M> operator*(TMatrix<M>& lhs, TMatrix<M>& rhs)
{
    if (lhs.columns != rhs.rows)
        throw "Can't multiply";

    TMatrix<M> result(lhs.rows, rhs.columns);
    M t;
    for (int i = 0; i < lhs.rows; i++)
        for (int j = 0; j < rhs.columns; j++)
        {
            t = 0;
            for (int k = 0; k < lhs.columns; k++)
                t += lhs[i][k] * rhs[k][j];
            result[i][j] = t;
        }
    return result;
}

template<class M, typename N>
inline TMatrix<M> operator*(TMatrix<M>& lhs, N rhs)
{
    TMatrix<M> result(lhs.rows, lhs.columns);

    for (int i = 0; i < lhs.rows; i++)
        for (int j = 0; j < lhs.columns; j++)
            result[i][j] = lhs[i][j] * rhs;

    return result;
}

template<class D, typename N>
inline TMatrix<D> operator/(TMatrix<D>& lhs, N rhs)
{
    TMatrix<D> result(lhs.rows, lhs.columns);

    for (int i = 0; i < lhs.rows; i++)
        for (int j = 0; j < lhs.columns; j++)
            result[i][j] = lhs[i][j] / rhs;

    return result;
}

template<class I>
inline istream& operator>>(istream& in, TMatrix<I>& t)
{
    for (int i = 0; i < t.rows; i++)
    {
        for (int j = 0; j < t.columns; j++)
        {
            in >> t[i][j];
        }
    }
    return in;
}

template<class O>
inline ostream& operator<<(ostream& out, const TMatrix<O>& t)
{
    for (int i = 0; i < t.rows; i++)
    {
        for (int j = 0; j < t.columns; j++)
        {
            out << t[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

template<class T>
inline void TMatrix<T>::set_size(int new_r, int new_c)
{
    if ((new_r < 0 || new_c < 0) & (new_r != -1) & (new_c != -1))
        throw length_error("Incorrect size");

    TMatrix<T> D(*this);

    for (int i = 0; i < rows; i++) delete[] matrix[i];
    delete[]  matrix;

    if (new_r != -1)
        rows = new_r;
    if (new_c != -1)
        columns = new_c;

    matrix = new T * [rows];

    for (int i = 0; i < rows; i++)
        matrix[i] = new T[columns];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 0;
        }
    }
    
    int wb = (D.rows < rows) ? D.rows : rows;
    int lb = (D.columns < columns) ? D.columns : columns;
    for (int i = 0; i < wb; i++) {
        for (int j = 0; j < lb; j++) {
            matrix[i][j] = D[i][j];
        }
    }
}
