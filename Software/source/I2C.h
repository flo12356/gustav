/*
 * I2C.h
 *
 * Created: 11.06.2020 10:27:59
 *  Author: Flo
 */ 


#ifndef I2C_H_
#define I2C_H_

bool i2cInit(int freq);
bool i2cSend(char* data, char adress, int dataLen);
bool i2cRecive(char* data, char adress, int* dataLen);

enum CLKDIV{
	CLKDIV1,
	CLKDIV4,
	CLKDIV16,
	CLKDIV64	
	};


#endif /* I2C_H_ */