#include "PhongMaterial.h"

#include <stdexcept>

namespace phi {

PhongMaterial::PhongMaterial() : m_diffuse(1, 1, 1, 1), m_specular(0, 0, 0, 1) {
    try {
        m_program = Material::g_cache.Get(GetName());
    } catch (std::out_of_range &) {
        m_program = std::make_shared<phi::Program>();
        m_program->SetSourceFromFile(phi::ShaderType::Vertex, "assets/shaders/PhongMaterial.vs");
        m_program->SetSourceFromFile(phi::ShaderType::Fragment, "assets/shaders/PhongMaterial.fs");
        m_program->Link();
    }
}

void PhongMaterial::SetDiffuse(const glm::vec4 &diffuse) {
    m_diffuse = diffuse;
}

void PhongMaterial::SetSpecular(const glm::vec4 &specular) {
    m_specular = specular;
}

void PhongMaterial::FillTextureBindings(std::vector<phi::TextureBinding> &) const {
}

void PhongMaterial::FillProgramConstants(std::vector<phi::ProgramConstant> &constants) const {
    constants.emplace_back("Diffuse", &m_diffuse);
    constants.emplace_back("Specular", &m_specular);
}

} // namespace phi
