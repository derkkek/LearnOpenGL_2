#include "MeshData.h"
#include "glad/glad.h"

const int MeshData::GetVertexCount() const
{
	return this->vertices.size();
}
