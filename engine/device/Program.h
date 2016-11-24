#ifndef PHI_DEVICE_PROGRAM_H
#define PHI_DEVICE_PROGRAM_H
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "Prototypes.h"
#include "Resource.h"
#include "Shader.h"

#include "utils/Logging.h"

namespace phi {

class Program : public virtual Resource {
    void Destroy();

public:
    struct ParamInfo {
        GLenum type;
        GLint location;
    };

    Program(const Program &) = delete;
    Program &operator=(const Program &) = delete;

    Program &operator=(Program &&);
    Program(Program &&);
    Program();
    virtual ~Program();

    template <typename T>
    void SetConstant(const std::string &name, const T &value) {
        SetConstant(name.c_str(), (const void *) &value);
    }

    void SetConstant(const char *name, const void *value) {
        if (!m_id) {
            throw std::logic_error("Shader not linked yet");
        } else if (auto &&info = FindConstant(name)) {
            SetConstant(info->location, info->type, value);
        } else {
            PHI_LOG(WARNING, "Shader: cannot set constant %s: not found", name);
        }
    }

    virtual void SetSource(ShaderType type, const char *source);
    virtual void Link();

    virtual GLuint GetId() const {
        return m_id;
    }

    const ParamInfo *FindConstant(const std::string &name) const;
    const ParamInfo *FindAttribute(const std::string &name) const;

private:
    GLuint m_id;

    std::map<std::string, struct ParamInfo> m_constants;
    std::map<std::string, struct ParamInfo> m_attributes;
    std::vector<Shader> m_shaders;

    void SetConstant(GLint location, GLenum type, const void *value);

};

} // namespace phi

#endif