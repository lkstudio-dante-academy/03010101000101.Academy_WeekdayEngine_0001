#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

#define EXAMPLE_TYPE_STRUCTURE			1
#define EXAMPLE_TYPE_MATH				2
#define EXAMPLE_TYPE_DIRECT				3

#define EXAMPLE_TYPE			EXAMPLE_TYPE_DIRECT

#if EXAMPLE_TYPE == EXAMPLE_TYPE_STRUCTURE
#include "Example_1/Example_1.h"
#include "Example_2/Example_2.h"
#include "Example_3/Example_3.h"
#include "Example_4/Example_4.h"
#include "Example_5/Example_5.h"
#elif EXAMPLE_TYPE == EXAMPLE_TYPE_MATH
#include "Example_6/Example_6.h"
#include "Example_7/Example_7.h"
#elif EXAMPLE_TYPE == EXAMPLE_TYPE_DIRECT
#include "Example_8/Example_8.h"
#include "Example_9/Example_9.h"
#include "Example_10/Example_10.h"
#include "Example_11/Example_11.h"
#include "Example_12/Example_12.h"
#include "Example_13/Example_13.h"
#include "Example_14/Example_14.h"
#include "Example_15/Example_15.h"
#include "Example_16/Example_16.h"
#include "Example_17/Example_17.h"
#include "Example_18/Example_18.h"
#include "Example_19/Example_19.h"
#include "Example_20/Example_20.h"
#include "Example_21/Example_21.h"
#include "Example_22/Example_22.h"
#include "Example_23/Example_23.h"
#include "Example_24/Example_24.h"
#include "Example_25/Example_25.h"
#include "Example_26/Example_26.h"
#include "Example_27/Example_27.h"
#include "Example_28/Example_28.h"
#include "Example_29/Example_29.h"
#include "Example_30/Example_30.h"
#include "Example_31/Example_31.h"
#include "Example_32/Example_32.h"
#include "Example_33/Example_33.h"
#include "Example_34/Example_34.h"
#include "Example_35/Example_35.h"
#include "Example_36/Example_36.h"
#endif			// #if EXAMPLE_TYPE == EXAMPLE_TYPE_DATA_STRUCTURE

int APIENTRY _tWinMain(HINSTANCE a_hInstance, HINSTANCE a_hPrevInstance, TCHAR* a_pszCommandLine, int a_nOptions)
{
#if EXAMPLE_TYPE == EXAMPLE_TYPE_STRUCTURE || EXAMPLE_TYPE == EXAMPLE_TYPE_MATH
	if(AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}

#if EXAMPLE_TYPE == EXAMPLE_TYPE_STRUCTURE
	//Example_1();
	//Example_2();
	//Example_3();
	//Example_4();
	Example_5();
#else
	//Example_6();
	Example_7();
#endif			// EXAMPLE_TYPE == EXAMPLE_TYPE_STRUCTURE

	system("pause");
	FreeConsole();

	return 0;
#elif EXAMPLE_TYPE == EXAMPLE_TYPE_DIRECT
	SIZE stWindowSize = {
		480, 320
	};

	//Example_8 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_9 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_10 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_11 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_12 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_13 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_14 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_15 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_16 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_17 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_18 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_19 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_20 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_21 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_22 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_23 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_24 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_25 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_26 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_27 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_28 oApplication(a_hInstance, a_nOptions, stWindowSize);
	Example_29 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_30 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_31 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_32 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_33 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_34 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_35 oApplication(a_hInstance, a_nOptions, stWindowSize);
	//Example_36 oApplication(a_hInstance, a_nOptions, stWindowSize);

	return oApplication.runApplication();
#endif			// #if EXAMPLE_TYPE == EXAMPLE_TYPE_STRUCTURE
}
