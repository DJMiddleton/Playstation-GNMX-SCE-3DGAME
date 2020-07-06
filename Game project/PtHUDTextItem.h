#ifndef __PT_HUD_TEXT_ITEM__
#define __PT_HUD_TEXT_ITEM__

#include <scebase.h>
#include "ptVertex.h"
#include "../../common/allocator.h"
#include "PtMaterial.h"
#include <vectormath.h>
#include <memory>
using namespace sce;

class PtHUDTextItem
{
private:
	//vertex data
	PtVertex* vertices;
	PtVertex* gpuVertexData;
	uint16_t vertexCount;
	size_t verticesSize;

	//vertex data descriptions buffers
	Gnm::Buffer vertexBuffers[PT_VERTEX_ELEM_COUNT];

	//indices
	uint16_t* indices;
	uint16_t* gpuIndexData;
	uint32_t indexCount;
	size_t indicesSize;
	PtTriangle* triangles;

	std::shared_ptr<PtMaterial> pMaterial;
	bool validData;
	bool verbose;
	int length;

public:
	PtHUDTextItem();
	~PtHUDTextItem();
	void initialise(LinearAllocator* garlicAllocator);
	void initialise(LinearAllocator* garlicAllocator, const char* text, float scale, float xOffset, float yOffset);
	void initialise(LinearAllocator* garlicAllocator, uint32_t number, float scale, float xOffset, float yOffset, int memoryLength);
	int copyDataToGPU(LinearAllocator* garlicAllocator);
	bool getValidData();
	Gnm::Buffer* getVertexBuffers();
	std::shared_ptr<PtMaterial> getMaterial();
	uint32_t getIndexCount();
	uint16_t* getGpuIndexData();
	void setMaterial(std::shared_ptr<PtMaterial> material);
	void updateText(LinearAllocator* garlicAllocator, const char* text);
	void updateNumber(LinearAllocator* garlicAllocator, uint32_t number);
};

#endif