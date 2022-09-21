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
    this->MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    pMem = new TELEM[bf.MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
   
    return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return (TELEM)1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n > BitLen) {
        throw std::invalid_argument("Bit can't be negative");
    }
    TELEM tmp = pMem[GetMemIndex(n)] | GetMemMask(n);
    pMem[GetMemIndex(n)] = tmp;
    //pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n > BitLen) {
        throw std::invalid_argument("Bit can't be negative");
    }
    TELEM tmp = pMem[GetMemIndex(n)] & ~GetMemMask(n);
    pMem[GetMemIndex(n)] = tmp;
}

void TBitField::ClrForNegBit(const int n)
{
    if (n < 0) {
        throw std::invalid_argument("Bit can't be negative");
    }
    TELEM tmp = pMem[GetMemIndex(n)] & ~GetMemMask(n);
    pMem[GetMemIndex(n)] = tmp;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > BitLen) {
        throw std::invalid_argument("Bit can't be negative");
    }
  return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n % (sizeof(TELEM) * 8));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    TELEM* copy = new TELEM[bf.MemLen];
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    for (int i = 0; i < MemLen; i++) {
        copy[i] = bf.pMem[i];
    }
    delete[] pMem;
    pMem = copy;
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (this->BitLen != bf.BitLen || this->MemLen != bf.MemLen) {
        return 0;
    }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }

  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return ~(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField res(this->BitLen > bf.BitLen ? this->BitLen : bf.BitLen);
    int minMem = this->MemLen > bf.MemLen ? bf.MemLen : this->MemLen;
    for (int i = 0; i < minMem; i++) {
        res.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField res(this->BitLen > bf.BitLen ? this->BitLen : bf.BitLen);
    int minMem = this->MemLen > bf.MemLen ? bf.MemLen : this->MemLen;
    for (int i = 0; i < minMem; i++) {
        res.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(this->BitLen);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~(this->pMem[i]);
    }
    for (int i = BitLen; i < (sizeof(TELEM) * 8) * MemLen; i++) {
        res.ClrForNegBit(i);
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
