#include "DebugDrawer.h"
#include "Common.h"
#include "DrawCall.h"
#include "Renderer.h"

#include "math/AABB.h"
#include "math/Rect2D.h"

#include "device/Sampler.h"

#include "scene/Camera.h"
#include "scene/DummyCamera.h"

#include <vector>

namespace phi {
using namespace glm;

static const phi::Layout *DebugLayout() {
    static const phi::Layout layout(sizeof(glm::vec4), {
        { phi::Layout::Position, phi::Layout::Float4, 0u }
    });
    return &layout;
}

DebugDrawer::DebugDrawer(phi::Device &device)
        : m_device(device),
          m_vbo(BufferType::Vertex,
                BufferHint::Dynamic,
                nullptr,
                DebugDrawer::BUFFER_SIZE),
          m_debug_program(),
          m_quad_program() {
    m_debug_program.SetSourceFromFile(ShaderType::Vertex, "assets/shaders/Debug.vs");
    m_debug_program.SetSourceFromFile(ShaderType::Fragment, "assets/shaders/Debug.fs");
    m_debug_program.Link();

    m_quad_program.SetSourceFromFile(ShaderType::Vertex, "assets/shaders/Quad.vs");
    m_quad_program.SetSourceFromFile(ShaderType::Fragment, "assets/shaders/QuadTexture.fs");
    m_quad_program.Link();
}

void DebugDrawer::DrawAABB(const phi::Camera &view,
                           const phi::AABB &box,
                           const vec3 &color) {
    auto MakeVertex = [&](AABB::Vertex vertex) {
        return vec4(box.GetVertex(vertex), 1);
    };
    std::vector<vec4> data = {
        MakeVertex(AABB::Vertex::MinMinMin), MakeVertex(AABB::Vertex::MaxMinMin),
        MakeVertex(AABB::Vertex::MaxMinMin), MakeVertex(AABB::Vertex::MaxMaxMin),
        MakeVertex(AABB::Vertex::MaxMaxMin), MakeVertex(AABB::Vertex::MinMaxMin),
        MakeVertex(AABB::Vertex::MinMaxMin), MakeVertex(AABB::Vertex::MinMinMin),

        MakeVertex(AABB::Vertex::MinMinMax), MakeVertex(AABB::Vertex::MaxMinMax),
        MakeVertex(AABB::Vertex::MaxMinMax), MakeVertex(AABB::Vertex::MaxMaxMax),
        MakeVertex(AABB::Vertex::MaxMaxMax), MakeVertex(AABB::Vertex::MinMaxMax),
        MakeVertex(AABB::Vertex::MinMaxMax), MakeVertex(AABB::Vertex::MinMinMax),

        MakeVertex(AABB::Vertex::MinMinMin), MakeVertex(AABB::Vertex::MinMinMax),
        MakeVertex(AABB::Vertex::MaxMinMin), MakeVertex(AABB::Vertex::MaxMinMax),
        MakeVertex(AABB::Vertex::MaxMaxMin), MakeVertex(AABB::Vertex::MaxMaxMax),
        MakeVertex(AABB::Vertex::MinMaxMin), MakeVertex(AABB::Vertex::MinMaxMax),
    };
    m_vbo.UpdateData(data.data(), sizeof(data) * sizeof(vec4));
    m_device.BindProgram(&m_debug_program);
    m_device.BindVbo(&m_vbo);
    m_device.BindLayout(DebugLayout());
    m_debug_program.SetConstant("ProjViewModelMatrix",
                                view.GetProjMatrix() * view.GetViewMatrix());
    m_debug_program.SetConstant("Color", glm::vec4(color, 1.0f));
    m_device.Draw(phi::Primitive::Lines, 0, data.size());
}

void DebugDrawer::DrawTexture(const Texture2D &texture, int x, int y, int w, int h) {
    m_device.BindProgram(&m_quad_program);
    m_device.BindVbo(&Common::QuadVbo());
    m_device.BindLayout(&Common::QuadLayout());
    m_device.BindTexture(0, &texture);
    m_device.BindSampler(0, &phi::Samplers<phi::WrapMode::ClampToEdge>::Bilinear2D());
    auto viewport = m_device.GetViewport();
    auto scissor = m_device.GetScissor();
    m_device.SetViewport({ x, y, w, h });
    m_device.SetScissor({ x, y, w, h });
    m_device.Draw(phi::Primitive::Triangles, 0, 6);
    m_device.SetViewport(viewport);
    m_device.SetScissor(scissor);
}

} // namespace phi
