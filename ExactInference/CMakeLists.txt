cmake_minimum_required(VERSION 3.19)
project(ExactInference)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ExactInference
        CBNSumProduct.cpp
        CBNSumProduct.h
        CBNSumProduct_GetFactor.cpp
        CBNSumProduct_Init.cpp
        CBNSumProduct_OutputToXML.cpp
        CBNSumProduct_Preprocess.cpp
        CBNSumProduct_Preprocess_BN.cpp
        CBNSumProduct_Preprocess_Factor.cpp
        CBNSumProduct_Query.cpp
        CBNSumProduct_Query_Helper.cpp
        CBNSumProduct_Query_Marginal.cpp
        CBNSumProduct_Read_BN.cpp
        CBNSumProduct_Read_Query.cpp
        CBNSumProduct_SumPruductElimateVar.cpp
        CFactor.cpp
        CFactor.h
        CFactor_Init.cpp
        CFactor_Normalize.cpp
        CFactor_Operator.cpp
        CFactor_Query.cpp
        CFactor_ReduceGivenVariable.cpp
        CFactor_SumOutVariable.cpp
        ExactInference.cpp
        ExactInference.h
        ExactInferenceDlg.cpp
        ExactInferenceDlg.h
        ExactInferenceDlg_User.cpp
        Helper.cpp
        Helper.h
        resource.h
        stdafx.cpp
        stdafx.h
        targetver.h
        tinystr.cpp
        tinystr.h
        tinyxml.cpp
        tinyxml.h
        tinyxml2.cpp
        tinyxml2.h
        tinyxmlerror.cpp
        tinyxmlparser.cpp)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
set(CMAKE_MFC_FLAG 1)
find_package(MFC)
if(NOT MFC_FOUND)
    message(FATAL_ERROR "MFC is not found, please check MFC installation")
endif()
add_executable(MFCApplication1 WIN32 )
target_sources(MFCApplication1 PRIVATE
        xxx.cpp
        )
target_compile_definitions(MFCApplication1 PRIVATE
        -DWIN32
        -D_DEBUG
        -D_WINDOWS
        -D_UNICODE
        -DUNICODE
        -D_AFXDLL
        )
target_link_options(MFCApplication1 PRIVATE
        /ENTRY:wWinMainCRTStartup
        )