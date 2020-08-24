#include "Geometry.h"


GPU_Geometry::GPU_Geometry()
	: vao()
	, vertBuffer(0, 3, GL_FLOAT)
	, colBuffer(1, 3, GL_FLOAT)
{}


void GPU_Geometry::setVerts(std::vector<glm::vec3>& verts) {
	vertBuffer.uploadData(GLsizeiptr(sizeof(glm::vec3) * verts.size()), verts.data(), GL_STATIC_DRAW);
}


void GPU_Geometry::setCols(std::vector<glm::vec3>& cols) {
	colBuffer.uploadData(GLsizeiptr(sizeof(glm::vec3) * cols.size()), cols.data(), GL_STATIC_DRAW);
}
