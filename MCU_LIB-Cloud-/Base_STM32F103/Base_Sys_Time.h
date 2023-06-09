#ifndef _SYS_TIME_H__
#define _SYS_TIME_H__

#ifdef DEFAULT
#include "items.h"              //默认功能
#endif

#ifndef DEFAULT
#include "User_items.h"         //自行设置功能，一般出现在本地文件的User中
#endif

/*
Tick_Set_CMP 不可以大于 2的24次方 16,777,216；也就是16M最大
*/

#define Tick_Frequency (MCU_SYS_Freq)   //滴答分频（1分频）
#define Tick_Set_CMP (Tick_Frequency / 8)   //设置滴答初始值(/8 就是 1/8 s)
#define Tick_Over_IT (0.125)                 //定时器溢出时间（24位滴答才有）


/* 【宏函数群】 会给到 mode  */

//很长的时间戳（一天）
struct _SYS_Ticktime
{
    volatile uint32_t SYS_Tick_H; //每Frequency进1
    volatile uint32_t SYS_Tick_L; // 24bit 的
};

extern struct _SYS_Ticktime SYS_Ticktime;

// source
uint64_t GET_SysTick(void); //请在空闲时尽可能调用它
void SET_SysTick(uint64_t time);

// Init
void Sys_Time_Init(int Set);

// Delay
void SYS_Delay_us(int n);
void SYS_Delay_ms(int n);
void SYS_Delay_S(int n);

#endif
