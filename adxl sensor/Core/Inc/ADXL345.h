/*
 * ADXL345.h
 *
 *  Created on: Aug 6, 2024
 *      Author: ENES
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_
#include "main.h"


#define ADXL345_DEVICE_ADDRESS   0xA6
#define  DEVID           0x00
#define  THRESH_TAP      0x1D
#define  OFSX            0x1E
#define  OFSY            0x1F
#define  OFSZ            0x20
#define  DUR             0x21
#define  LATENT          0x22
#define  WINDOW          0x23
#define  THRESH_ACT      0x24
#define  THRESH_INACT    0x25
#define  TIME_INACT      0x26
#define  ACT_INACT_CTL   0x27
#define  THRESH_FF       0x28
#define  TIME_FF         0x29
#define  TAP_AXES        0x2A
#define  ACT_TAP_STATUS  0x2B
#define  BW_RATE         0x2C
#define  POWER_CTL       0x2D
#define  INT_ENABLE      0x2E
#define  INT_MAP         0x2F
#define  INT_SOURCE      0x30
#define  DATA_FORMAT     0x31
#define  DATAX0          0x32
#define  DATAX1          0x33
#define  DATAY0          0x34
#define  DATAY1          0x35
#define  DATAZ0          0x36
#define  DATAZ1          0x37
#define  FIFO_CTL        0x38
#define  FIFO_STATUS     0x39
#define  TIMEOUT        1000

#define  WAKEUP_8HZ      0X00
#define  WAKEUP_4HZ      0X01
#define  WAKEUP_2HZ      0X02
#define  WAKEUP_1HZ      0X03

#define RANGE_2G          0X00
#define  RANGE_4G    0X01
#define  RANGE_8G      0X02
#define  RANGE_16G     0X03

#define  BANDWIDTH_RATE_1600  0X0F
#define  BANDWIDTH_RATE_800  0X0E

#define  BANDWIDTH_RATE_400  0X0D

#define  BANDWIDTH_RATE_200  0X0C

#define  BANDWIDTH_RATE_100  0X0B

#define  BANDWIDTH_RATE_50 0X0A
#define  BANDWIDTH_RATE_25  0X09

#define 	X      DATAX0
#define     Y      DATAY0
#define     Z      DATAZ0

#define  SCALE_FACTOR_2G  (float)1/256.0
#define  SCALE_FACTOR_4G  (float)1/128.0
#define  SCALE_FACTOR_8G  (float)1/64.0
#define  SCALE_FACTOR_16G  (float)1/32.0



















typedef enum {
	READ_FAIL =0,
	READ_SUCCESS =1,
}ADXL345ReadStatus;

typedef enum {
	INIT_FAIL =0,
	INIT_SUCCESS =1,
}ADXL345InitStatus;


typedef enum {
	WRITE_FAIL =0,
	WRITE_SUCCESS =1,
}ADXL345WriteStatus;





typedef struct {
	uint8_t Wakeup:2 ;
	uint8_t Sleep:1 ;
	uint8_t Measure:1 ;
	uint8_t AUTO_SLEEP:1 ;
	uint8_t Link:1  ;
	uint8_t Reserved:2 ;
}PowerControlRegister_t;

typedef struct {
	uint8_t Range:2 ;
	uint8_t Justify:1 ;
	uint8_t FULL_RES:1 ;
	uint8_t Reserved:1 ;
	uint8_t INT_INVERT:1  ;
	uint8_t SPI:1 ;
	uint8_t SELF_TEST:1;
}DataFormatRegister_t;


typedef struct {
	uint8_t Range:4 ;
	uint8_t LOW_POWER:1;

	uint8_t Reserved:3 ;



}BWRATERegister_t;













int16_t ADXL345_getAxisValue(uint8_t axis);
float ADXL345_getGValue(uint8_t axis,float scaleFactor);



 int ADXL345_ScanDeviceID(void);
 ADXL345InitStatus ADXL345_Init(void);

 ADXL345ReadStatus  ADXL345_ReadRegisterData(uint16_t registerAddress,uint16_t sizeofData,uint8_t *dataBuffer);


 ADXL345WriteStatus  ADXL345_WriteRegisterData(uint16_t registerAddress,uint16_t value);


#endif /* INC_ADXL345_H_ */




