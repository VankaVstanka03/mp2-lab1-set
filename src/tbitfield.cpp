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
        throw std::invalid_argument("Length can't be negative");
    }
    this->BitLen = len;
    if (BitLen % sizeof(TELEM) == 0) {
        this->MemLen = BitLen / sizeof(TELEM);
    }
    else {
        this->MemLen = BitLen / sizeof(TELEM) + 1;
    }
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
   
    return (MemLen - 1) - (n / sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return (TELEM)1 << (n % sizeof(TELEM));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0) {
        throw std::invalid_argument("Bit can't be negative");
    }
    TELEM tmp = pMem[GetMemIndex(n)] | GetMemMask(n);
    pMem[GetMemIndex(n)] = tmp;
    //pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0) {
        throw std::invalid_argument("Bit can't be negative");
    }
    TELEM tmp = pMem[GetMemIndex(n)] & ~GetMemMask(n);
    pMem[GetMemIndex(n)] = tmp;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0) {
        throw std::invalid_argument("Bit can't be negative");
    }
  return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n % sizeof(TELEM));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return TBitField(0);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
    return TBitField(0);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
