#include "PtHUDTextItem.h"
#include <iostream>

PtHUDTextItem::PtHUDTextItem()
{
	vertices = nullptr;
	gpuVertexData = nullptr;
	vertexCount = 0;
	verticesSize = 0;
	indices = nullptr;
	gpuIndexData = nullptr;
	indexCount = 0;
	indicesSize = 0;
	length = 0;
	triangles = nullptr;
	pMaterial = nullptr;
	validData = false;
	verbose = false;
}

PtHUDTextItem::~PtHUDTextItem()
{
	vertices = nullptr;
	indices = nullptr;
	delete vertices;
	delete indices;
}

void PtHUDTextItem::initialise(LinearAllocator* garlicAllocator)
{
	vertices = new PtVertex[4]
	{
		//	x		y			z		r	g	b		nx	ny	nz		u		v
		{ -0.5,	0.5,		0,		1,	1,	1,	float((2 * 0.0625) + 0.0625), float(0.25),	0,	0,	1,		 },
		{ 0.5,		0.5,		0,		1,	1,	1,	float((2 * 0.0625) + 0.125), float(0.25), 	0,	0,	1,		},
		{ 0.5,		-0.5,	0,		1,	1,	1,	float((2 * 0.0625) + 0.125), float(0.3125),	0,	0,	1,		 },
		{ -0.5,	-0.5,	0,		1,	1,	1,	float((2 * 0.0625) + 0.0625), float(0.3125) ,	0,	0,	1,		}
	};//vertex data

	indices = new uint16_t[6]
	{
		0, 3, 2,
		0, 2, 1
	};//triangle construction

	vertexCount = 4;
	verticesSize = vertexCount * sizeof(PtVertex);
	indexCount = 6;
	indicesSize = indexCount * sizeof(uint16_t);
	triangles = (PtTriangle*)indices;

	int error = copyDataToGPU(garlicAllocator);
	if (error != SCE_OK)
	{
		printf("Unable to copy model data to GPU memory: 0x%08X\n", error);
	}
	else
	{
		validData = true;
	}
}

void PtHUDTextItem::initialise(LinearAllocator* garlicAllocator, const char* text, float scale, float xOffset, float yOffset)
{
	int counter = 0;
	for (int index = 0; text[index] != '\0'; index++)
	{
		counter++;
	}

	length = counter;
	if (verbose)
	{
		printf("%i", counter);
	}

	vertices = new PtVertex[counter * 4];
	indices = new uint16_t[counter * 6];

	vertexCount = 4 * counter;
	verticesSize = vertexCount * sizeof(PtVertex);
	indexCount = 6 * counter;
	indicesSize = indexCount * sizeof(uint16_t);
	triangles = (PtTriangle*)indices;

	for (int i = 0; i < counter; i++)
	{
		int charNumber = (int)text[i];
		int row = charNumber / 16;
		int column = charNumber % 16;

		column = column - 1;
		row = row - 4;

		vertices[i * 4]		= { float(-0.01 * scale + (i * ((scale / 2.0f) * 0.02) + xOffset)),	float(0.0177 * scale + yOffset),	0,   1,	1,	1 ,	0,	0,	1,	float(0.0625 + (0.0625 * column)), float(0.25 + (0.0625 * row)) };
		vertices[i * 4 + 1] = { float(0.01 * scale + (i * ((scale / 2.0f) * 0.02) + xOffset)),	float(0.0177 * scale + yOffset),	0,	 1,	1,	1, 	0,	0,	1,	float(0.125 + (0.0625 * column)), float(0.25 + (0.0625 * row)) };
		vertices[i * 4 + 2] = { float(0.01 * scale + (i * ((scale / 2.0f) * 0.02) + xOffset)),	float(-0.0177 * scale + yOffset),	0,	 1,	1,	1,	0,	0,	1,	float(0.125 + (0.0625 * column)), float(0.3125 + (0.0625 * row)), };
		vertices[i * 4 + 3] = { float(-0.01 * scale + (i * ((scale / 2.0f) * 0.02) + xOffset)),	float(-0.0177 * scale + yOffset),	0,	 1,	1,	1,  0,	0,	1,	float(0.0625 + (0.0625 * column)), float(0.3125 + (0.0625 * row)) };
		
		if (verbose)
		{
			printf("Character at (%i, %i)\n", column, row);
			for (int c = 0; c < counter * 4; c++)
			{
				printf("%f, %f\n", vertices[c].u, vertices[c].v);
			}
		}

		indices[i * 6] = 0 + (i * 4);
		indices[i * 6 + 1] = 3 + (i * 4);
		indices[i * 6 + 2] = 2 + (i * 4);
		indices[i * 6 + 3] = 0 + (i * 4);
		indices[i * 6 + 4] = 2 + (i * 4);
		indices[i * 6 + 5] = 1 + (i * 4);
	}

	int error = copyDataToGPU(garlicAllocator);
	if (error != SCE_OK)
	{
		printf("Unable to copy model data to GPU memory: 0x%08X\n", error);
	}
	else
	{
		validData = true;
	}
}

void PtHUDTextItem::initialise(LinearAllocator* garlicAllocator, uint32_t number, float scale, float xOffset, float yOffset, int memoryLength)
{
	int digitCount = 1;
	uint32_t value = number;
	while (value > 9)
	{
		value /= 10;
		digitCount++;
	}
	if (verbose)
	{
		printf("%i digits found\n", digitCount);
	}

	vertices = new PtVertex[memoryLength * 4];
	indices = new uint16_t[memoryLength * 6];

	vertexCount = 4 * memoryLength;
	verticesSize = vertexCount * sizeof(PtVertex);
	indexCount = 6 * memoryLength;
	indicesSize = indexCount * sizeof(uint16_t);
	triangles = (PtTriangle*)indices;

	length = memoryLength;
	for (int c = 0; c < length; c++)
	{
		uint32_t util = number;
		for (int i = 0; i < digitCount - 1; i++)
		{
			util /= 10;
		}
		if (verbose)
		{
			printf("%i\n", (int)util);
		}

		uint32_t digit = util;
		for (int i = 0; i < digitCount - 1; i++)
		{
			util *= 10;
		}
		number -= util;
		digitCount--;

		int charNumber = (int)(digit + 48);
		if (digitCount < 0)
		{
			charNumber = 13;
		}
		int row = charNumber / 16;
		int column = charNumber % 16;

		column = column - 1;
		row = row - 4;

		if (verbose)
		{
			printf("Character at (%i, %i)\n", column, row);
		}

		vertices[c * 4] = { float(-0.01 * scale + (c * ((scale / 2.0f) * 0.02) + xOffset)),	float(0.0177 * scale + yOffset),	0,   1,	1,	1,	0,	0,	1, float(0.0625 + (0.0625 * column)), float(0.25 + (0.0625 * row)) };
		vertices[c * 4 + 1] = { float(0.01 * scale + (c * ((scale / 2.0f) * 0.02) + xOffset)),	float(0.0177 * scale + yOffset),	0,	 1,	1,	1, 	0,	0,	1, float(0.125 + (0.0625 * column)), float(0.25 + (0.0625 * row)) };
		vertices[c * 4 + 2] = { float(0.01 * scale + (c * ((scale / 2.0f) * 0.02) + xOffset)),	float(-0.0177 * scale + yOffset),	0,	 1,	1,	1,	0,	0,	1, float(0.125 + (0.0625 * column)), float(0.3125 + (0.0625 * row)) };
		vertices[c * 4 + 3] = { float(-0.01 * scale + (c * ((scale / 2.0f) * 0.02) + xOffset)),	float(-0.0177 * scale + yOffset),	0,	 1,	1,	1,  0,	0,	1, float(0.0625 + (0.0625 * column)), float(0.3125 + (0.0625 * row)) };
	
		indices[c * 6] = 0 + (c * 4);
		indices[c * 6 + 1] = 3 + (c * 4);
		indices[c * 6 + 2] = 2 + (c * 4);
		indices[c * 6 + 3] = 0 + (c * 4);
		indices[c * 6 + 4] = 2 + (c * 4);
		indices[c * 6 + 5] = 1 + (c * 4);
	}

	int error = copyDataToGPU(garlicAllocator);
	if (error != SCE_OK)
	{
		printf("Unable to copy model data to GPU memory: 0x%08X\n", error);
	}
	else
	{
		validData = true;
	}
}

int PtHUDTextItem::copyDataToGPU(LinearAllocator* garlicAllocator)
{
	int result = SCE_OK;

	// Allocate the vertex buffer memory
	PtVertex* gpuVertexData = static_cast<PtVertex*>(garlicAllocator->allocate(verticesSize, Gnm::kAlignmentOfBufferInBytes));
	if (!gpuVertexData)
	{
		printf("Cannot allocate vertex data\n"); 
		return SCE_KERNEL_ERROR_ENOMEM;
	}

	// Allocate the index buffer memory
	uint16_t* gpuIndexData = static_cast<uint16_t*>(garlicAllocator->allocate(indicesSize, Gnm::kAlignmentOfBufferInBytes));
	if (!gpuIndexData)
	{
		printf("Cannot allocate index data\n");
		return SCE_KERNEL_ERROR_ENOMEM;
	}

	// Copy the vertex/index data onto the GPU mapped memory
	memcpy(gpuVertexData, vertices, verticesSize);
	memcpy(gpuIndexData, indices, indicesSize);

	vertexBuffers[PT_VERTEX_POSITION].initAsVertexBuffer(
		&gpuVertexData->x,
		Gnm::kDataFormatR32G32B32Float,
		sizeof(PtVertex),
		verticesSize / sizeof(PtVertex));

	vertexBuffers[PT_VERTEX_COLOUR].initAsVertexBuffer(
		&gpuVertexData->r,
		Gnm::kDataFormatR32G32B32Float,
		sizeof(PtVertex),
		verticesSize / sizeof(PtVertex));

	vertexBuffers[PT_VERTEX_NORMAL].initAsVertexBuffer(
		&gpuVertexData->nx,
		Gnm::kDataFormatR32G32B32Float,
		sizeof(PtVertex),
		verticesSize / sizeof(PtVertex));

	vertexBuffers[PT_VERTEX_TEXCOORD].initAsVertexBuffer(
		&gpuVertexData->u,
		Gnm::kDataFormatR32G32Float,
		sizeof(vertices[0]),
		vertexCount);

	this->gpuIndexData = gpuIndexData;
	this->gpuVertexData = gpuVertexData;

	return result;
}

void PtHUDTextItem::updateText(LinearAllocator* garlicAllocator, const char* text)
{
	int counter = 0;
	for (int index = 0; text[index] != '\0'; index++)
	{
		counter++;
	}

	int lastIndex = 0;

	for (int i = 0; i < length; i++)
	{
		int charNumber = 0;
		if (i >= counter)
		{
			charNumber = 13;
		}
		else
		{
			charNumber = (int)text[i];
		}

		int row = charNumber / 16;
		int column = charNumber % 16;

		column = column - 1;
		row = row - 4;

		vertices[i * 4].u = float(0.0625 + (0.0625 * column));
		vertices[i * 4].v = float(0.25 + (0.0625 * row));

		vertices[i * 4 + 1].u = float(0.125 + (0.0625 * column));
		vertices[i * 4 + 1].v = float(0.25 + (0.0625 * row));

		vertices[i * 4 + 2].u = float(0.125 + (0.0625 * column));
		vertices[i * 4 + 2].v = float(0.3125 + (0.0625 * row));

		vertices[i * 4 + 3].u = float(0.0625 + (0.0625 * column));
		vertices[i * 4 + 3].v = float(0.3125 + (0.0625 * row));

		lastIndex = i * 4 + 3;
	}

	int l_error = copyDataToGPU(garlicAllocator);
	if (l_error != SCE_OK)
	{
		validData = false;
		printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error);
	}
	else
	{
		validData = true;
	}
}

void PtHUDTextItem::updateNumber(LinearAllocator* garlicAllocator, uint32_t number)
{
	int digitCount = 1;
	uint32_t value = number;
	while (value > 9)
	{
		value /= 10;
		digitCount++;
	}

	int newLength = digitCount;
	for (int c = 0; c < length; c++)
	{
		uint32_t util = number;
		for (int i = 0; i < digitCount - 1; i++)
		{
			util /= 10;
		}
		if (verbose)
		{
			printf("%i\n", (int)util);
		}

		uint32_t digit = util;
		for (int i = 0; i < digitCount - 1; i++)
		{
			util *= 10;
		}
		number -= util;
		digitCount--;

		int charNumber = 0;
		if (c >= newLength)
		{
			charNumber = 13;
		}
		else
		{
			charNumber = (int)(digit + 48);
			if (digitCount < 0)
			{
				charNumber = 13;
			}
		}
		
		int row = charNumber / 16;
		int column = charNumber % 16;

		column = column - 1;
		row = row - 4;

		if (verbose)
		{
			printf("Character at (%i, %i)\n", column, row);
		}

		vertices[c * 4].u = float(0.0625 + (0.0625 * column));
		vertices[c * 4].v = float(0.25 + (0.0625 * row));

		vertices[c * 4 + 1].u = float(0.125 + (0.0625 * column));
		vertices[c * 4 + 1].v = float(0.25 + (0.0625 * row));

		vertices[c * 4 + 2].u = float(0.125 + (0.0625 * column));
		vertices[c * 4 + 2].v = float(0.3125 + (0.0625 * row));

		vertices[c * 4 + 3].u = float(0.0625 + (0.0625 * column));
		vertices[c * 4 + 3].v = float(0.3125 + (0.0625 * row));
	}

	int error = copyDataToGPU(garlicAllocator);
	if (error != SCE_OK)
	{
		validData = false;
		printf("Unable to copy model data to GPU memory: 0x%08X\n", error);
	}
	else
	{
		validData = true;
	}
}

bool PtHUDTextItem::getValidData()
{
	return validData;
}

Gnm::Buffer* PtHUDTextItem::getVertexBuffers()
{
	return vertexBuffers;
}

std::shared_ptr<PtMaterial> PtHUDTextItem::getMaterial()
{
	return pMaterial;
}

uint32_t PtHUDTextItem::getIndexCount()
{
	return indexCount;
}

uint16_t* PtHUDTextItem::getGpuIndexData()
{
	return gpuIndexData;
}

void PtHUDTextItem::setMaterial(std::shared_ptr<PtMaterial> material)
{
	pMaterial = material;
}