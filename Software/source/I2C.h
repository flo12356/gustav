/*
 * I2C.h
 *
 * Created: 11.06.2020 10:27:59
 *  Author: Flo
 */ 


#ifndef I2C_H_
#define I2C_H_

bool i2cInit(int baud);
bool i2cSend(char* data, char adress);
bool i2cRecive(char* data, char adress);



#endif /* I2C_H_ */