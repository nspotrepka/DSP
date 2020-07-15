#include "GreaterThan.h"

dsp::GreaterThan::GreaterThan(Type type, Space space)
        : Processor(type, Type::BINARY, space)
        , comparisonSignal(pushInput(type, space)) {}

std::shared_ptr<dsp::InputParameter> dsp::GreaterThan::getComparisonSignal() const {
    return comparisonSignal;
}

void dsp::GreaterThan::process() {
    Unit::process();
    transform(getComparisonSignal(), [](DSP_FLOAT x, DSP_FLOAT y) { return x > y; });
}
