#ifndef PHI_SCENE_LIST_SCENE_H
#define PHI_SCENE_LIST_SCENE_H
#include "Scene.h"

#include <vector>

namespace phi {

/**
 * Very basic implementation of the Scene that keeps everything in the lists.
 */
class ListScene : public Scene {
    std::vector<phi::Entity *> m_entities;
    std::vector<phi::Light *> m_lights;
    const phi::Camera *m_camera;

public:
    virtual void SetCamera(phi::Camera *);
    virtual void AddEntity(phi::Entity *);
    virtual void AddLight(phi::Light *);
    virtual void Render(phi::CommandQueue *);
    virtual const phi::Camera *GetCamera() const {
        return m_camera;
    }
};

} // namespace phi

#endif
