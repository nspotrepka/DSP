#include "Trigonometric.h"

dsp::Trigonometric::Trigonometric(Space space)
        : Transformer(Type::RATIO, Type::RATIO, space)
        , mode(std::make_shared<Input>(Type::INTEGER, space)) {
    getInputs().push_back(mode);
}

std::shared_ptr<dsp::Input> dsp::Trigonometric::getMode() const {
    return mode;
}

void dsp::Trigonometric::processNoLock() {
    getOutput()->getWrapper().replaceWithApplicationOf(
            [](Sample x, Sample y) {
                const Sample modeClipped = clip(y, Mode::MIN, Mode::MAX);
                switch (static_cast<int>(modeClipped)) {
                    case Mode::SINE: return sin(x); break;
                    case Mode::COSINE: return cos(x); break;
                }
            },
            getInput()->getWrapper(),
            getMode()->getWrapper());
}