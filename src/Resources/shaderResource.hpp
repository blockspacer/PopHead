#ifndef POPHEAD_RESOURCE_SHADERRESOURCE_H_
#define POPHEAD_RESOURCE_SHADERRESOURCE_H_

#include <string>

#include <SFML/Graphics.hpp>

#include "resource.hpp"

namespace PopHead {
namespace Resources {

class ShaderResource : public Resource< ShaderResource >
{
  private:
    virtual bool load( std::string path ) override;

    sf::Shader mShader;
};

}}

#endif // !POPHEAD_RESOURCE_SHADERRESOURCE_H_