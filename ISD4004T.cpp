
/*  last update 20/09/24 */
/*  Avi Hayun */

#include "ISD4004T.h"
#include "Arduino.h"
#include "SPI.h"

#define POWERUP 0x20
#define STOP    0x30
#define SETREC  0xa0
#define SETPLAY 0xe0
#define  STOPPOWERDOWN 0x10 

SPISettings mySetting;


ISD4004::ISD4004() 
{
	_latchPin = 14;
	_eomPin=22;
	pinMode (_latchPin, OUTPUT); //just in case _latchPin is not 10 or 53 set it to output
	pinMode(_eomPin,INPUT_PULLUP);
}

ISD4004::ISD4004(uint8_t ssPin) 
{
	_latchPin = ssPin;
	_eomPin=22;
	pinMode (_latchPin, OUTPUT); //just in case _latchPin is not 10 or 53 set it to output
	pinMode(_eomPin,INPUT_PULLUP);
}

ISD4004::ISD4004(uint8_t ssPin,uint8_t intPin)
{
	_latchPin = ssPin;
	_eomPin=intPin;
	pinMode (_latchPin, OUTPUT); //just in case _latchPin is not 10 or 53 set it to output
	pinMode(_eomPin,INPUT_PULLUP);
}


void ISD4004::begin()//(uint8_t ssPin) 
{
	digitalWrite(_latchPin, HIGH);
	SPI.begin(); 
}


void ISD4004::spiSendOut(uint8_t value) 
{
	digitalWrite(_latchPin, LOW);
	SPI.transfer(value);
	digitalWrite(_latchPin, HIGH); 
}


void ISD4004::spiSendOutAddCode(uint16_t Add,uint8_t Cod)
{
	digitalWrite(_latchPin, LOW);
	SPI.transfer(Add);
	SPI.transfer(Add>>8);
	SPI.transfer(Cod);
	digitalWrite(_latchPin, HIGH);
}

void ISD4004::Play(uint16_t Add)
{
	SPI.endTransaction();

	mySetting=SPISettings();

	SPI.beginTransaction(SPISettings(SPI_ISD, LSBFIRST, SPI_MODE0));
	Add=(Add*5)/2; //sec

	spiSendOut(POWERUP); 
	delay(60);    //60msec
	spiSendOutAddCode(Add,SETPLAY); //send address+setplay

	delay(110);//Tstop
	SPI.endTransaction();
	//SPI.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, SPI_MODE0));
	SPI.beginTransaction(mySetting);

}


void ISD4004::PlayInt(uint16_t Add)
{
	SPI.endTransaction();
	mySetting=SPISettings();

	SPI.beginTransaction(SPISettings(SPI_ISD, LSBFIRST, SPI_MODE0));
	Add=(Add*5)/2; //sec

	spiSendOut(POWERUP); 
	delay(60);    //60msec
	spiSendOutAddCode(Add,SETPLAY); //send address+setplay

	while(digitalRead(_eomPin));
	spiSendOut(STOPPOWERDOWN);  

	delay(110);//Tstop
	SPI.endTransaction();
	//SPI.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, SPI_MODE0));
	SPI.beginTransaction(mySetting);

}


void ISD4004::StartRecord(uint16_t Add)
{	
	SPI.endTransaction();
	mySetting=SPISettings();

	SPI.beginTransaction(SPISettings(SPI_ISD, LSBFIRST, SPI_MODE0));
	Add=(Add*5)/2; //sec
	delay(20);

	spiSendOut(POWERUP); 
	delay(60);    //60msec
	spiSendOut(POWERUP);  
	delay(110);
	spiSendOutAddCode(Add,SETREC); //send address+setrec
	SPI.endTransaction();
	//SPI.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, SPI_MODE0));
	SPI.beginTransaction(mySetting);

}

void ISD4004::StopRecord()
{
	SPI.endTransaction();
	mySetting=SPISettings();

	SPI.beginTransaction(SPISettings(SPI_ISD, LSBFIRST, SPI_MODE0));
	spiSendOut(STOPPOWERDOWN);  
	delay(110); //Tstop
	SPI.endTransaction();
	//SPI.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, SPI_MODE0));
	SPI.beginTransaction(mySetting);

}




