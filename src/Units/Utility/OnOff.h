#pragma once

#include "Generator.h"

namespace dsp {

class OnOff : public Generator {

public:
    OnOff();
    std::shared_ptr<InputParameter> getOnTrigger();
    std::shared_ptr<InputParameter> getOffTrigger();

protected:
    void setNumChannelsNoLock(unsigned int numChannels) override;
    void process() override;

private:
    static const unsigned int ON_TRIGGER;
    static const unsigned int OFF_TRIGGER;
    std::vector<DSP_FLOAT> state;
};

} // namespace dsp