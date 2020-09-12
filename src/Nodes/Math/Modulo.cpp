#include "Modulo.h"

dsp::Modulo::Modulo(Type type, Space space)
        : Transformer(type, type == Type::INTEGER ? Type::LOGARITHMIC : type, space)
        , divisor(std::make_shared<Input>(type, space, 1.0)) {
    getInputs().push_back(divisor);
}

std::shared_ptr<dsp::Input> dsp::Modulo::getDivisor() const {
    return divisor;
}

void dsp::Modulo::processNoLock() {
    transform(getDivisor(), wrap);
}