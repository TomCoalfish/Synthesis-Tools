class DelayLine
{
public:
    DelayLine();

    DelayLine (unsigned int maxLengthSamples);

    void setup (unsigned int maxLengthSamples); // Create the buffer with 'maxLengthSamples' number of samples.

    void setFractionalSamples (double fractionalSamples); // Set the current delay length in a fractional number of samples.

    float process (float& input); // The process function, to be called once for ever sample.

private:
    std::vector<float> buffer;
    unsigned int maxBufferSampleLength;

    double fractionalSampleLength;

    int writePointer;
    double readPointer;

    float out = 0;
};