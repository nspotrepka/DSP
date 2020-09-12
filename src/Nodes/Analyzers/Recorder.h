#pragma once

#include "../Core/Consumer.h"

namespace dsp {

class Recorder : public Consumer {

public:
    enum Mode { FIXED_SINGLE, FIXED_DOUBLE, VARIABLE };

    Recorder(Type type, Space space = Space::TIME, Sample defaultValue = 0.0);

    Mode getMode() const;
    void setMode(Mode mode);

    Sample getRecordingTime() const;
    void setRecordingTime(Sample seconds);
    std::shared_ptr<Buffer> getRecordingBuffer() const;

    std::shared_ptr<Input> getResetTrigger() const;
    std::shared_ptr<Input> getGate() const;

protected:
    void setNumInputChannelsNoLock(size_t numChannels) override;
    void setSampleRateNoLock(double sampleRate) override;
    void processNoLock() override;

private:
    Mode mode;
    Sample recordingTime;
    Sample recordingNumSamples;
    Array writeIndex;
    std::shared_ptr<Buffer> primary;
    std::shared_ptr<Buffer> secondary;
    const std::shared_ptr<Input> resetTrigger;
    const std::shared_ptr<Input> gate;

    void setRecordingTimeNoLock(Sample seconds);
};

} // namespace dsp