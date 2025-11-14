// Halcon_Hik.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "windows.h"
#include "stdio.h"
#include "engine.h"
#include "Halcon_Matlab.h"

#ifndef __APPLE__
#include "HalconCpp.h"
#include "HDevThread.h"
#if defined(__linux__) && (defined(__i386__) || defined(__x86_64__)) && !defined(NO_EXPORT_APP_MAIN)
#include <X11/Xlib.h>
#endif
#else
#ifndef HC_LARGE_IMAGES
#include <HALCONCpp/HalconCpp.h>
#include <HALCONCpp/HDevThread.h>
#else
#include <HALCONCppxl/HalconCpp.h>
#include <HALCONCppxl/HDevThread.h>
#endif
#include <stdio.h>
#include <HALCON/HpThread.h>
#include <CoreFoundation/CFRunLoop.h>
#endif
using namespace HalconCpp;
static char p[1024];

Engine *ep;
// extern "C"
// {
// #define H_MATLAB_ENGINE_TAG 0xC0FFEE10
// #define H_MATLAB_ENGINE_SEM_TYPE "matlab_engine"

// typedef struct {
//     Engine *ep;
// } HUserHandleData;

// static Herror HUserHan
//         engClose(data-dleDestructor(Hproc_handle ph, HUserHandleData *data) {
//     if (data->ep) {>ep);
//         data->ep = NULL;
//     }
//     return HFree(ph, data);
// }

// // 句柄类型描述符
//  const HHandleInfo HandleTypeUser =
//     HANDLE_INFO_INITIALIZER_NOSER(H_MATLAB_ENGINE_TAG, H_MATLAB_ENGINE_SEM_TYPE,
//                                   HUserHandleDestructor, NULL, NULL);

// }
Herror HMatlab_engOpen(Hproc_handle proc_handle)
{
	//HUserHandleData **handle_data;

    // 分配输出句柄
    //HCkP(HAllocOutputHandle(proc_handle, 1, &handle_data, &HandleTypeUser));

    // 分配并初始化用户数据
    //HCkP(HAlloc(proc_handle, sizeof(HUserHandleData), (void**)handle_data));

    //(*handle_data)->
	ep = engOpen(NULL);
    //if (!(*handle_data)->ep) {
    //    return H_ERR_WIPV1;  // 或自定义错误码
    //}
	//ep =(*handle_data)->ep;//这个后面要删掉
    return H_MSG_TRUE;
}
// static Herror HUserHandleCreate(Hproc_handle ph, HUserHandleData** user_handle)
// {
//   HUserHandleData* uh;

//   *user_handle = NULL;
//   HCkP(HAlloc(ph, sizeof(*uh), &uh));
//   //memset(uh, 0, sizeof(*uh));

//   /* 你的内容在这写*/


//   *user_handle = uh;
//   return H_MSG_OK;
// }


Herror HMatlab_engClose(Hproc_handle proc_handle)
{
    //HUserHandleData *handle_data;
    //HGetCElemH1(proc_handle, 1, &HandleTypeUser, &handle_data);
    // HALCON 会自动调用析构函数释放句柄
	 engClose(ep);
    return H_MSG_TRUE;
}

Herror HMatlab_engEvalString(Hproc_handle proc_handle)
{
    //HUserHandleData *handle_data;
    Hcpar MatlabString;

    // 获取句柄
    //HGetCElemH1(proc_handle, 1, &HandleTypeUser, &handle_data);

    // 获取字符串参数
    HAllocStringMem(proc_handle, 1024 * 512);
    HGetSPar(proc_handle, 1, STRING_PAR, &MatlabString, 1);

    // 执行 MATLAB 命令
    int ret = engEvalString(ep, MatlabString.par.s);
    if (ret != 0) {
        return H_ERR_WIPV2;  // 或自定义错误码
    }

    return H_MSG_TRUE;
}

Herror HMatlab_engOutputBuffer(Hproc_handle proc_handle)
{
	Hcpar BufferSize;

	HAllocStringMem(proc_handle, 1024);
	HGetSPar(proc_handle, 1, LONG_PAR, &BufferSize, 1);
	if (BufferSize.par.l > 1024)
	{

		return 11024;
	}
	else if (BufferSize.par.l == -1)//刷1024个字符出来
	{
		char *pp;
		HAllocTmp(proc_handle, &pp, 1024);

		memcpy(pp, p, 1024);
		HPutElem(proc_handle, 1, &pp, 1, STRING_PAR);
		return H_MSG_TRUE;
	}
	else if (BufferSize.par.l == 0)
	{
		return engOutputBuffer(ep, NULL, 0) + H_MSG_TRUE;
	}
	else
	{
		return engOutputBuffer(ep, p, BufferSize.par.l) + H_MSG_TRUE;
	}
}

Herror HMatlab_engSetVisible(Hproc_handle proc_handle)
{
	Hcpar Visible;
	// HAllocStringMem(proc_handle, 1024);
	HGetSPar(proc_handle, 1, LONG_PAR, &Visible, 1);
	if (Visible.par.l == 1)
	{
		return engSetVisible(ep, true) + H_MSG_TRUE;
	}
	else
	{
		return engSetVisible(ep, false) + H_MSG_TRUE;
	}
}

Herror HMatlab_engSetmxArray(Hproc_handle proc_handle)
{

	HAllocStringMem(proc_handle, 32);
	Hcpar hv_M;
	Hcpar hv_N;
	Hcpar NAME;
	HGetSPar(proc_handle, 1, LONG_PAR, &hv_M, 1);
	HGetSPar(proc_handle, 2, LONG_PAR, &hv_N, 1);
	HGetSPar(proc_handle, 3, STRING_PAR, &NAME, 1);
	Hcpar  *hv_VAL;
	INT4_8 num_params;
	HGetPPar(proc_handle, 4, &hv_VAL, &num_params);
	if(num_params!= hv_M.par.l* hv_N.par.l)
	{
		return H_ERR_WIPT4; // 错误代码：控制参数数量与矩阵大小不匹配
	}




	mxArray *xx = mxCreateDoubleMatrix(hv_M.par.l, hv_N.par.l, mxREAL);
	for (INT4_8 i = 0; i < num_params; i++)
	{
		mxGetPr(xx)[i] = hv_VAL[i].par.d;
	}

	int ret = engPutVariable(ep, NAME.par.s, xx);
	mxDestroyArray(xx);
	// free(value);
	return H_MSG_TRUE;
}
Herror HMatlab_engGetmxArray(Hproc_handle proc_handle)
{
	HAllocStringMem(proc_handle, 32);
	Hcpar NAME;
	HTuple hv_MatrixID;
	HGetSPar(proc_handle, 1, STRING_PAR, &NAME, 1);

	mxArray *A = NULL;
	if ((A = engGetVariable(ep, NAME.par.s)) == NULL)
	{
		return 9999;
	}
	double *C;
	HAllocTmp(proc_handle, &C, (int)mxGetM(A) * (int)mxGetN(A) * sizeof(double));

	INT4_8 m = mxGetM(A);
	INT4_8 n = mxGetN(A);
	memcpy(C, mxGetPr(A), (int)mxGetM(A) * (int)mxGetN(A) * sizeof(double)); // 将数组x复制到mxarray数组xx中。

	HPutElem(proc_handle, 1, &m, 1, LONG_PAR);
	HPutElem(proc_handle, 2, &n, 1, LONG_PAR);
	HPutElem(proc_handle, 3, C, m * n, DOUBLE_PAR);

	mxDestroyArray(A);

	return H_MSG_TRUE;
}

Herror HMatlab_engGetVariable(Hproc_handle proc_handle)

{
	// HAllocStringMem(proc_handle, 32);
	// Hcpar NAME;
	// Hcpar *Matrix;
	// INT4_8 num;
	// HGetSPar(proc_handle, 1, STRING_PAR, &NAME, 1);
	// HGetPPar(proc_handle, 2, &Matrix, &num);
	// mxArray *A = NULL;
	// if ((A = engGetVariable(ep, NAME.par.s)) == NULL){return 9999;}
	// double* C =mxGetPr(A);
	// HTuple hv_MatrixID;
	// HTuple hv_MatrixID(Matrix, 1);
	// HTuple hv_C(mxGetPr(A), (int)mxGetM(A) * (int)mxGetN(A));
	// HalconCpp::CreateMatrix((int)mxGetM(A), (int)mxGetN(A), hv_C, &hv_MatrixID);
	// mxDestroyArray(A);
	// hv_C.Clear();
	Hcpar *dict;
	INT4_8 num;
	HGetPPar(proc_handle, 1, &dict, &num);
	HTuple hv_DictHandle(dict, 1);
	HTuple hv_C, hv_GenParamValue;
	HTuple hv_Index, hv_name, hv_MatrixID;
	GetDictParam(hv_DictHandle, "keys", HTuple(), &hv_GenParamValue);
	{
		HTuple end_val7 = (hv_GenParamValue.TupleLength()) - 1;
		HTuple step_val7 = 1;
		for (hv_Index = 0; hv_Index.Continue(end_val7, step_val7); hv_Index += step_val7)
		{
			hv_name = HTuple(hv_GenParamValue[hv_Index]);
			mxArray *A = NULL;
			if ((A = engGetVariable(ep, hv_name.S())) == NULL)
			{
				return 9999;
			}
			// double* C =mxGetPr(A);
			HTuple hv_C(mxGetPr(A), (int)mxGetM(A) * (int)mxGetN(A));

			HalconCpp::CreateMatrix((int)mxGetM(A), (int)mxGetN(A), hv_C, &hv_MatrixID);
			SetDictTuple(hv_DictHandle, hv_name, hv_MatrixID);
			mxDestroyArray(A);
			hv_C.Clear();
		}
	}

	return H_MSG_TRUE;
}

Herror HMatlab_engPutVariable(Hproc_handle proc_handle)

{
	Hcpar *dict;
	INT4_8 num;
	HGetPPar(proc_handle, 1, &dict, &num);
	HTuple hv_DictHandle(dict, 1);
	HTuple hv_GenParamValue;
	HTuple hv_Index, hv_MatrixIDTuple, hv_Values, hv_M, hv_N;

	// int ret =engPutVariable(ep, const char* name, const mxArray * mp);
	GetDictParam(hv_DictHandle, "keys", HTuple(), &hv_GenParamValue);
	{
		HTuple end_val6 = (hv_GenParamValue.TupleLength()) - 1;
		HTuple step_val6 = 1;
		for (hv_Index = 0; hv_Index.Continue(end_val6, step_val6); hv_Index += step_val6)
		{
			GetDictTuple(hv_DictHandle, HTuple(hv_GenParamValue[hv_Index]), &hv_MatrixIDTuple);
			GetFullMatrix(hv_MatrixIDTuple, &hv_Values);
			GetSizeMatrix(hv_MatrixIDTuple, &hv_M, &hv_N);
			mxArray *xx = mxCreateDoubleMatrix(hv_M.L(), hv_N.L(), mxREAL);
			memcpy(mxGetPr(xx), hv_Values.DArr(), hv_M.L() * hv_N.L() * sizeof(double)); // 将数组x复制到mxarray数组xx中。
			int ret = engPutVariable(ep, hv_GenParamValue[hv_Index].S(), xx);			 // 将mxArray数组xx写入到Matlab工作空间，命名为xx。
			mxDestroyArray(xx);

			if (ret != 0)
			{
				return 9999;
			}
		}
		return H_MSG_TRUE;
	}
}

// int main()
//{
//
// }