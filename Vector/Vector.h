#pragma once
#include "Matrix.h"

using namespace std::chrono;

template <class T>
class TVector :public TMatrix<T>
{
public:
	TVector() :TMatrix<T>() {}
	TVector(int _size) :TMatrix<T>(1, _size) {}
	TVector(const TVector& t) : TMatrix<T>(t) {}
	virtual ~TVector();
	TVector(const std::initializer_list<T>& list);
	TVector(int n, int a, int b);

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

	void BubbleSort();
	void InsertSort();
	void QuickSort();

	void Find(T a) override;
	void FindAll(T a) override;
protected:
	void qs(int first, int last);
};

#include "Vector_imp.h"