﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if ( (sz == 0) || (sz > MAX_VECTOR_SIZE) )
      throw out_of_range("Vector size should be legal");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    pMem = nullptr;
    swap(*this, v);
  }
  ~TDynamicVector()
  {
    delete[] pMem;    
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v)
    return *this;
    if (sz != v.sz) 
    {
      T* p = new T[v.sz];
      delete[] pMem;
      sz = v.sz;
      pMem = p;
      //return *this;
    }
    std::copy(v.pMem, v.pMem + sz, pMem);
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    swap(*this, v);
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind >= sz ) throw out_of_range("Index out of range");
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz) throw out_of_range("Index out of range");
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if(this == &v) return true;
      if(sz != v.size()) return false;
      for(size_t i = 0 ; i < sz ; i++)
	    {
		    if(pMem[i] != v.pMem[i]) return false; // must relise != for class T
	    }
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    if(this == &v) return false;
      if(sz != v.size()) return true;
      long int k = 0;
      for(size_t i = 0 ; i < sz ; i++)
	    {
		    if(pMem[i] == v.pMem[i]) k++; // must relise == for class T

	    }
      if(k==sz) return false;
      return true;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
      {
        tmp.pMem[i] = pMem[i] + val;
      }
    return tmp;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
      {
        tmp.pMem[i] = pMem[i] - val;
      }
    return tmp;
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
      {
        tmp.pMem[i] = pMem[i] * val;
      }
    return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if(sz != v.size()) throw domain_error("error of size");
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
      {
        tmp.pMem[i] = pMem[i] + v.pMem[i];
      }
    return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if(sz != v.size()) throw domain_error("error of size");
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
      {
        tmp.pMem[i] = pMem[i] - v.pMem[i];
      }
    return tmp;
  }
  T operator*(const TDynamicVector& v) 
  {
    if(sz != v.size()) throw domain_error("error of size");
    T zxc{};
    for (size_t i = 0; i < sz; i++)
      {
        zxc = zxc + (pMem[i] * v.pMem[i]);
      }
    return zxc;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s == 0 || s > MAX_MATRIX_SIZE) throw out_of_range("Exceeding the range");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }


  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {

      return (*pMem == *m.pMem);/////////? /// все через наслед
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)
      {
          return true;
      }
      else
      {
          for (size_t i = 0; i < sz; i++)
          {
              if (pMem[i] != m.pMem[i])
              {
                  return true;
              }
          }
      }

      return false;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
    TDynamicMatrix tmp(val*pMem);
    return tmp;
  }
  

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if ( v.size() != pMem[0].size()) return throw domain_error("ERROR");
    TDynamicVector<T> tmp(sz);
    for (size_t i = 0; i < sz; i++)
    {
      tmp[i] = pMem[i] * v;
    }
    return tmp;
}

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  { 
    if (sz != m.size()) throw domain_error("size_ERROR");
    TDynamicMatrix tmp(sz);
    for (size_t i = 0; i < sz; i++)
    {
      tmp.pMem[i] = pMem[i] + m.pMem[i];
    }
    return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.size()) throw domain_error("size_ERROR");
    TDynamicMatrix tmp(sz);
    for (size_t i = 0; i < sz; i++)
    {
      tmp.pMem[i] = pMem[i] - m.pMem[i];
    }
    return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.size()) throw domain_error("size_ERROR");
    TDynamicMatrix tmp(sz);
    for (size_t i = 0; i < sz; i++)
    {
      for (size_t j = 0; j < sz; j++)
      {
        for (size_t k = 0; k < sz; k++)
        {
          tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
        }
      }
    }
    return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
    {
      istr>>v.pMem[i];
      cout<<endl;
    }
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
    {
      ostr<<v.pMem[i];
      cout<<endl;
    }
    return ostr;
  }
};

#endif
