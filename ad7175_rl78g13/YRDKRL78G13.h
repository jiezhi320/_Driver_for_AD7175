/***************************************************************************//**
 *   @file   YRDKRL78G13.h
 *   @brief  Header file of YRDKRL78G13 Driver.
 *   @author DBogdan (dragos.bogdan@analog.com)
********************************************************************************
 * Copyright 2012(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
********************************************************************************
 *   SVN Revision: 750
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include <ior5f100le.h>
#include <ior5f100le_ext.h>
#include <intrinsics.h>

/******************************************************************************/
/**************************** GPIO Definitions ********************************/
/******************************************************************************/
#define ST7579_CS_PIN       0x01
#define ST7579_CS_PIN_OUT   PM1 &= ~ST7579_CS_PIN;
#define ST7579_CS_LOW       P1 &= ~ST7579_CS_PIN;
#define ST7579_CS_HIGH	    P1 |=  ST7579_CS_PIN;

#define ST7579_RS_PIN       0x20
#define ST7579_RS_PIN_OUT   PM1 &= ~ST7579_RS_PIN;
#define ST7579_RS_LOW       P1 &= ~ST7579_RS_PIN;
#define	ST7579_RS_HIGH	    P1 |=  ST7579_RS_PIN;

#define PMOD1_CS_PIN        (1 << 1)
#define PMOD1_CS_OUT        PM7 &= ~(PMOD1_CS_PIN);
#define PMOD1_CS_LOW        P7 &= ~PMOD1_CS_PIN;
#define PMOD1_CS_HIGH       P7 |=  PMOD1_CS_PIN;

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/

/* Initializes YRDKRL78G13. */
void YRDKRL78G13_Init(void);

/* Resets YRDKRL78G13. */
void YRDKRL78G13_Reset(void);