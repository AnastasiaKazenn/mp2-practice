// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(1)
{
    this->MaxPower = mp;
    this->BitField = TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(1)
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(1)
{
    this->MaxPower = bf.GetLength();
    this->BitField = bf;
}

TSet::operator TBitField()
{
    return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem >= this->MaxPower) return 0;
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
    this->MaxPower = s.GetMaxPower();
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (this->BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return (this->BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение // !!!!
{
    TSet ts(max(this->GetMaxPower(), s.GetMaxPower()));
    ts.BitField = this->BitField | s.BitField;
    
    return ts;
}

TSet TSet::operator+(const int Elem) // объединение с элементом// !!!!
{
    TSet ts(this->BitField);
    ts.InsElem(Elem);
    return ts;
}

TSet TSet::operator-(const int Elem) // разность с элементом// !!!!
{
    TSet ts(this->BitField);
    ts.DelElem(Elem);
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet t1(max(this->GetMaxPower(), s.GetMaxPower()));
    t1.BitField =  this->BitField & s.BitField;
    return t1;
}

TSet TSet::operator~(void) // дополнение // !!!!
{
    TSet ts(this->GetMaxPower());
    ts.BitField = ~this->BitField;
    return ts;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int n;
    do {
        cout << "Enter an element of the set :" << endl;
        cin >> n;
        s.InsElem(n);
    } while (s.GetMaxPower() <= n && n < 0);    
    istr >> s;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << "Data set: " << endl;
    ostr << "{ ";
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i)) {
            ostr << i << " ";
        }

    }
    ostr<<"}" << endl;
    return ostr;
}
