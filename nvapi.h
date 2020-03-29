/*
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004
 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
  0. You just DO WHAT THE FUCK YOU WANT TO.
*/
#pragma once

#include <windows.h>

typedef unsigned long NvU32;

typedef struct {
    NvU32   version;
    NvU32   ClockType:2;
    NvU32   reserved:22;
    NvU32   reserved1:8;
    struct {
        NvU32   bIsPresent:1;
        NvU32   reserved:31;
        NvU32   frequency;
    }domain[32];
} NV_GPU_CLOCK_FREQUENCIES_V2;

typedef struct {
    int value;
    struct {
        int   mindelta;
        int   maxdelta;
    } valueRange;
} NV_GPU_PERF_PSTATES20_PARAM_DELTA;

typedef struct {
    NvU32   domainId;
    NvU32   typeId;
    NvU32   bIsEditable:1;
    NvU32   reserved:31;
    NV_GPU_PERF_PSTATES20_PARAM_DELTA   freqDelta_kHz;
    union {
        struct {
            NvU32   freq_kHz;
        } single;
        struct {
            NvU32   minFreq_kHz;
            NvU32   maxFreq_kHz;
            NvU32   domainId;
            NvU32   minVoltage_uV;
            NvU32   maxVoltage_uV;
        } range;
    } data;
} NV_GPU_PSTATE20_CLOCK_ENTRY_V1;

typedef struct {
    NvU32   domainId;
    NvU32   bIsEditable:1;
    NvU32   reserved:31;
    NvU32   volt_uV;
    int     voltDelta_uV;
} NV_GPU_PSTATE20_BASE_VOLTAGE_ENTRY_V1;

typedef struct {
    NvU32   version;
    NvU32   bIsEditable:1;
    NvU32   reserved:31;
    NvU32   numPstates;
    NvU32   numClocks;
    NvU32   numBaseVoltages;
    struct {
        NvU32                                   pstateId;
        NvU32                                   bIsEditable:1;
        NvU32                                   reserved:31;
        NV_GPU_PSTATE20_CLOCK_ENTRY_V1          clocks[8];
        NV_GPU_PSTATE20_BASE_VOLTAGE_ENTRY_V1   baseVoltages[4];
    } pstates[16];
} NV_GPU_PERF_PSTATES20_INFO_V1;

typedef void *(*NvAPI_QueryInterface_t)(unsigned int offset);
typedef int (*NvAPI_Initialize_t)(void);
typedef int (*NvAPI_Unload_t)(void);
typedef int (*NvAPI_EnumPhysicalGPUs_t)(int **handles, int *count);
typedef int (*NvAPI_GPU_GetSystemType_t)(int *handle, int *systype);
typedef int (*NvAPI_GPU_GetFullName_t)(int *handle, char *sysname);
typedef int (*NvAPI_GPU_GetPhysicalFrameBufferSize_t)(int *handle, int *memsize);
typedef int (*NvAPI_GPU_GetRamType_t)(int *handle, int *memtype);
typedef int (*NvAPI_GPU_GetVbiosVersionString_t)(int *handle, char *biosname);
typedef int (*NvAPI_GPU_GetAllClockFrequencies_t)(int *handle, NV_GPU_CLOCK_FREQUENCIES_V2 *pstates_info);
typedef int (*NvAPI_GPU_GetPstates20_t)(int *handle, NV_GPU_PERF_PSTATES20_INFO_V1 *pstates_info);
typedef int (*NvAPI_GPU_SetPstates20_t)(int *handle, NV_GPU_PERF_PSTATES20_INFO_V1 *pstates_info);

void *NvQueryInterface_trampoline(unsigned int offset);
int NvInit_trampoline(void);
int NvUnload_trampoline(void);
int NvEnumGPUs_trampoline(int **handles, int *count);
int NvGetSysType_trampoline(int *handle, int *systype);
int NvGetName_trampoline(int *handle, char *sysname);
int NvGetMemSize_trampoline(int *handle, int *memsize);
int NvGetMemType_trampoline(int *handle, int *memtype);
int NvGetBiosName_trampoline(int *handle, char *biosname);
int NvGetFreq_trampoline(int *handle, NV_GPU_CLOCK_FREQUENCIES_V2 *clock_info);
int NvGetPstates_trampoline(int *handle, NV_GPU_PERF_PSTATES20_INFO_V1 *pstates_info);
int NvSetPstates_trampoline(int *handle, NV_GPU_PERF_PSTATES20_INFO_V1 *pstates_info);

extern NvAPI_QueryInterface_t NvQueryInterface;
extern NvAPI_Initialize_t NvInit;
extern NvAPI_Unload_t NvUnload;
extern NvAPI_EnumPhysicalGPUs_t NvEnumGPUs;
extern NvAPI_GPU_GetSystemType_t NvGetSysType;
extern NvAPI_GPU_GetFullName_t NvGetName;
extern NvAPI_GPU_GetPhysicalFrameBufferSize_t NvGetMemSize;
extern NvAPI_GPU_GetRamType_t NvGetMemType;
extern NvAPI_GPU_GetVbiosVersionString_t NvGetBiosName;
extern NvAPI_GPU_GetAllClockFrequencies_t NvGetFreq;
extern NvAPI_GPU_GetPstates20_t NvGetPstates;
extern NvAPI_GPU_SetPstates20_t NvSetPstates;