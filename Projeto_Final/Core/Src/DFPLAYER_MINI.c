/*
 * DFPLAYER_MINI.c
 *
 *  Created on: May 16, 2020
 *      Author: controllerstech
 */

#include "stm32f0xx_hal.h"
#include "stdio.h"
#include "OledDriver.h"
#include "OledGrph.h"
#include "OledChar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern UART_HandleTypeDef huart1;
#define DF_UART &huart1

#define Source      0x02  // TF CARD

#define Decrease_Key   GPIO_PIN_3
#define Decrease_Port  GPIOA
#define Increase_Key   GPIO_PIN_4
#define Increase_Port  GPIOA
#define Next_Key       GPIO_PIN_6
#define Next_Port      GPIOA
#define Pause_Key      GPIO_PIN_1
#define Pause_Port     GPIOB

/*************************************** NO CHANGES AFTER THIS *************************************************/

int ispause    = 0;
int isplaying  = 1;
int volume     = 16;

# define Start_Byte 0x7E
# define End_Byte   0xEF
# define Version    0xFF
# define Cmd_Len    0x06
# define Feedback   0x00    //If need for Feedback: 0x01,  No Feedback: 0

void Send_cmd (uint8_t cmd, uint8_t Parameter1, uint8_t Parameter2)
{
	uint16_t Checksum = Version + Cmd_Len + cmd + Feedback + Parameter1 + Parameter2;
	Checksum = 0-Checksum;

	uint8_t CmdSequence[10] = { Start_Byte, Version, Cmd_Len, cmd, Feedback, Parameter1, Parameter2, (Checksum>>8)&0x00ff, (Checksum&0x00ff), End_Byte};

	HAL_UART_Transmit(DF_UART, CmdSequence, 10, HAL_MAX_DELAY);
}

void DF_PlayFromStart(void)
{
	Send_cmd(0x03,0x00,0x01);
	HAL_Delay(200);
	Send_cmd(0x11,0x00,0x01);
	HAL_Delay(200);

	OledSetCursor(0,0);
	OledPutString("Volume:16");
	OledSetCursor(0,2);
	OledPutString("Reproduzindo");
}

void DF_Init (uint8_t volume)
{
	Send_cmd(0x3F, 0x00, Source);
	HAL_Delay(200);
	Send_cmd(0x06, 0x00, volume);
	HAL_Delay(500);
}

void DF_Next (void)
{
	if(isplaying)
	{
		Send_cmd(0x01, 0x00, 0x00);
		HAL_Delay(200);
	}
}

void DF_Pause (void)
{
	Send_cmd(0x0E, 0, 0);
	HAL_Delay(200);

	OledSetCursor(0,2);
	OledPutString("              ");
	OledSetCursor(0,2);
	OledPutString("Pausado");
}

void DF_Playback (void)
{
	Send_cmd(0x0D, 0, 0);
	HAL_Delay(200);

	OledSetCursor(0,2);
	OledPutString("              ");
	OledSetCursor(0,2);
	OledPutString("Reproduzindo");
}

void DF_IncreaseVolume (void)
{
	Send_cmd(0x04, 0, 0);
	HAL_Delay(200);

	if (volume <= 29)
	{
		volume++;
		char string[2];
		itoa(volume, string, 10);

		OledSetCursor(7,0);
		OledPutString("  ");
		OledSetCursor(7,0);
		OledPutString(string);

		if (volume == 30)
		{
			OledSetCursor(0,4);
			OledPutString("Volume maximo!");
		}
	}
}

void DF_DecreaseVolume (void)
{
	Send_cmd(0x05, 0, 0);
	HAL_Delay(200);

	if (volume >= 1)
	{
		volume--;
		char string[2];
		itoa(volume, string, 10);

		OledSetCursor(7,0);
		OledPutString("  ");
		OledSetCursor(7,0);
		OledPutString(string);

		if (volume == 29)
		{
			OledSetCursor(0,4);
			OledPutString("              ");
		}
	}
}

void Check_Key (void)
{
	if (HAL_GPIO_ReadPin(Pause_Port, Pause_Key))
	{
		while (HAL_GPIO_ReadPin(Pause_Port, Pause_Key));
		if (isplaying)
		{
			ispause = 1;
			isplaying = 0;
			DF_Pause();
		}

		else if (ispause)
		{
			isplaying = 1;
			ispause = 0;
			DF_Playback();
		}
	}

	if (HAL_GPIO_ReadPin(Decrease_Port, Decrease_Key))
	{
		while (HAL_GPIO_ReadPin(Decrease_Port, Decrease_Key));
		DF_DecreaseVolume();
	}

	if (HAL_GPIO_ReadPin(Increase_Port, Increase_Key))
	{
		while (HAL_GPIO_ReadPin(Increase_Port, Increase_Key));
		DF_IncreaseVolume();
	}

	if (HAL_GPIO_ReadPin(Next_Port, Next_Key))
	{
		while (HAL_GPIO_ReadPin(Next_Port, Next_Key));
		DF_Next();
	}
}















