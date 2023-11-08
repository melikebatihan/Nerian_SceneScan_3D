# CMakeList.txt : CMake project for Scan3D, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.0.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (Scan3D)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_definitions ( -DVARNAME="${CMAKE_CURRENT_SOURCE_DIR}/ML_Models/")
set(OpenCV_DIR "$ENV{OpenCV_DIR}/lib")

# find_package(OpenCV REQUIRED PATH <location to OpenCV installation>)
find_package(OpenCV REQUIRED)
find_package(Open3D)

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
else()
    message(WARNING "Not building OpenCV example!")
endif()

if(Open3D_FOUND)
    include_directories(${Open3D_INCLUDE_DIRS})

    # Check Open3D C++ ABI
    get_property(def TARGET Open3D::Open3D PROPERTY INTERFACE_COMPILE_DEFINITIONS)
    if(def MATCHES "GLIBCXX_USE_CXX11_ABI=0")
        set(OPEN3D_CXX11_ABI 0)
    else()
        set(OPEN3D_CXX11_ABI 1)
    endif()

    # Check system C++ ABI
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles("\
        #include <string>\n\
        #if _GLIBCXX_USE_CXX11_ABI == 0\n\
        #error\n\
        #endif\n\
        int main(int, char**) {return 0;}"
        SYSTEM_CXX11_ABI)

    # Check if ABIs match
    set(OPEN3D_LIB_SUFFIX "")
    if(NOT MSVC)
        if(${SYSTEM_CXX11_ABI} AND (NOT ${OPEN3D_CXX11_ABI}))
            message(WARNING
                "Open3D was built with old C++ ABI (_GLIBCXX_USE_CXX11_ABI=0). "
                "A separate version of libvisiontransfer will be built for linking "
                "against Open3D. Using Open3D in combination with other libraries "
                "that are built with the more recent C++ ABI will not be possible.")
            set(BUILD_WITHOUT_CXX11_ABI 1)
            set(OPEN3D_LIB_SUFFIX "-without-cxx11-abi${LIB_SUFFIX}")
        endif()
    endif()
else()
    message(WARNING "Not building Open3D example!")
endif()

set(Visiontransfer_DIR "${CMAKE_SOURCE_DIR}/visiontransfer")
set(Visiontransfer_LIB "$ENV{Nerian_DIR}/lib64/Debug/visiontransfer-debug.lib")

include_directories(${Visiontransfer_DIR})
add_subdirectory(ML_Models)
add_subdirectory(Modules)

add_executable (Scan3D "Scan3D.cpp" "Scan3D.h")

target_link_libraries(Scan3D Modules)