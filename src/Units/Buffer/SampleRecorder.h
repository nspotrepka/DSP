#pragma once

#include "Buffer.h"
#include "Consumer.h"

namespace dsp {

class SampleRecorder : public Consumer {

public:
    SampleRecorder();
    std::shared_ptr<Buffer> getSample() const;
    std::shared_ptr<InputParameter> getResetTrigger() const;
    std::shared_ptr<InputParameter> getGate() const;

protected:
    void setNumChannelsNoLock(unsigned int numChannels) override;
    void process() override;

private:
    static const unsigned int RESET_TRIGGER;
    static const unsigned int GATE;
    std::shared_ptr<Buffer> sample;
    std::vector<DSP_FLOAT> gatePrevious;
};

} // namespace dsp
