#include "StdAfx.h"
#include "CTablePositioner.h"

#include "CSharedMem.h"
#include "MagicNumbers.h"
#include "Winuser.h"


CTablePositioner *p_table_positioner = NULL;


CTablePositioner::CTablePositioner()
{}

CTablePositioner::~CTablePositioner()
{}

void CTablePositioner::PositionMyWindow()
{		
	// Build list of poker tables (child windows)
	// Use the shared memory (auto-connector) for that.
	// There will be some NULL-windows in the list, but this does not harm,
	// NULL means: desktop.
	int number_of_child_windows = MAX_SESSION_IDS;
	HWND *HWNDs_of_child_windows = p_sharedmem->GetListOfConnectedPokerWindows();

	// Tiling windows: http://msdn.microsoft.com/en-us/library/windows/desktop/ms633554(v=vs.85).aspx
	// Cascading windows: http://msdn.microsoft.com/en-us/library/windows/desktop/ms632674(v=vs.85).aspx
	TileWindows(
		NULL,				// Parent; NULL = whole desktop
		MDITILE_HORIZONTAL,	// How; either MDITILE_HORIZONTA or MDITILE_VERTICAL
		NULL,				// Target area; NULL = parent window, here desktop
		number_of_child_windows,
		HWNDs_of_child_windows);
}