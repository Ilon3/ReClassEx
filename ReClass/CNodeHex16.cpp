#include "stdafx.h"
#include "CNodeHex16.h"

CNodeHex16::CNodeHex16( )
{
	m_nodeType = nt_hex16;
}

void CNodeHex16::Update( const PHOTSPOT Spot )
{
	StandardUpdate( Spot );
	unsigned char v = (unsigned char)(_tcstoul( Spot->Text.GetString( ), NULL, 16 ) & 0xFF);
	if (Spot->Id == 0)
		ReClassWriteMemory( (LPVOID)Spot->Address, &v, 1 );
	if (Spot->Id == 1)
		ReClassWriteMemory( (LPVOID)(Spot->Address + 1), &v, 1 );
}

NODESIZE CNodeHex16::Draw( const PVIEWINFO View, int x, int y )
{
    int tx;
    NODESIZE DrawSize;
    const UCHAR* Data;

	if (m_bHidden)
		return DrawHidden( View, x, y );
  
	Data = (const UCHAR*)(View->Data + m_Offset);
	AddSelection( View, 0, y, g_FontHeight );
	AddDelete( View, x, y );
	AddTypeDrop( View, x, y );
	//AddAdd(View,x,y);

    tx = x + TXOFFSET + 16;
	tx = AddAddressOffset( View, tx, y );

	if (g_bText)
	{
		CStringA str = GetStringFromMemoryA( (const char*)Data, 2 );
		str += "       ";
		tx = AddText( View, tx, y, g_crChar, HS_NONE, "%s", str.GetBuffer( ) );
	}

	tx = AddText( View, tx, y, g_crHex, 0, _T( "%0.2X" ), Data[0] & 0xFF ) + g_FontWidth;
	tx = AddText( View, tx, y, g_crHex, 1, _T( "%0.2X" ), Data[1] & 0xFF ) + g_FontWidth;
	tx = AddComment( View, tx, y );

    DrawSize.x = tx;
    DrawSize.y = y + g_FontHeight;
	return DrawSize;
}
