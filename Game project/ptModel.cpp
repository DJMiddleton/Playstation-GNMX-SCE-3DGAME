#include "ptModel.h"
#include <gnmx.h>
#include "../../common/danGraphicsWrapper.h"
#include <vector>
#include "../../common/danOBJHelpers.h"

using namespace sce;

PtModel::PtModel()
{
	vertices = nullptr;
	indices = nullptr;
	triangles = nullptr;
	vertexCount = 0;
	verticesSize = 0;
	indexCount = 0;
	indicesSize = 0;
	validData = false;
	verbose = false;
	onionMemorySize = 16 * 1024 * 1024;
	noColour = false;
	generateSequentialTriangles = false;
	oneColour = false;
	centralisePositionsRequired = false;
	normalisePositionsRequired = false;
	generateNormalsRequired = false;
	gotTexCoords = false;
	defaultColour = { 0.5, 0.5, 0.5 };
}

int PtModel::copyDataToGPU(LinearAllocator* garlicAllocator)
{
	int l_result = SCE_OK;

	// Allocate the vertex buffer memory
	PtVertex* l_gpuVertexData = static_cast<PtVertex*>(garlicAllocator->allocate(verticesSize, Gnm::kAlignmentOfBufferInBytes));
	if (!l_gpuVertexData) 
	{ 
		printf("Cannot allocate vertex data\n"); 
		return SCE_KERNEL_ERROR_ENOMEM; 
	}

	// Allocate the index buffer memory
	uint16_t* l_gpuIndexData = static_cast<uint16_t*>(garlicAllocator->allocate(indicesSize, Gnm::kAlignmentOfBufferInBytes));
	if (!l_gpuIndexData) 
	{ 
		printf("Cannot allocate index data\n"); 
		return SCE_KERNEL_ERROR_ENOMEM; 
	}

	// Copy the vertex/index data onto the GPU mapped memory
	memcpy(l_gpuVertexData, vertices, verticesSize);
	memcpy(l_gpuIndexData, indices, indicesSize);

	myVertexBuffers[PT_VERTEX_POSITION].initAsVertexBuffer(
		&l_gpuVertexData->x,
		Gnm::kDataFormatR32G32B32Float,
		sizeof(PtVertex),
		verticesSize / sizeof(PtVertex));

	myVertexBuffers[PT_VERTEX_COLOUR].initAsVertexBuffer(
		&l_gpuVertexData->r,
		Gnm::kDataFormatR32G32B32Float,
		sizeof(PtVertex),
		verticesSize / sizeof(PtVertex));

	myVertexBuffers[PT_VERTEX_NORMAL].initAsVertexBuffer(
		&l_gpuVertexData->nx,
		Gnm::kDataFormatR32G32B32Float,
		sizeof(PtVertex),
		verticesSize / sizeof(PtVertex));

	myVertexBuffers[PT_VERTEX_TEXCOORD].initAsVertexBuffer(
		&l_gpuVertexData->u,
		Gnm::kDataFormatR32G32Float,
		sizeof(vertices[0]),
		vertexCount);

	gpuIndexData = l_gpuIndexData;
	gpuVertexData = l_gpuVertexData;

	return l_result;
}

int PtModel::loadModelPTM(LinearAllocator* garlicAllocator)
{
	int error = 0;
	char letter = ' ';
	int pCount = 0;
	int pIndex = 0;
	float pX = 0;
	float pY = 0;
	float pZ = 0;

	int cCount = 0;
	int cIndex = 0;
	float cR = 0;
	float cG = 0;
	float cB = 0;

	int tCount = 0;
	int tIndex = 0;
	int tA = 0;
	int tB = 0;
	int tC = 0;

	int nCount = 0;
	int nIndex = 0;
	float nA = 0;
	float nB = 0;
	float nC = 0;

	int uCount = 0;
	int uIndex = 0;
	float uA = 0;
	float uB = 0;

	char word[50];

	onionMemorySize = 16 * 1024 * 1024;
	LinearAllocator myOnionAllocator;
	error = myOnionAllocator.initialize(onionMemorySize, SCE_KERNEL_WB_ONION, SCE_KERNEL_PROT_CPU_RW | SCE_KERNEL_PROT_GPU_ALL);
	if (error != SCE_OK)
	{
		printf("Onion allocator failed to initialise: 0x%08X\n", error);
		return error;
	}

	//file parser
	danFileParser myDFP;
	error = myDFP.openFile(filename);
	if (error != SCE_OK)
	{
		printf("Unable to load file in model\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	while (!myDFP.atEOF())
	{
		if (myDFP.getChar(letter))
		{
			if (letter == 'P')
			{
				pCount++;
			}
			else if (letter == 'C')
			{
				cCount++;
			}
			else if (letter == 'T')
			{
				tCount++;
			}
			else if (letter == 'N')
			{
				nCount++;
			}
			else if(letter == 'U')
			{
				uCount++;
			}
			else if (letter == 'X')
			{
				myDFP.getWordNoNewLine(word);
				if (myDFP.stringCompare(word, "SINGLE_COLOUR"))
				{
					oneColour = true;
				}
				else if (myDFP.stringCompare(word, "NO_COLOUR"))
				{
					noColour = true;
				}
				else if (myDFP.stringCompare(word, "GEN_SEQUENTIAL_TRIS"))
				{
					generateSequentialTriangles = true;
				}
				else if (myDFP.stringCompare(word, "GEN_SPLAYED_NORMALS") || myDFP.stringCompare(word, "GEN_NORMALS"))
				{
					generateNormalsRequired = true;
				}
			}
		}
		myDFP.nextLine();
	}

	indexCount = tCount * 3;
	vertexCount = pCount;
	verticesSize = vertexCount * sizeof(PtVertex);
	indicesSize = indexCount * sizeof(uint16_t);

	if (verbose)
	{
		printf("found %i positions, %i colours in %i triangles\n", pCount, cCount, tCount);
	}

	vertices = (PtVertex*)myOnionAllocator.allocate(verticesSize, Gnm::kAlignmentOfBufferInBytes);
	if (!vertices)
	{
		printf("Unable to allocate memory for m_vertices in ptModel::loadModelPTM\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	indices = (uint16_t*)myOnionAllocator.allocate(indicesSize, Gnm::kAlignmentOfBufferInBytes);
	if (!indices)
	{
		printf("Unable to allocate memory for m_vertices in ptModel::loadModelPTM\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	if (verbose)
	{
		printf("Memory allocated: %i for vertices, %i for indices\n", (int)verticesSize, (int)indicesSize);
	}

	std::vector<bool> pCheck;
	std::vector<bool> cCheck;
	std::vector<bool> uCheck;
	for (int x = 0; x < pCount; x++)
	{
		pCheck.push_back(false);
	}
	for (int x = 0; x < cCount; x++)
	{
		cCheck.push_back(false);
	}
	for (int x = 0; x < uCount; x++)
	{
		uCheck.push_back(false);
	}

	triangles = (PtTriangle*)indices;
	myDFP.reset();

	while (!myDFP.atEOF())
	{
		if (myDFP.getChar(letter))
		{
			if (letter == 'P')
			{
				if (myDFP.getInt(pIndex) && myDFP.getFloat(pX) && myDFP.getFloat(pY) && myDFP.getFloat(pZ))
				{
					vertices[pIndex].x = pX;
					vertices[pIndex].y = pY;
					vertices[pIndex].z = pZ;

					if (pIndex > pCount)
					{
						printf("Position index out of range\n");
						return SCE_ERROR_ERROR_FLAG;
						continue;
					}
					else if (pCheck[pIndex])
					{
						printf("Duplicate position for index %i, replacing previous data\n", pIndex);
					}
					pCheck[pIndex] = true;
					//printf("Position[%i] = (%f,%f,%f)\n", pIndex, pX, pY, pZ);
				}
			}
			else if (letter == 'C')
			{
				if (myDFP.getInt(cIndex) && myDFP.getFloat(cR) && myDFP.getFloat(cG) && myDFP.getFloat(cB))
				{
					vertices[cIndex].r = cR;
					vertices[cIndex].g = cG;
					vertices[cIndex].b = cB;

					//printf("Position[%i] = (%f,%f,%f)\n", cIndex, cR, cG, cB);
				}
			}
			else if (letter == 'T')
			{
				if (myDFP.getInt(tIndex) && myDFP.getInt(tA) && myDFP.getInt(tB) && myDFP.getInt(tC))
				{
					triangles[tIndex].a = tA;
					triangles[tIndex].b = tB;
					triangles[tIndex].c = tC;

					//printf("Position[%i] = (%i,%i,%i)\n", tIndex, tA, tB, tC);
				}
			}
			else if (letter == 'N')
			{
				if (myDFP.getInt(nIndex) && myDFP.getFloat(nA) && myDFP.getFloat(nB) && myDFP.getFloat(nC))
				{
					vertices[nIndex].nx = nA;
					vertices[nIndex].ny = nB;
					vertices[nIndex].nz = nC;
				}
			}
			else if (letter == 'U')
			{
				if (myDFP.getInt(uIndex) && myDFP.getFloat(uA) && myDFP.getFloat(uB))
				{
					vertices[uIndex].u = uA;
					vertices[uIndex].v = uB;

					uCheck[uIndex] = true;
				}
			}
		}
		myDFP.nextLine();
	}

	for (int x = 0; x < pCount; x++)
	{
		if (pCheck[x] == false)
		{
			return SCE_ERROR_ERROR_FLAG;
		}
	}

	for (int x = 0; x < uCount; x++)
	{
		if (uCheck[x] == false)
		{
			return SCE_ERROR_ERROR_FLAG;
		}
	}

	if (generateNormalsRequired)
	{
		generateNormals();
	}

	if (noColour)
	{
		fillRandomColour();
	}

	if (oneColour && !cCheck[0]) 
	{
		oneColour = false; 
		noColour = true; 
	}

	if (generateSequentialTriangles)
	{
		generateSequentialIndices(&myOnionAllocator);
	}
	/*for (int x = 0; x < pCount; x++)
	{
		if (cCheck[x] == false)
		{
			return SCE_ERROR_ERROR_FLAG;
		}
	}*/

	if (normalisePositionsRequired)
	{
		normalisePositions();
	}
	if (centralisePositionsRequired)
	{
		centralisePositions();
	}

	error = copyDataToGPU(garlicAllocator);
	if (error != SCE_OK) 
	{ 
		printf("Unable to copy model data to GPU memory: 0x%08X\n", error);  
		return error; 
	}

	myOnionAllocator.terminate();

	//leave this near end to protect against bad data
	if ((vertexCount > 2) && (indexCount > 2))
	{
		validData = true;
	}

	return error;
}

bool PtModel::getValidData()
{
	return validData;
}

Gnm::Buffer* PtModel::getVertexBuffers()
{
	return myVertexBuffers;
}

uint32_t PtModel::getIndexCount()
{
	return indexCount;
}

uint16_t* PtModel::getGpuIndexData()
{
	return gpuIndexData;
}

void PtModel::fillColour(Vector3 colour)
{
	for (int x = 0; x < vertexCount; x++)
	{
		vertices[x].r = colour[0];
		vertices[x].g = colour[1];
		vertices[x].b = colour[2];
	}
}

void PtModel::setDefaultColour(Vector3 colour)
{
	defaultColour = colour;
}

void PtModel::generateSequentialIndices(LinearAllocator* onionAllocator)
{
	indices = (uint16_t*)onionAllocator->allocate(indicesSize, Gnm::kAlignmentOfBufferInBytes);

	for (int x = 0; x < vertexCount; x++)
	{
		indices[x] = x;
	}
}

void PtModel::fillRandomColour()
{
	danRandom random;
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].r = random.getFraction();
		vertices[i].g = random.getFraction();
		vertices[i].b = random.getFraction();
	}//for
}

int PtModel::loadModelOBJ(LinearAllocator* garlicAllocator)
{
	int error = 0;
	int pCount = 0; //vertex positions
	int uCount = 0; //vertex texture coordinates
	int nCount = 0; //vertex normals
	int fCount = 0; //faces
	int tCount = 0; //triangles
	int vCount = 0; //vertex index sets

	char lineType[50];			//read in the data type
	char vertexString[50];		//for vertex-index triples
	float a = 0;
	float b = 0;
	float c = 0;				//for float data
	int smoothingGroup = 0;		//keep a track of the smoothing group

	centralisePositionsRequired = true;
	normalisePositionsRequired = true;
	
	onionMemorySize = 16 * 1024 * 1024;
	LinearAllocator myOnionAllocator;
	error = myOnionAllocator.initialize(onionMemorySize, SCE_KERNEL_WB_ONION, SCE_KERNEL_PROT_CPU_RW | SCE_KERNEL_PROT_GPU_ALL);
	if (error != SCE_OK)
	{
		printf("Onion allocator failed to initialise: 0x%08X\n", error);
		return error;
	}

	danFileParser myDFP;
	error = myDFP.openFile(filename);
	if (error != SCE_OK)
	{
		printf("Unable to load file in model\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	while (!myDFP.atEOF())
	{
		if (myDFP.getWord(lineType))
		{
			if (myDFP.stringCompare(lineType, "v"))
			{
				pCount++;
			}
			else if (myDFP.stringCompare(lineType, "vt"))
			{
				uCount++;
			}
			else if (myDFP.stringCompare(lineType, "vn"))
			{
				nCount++;
			}
			else if (myDFP.stringCompare(lineType, "f"))
			{
				int counter = 0;
				while (myDFP.getWordNoNewLine(vertexString))
				{
					counter++;
				}
				vCount += counter;
				tCount += counter - 2;
				fCount++;
			}
		}
		myDFP.nextLine();
	}

	if (nCount == 0)
	{
		generateNormalsRequired = true;
	}

	if (verbose)
	{
		printf("Found %i positions, %i texcoords and %i normals\n", pCount, uCount, nCount);
		printf("Found %i triangles, in %i faces (using %i vertices)\n", tCount, fCount, vCount);
	}
	indexCount = tCount * 3;
	
	size_t objectPositionSize = pCount * sizeof(danObjPosition);
	danObjPosition* objectPositions = (danObjPosition*)myOnionAllocator.allocate(objectPositionSize, Gnm::kAlignmentOfBufferInBytes);
	if (!objectPositions)
	{ 
		printf("Unable to allocate memory for ObjPositions in ptModel::loadModelOBJ\n"); 
		return SCE_ERROR_ERROR_FLAG;
	}

	size_t objectTexcoordSize = uCount * sizeof(danObjTexcoord);
	danObjTexcoord* objectTexcoords = (danObjTexcoord*)myOnionAllocator.allocate(objectTexcoordSize, Gnm::kAlignmentOfBufferInBytes);
	if (!objectTexcoords)
	{
		printf("Unable to allocate memory for ObjTexcoords in ptModel::loadModelOBJ\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	size_t objectNormalSize = nCount * sizeof(danObjNormal);
	danObjNormal* objectNormals = (danObjNormal*)myOnionAllocator.allocate(objectNormalSize, Gnm::kAlignmentOfBufferInBytes);
	if (!objectNormals)
	{
		printf("Unable to allocate memory for ObjNormals in ptModel::loadModelOBJ\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	size_t objectTriplesSize = vCount * sizeof(danObjTriple);
	danObjTriple* objectTriples = (danObjTriple*)myOnionAllocator.allocate(objectTriplesSize, Gnm::kAlignmentOfBufferInBytes);
	if (!objectTriples)
	{
		printf("Unable to allocate memory for ObjTriples in ptModel::loadModelOBJ\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	//m_indices memory. This is will eventually be the final index data
	//indices will start by using indices to danObjTriple objects
	indicesSize = sizeof(uint16_t) * indexCount;
	indices = (uint16_t*)myOnionAllocator.allocate(indicesSize, Gnm::kAlignmentOfBufferInBytes);
	if (!indices) 
	{ 
		printf("Unable to allocate memory for m_indices in ptModel::loadModelOBJ\n"); 
		return SCE_ERROR_ERROR_FLAG; 
	}
	triangles = (PtTriangle*)indices;

	pCount = 0;
	uCount = 0; 
	nCount = 0;
	fCount = 0;
	tCount = 0;
	vCount = 0;
	
	myDFP.reset();
	while (!myDFP.atEOF())
	{
		if (myDFP.getWord(lineType))
		{
			if (myDFP.stringCompare(lineType, "v"))
			{
				if ((myDFP.getFloat(a) && myDFP.getFloat(b) && myDFP.getFloat(c)))
				{
					objectPositions[pCount].x = a;
					objectPositions[pCount].y = b;
					objectPositions[pCount].z = c;
					pCount++;
				}
			}
			else if (myDFP.stringCompare(lineType, "vt"))
			{
				if ((myDFP.getFloat(a) && myDFP.getFloat(b)))
				{
					objectTexcoords[uCount].u = a;
					objectTexcoords[uCount].v = 1 - b;
					uCount++;
				}
			}
			else if (myDFP.stringCompare(lineType, "vn"))
			{
				if ((myDFP.getFloat(a) && myDFP.getFloat(b) && myDFP.getFloat(c)))
				{
					objectNormals[nCount].x = a;
					objectNormals[nCount].y = b;
					objectNormals[nCount].z = c;
					nCount++;

					if (verbose)
					{
						printf("%i, (%f, %f, %f)\n", nCount, a, b, c);
					}
				}
			}
			else if (myDFP.stringCompare(lineType, "s"))
			{
				if (!myDFP.getInt(smoothingGroup))
				{
					smoothingGroup = 0;
				}
			}
			else if (myDFP.stringCompare(lineType, "f"))
			{
				int counter = 0;
				int triA = vCount;

				//parse index data into our ptObjTriples structure
				while (myDFP.getWordNoNewLine(vertexString))
				{
					objectTriples[vCount].parseTriple(vertexString, pCount, uCount, nCount, smoothingGroup);
					counter++;
					vCount++;
				}

				//create triangles from faces
				//this is tricky to work out the logic, basically a face is a triangle fan
				int secondCounter = 2;
				while (secondCounter < counter)
				{
					triangles[tCount].a = triA;
					triangles[tCount].b = triA + secondCounter - 1;
					triangles[tCount].c = triA + secondCounter;
					secondCounter++;
					tCount++;
				}
				fCount++;
			}
		}
		myDFP.nextLine();
	}
	
	for (int i = 0; i < vCount; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (objectTriples[i].matchAndMark(&objectTriples[j], j))
			{
				if (verbose)
				{
					printf("Triple %i is a duplicate of %i\n", i, j);
				}
				j = i;
			}
		}
	}

	//mark "real index" on originals by counting through them
	int rCount = 0;
	for (int i = 0; i < vCount; i++)
	{
		if (!objectTriples[i].m_duplicate)
		{
			objectTriples[i].m_realIndex = rCount;
			rCount++;
		}
	}

	//create memory for final vertex data
	vertexCount = rCount;
	verticesSize = sizeof(PtVertex)*vertexCount;
	vertices = (PtVertex*)myOnionAllocator.allocate(verticesSize, Gnm::kAlignmentOfBufferInBytes);
	if (!vertices)
	{
		printf("Unable to allocate memory for m_vertices in ptModel::loadModelOBJ\n"); 
		return SCE_ERROR_ERROR_FLAG; 
	}

	//copy vertex data from intermediate arrays to final array 
	//use counter to ONLY transfer the originals and not duplicates 
	int counter = 0;
	for (int i = 0; i < vCount; i++)
	{
		if (!objectTriples[i].m_duplicate)
		{
			if (objectTriples[i].m_gotPosition)
			{
				vertices[counter].x = objectPositions[objectTriples[i].m_positionIndex].x;
				vertices[counter].y = objectPositions[objectTriples[i].m_positionIndex].y;
				vertices[counter].z = objectPositions[objectTriples[i].m_positionIndex].z;

				vertices[counter].nx = objectNormals[objectTriples[i].m_normalIndex].x;
				vertices[counter].ny = objectNormals[objectTriples[i].m_normalIndex].y;
				vertices[counter].nz = objectNormals[objectTriples[i].m_normalIndex].z;

				vertices[counter].u = objectTexcoords[objectTriples[i].m_texcoordIndex].u;
				vertices[counter].v = objectTexcoords[objectTriples[i].m_texcoordIndex].v;
			}//if
			counter++;
		}//if
	}//for

	 //correct indices in m_indices to point to correct places in m_vertices
	for (int i = 0; i < indexCount; i++)
	{
		if (objectTriples[indices[i]].m_duplicate)
		{
			indices[i] = objectTriples[objectTriples[indices[i]].m_duplicateIndex].m_realIndex;
		}
		else
		{
			indices[i] = objectTriples[indices[i]].m_realIndex;
		}
	}//for

	if (generateNormalsRequired)
	{
		generateNormals();
	}

	 //data generation
	if (normalisePositionsRequired)
	{
		normalisePositions();
	}
	if (centralisePositionsRequired)
	{
		centralisePositions();
	}

	error = copyDataToGPU(garlicAllocator);
	if (error != SCE_OK) 
	{ 
		printf("Unable to copy model data to GPU memory: 0x%08X\n", error); 
		return error; 
	}

	validData = true;
	myOnionAllocator.terminate();
	return error;
}

void PtModel::centralisePositions()
{
	float totalX = 0;
	float averageX = 0;
	float totalY = 0;
	float averageY = 0;
	float totalZ = 0;
	float averageZ = 0;

	//add all up
	for (int i = 0; i < vertexCount; i++)
	{
		totalX += vertices[i].x;
		totalY += vertices[i].y;
		totalZ += vertices[i].z;
	}

	 //find centre
	averageX = totalX / vertexCount;
	averageY = totalY / vertexCount;
	averageZ = totalZ / vertexCount;

	//ofset from local origin
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].x -= averageX;
		vertices[i].y -= averageY;
		vertices[i].z -= averageZ;
	}
}

void PtModel::normalisePositions()
{
	float largest = 0.0f;
	for (int i = 0; i < vertexCount; i++)
	{
		float length = sqrt((vertices[i].x * vertices[i].x) + (vertices[i].y * vertices[i].y) + (vertices[i].z * vertices[i].z));
		if (length > largest)
		{
			largest = length;
		}
	}//for

	printf("Normalizing model size by factor %f\n", largest);
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].x = vertices[i].x / largest;
		vertices[i].y = vertices[i].y / largest;
		vertices[i].z = vertices[i].z / largest;
	}
}

void PtModel::generateNormals()
{
	cleanNormals();

	unsigned int count = indexCount / 3;
	for (int i = 0; i < count; i++)
	{
		Vector3 tA(vertices[triangles[i].a].x, vertices[triangles[i].a].y, vertices[triangles[i].a].z);
		Vector3 tB(vertices[triangles[i].b].x, vertices[triangles[i].b].y, vertices[triangles[i].b].z);
		Vector3 tC(vertices[triangles[i].c].x, vertices[triangles[i].c].y, vertices[triangles[i].c].z);

		Vector3 tAB = tB - tA;
		Vector3 tAC = tC - tA;
		Vector3 crossProduct = Vectormath::Scalar::Aos::cross(tAB, tAC);
		Vector3 normalized = Vectormath::Scalar::Aos::normalize(crossProduct);

		vertices[triangles[i].a].nx += normalized.getX();
		vertices[triangles[i].a].ny += normalized.getY();
		vertices[triangles[i].a].nz += normalized.getZ();

		vertices[triangles[i].b].nx += normalized.getX();
		vertices[triangles[i].b].ny += normalized.getY();
		vertices[triangles[i].b].nz += normalized.getZ();

		vertices[triangles[i].c].nx += normalized.getX();
		vertices[triangles[i].c].ny += normalized.getY();
		vertices[triangles[i].c].nz += normalized.getZ();
	}

	normaliseNormals();
}

void PtModel::cleanNormals() 
{
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].nx = 0;
		vertices[i].ny = 0;
		vertices[i].nz = 0;
	}
}

void PtModel::normaliseNormals()
{
	for (int i = 0; i < vertexCount; i++)
	{
		Vector3 points(vertices[i].nx, vertices[i].ny, vertices[i].nz);
		Vector3 normalised = Vectormath::Scalar::Aos::normalize(points);

		vertices[i].nx = normalised.getX();
		vertices[i].ny = normalised.getY();
		vertices[i].nz = normalised.getZ();
	}
}

void PtModel::setFilename(const char* name)
{
	filename = name;
}

void PtModel::setAssetType(PtAssetTypes type)
{
	assetType = type;
}

PtAssetTypes PtModel::getAssetType()
{
	return assetType;
}

void PtModel::printFirst10UVs()
{
	printf("First 10 UVS...\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%i, (%f, %f)\n", i, gpuVertexData[i].u, gpuVertexData[i].v);
	}
}