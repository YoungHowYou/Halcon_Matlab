#pragma once
#ifndef __APPLE__
#include "Halcon.h"
#else
#  ifndef HC_LARGE_IMAGES
#    include <HALCON/Halcon.h>
#  else
#    include <HALCONxl/Halcon.h>
#  endif
#endif
#define Test_EXPORTS_API __declspec(dllexport)




#ifdef __cplusplus
extern "C" {
#endif

#pragma region Matlab
	extern Test_EXPORTS_API Herror	HMatlab_engOpen(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror	HMatlab_engClose(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HMatlab_engEvalString(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HMatlab_engGetVariable(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HMatlab_engPutVariable(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HMatlab_engOutputBuffer(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HMatlab_engSetVisible(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HMatlab_engSetmxArray(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HMatlab_engGetmxArray(Hproc_handle proc_handle);

#pragma endregion



#ifdef __cplusplus
}
#endif 



