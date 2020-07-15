/*
 * I2C.cpp
 *
 * Created: 11.06.2020 10:27:43
 *  Author: Flo
 */ 

private void sendStart();


bool i2cInit(int baud)
{
	
	TWCR |= TWEN; //Enables TWI
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
	if(TWSR == 0x18)
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


bool i2cRecive(char* data, char adress)
{
	sendStart();	
	
	//Wait for start send in TWSR
		
	//Write Slav R in TWDR
	
	//Set TWINT to write
	
	//Wait for TWINT
	
	//Check status code in TWSR
	
	//Data is available in TWDR when TWINT is HIGH
	
	//Send NACK after last byte
	
	//Send STOP by writing TWCR
}


private void sendStart()
{
	TWCR |= TWSTA; //Start signal
	TWCR |= TWINT; //Send current order
}

private void sendStop()
{
	TWCR |= TWSTO; //Stop signal
	TWCR |= TWINT; //Send current oder
}