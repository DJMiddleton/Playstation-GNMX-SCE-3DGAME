#ifndef __PT_VERTEX__
#define __PT_VERTEX__

#include "modelTypes.h"
#include "../../common/allocator.h"
#include "../../common/danFileParser.h"
#include "scebase.h"
#include <memory>

// struct to hold vertex data. Needs to reflect the input to the vertex shader, ptVSInput
struct PtVertex
{
	float x, y, z;	// Position
	float r, g, b;	// Color
	float nx, ny, nz;
	float u, v;		// UVs
};//struct


  //a list of the vertex data elements
enum PtVertexElements
{
	PT_VERTEX_POSITION = 0,
	PT_VERTEX_COLOUR,
	PT_VERTEX_NORMAL,
	PT_VERTEX_TEXCOORD,
	PT_VERTEX_ELEM_COUNT
};//enum

struct PtTriangle
{
	uint16_t a, b, c;
};

#endif