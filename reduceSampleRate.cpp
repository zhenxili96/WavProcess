
#include "WavHeader.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int ReduceSampleRate(const string &inputPath, const string &outputPath,
                        int targetSampleRate) {
    ifstream inFile(inputPath);

    WavHeader header;
    inFile.read((char*)&header, sizeof(header));

    header.print();
    if (header.noChannels!=1 && header.noChannels!=2) {
        cerr << "Unkown channel num: " << header.noChannels << endl;
        return -1;
    }
    int oldSampleRate = header.sampleRate;
    float srRate = float(header.sampleRate)/targetSampleRate;

    header.sampleRate = targetSampleRate;
    header.blockAlign = (header.bitsPerSample*header.noChannels)/8;
    header.bytesPerSec = (header.sampleRate*header.bitsPerSample*header.noChannels)/8;
    header.fileSize = header.dataSize = 0;

    ofstream outFile(outputPath, ios::binary);
    outFile.write((char*)&header, sizeof(header));

    uint16_t channel1, channel2;    // bitsPerSample is 16
    uint32_t dataSize = 0;
    float idx = 0;
    float saveIdx = 0;
    while (!inFile.eof()) {
        if (header.noChannels==1) {
            inFile.read((char*)&channel1, sizeof(channel1));
        } else {
            inFile.read((char*)&channel1, sizeof(channel1));
            inFile.read((char*)&channel2, sizeof(channel2));
        }
        if (idx/srRate >= saveIdx) {
            if (header.noChannels==1) {
                outFile.write((char*)&channel1, sizeof(channel1));
                dataSize += sizeof(channel1);
            } else {
                outFile.write((char*)&channel1, sizeof(channel1));
                outFile.write((char*)&channel2, sizeof(channel2));
                dataSize += sizeof(channel1);
                dataSize += sizeof(channel2);
            }
            saveIdx++;
        }
        idx++;
    }
    outFile.seekp(40, ios_base::beg);
    outFile.write((char*)&dataSize, sizeof(dataSize));

    dataSize+=44;
    outFile.seekp(4, ios_base::beg);
    outFile.write((char*)&dataSize, sizeof(dataSize));

    inFile.close();
    outFile.close();
    return 0;
}


int main() {
    string highSRWavPath = "highSR.wav";
    string lowSRWavPath = "lowSR.wav";
    int targetSR = 16000;

    ReduceSampleRate(highSRWavPath, lowSRWavPath, targetSR);
    return 0;
}