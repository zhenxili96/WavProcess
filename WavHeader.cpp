
#include "WavHeader.h"
#include <iostream>

using namespace std;

WavHeader::WavHeader() {

}

WavHeader::WavHeader(uint32_t fileSize, uint16_t noChannels, uint32_t sampleRate,
        uint16_t bitsPerSample, uint32_t dataSize){

    // RIFF descriptor
    RIFF[0] = 'R';RIFF[1] = 'I';RIFF[2] = 'F';RIFF[3] = 'F';
    this->fileSize = fileSize;
    WAVE[0] = 'W';WAVE[1] = 'A';WAVE[2] = 'V';WAVE[3] = 'E';

    // fmt sub-chunk
    fmt[0] = 'f';fmt[1] = 'm';fmt[2] = 't';fmt[3] = 32;
    fmtSize = 16;
    audioFormat = 1;
    this->noChannels = noChannels;
    this->sampleRate = sampleRate;
    this->bitsPerSample = bitsPerSample;
    blockAlign = (bitsPerSample * noChannels) / 8;
    bytesPerSec = (sampleRate * bitsPerSample * noChannels) / 8;

    // data sub-chunk
    data[0] = 'd';data[1] = 'a';data[2] = 't';data[3] = 'a';
    this->dataSize = dataSize;

}

void WavHeader::print() {
    cout << "RIFF: " << (char)RIFF[0] << (char)RIFF[1]
        << (char)RIFF[2] << (char)RIFF[3] << endl;
    cout << "fileSize: " << fileSize << endl;
    cout << "WAVE: " << (char)WAVE[0] << (char)WAVE[1]
        << (char)WAVE[2] << (char)WAVE[3] << endl;
    cout << "fmt: " << (char)fmt[0] << (char)fmt[1]
        << (char)fmt[2] << (char)fmt[3] << endl;
    cout << "fmtSize: " << fmtSize << endl;
    cout << "audioFormat: " << audioFormat << endl;
    cout << "noChannels: " << noChannels << endl;
    cout << "sampleRate: " << sampleRate << endl;
    cout << "bytesPerSec: " << bytesPerSec << endl;
    cout << "blockAlign: " << blockAlign << endl;
    cout << "bitsPerSample: " << bitsPerSample << endl;
    cout << "data: " << (char)data[0] << (char)data[1]
        << (char)data[2] << (char)data[3] << endl;
    cout << "dataSize: " << dataSize << endl;
}

