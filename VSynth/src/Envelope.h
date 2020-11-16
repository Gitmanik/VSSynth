#pragma once

namespace VSynth
{

/**
 * @brief ADSR envelope
 * This envelope should be used to modulate the amplitude of a waveform.
 */
struct ADSREnvelope{
    ADSREnvelope(): sustainable(true)
    {}

    double attack, sustain;
    double attackTime, decayTime, releaseTime;
    bool sustainable;
};

class Envelope
{
    public:
        Envelope(const ADSREnvelope adsr);
        virtual ~Envelope();

        double getAmplitude() const;
        void updateTime(double deltaTime);

        void hold();
        void release();

    private:

        ADSREnvelope mADSR;
        double mTime;
        double mReleaseStart;

        bool mHold;
        bool mActive;
};
}; // namespace VSynth