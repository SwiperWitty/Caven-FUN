/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_conf.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : This file contains all the functions prototypes for the  
 *                      USB configration firmware library.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/ 
#ifndef __USB_CONF_H
#define __USB_CONF_H


#define EP_NUM                          (3)  // dd-dd

/* Buffer Description Table */
/* buffer table base address */
/* buffer table base address */
#define BTABLE_ADDRESS      (0x00)

/* EP0  */
/* rx/tx buffer base address */
#define ENDP0_RXADDR        (0x40)
#define ENDP0_TXADDR        (0x80)

/* EP1  */
/* tx buffer base address */
#define ENDP1_TXADDR        (0xC0)
#define ENDP1_RXADDR        (ENDP1_TXADDR + 0x40)
#define ENDP2_TXADDR        (ENDP1_RXADDR + 0x40)
#define ENDP2_RXADDR        (ENDP2_TXADDR + 0x40)          // dd-dd

// #define ENDP3_TXADDR        (ENDP2_RXADDR + 0x10)
// #define ENDP3_RXADDR        (ENDP3_TXADDR + 0x10)
// #define ENDP4_TXADDR        (ENDP3_RXADDR + 0x10)
// #define ENDP4_RXADDR        (ENDP4_TXADDR + 0x10)
// #define ENDP5_TXADDR        (ENDP4_RXADDR + 0x10)
// #define ENDP5_RXADDR        (ENDP5_TXADDR + 0x10)
// #define ENDP6_TXADDR        (ENDP5_RXADDR + 0x10)
// #define ENDP6_RXADDR        (ENDP6_TXADDR + 0x10)
// #define ENDP7_TXADDR        (ENDP6_RXADDR + 0x10)
// #define ENDP7_RXADDR        (ENDP7_TXADDR + 0x10)
/* ISTR events */
/* IMR_MSK */
/* mask defining which events has to be handled */
/* by the device application software */
#define IMR_MSK (CNTR_CTRM  | CNTR_WKUPM | CNTR_SUSPM | CNTR_ERRM  | CNTR_SOFM \
                 | CNTR_ESOFM | CNTR_RESETM )

/*#define CTR_CALLBACK*/
/*#define DOVR_CALLBACK*/
/*#define ERR_CALLBACK*/
/*#define WKUP_CALLBACK*/
/*#define SUSP_CALLBACK*/
/*#define RESET_CALLBACK*/
#define SOF_CALLBACK
/*#define ESOF_CALLBACK*/


/* CTR service routines */
/* associated to defined endpoints */
//#define  EP1_IN_Callback   NOP_Process          // dd-dd
/*#define  EP2_IN_Callback   NOP_Process*/
#define  EP3_IN_Callback   NOP_Process
#define  EP4_IN_Callback   NOP_Process
#define  EP5_IN_Callback   NOP_Process
#define  EP6_IN_Callback   NOP_Process
#define  EP7_IN_Callback   NOP_Process

//#define  EP1_OUT_Callback   NOP_Process         // dd-dd
/*#define  EP2_OUT_Callback   NOP_Process*/
#define  EP3_OUT_Callback   NOP_Process
#define  EP4_OUT_Callback   NOP_Process
#define  EP5_OUT_Callback   NOP_Process
#define  EP6_OUT_Callback   NOP_Process
#define  EP7_OUT_Callback   NOP_Process

#endif /* __USB_CONF_H */






