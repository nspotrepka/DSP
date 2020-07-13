#pragma once

#include "Generator.h"

namespace dsp {

class Trigger : public Generator {

public:
    Trigger();

    std::shared_ptr<InputParameter> getResetTrigger() const;
    std::shared_ptr<InputParameter> getInterval() const;
    std::shared_ptr<InputParameter> getDelay() const;
    std::shared_ptr<OutputParameter> getCurrentTime() const;

protected:
    void setNumChannelsNoLock(unsigned int numChannels) override;
    void process() override;

private:
    static const unsigned int RESET_TRIGGER;
    static const unsigned int INTERVAL;
    static const unsigned int DELAY;
    static const unsigned int CURRENT_TIME;

    std::vector<DSP_FLOAT> index;
};

} // namespace dsp
