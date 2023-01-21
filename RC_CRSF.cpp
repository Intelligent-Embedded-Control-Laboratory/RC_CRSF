// 2023-01-21

#include "RC_CRSF.h"

void RC_CRSF::begin(HardwareSerial &_pSerial, uint32_t baud)
{
    pSerial = &_pSerial;
    pSerial->begin(baud);
    memset(buf, 0, sizeof(buf));
}

int RC_CRSF::read(uint16_t *_dest_channels)
{
    is_update = CRSF_NO_DATA;
    while (pSerial->available() >= 26)
    {
        pSerial->readBytes(buf, 3);
        if (buf[0] == start_byte[0] && buf[1] == start_byte[1] && buf[2] == start_byte[2])
        {
            pSerial->readBytes(buf, 23);
            parse_data(_dest_channels, buf);
            is_update = CRSF_OK;
        }
        else
        {
            is_update = CRSF_LOST_BEGIN_BYTES;
        }
    }
    return is_update;
}

void RC_CRSF::parse_data(uint16_t *_dest_channels, uint8_t *_buffer)
{
    _dest_channels[0] = (uint16_t)((_buffer[0] | _buffer[1] << 8) & 0x07FF);
    _dest_channels[1] = (uint16_t)((_buffer[1] >> 3 | _buffer[2] << 5) & 0x07FF);
    _dest_channels[2] = (uint16_t)((_buffer[2] >> 6 | _buffer[3] << 2 | _buffer[4] << 10) & 0x07FF);
    _dest_channels[3] = (uint16_t)((_buffer[4] >> 1 | _buffer[5] << 7) & 0x07FF);
    _dest_channels[4] = (uint16_t)((_buffer[5] >> 4 | _buffer[6] << 4) & 0x07FF);
    _dest_channels[5] = (uint16_t)((_buffer[6] >> 7 | _buffer[7] << 1 | _buffer[8] << 9) & 0x07FF);
    _dest_channels[6] = (uint16_t)((_buffer[8] >> 2 | _buffer[9] << 6) & 0x07FF);
    _dest_channels[7] = (uint16_t)((_buffer[9] >> 5 | _buffer[10] << 3) & 0x07FF);
    _dest_channels[8] = (uint16_t)((_buffer[11] | _buffer[12] << 8) & 0x07FF);
    _dest_channels[9] = (uint16_t)((_buffer[12] >> 3 | _buffer[13] << 5) & 0x07FF);
    _dest_channels[10] = (uint16_t)((_buffer[13] >> 6 | _buffer[14] << 2 | _buffer[15] << 10) & 0x07FF);
    _dest_channels[11] = (uint16_t)((_buffer[15] >> 1 | _buffer[16] << 7) & 0x07FF);
    _dest_channels[12] = (uint16_t)((_buffer[16] >> 4 | _buffer[17] << 4) & 0x07FF);
    _dest_channels[13] = (uint16_t)((_buffer[17] >> 7 | _buffer[18] << 1 | _buffer[19] << 9) & 0x07FF);
    _dest_channels[14] = (uint16_t)((_buffer[19] >> 2 | _buffer[20] << 6) & 0x07FF);
    _dest_channels[15] = (uint16_t)((_buffer[20] >> 5 | _buffer[21] << 3) & 0x07FF);
}