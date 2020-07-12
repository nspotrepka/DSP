#pragma once

#include "Generator.h"

namespace dsp {

class Maximum : public Generator {

public:
    Maximum(Type type, Space space = Space::TIME);
    void pushInput();

protected:
    void process() override;
};

} // namespace dsp
