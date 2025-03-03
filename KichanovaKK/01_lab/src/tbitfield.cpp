// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


TBitField::TBitField(int len)
{
    if (len < 0) {
        throw "Negative length";
    }
    BitLen = len;
    MemLen = (len/(sizeof(TELEM)*8))+1; 
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] this->pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen) {
        throw "Bit index out of range";
    }
    return n/ (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n(n=1, остальные = 0)
{
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 && n >= BitLen)
    {
        throw "Bit index out of range";
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит 
{
    if (n < 0 && n >= BitLen) {
        throw "Bit index out of range";
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита 
{
    if (n < 0 && n >= BitLen) {
        throw "Bit index out of range";
    }
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

const TBitField& TBitField::operator=(const TBitField &bf) // присваивание для копирования битового поля.
{
    if (this == &bf) {
        return *this;
    }
    if (MemLen != bf.MemLen)
    {
        delete[] pMem;
        MemLen = bf.MemLen;
    }    
    BitLen = bf.BitLen;
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen) {
        return 0;
    }

    for (int i = 0; i < MemLen; ++i) {
        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int max_len = std::max(BitLen, bf.BitLen);
    TBitField res(max_len);

    for (int i = 0; i < (std::min(MemLen, bf.MemLen)); ++i) {
        res.pMem[i] = this->pMem[i] | bf.pMem[i];
    }

    if (MemLen > bf.MemLen) {
        for (int i = (std::min(MemLen, bf.MemLen)); i < max_len / 8; ++i) {
            res.pMem[i] = this->pMem[i];
        }
    }
    else {
        for (int i = (std::min(MemLen, bf.MemLen)); i < max_len / 8; ++i) {
            res.pMem[i] = bf.pMem[i];
        }
    }

    return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int max_len = std::max(BitLen, bf.BitLen);
    TBitField res(max_len);

    for (int i = 0; i < (std::min(MemLen, bf.MemLen)); ++i) {
        res.pMem[i] = this->pMem[i] & bf.pMem[i];
    }

    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);

    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~pMem[i];
    }
    int LastElem = BitLen % (sizeof(TELEM) * 8);
    if (LastElem != 0) {
        TELEM mask = (static_cast<TELEM>(1 << LastElem) - 1);
        res.pMem[MemLen - 1] &= mask;
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char sy;
    int bitindex = 0;
    for (int i = 0; i < bf.GetLength(); i++) {
        bf.ClrBit(i);
    }
    while (bitindex < bf.GetLength()) {
        istr >> sy;
        if (sy == '1') {
            bf.SetBit(bitindex);
            bitindex++;
        }
        else if (sy == '0') {
            bf.ClrBit(bitindex);
            bitindex++;
        }
        else {
            throw "Invalid bit input";
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++) {
        if (bf.GetBit(i) == 1)
            ostr << '1';
        else
            ostr << '0';
    }

    return ostr;
}
