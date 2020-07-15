/*
 * I2C.cpp
 *
 * Created: 11.06.2020 10:27:43
 *  Author: Flo
 */ 

#include <avr/io.h>

void sendStart()
{
	TWCR |= TWSTA; //Start signal
	TWCR |= TWINT; //Send current order
}

void sendStop()
{
	TWCR |= TWSTO; //Stop signal
	TWCR |= TWINT; //Send current oder
}

bool i2cInit(int freq)
{
	TWBR = 0x03; //only for test set fix at 400kHz, ToDo: variable freq
	TWSR &= 0xFC;
	
	TWCR |= TWEN; //Enables TWI
	
	return true;
}


bool i2cSend(char* data, char adress, int dataLen)
{
	sendStart();
	
	//Wait for start send in TWSR
	while((TWCR & 0x80) == false); //Wait for TWINT flag
	if (TWSR != 0x08) //Check if correct status code
		return false;
	
	//Write Slav W in TWDR
	TWDR = ((adress << 0x01) | 0x01);	//Sla+W
	
	//Write TWCR to send
	TWCR &= 0xCF;	//Clear start and stop
	TWCR |= 0x80;	//Send oder
	
	//Wait for TWINT flag in TWCR
	while((TWCR & 0x80) == false); //Wait for TWINT flag
	
	//Check in TWSR if successfully
	if(TWSR == 0x18);
	else
		return false;
	
	//Write data to TWDR
	
	for (int i=0; i<dataLen; i++)
	{
		TWDR = data[i];
		TWCR |= 0x80; //Send data byte
		
		while((TWCR & 0x80) == false); //Wait for TWINT flag
		
		//Check in TWSR if successfully
		if(TWSR != 0x28)
			return false;
	}	
	
	//Write TWCR to STOP
	sendStop();
	
	return true;	
}


bool i2cRecive(char* data, char adress, int dataLen)
{
	sendStart();	
	
	//Wait for start send in TWSR
	while((TWCR & 0x80) == false); //Wait for TWINT flag
	if (TWSR != 0x08) //Check if correct status code
		return false;
	
	//Write Slav R in TWDR
	TWDR = ((adress << 0x01));	//Sla+R
	
	//Set TWINT to write
	TWCR &= 0xCF;	//Clear start and stop
	TWCR |= 0x80;	//Send oder
	
	//Wait for TWINT
	while((TWCR & 0x80) == false); //Wait for TWINT flag
	
	//Check status code in TWSR
		if(TWSR == 0x40);
		else
			return false;
	
	//Data is available in TWDR when TWINT is HIGH
	for (int i=0; i<(dataLen-1); i++)
	{
		while((TWCR & 0x80) == false);//Wait for TWINT flag
		data[i] = TWDR;
		TWCR |= TWEA;
		TWCR |= TWINT;
		
		while((TWCR & 0x80) == false);//Wait for TWINT flag
		//Check in TWSR if successfully
		if(TWSR != 0x50)
			return false;
	}
	
	
	//Send NACK after last byte
	while((TWCR & 0x80) == false);//Wait for TWINT flag
	data[dataLen] = TWDR;
	TWCR &= (TWEA | TWSTO | TWSTA);
	TWCR |= TWINT;
	
	
	while((TWCR & 0x80) == false);//Wait for TWINT flag
	if(TWSR != 0x58)
		return false;
	
	//Send STOP by writing TWCR
	sendStop();
	
	return true;
}


