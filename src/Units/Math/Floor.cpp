#include "Floor.h"

const unsigned int dsp::Floor::DIVISOR = 1;

dsp::Floor::Floor(Type type, Space space) : Processor(type, type, space) {
    assert(type != Type::BINARY);
    assert(type != Type::INTEGER);
}

std::shared_ptr<dsp::Unit::InputParameter> dsp::Floor::getDivisor() {
    return getInput(DIVISOR);
}

void dsp::Floor::process() {
    Unit::process();
    transform(getDivisor(), [](DSP_FLOAT x, DSP_FLOAT y) { return y == 0.0 ? x : floor(x / y) * y; });
}
