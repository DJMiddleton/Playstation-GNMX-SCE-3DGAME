/* SIE CONFIDENTIAL
PlayStation(R)4 Programmer Tool Runtime Library Release 04.008.061
* Copyright (C) 2011 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#ifndef __PT_TDT_VS_OUTPUT__
#define __PT_TDT_VS_OUTPUT__

struct ptTDTVSOutput
{
	float4 m_position		: S_POSITION;
	float3 m_originalPosition	: ORIG_POS;
	float2 m_texcoord		: TEX_COORDS;
	float3 m_normal			: NORMAL;
	float3 m_positionWorld	: POSITION_WORLD;
	float3 m_colour			: COLOUR;
};//struct

#endif