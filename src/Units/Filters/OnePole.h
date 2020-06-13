#pragma once

#include "Processor.h"

namespace dsp {

class OnePole : public Processor {

public:
    enum class Mode { LOW_PASS, HIGH_PASS };

    OnePole();
    void setNumChannels(std::size_t numChannels) override;
    Mode getMode();
    void setMode(Mode mode);
    std::shared_ptr<InputParameter> getFrequency();

protected:
    void process() override;

private:
    static const std::size_t FREQUENCY;
    Mode mode;
    std::vector<DSP_FLOAT> y1;
};

} // namespace dsp