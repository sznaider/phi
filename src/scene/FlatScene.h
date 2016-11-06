#ifndef PHI_SCENE_FLAT_SCENE_H
#define PHI_SCENE_FLAT_SCENE_H
#include <vector>

#include "Scene.h"

#include "math/AABB.h"

namespace phi {

/**
 * Very basic implementation of the Scene that keeps everything in the lists.
 */
class FlatScene : public Scene {
    std::vector<phi::Entity *> m_entities;
    std::vector<phi::PointLight *> m_point_lights;
    std::vector<phi::DirLight *> m_dir_lights;
    mutable phi::AABB m_box;
    const phi::Camera *m_camera;

public:
    virtual void SetCamera(phi::Camera *);
    virtual void AddEntity(phi::Entity *);
    virtual void AddLight(phi::DirLight *);
    virtual void AddLight(phi::PointLight *);
    virtual void Render(phi::DrawCallQueue *);
    virtual const phi::Camera *GetCamera() const {
        return m_camera;
    }
    virtual const std::vector<phi::DirLight *> &GetDirLights() {
        return m_dir_lights;
    }
    virtual const std::vector<phi::PointLight *> &GetPointLights() {
        return m_point_lights;
    }

    virtual const phi::AABB &GetAABB() const;
};

} // namespace phi

#endif
