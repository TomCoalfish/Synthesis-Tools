#include "DelayLine.h"

/** ========================================================================= */
//

DelayLine::DelayLine(int maxLen)
  : maxBufferLength(maxLen)
{
    reset();
}

forcedinline float DelayLine::process(float inputSample, float delayLen)
{
    // integer part of delay length
    int dInt = std::floor(delayLen);

    // fractional part of delay length
    float dFrac = delayLen - dInt;
    
    // get buffer indices that output comes from
    int idx1 = writeIdx - dInt - 1;
    if (idx1 < 0) idx1 += maxBufferLength;
    int idx2 = (idx1 + 1) % maxBufferLength;

    // perform interpolation
    float outputSample = dFrac * data[idx1] + (1-dFrac) * data[idx2];

    // write new sample to delay buffer
    data[writeIdx] = inputSample + feedback * outputSample;

    // increment write index
    writeIdx = (writeIdx + 1) % maxBufferLength;

    return outputSample;
}

// process a block of audio through the delay line with a single delay length
void DelayLine::processBlock(float* buffer, float delayLen, int numSamples)
{
    // process through delay line using the given delay length
    for (int i = 0; i < numSamples; i++) {
        buffer[i] = process(buffer[i], delayLen);
    }
}

// process a block of audio through the delay line with an lfo buffer of delay lengths
void DelayLine::processBlock(float* buffer, const float* delayLenBuffer, int numSamples)
{
    // process through delay line
    for (int i = 0; i < numSamples; i++) {
        buffer[i] = process(buffer[i], delayLenBuffer[i]);
    }
}

void DelayLine::reset()
{
    buffer.setSize(1, maxBufferLength);
    buffer.clear();
    writeIdx = 0;
    data = buffer.getWritePointer(0);
}