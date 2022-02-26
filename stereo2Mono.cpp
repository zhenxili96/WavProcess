
#include "WavHeader.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int Stereo2Mono(const string &inputPath, const string &outputPath) {
    ifstream inFile(inputPath);

    WavHeader header;
    inFile.read((char*)&header, sizeof(header));

    if (header.noChannels!=2) {
        cerr << "Input file is not stereo format. " << inputPath << endl;
        return -1;
    }

    header.print();
    header.data[0] = 'd';
    header.data[1] = 'a';
    header.data[2] = 't';
    header.data[3] = 'a';
    header.noChannels = 1;
    header.blockAlign = (header.bitsPerSample*header.noChannels)/8;
    header.bytesPerSec = (header.sampleRate*header.bitsPerSample*header.noChannels)/8;
    header.fileSize = header.dataSize = 0;

    ofstream outFile(outputPath, ios::binary);
    outFile.write((char*)&header, sizeof(header));
    uint16_t channel1, channel2;    // bitsPerSample is 16
    uint32_t dataSize = 0;
    while (!inFile.eof()) {
        // read contents of both channels
        inFile.read((char*)&channel1, sizeof(channel1));
        inFile.read((char*)&channel2, sizeof(channel2));

        // write data of channel1 to output file
        // TODO you can also average channel1 and channel2 as the output
        outFile.write((char*)&channel1, sizeof(sizeof(channel1)));

        dataSize += sizeof(channel1);
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
    string stereoWavPath = "stereo.wav";
    string monoWavPath = "mono.wav";

    Stereo2Mono(stereoWavPath, monoWavPath);
    return 0;
}


