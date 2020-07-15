#include "Modulo.h"

dsp::Modulo::Modulo(Type type, Space space)
        : Processor(type, type, space)
        , divisor(pushInput(type, space, 1.0)) {
    assert(type != Type::BINARY);
    assert(type != Type::INTEGER);
}

std::shared_ptr<dsp::InputParameter> dsp::Modulo::getDivisor() const {
    return divisor;
}

void dsp::Modulo::process() {
    Unit::process();
    transform(getDivisor(), [](DSP_FLOAT x, DSP_FLOAT y) { return y == 0.0 ? 0.0 : x - floor(x / y) * y; });
}
