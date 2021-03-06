// copyright (c) 2007 magnus auvinen, see licence.txt for more info
#include <engine/graphics.h>
#include <engine/map.h>
#include <game/client/component.h>
#include <game/mapitems.h>

#include "mapimages.h"

CMapImages::CMapImages()
{
	m_Count = 0;
	m_EntitiesTextures = -1;
}

int CMapImages::GetEntities()
{
	if(m_EntitiesTextures == -1)
	{
		m_EntitiesTextures = Graphics()->LoadTexture("editor/col_entities.png", CImageInfo::FORMAT_AUTO, 0); // load the clear entities

	}
	return m_EntitiesTextures;
}

void CMapImages::OnMapLoad()
{
	IMap *pMap = Kernel()->RequestInterface<IMap>();
	
	// unload all textures
	for(int i = 0; i < m_Count; i++)
	{
		Graphics()->UnloadTexture(m_aTextures[i]);
		m_aTextures[i] = -1;
	}
	m_Count = 0;
	

	int Start;
	pMap->GetType(MAPITEMTYPE_IMAGE, &Start, &m_Count);
	
	// load new textures
	for(int i = 0; i < m_Count; i++)
	{
		m_aTextures[i] = 0;
		
		CMapItemImage *pImg = (CMapItemImage *)pMap->GetItem(Start+i, 0, 0);
		if(pImg->m_External)
		{
			char Buf[256];
			char *pName = (char *)pMap->GetData(pImg->m_ImageName);
			str_format(Buf, sizeof(Buf), "mapres/%s.png", pName);
			m_aTextures[i] = Graphics()->LoadTexture(Buf, CImageInfo::FORMAT_AUTO, 0);
		}
		else
		{
			void *pData = pMap->GetData(pImg->m_ImageData);
			m_aTextures[i] = Graphics()->LoadTextureRaw(pImg->m_Width, pImg->m_Height, CImageInfo::FORMAT_RGBA, pData, CImageInfo::FORMAT_RGBA, 0);
			pMap->UnloadData(pImg->m_ImageData);
		}
	}
}

