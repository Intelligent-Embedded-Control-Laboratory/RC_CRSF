// 2023-01-21

#pragma once

#include <Arduino.h>

class RC_CRSF
{
public:
	enum CRSF_STATUS : int
	{
		CRSF_OK,
		CRSF_NO_DATA,
		CRSF_LOST_BEGIN_BYTES
	};
	void begin(HardwareSerial &_pSerial, uint32_t baud);
	int read(uint16_t *_dest_channels);

protected:
	const uint8_t start_byte[3] = {0xC8, 0x18, 0x16};
	HardwareSerial *pSerial;
	uint8_t buf[32];
	int is_update;
	void parse_data(uint16_t *_dest_channels, uint8_t *_buffer);
};