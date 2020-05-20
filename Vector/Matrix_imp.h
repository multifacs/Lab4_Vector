#include "Matrix.h"
template<class T>
inline TMatrix<T>::TMatrix(int _r, int _c)
{
    matrix = new T * [_r];
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
inline TMatrix<T>::TMatrix(int _r, int _c, int a, int b)
{
    matrix = new T * [_r];
    for (int i = 0; i < _r; i++)
    {
        matrix[i] = new T[_c];
        for (int j = 0; j < _c; j++)
            matrix[i][j] = ((double)rand() / (double)RAND_MAX) * (b - a) + a;
    }

    rows = _r;
    columns = _c;
}

template<class T>
inline TMatrix<T>::~TMatrix()
{
    if ((rows != 0) & (columns != 0))
    {
        for (int i = 0; i < rows; i++) delete[] matrix[i];
        delete[] matrix;
        rows = 0;
        columns = 0;
    }
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
const TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& rhs)
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

    auto start = high_resolution_clock::now();

    TMatrix<P> result(lhs.rows, lhs.columns);
    for (int i = 0; i < lhs.rows; i++)
    {
        for (int j = 0; j < lhs.columns; j++)
        {
            result[i][j] = lhs[i][j] + rhs[i][j];
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by addition: "
        << duration.count() << " microseconds" << endl;

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

    auto start = high_resolution_clock::now();

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

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by multiplication: "
        << duration.count() << " microseconds" << endl;

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

template<class T>
inline void TMatrix<T>::Find(T a)
{
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (matrix[i][j] == a)
            {
                cout << "Item found at [" << i << "][" << j << "]" << endl;
                k = 1;
            }
    if (k == 0)
        cout << "Item not found" << endl;
}

template<class T>
inline void TMatrix<T>::FindAll(T a)
{
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (matrix[i][j] == a)
            {
                cout << "Item found at [" << i << "][" << j << "]" << endl;
                k = 1;
            }
    if (k == 0)
        cout << "Item not found" << endl;
}

template<class T>
void TMatrix<T>::inversion()
{
    double temp;
    int N = rows;

    T** E = new T* [N];

    for (int i = 0; i < N; i++)
        E[i] = new T[N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            E[i][j] = 0.0;

            if (i == j)
                E[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++)
    {
        temp = matrix[k][k];

        for (int j = 0; j < N; j++)
        {
            matrix[k][j] /= temp;
            E[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++)
        {
            temp = matrix[i][k];

            for (int j = 0; j < N; j++)
            {
                matrix[i][j] -= matrix[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = matrix[i][k];

            for (int j = 0; j < N; j++)
            {
                matrix[i][j] -= matrix[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = E[i][j];

    for (int i = 0; i < N; i++)
        delete[] E[i];

    delete[] E;
}

template<class D>
inline TMatrix<D> operator/(TMatrix<D>& lhs, TMatrix<D>& rhs)
{
    if ((lhs.get_rows() == rhs.get_rows()) & (lhs.get_columns() == rhs.get_rows()))
    {
        TMatrix<D> I = rhs;
        I.inversion();

        return lhs * I;
    }
    else
        throw "Yikes";

}