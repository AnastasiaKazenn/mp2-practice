// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->BitField.GetLength();
}

int TSet::IsMember(const int Elem) const // элемент множества? проверка входит ли в множество
{
    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

const TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s) {
        this->MaxPower = s.MaxPower;
        this->BitField = s.BitField;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (this->BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(this->BitField == s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение 
{
    TSet res(std::max(this->MaxPower, s.MaxPower));
    res.BitField = this->BitField | s.BitField; 
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение  // TODO!!! & bitfield
{
    TSet res(std::max(this->MaxPower, s.MaxPower));
    res.BitField = this->BitField & s.BitField;
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(*this);
    res.BitField = ~res.BitField;
    return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int elem;
    while (istr >> elem)
    {
        s.InsElem(elem);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); ++i)
    {
        if (s.IsMember(i))
            ostr << i << " ";

    }
    return ostr;
}
