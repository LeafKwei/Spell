#ifndef SPELL_MODES_HPP
#define SPELL_MODES_HPP

#include "def/types.hpp"

/* 内存(0) */
constexpr regsize_t MODE_MEM = 0;

/* 设备(1)*/
constexpr regsize_t MODE_DEV = 1;

/* 寄存器(范围127~255) */
constexpr regsize_t MODE_QAX = 130;
constexpr regsize_t MODE_QBX = 131;
constexpr regsize_t MODE_QCX = 132;
constexpr regsize_t MODE_QDX = 133;
constexpr regsize_t MODE_QEX = 134;
constexpr regsize_t MODE_QFX = 135;
constexpr regsize_t MODE_QGX = 136;
constexpr regsize_t MODE_QHX = 137;
constexpr regsize_t MODE_QIX = 138;
constexpr regsize_t MODE_QJX = 139;
constexpr regsize_t MODE_QKX = 140;
constexpr regsize_t MODE_QLX = 141;
constexpr regsize_t MODE_QMX = 142;
constexpr regsize_t MODE_QNX = 143;
constexpr regsize_t MODE_QOX = 144;
constexpr regsize_t MODE_QPX = 145;
constexpr regsize_t MODE_QQX = 146;
constexpr regsize_t MODE_QRX = 147;
constexpr regsize_t MODE_QSX = 148;
constexpr regsize_t MODE_QTX = 149;
constexpr regsize_t MODE_QUX = 150;
constexpr regsize_t MODE_QVX = 151;
constexpr regsize_t MODE_QWX = 152;
constexpr regsize_t MODE_QXX = 153;
constexpr regsize_t MODE_QYX = 154;
constexpr regsize_t MODE_QZX = 155;

/* 通用寄存器 */
constexpr regsize_t MODE_QC0 = 160;
constexpr regsize_t MODE_QC1 = 161;
constexpr regsize_t MODE_QC2 = 162;
constexpr regsize_t MODE_QC3 = 163;
constexpr regsize_t MODE_QC4 = 164;
constexpr regsize_t MODE_QC5 = 165;
constexpr regsize_t MODE_QC6 = 166;
constexpr regsize_t MODE_QC7 = 167;
constexpr regsize_t MODE_QC8 = 168;
constexpr regsize_t MODE_QC9 = 169;

#endif