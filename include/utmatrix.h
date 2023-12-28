#ifndef __TMATRIX_H__
#define __TMATRIX_H__
#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000;


// Шаблон вектора
template <class ValType>
class TVector
{
protected:
    int StartIndex;
    ValType* pVector;
    int Size;
public:
    TVector<ValType>(int s = 10, int si = 0);
    TVector<ValType>(const TVector& v);
    virtual ~TVector<ValType>();
    int GetSize() const { return Size; }
    int GetStartIndex() const { return StartIndex; }
    ValType& operator[](int pos);
    bool operator==(const TVector<ValType>& v) const;
    bool operator!=(const TVector<ValType>& v) const;
    const TVector<ValType>& operator=(const TVector<ValType>& v);

    // скалярные операции
    TVector<ValType>  operator+(const ValType& val);
    TVector<ValType>  operator-(const ValType& val);
    TVector<ValType>  operator*(const ValType& val);

    // векторные операции
    TVector<ValType>  operator+(const TVector<ValType>& v);
    TVector<ValType>  operator-(const TVector<ValType>& v);
    ValType  operator*(const TVector<ValType>& v);

    // ввод-вывод
    friend istream& operator>>(istream& in, TVector<ValType>& v)
    {
        for (int i = v.StartIndex; i < v.StartIndex + v.Size; i++)
            in >> v[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, TVector<ValType>& v)
    {
        for (int i = 0; i < v.StartIndex; i++)
        {
            out << ValType() << " ";
        }
        for (int i = v.StartIndex; i < v.Size + v.StartIndex; i++) {

            out << v[i] << " ";
        }
        return out;
    }
};

template <class ValType>
TVector<ValType>::TVector<ValType>(int s, int si) :Size(s), StartIndex(si)
{
    if (s <= 0 || s > MAX_VECTOR_SIZE)
        throw "Incorrect size";
    if (si < 0)
        throw "You cannot start at negative index!";
    pVector = new ValType[s]();
}

template <class ValType>
TVector<ValType>::TVector<ValType>(const TVector<ValType>& v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    std::copy(v.pVector, v.pVector + v.Size, pVector);
}
template <class ValType>
TVector<ValType>::~TVector<ValType>()
{
    delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int index)
{
    if (index < 0 || index >= MAX_VECTOR_SIZE)
        throw "Wrong indexition";
    if (index < StartIndex)
        throw "Wrong indexition (less than start index)";

    if (index - StartIndex < Size)
        return pVector[index - StartIndex];
    throw "Access Error";
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& vec) const
{
    if ((StartIndex != vec.StartIndex) || (Size != vec.Size)) return false;

    for (int i = 0; i < Size; ++i)
    {
        if (pVector[i] != vec.pVector[i]) {
            return false;
        }
    }
    return true;
}



template <class ValType>
bool TVector<ValType>::operator!=(const TVector<ValType>& vec) const
{
    return !(*this == vec);
}


template <class ValType>
const TVector<ValType>& TVector<ValType>::operator=(const TVector<ValType>& vec)
{
    if (this == &vec)
        return *this;

    if (Size != vec.Size)
    {
        delete[] pVector;
        pVector = new ValType[vec.Size];
    }

    Size = vec.Size;
    StartIndex = vec.StartIndex;
    for (int i = 0; i < Size; i++)
    {
        pVector[i] = vec.pVector[i];
    }
    return *this;
}



template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
    TVector<ValType> Mas(Size, StartIndex);
    for (int i = 0; i < Mas.Size; ++i)
    {
        Mas[i] = pVector[i] + val;
    }
    return Mas;
}
template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
    TVector<ValType> Mas(Size, StartIndex);
    for (int i = 0; i < Mas.Size; ++i)
    {
        Mas[i] = pVector[i] - val;
    }
    return Mas;
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
    TVector<ValType> Mas(Size, StartIndex);
    for (int i = 0; i < Mas.Size; ++i)
    {
        Mas[i] = pVector[i] * val;
    }
    return Mas;
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& vec)
{
    if ((Size != vec.Size) || (StartIndex != vec.StartIndex))
        throw "Size and StartIndex should be equal";

    TVector<ValType> Mas(Size, StartIndex), tmp(vec);
    for (int i = 0; i < Size; ++i)
    {
        Mas.pVector[i] = pVector[i] + vec.pVector[i];
    }
    return Mas;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& vec)
{
    if ((Size != vec.Size) || (StartIndex != vec.StartIndex))
        throw "Size and StartIndex should be equal";

    TVector<ValType> Mas(Size, StartIndex), tmp(vec);
    for (int i = 0; i < Size; ++i)
    {
        Mas.pVector[i] = pVector[i] - vec.pVector[i];
    }
    return Mas;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector<ValType>& vec)
{
    if ((vec.Size != Size) || (vec.StartIndex != StartIndex))
        throw "dimentions of vectors should be equal for dot product";

    ValType ans = ValType();
    TVector<ValType> tmp(vec);
    for (int i = 0; i < Size; ++i)
    {
        ans = ans + pVector[i] * tmp[i];
    }
    return ans;
}



const int MAX_MATRIX_SIZE = 100000;

//Наследуем матрицу от конкретного экземпляра TVector<ValType1>, где ValType1 = TVector<ValType>, причём поля в родительском классе.
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
    TMatrix<ValType>(int s = 10);
    TMatrix<ValType>(const TMatrix<ValType>& mt);
    TMatrix<ValType>(const TVector<TVector<ValType> >& mt);
    bool operator==(const TMatrix<ValType>& mt) const;
    bool operator!=(const TMatrix<ValType>& mt) const;
    const TMatrix<ValType>& operator=(const TMatrix<ValType>& mt);
    TMatrix<ValType> operator+(const TMatrix<ValType>& mt);
    TMatrix<ValType> operator-(const TMatrix<ValType>& mt);
    TMatrix<ValType> operator*(const TMatrix<ValType>& mt);

    //Эти операции изменят вид матрицы, что не логично для задачи.
    //TMatrix& operator=(const ValType& v);
    //TMatrix  operator+(const ValType& v);
    //TMatrix  operator-(const ValType &v);


    // ввод / вывод
    friend istream& operator>>(istream& in, TMatrix<ValType>& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TMatrix<ValType>& mt)
    {

        for (int i = 0; i < mt.Size; i++)
            out << mt.pVector[i] << endl;
        return out;
    }

};

template <class ValType>
TMatrix<ValType>::TMatrix<ValType>(int s) : TVector<TVector<ValType>>(s)
{
    for (int i = 0; i < Size; ++i)
    {
        TVector<ValType> x(Size - i, i);
        pVector[i] = x;
        pVector[i] = TVector<ValType>(Size - i, i);
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix<ValType>(const TMatrix<ValType>& mt) :TVector<TVector<ValType>>(mt)
{

}

template <class ValType>
TMatrix<ValType>::TMatrix<ValType>(const TVector<TVector<ValType>>& mt) :TVector<TVector<ValType>>(mt)
{

}


template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
    return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
    return !(*this == mt);
}

template <class ValType>
const TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
    return TVector<TVector<ValType>>::operator=(mt);
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
    return TVector<TVector<ValType>>::operator+(mt);
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
    return TVector<TVector<ValType>>::operator-(mt);
}
template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix<ValType>& mt)
{
    if (Size != mt.Size)
        throw "Sizes should be equal!\n";

    TMatrix<ValType> tmp(mt), res(Size);
    for (int i = 0; i < Size; i++)
    {
        for (int j = i; j < Size; j++)
        {
            for (int k = i; k <= j; k++)
            {
                res[i][j] += (*this)[i][k] * tmp[k][j];
            }
        }

    }
    return res;
}



#endif