#pragma once

#define DSP_FLOAT double

#define PI 3.141592653589793
#define TAU 6.283185307179586
#define PHI 1.618033988749895
#define SQRT2 1.414213562373095
#define SIX_DB 6.020599913279624

#define ONE_OVER_PI 0.3183098861837907
#define ONE_OVER_TAU 0.1591549430918953
#define ONE_OVER_PHI 0.6180339887498948
#define ONE_OVER_SQRT2 0.7071067811865475
#define ONE_OVER_SIX_DB 0.1660964047443681

namespace dsp {

enum class Type { BIPOLAR, UNIPOLAR, SECONDS, HERTZ, RATIO, LINEAR, INTEGER, BINARY };

enum class Space { TIME, FREQUENCY_REAL, FREQUENCY_IMAGINARY, FREQUENCY_MAGNITUDE, FREQUENCY_PHASE };

enum class Interpolation { LINEAR, HERMITE };

} // namespace dsp
