/*
 * I2C.cpp
 *
 * Created: 11.06.2020 10:27:43
 *  Author: Flo
 */ 

private void sendStart();


bool i2cInit(int baud)
{
	
}


bool i2cSend(char* data, char adress)
{
	sendStart();
	//Wait for start send in TWSR
	
	//Write Slav W in TWDR
	
	//Write TWCR to send
	
	//Set TWINT to write
	
	//Wait for TWINT flag in TWCR
	
	//Check in TWSR if successfully
	
	//Write first data to TWDR+
	
	//Set TWINT to write (clear FLAG with writing one on TWINT in TWCR)
}


bool i2cRecive(char* data, char adress)
{
	sendStart();	
}


private void sendStart()
{
	
}