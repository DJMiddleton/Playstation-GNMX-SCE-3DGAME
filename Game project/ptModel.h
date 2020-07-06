#ifndef __PT_MODEL__
#define __PT_MODEL__

#include "ptVertex.h"
#include "modelTypes.h"
#include "ptHardModels.h"
#include "PtAssetTypes.h"
#include "../../common/allocator.h"
#include "../../common/danFileParser.h"
#include "scebase.h"
#include <memory>
#include "../../common/danRandom.h"
#include "../../toolkit/toolkit.h"

using namespace sce;

class PtModel
{
private:
	PtVertex* vertices;
	uint16_t vertexCount;
	size_t verticesSize;

	uint16_t* indices;
	uint32_t indexCount;
	size_t indicesSize;

	PtVertex* gpuVertexData;
	uint16_t* gpuIndexData;

	bool validData;
	bool verbose;
	size_t onionMemorySize;

	PtTriangle* triangles;
	bool generateSequentialTriangles;

	Vector3 defaultColour;
	bool oneColour;
	bool noColour;
	
	Gnm::Buffer myVertexBuffers[PT_VERTEX_ELEM_COUNT];

	bool centralisePositionsRequired;
	bool normalisePositionsRequired;
	bool generateNormalsRequired;
	bool gotTexCoords;

	const char* filename;
	PtAssetTypes assetType;

public:
	PtModel();
	int copyDataToGPU(LinearAllocator* garlicAllocator);
	int loadModelPTM(LinearAllocator* garlicAllocator);
	int loadModelOBJ(LinearAllocator* garlicAllocator);
	bool getValidData();
	Gnm::Buffer* getVertexBuffers();
	uint32_t getIndexCount();
	uint16_t* getGpuIndexData();
	void fillColour(Vector3 colour);
	void generateSequentialIndices(LinearAllocator* onionAllocator);
	void fillRandomColour();
	void centralisePositions();
	void normalisePositions();
	void setDefaultColour(Vector3 colour);
	void cleanNormals();
	void generateNormals();
	void normaliseNormals();
	void setFilename(const char* name);
	void setAssetType(PtAssetTypes type);
	PtAssetTypes getAssetType();
	void printFirst10UVs();
};//ptModel


#endif