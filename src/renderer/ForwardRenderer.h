#ifndef PHI_RENDERER_FORWARD_RENDERER_H
#define PHI_RENDERER_FORWARD_RENDERER_H
#include <memory>

#include "DrawCallQueue.h"
#include "Renderer.h"

#include "math/Box.h"
#include "math/Math.h"

#include "device/FrameBuffer.h"
#include "device/Shader.h"
#include "device/Texture.h"

namespace phi {
class Layout;
class Scene;
class Light;

class ForwardRenderer : public Renderer {
    friend class DebugDrawer;

    std::vector<phi::Light *> m_shadow_casters;
    glm::mat4 m_proj;
    GLuint m_vao;

    struct State {
        std::vector<int> arrays;
        phi::Program *program;
        const phi::Buffer *vbo;
        const phi::Buffer *ibo;
    } m_last;

    void BindGlobals(const glm::mat4 &view, const glm::mat4 &model);
    void BindLights(const std::vector<phi::DirectionalLight *> &);
    void BindLights(const std::vector<phi::PointLight *> &);
    void BindProgram(phi::Program *program);
    void BindLayout(const phi::Layout *layout);
    void BindVbo(const phi::Buffer *buffer);
    void BindIbo(const phi::Buffer *buffer);
    void Draw(phi::PrimitiveType, int start, int count);

public:
    ForwardRenderer(int width, int height);
    virtual void Render(phi::Scene &);
    virtual void Render(const phi::Camera &, const phi::DrawCall &);
    virtual void Resize(int width, int height);
    virtual void SetViewport(int x, int y, int w, int h);
};

} // namespace phi

#endif