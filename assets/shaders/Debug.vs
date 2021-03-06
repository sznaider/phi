#include "Layout.h"

layout(location=POSITION) in vec4 in_Position;
uniform mat4 ProjViewModelMatrix;

void main() {
    gl_Position = ProjViewModelMatrix * in_Position;
}
