/*  last update 20/09/24 */
/*  Avi Hayun */

#ifndef ISD4004_h
#define ISD4004_h

#include <SPI.h>

/* SPI transaction Settings */
//#define SPI_FREQUENCY  12000000
#define SPI_ISD  500000

//#define TFT_SPI_MODE SPI_MODE0

class ISD4004 //: public Print
{
public:
	ISD4004(); 
	ISD4004(uint8_t ssPin);
	ISD4004(uint8_t ssPin,uint8_t intPin); 

	void begin();
	void Play(uint16_t Add);
	void PlayInt(uint16_t Add);
	void StartRecord(uint16_t Add);
	void StopRecord();
	uint8_t _latchPin;
	uint8_t _eomPin;
private:

	void spiSendOut(uint8_t value);
	void spiSendOutAddCode(uint16_t Add,uint8_t Cod);

};

#endif
