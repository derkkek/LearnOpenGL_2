#include "RenderableObject.h"

RenderableObject::RenderableObject(const std::string& vertex_path, const std::string& fragment_path)
	:shader(vertex_path.c_str(), fragment_path.c_str())
{

}
