#pragma once

namespace VSynth
{

    /**
    * @brief ADSR envelope data
    * 
    * Represent the ADSR curve with five parameters:
    * 
    * Attack Amplitude
    * Sustain Amplitude
    * Attack Time
    * Decay Time
    * Release Time
    */
    struct ADSREnvelope
    {
        ADSREnvelope(double attack, double sustain, double attackTime, double decayTime, double releaseTime)
            : attack(attack), sustain(sustain), attackTime(attackTime), decayTime(decayTime), releaseTime(releaseTime), sustainable(true)
        {
        }
        ADSREnvelope() : sustainable(true)
        {
        }

        double attack, sustain;
        double attackTime, decayTime, releaseTime;
        bool sustainable;
    };

    /**
     * @brief Waveform modulator
     * 
     * Modulates audio waveforms in accordance with the ADSR envelope.
     * Envelopes can be manipulated with the hold() and release() functions.
     * 
     * @see hold()
     * @see release()
     */
    class Envelope
    {
    public:
        /**
         * @brief Construct a new Envelope object
         * 
         * @param adsr - ADSR data
         */
        Envelope(const ADSREnvelope adsr);
        virtual ~Envelope();

        /**
         * @brief Get the current amplitude modifier
         * @return the current amplitude modifier
         */
        double getAmplitude() const;

        /**
         * @brief Update the timestamp for the envelope
         * 
         * While the envelope is within the Attack -> Release state,
         * the amplitudes returned by the envelope will modulate each
         * time this function is called. When the envelope is outside
         * those ranges of states, this function does nothing.
         * 
         * @param deltaTime - time in milliseconds
         */
        void update(double deltaTime);

        /**
         * @brief Starts the envelopes modulation
         * 
         * Starts the enevlope, or in other terms "presses the key".
         * Calling this function will restart the envelope to the attack state.
         */
        void hold();

        /**
         * @brief releases
         * 
         * Starts the ending for the envelope, or in other terms "releases the key".
         * Calling this function will transition the envelope to the release state.
         */
        void release();

    private:
        ADSREnvelope mADSR;
        double mTime;
        double mReleaseStart;

        bool mHold;
        bool mActive;
    };
}; // namespace VSynth