/*
 * ADXL345.c
 *
 *  Created on: Aug 6, 2024
 *      Author: ENES
 */

#include "ADXL345.h"
extern I2C_HandleTypeDef hi2c1;

 int ADXL345_ScanDeviceID() {

	 for (uint8_t address= 0; address < 256; address++) {
		 if (HAL_I2C_IsDeviceReady(&hi2c1, address, 1,TIMEOUT)==HAL_OK) {
			 return address;





	 }

 }
 return -1   ;
 }



 ADXL345ReadStatus ADXL345_ReadRegisterData(uint16_t registerAddress,uint16_t sizeofData,uint8_t *dataBuffer){

 	 if(HAL_I2C_Mem_Read(&hi2c1, ADXL345_DEVICE_ADDRESS, registerAddress, 1, dataBuffer, sizeofData, TIMEOUT)==HAL_OK){
 		return READ_FAIL;

 	 }return READ_SUCCESS;

  }






 ADXL345WriteStatus  ADXL345_WriteRegisterData(uint16_t registerAddress,uint16_t value){
	 uint8_t data[2]={0};
	 data[0]=registerAddress;
		  data[1]=value;


if( HAL_I2C_Master_Transmit(&hi2c1, ADXL345_DEVICE_ADDRESS, data, sizeof(data), TIMEOUT)==HAL_OK){
	return WRITE_SUCCESS;
}
return WRITE_FAIL;

 }




 ADXL345InitStatus ADXL345_Init(void){
	 uint8_t dataBuffer=0;
	 ADXL345_ReadRegisterData(DEVID, 1, &dataBuffer);
if (dataBuffer!=0xE5) {
	return INIT_FAIL;


}


uint8_t tempReg=0;
PowerControlRegister_t powerControl={0};
powerControl.Wakeup=WAKEUP_8HZ;
powerControl.AUTO_SLEEP =0x00;
powerControl.Link =0x00;
powerControl.Measure =0x01;
powerControl.Reserved =0x00;
powerControl.Sleep =0x00;
tempReg=*((uint8_t*)&powerControl);



ADXL345_WriteRegisterData(POWER_CTL, tempReg);
DataFormatRegister_t dataFormatControl={0};

dataFormatControl.Range=RANGE_4G;
dataFormatControl.Justify=0x00;
dataFormatControl.FULL_RES=0x00;
dataFormatControl.Reserved=0x00;
dataFormatControl.INT_INVERT=0x00;
dataFormatControl.SPI=0x00;
dataFormatControl.SELF_TEST=0x00;


tempReg=*((uint8_t*)&dataFormatControl);
ADXL345_WriteRegisterData(DATA_FORMAT, tempReg);

BWRATERegister_t BWRATECONTROL={0};

BWRATECONTROL.Range=BANDWIDTH_RATE_800;
BWRATECONTROL.Reserved=0x00;
BWRATECONTROL.LOW_POWER=0x00;

tempReg=*((uint8_t*)&BWRATECONTROL);
ADXL345_WriteRegisterData(BW_RATE, tempReg);







return INIT_SUCCESS;

 }

 int16_t ADXL345_getAxisValue(uint8_t axis){
	 uint8_t data[2]={0};
	 int16_t outputData=0;
	 ADXL345_ReadRegisterData(axis, 2, data[0]);
	 return outputData;




 }

 float ADXL345_getGValue(uint8_t axis,float scaleFactor){
	 int16_t outputData=0;
	 float gData=0;
	 outputData=ADXL345_getAxisValue(axis);
	 gData=(float)(outputData*scaleFactor);
			 return gData;


 }






