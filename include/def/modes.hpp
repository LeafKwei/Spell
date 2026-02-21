#ifndef SPELL_MODES_HPP
#define SPELL_MODES_HPP

#include "def/types.hpp"

/* 内存(范围0) */
constexpr regsize_t MODE_MEM = 0;

/* 特殊寄存器(范围1~127) */
constexpr regsize_t MODE_QAX = 1;
constexpr regsize_t MODE_QBX = 2;
constexpr regsize_t MODE_QCX = 3;
constexpr regsize_t MODE_QDX = 4;
constexpr regsize_t MODE_QEX = 5;
constexpr regsize_t MODE_QFX = 6;
constexpr regsize_t MODE_QGX = 7;
constexpr regsize_t MODE_QHX = 8;
constexpr regsize_t MODE_QIX = 9;
constexpr regsize_t MODE_QJX = 10;
constexpr regsize_t MODE_QKX = 11;
constexpr regsize_t MODE_QLX = 12;
constexpr regsize_t MODE_QMX = 13;
constexpr regsize_t MODE_QNX = 14;
constexpr regsize_t MODE_QOX = 15;
constexpr regsize_t MODE_QPX = 16;
constexpr regsize_t MODE_QQX = 17;
constexpr regsize_t MODE_QRX = 18;
constexpr regsize_t MODE_QSX = 19;
constexpr regsize_t MODE_QTX = 20;
constexpr regsize_t MODE_QUX = 21;
constexpr regsize_t MODE_QVX = 22;
constexpr regsize_t MODE_QWX = 23;
constexpr regsize_t MODE_QXX = 24;
constexpr regsize_t MODE_QYX = 25;
constexpr regsize_t MODE_QZX = 26;

/* 通用寄存器(范围128~255) */
constexpr regsize_t MODE_QC0 = 128;
constexpr regsize_t MODE_QC1 = 129;
constexpr regsize_t MODE_QC2 = 130;
constexpr regsize_t MODE_QC3 = 131;
constexpr regsize_t MODE_QC4 = 132;
constexpr regsize_t MODE_QC5 = 133;
constexpr regsize_t MODE_QC6 = 134;
constexpr regsize_t MODE_QC7 = 135;
constexpr regsize_t MODE_QC8 = 136;
constexpr regsize_t MODE_QC9 = 137;

#endif