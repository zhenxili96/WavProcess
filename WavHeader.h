#include <stdlib.h>
#include <sys/stat.h>
#include <cmath>
#include <string>

class WavHeader{
public:
    // RIFF Descriptor
    uint8_t  RIFF[4];
    uint32_t fileSize;
    uint8_t WAVE[4];

    // fmt sub-chunk
    uint8_t fmt[4];
    uint32_t fmtSize;
    uint16_t audioFormat;
    uint16_t noChannels;
    uint32_t sampleRate;
    uint32_t bytesPerSec;
    uint16_t blockAlign;
    uint16_t bitsPerSample;

    // data sub-chunk
    uint8_t data[4];
    uint32_t dataSize;

    WavHeader();

    WavHeader(uint32_t fileSize, uint16_t noChannels, uint32_t sampleRate,
            uint16_t bitsPerSample, uint32_t dataSize);

    void print();

};