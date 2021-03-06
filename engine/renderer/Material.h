#ifndef PHI_RENDERER_MATERIAL_H
#define PHI_RENDERER_MATERIAL_H
#include <vector>

#include "DataBinding.h"
#include "utils/Types.h"

namespace phi {
class Renderer;

enum class MaterialId {
    Phong
};

class Material {
public:
    virtual ~Material() {}

    /**
     * Compiles material.
     */
    virtual void Compile() {}

    /**
     * @returns texture bindings used by this material.
     */
    virtual phi::AnyRange<phi::TextureBinding> GetTextureBindings() const = 0;

    /**
     * @returns Pointer to the program being utilized by this material.
     */
    virtual phi::Program *GetProgram() = 0;

    /**
     * @returns Identifier of this material.
     */
    virtual phi::MaterialId GetId() const = 0;

    /**
     * @returns Human-readable material name.
     */
    virtual std::string GetName() const = 0;
};

} // namespace phi

#endif
