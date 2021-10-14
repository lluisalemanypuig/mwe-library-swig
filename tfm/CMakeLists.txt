cmake_minimum_required(VERSION 3.10.2)

# **********************************************************************

# PROJECT NAME AND VERSION

# project's version
set(TFM_MAJOR 99.99)
set(TFM_PATCH 99)

# project declaration
project(TFM VERSION "${TFM_MAJOR}.${TFM_PATCH}")
project(TFM DESCRIPTION "Test Library for MacOS")

# **********************************************************************

# needed includes to make CMake work
include(CheckCXXCompilerFlag)
# installation directories (platform dependent)
include(GNUInstallDirs)

# **********************************************************************
# Custom functions
function(add_comp_flag flag)
	check_cxx_compiler_flag(${flag} CXX_HAS_FLAG)
	if (CXX_HAS_FLAG)
		message(STATUS "    Adding flag ${flag}...")
		target_compile_options(${TargetStringLibrary} PRIVATE ${flag})
	else()
		message(STATUS "    ! Compiler does not support flag ${flag}.")
	endif()
endfunction(add_comp_flag)

function(add_debug_flag flag)
	check_cxx_compiler_flag(${flag} HAS_FLAG)
	if (HAS_FLAG)
		message(STATUS "    Adding flag ${flag}...")
		SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${flag}" PARENT_SCOPE)
	else()
		message(STATUS "    ! Compiler does not support flag ${flag}.")
	endif()
endfunction(add_debug_flag)

function(add_release_flag flag)
	check_cxx_compiler_flag(${flag} HAS_FLAG)
	if (HAS_FLAG)
		message(STATUS "    Adding flag ${flag}...")
		SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${flag}" PARENT_SCOPE)
	else()
		message(STATUS "    ! Compiler does not support flag ${flag}.")
	endif()
endfunction(add_release_flag)

# **********************************************************************
# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# **********************************************************************
# Set default build type
# (following the guide in https://blog.kitware.com/cmake-and-the-default-build-type/)

set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(
		CMAKE_BUILD_TYPE "${default_build_type}"
		CACHE STRING "Choose the type of build."
		FORCE
	)
	# Set the possible values of build type for cmake-gui
	set_property(
		CACHE CMAKE_BUILD_TYPE
		PROPERTY
			STRINGS "Debug" "Release"
	)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	message(STATUS "Target library tfmdebug")
	set(TargetStringLibrary "tfmdebug")
else()
	message(STATUS "Target library tfm")
	set(TargetStringLibrary "tfm")
endif()

# **********************************************************************
# **********************************************************************

# declare library
add_library(${TargetStringLibrary} SHARED "")

# define library's properties
set_target_properties(${TargetStringLibrary} PROPERTIES VERSION "${TFM_MAJOR}.${TFM_PATCH}")
set_target_properties(${TargetStringLibrary} PROPERTIES SOVERSION 1)
set_target_properties(${TargetStringLibrary} PROPERTIES LINKER_LANGUAGE CXX)

# **********************************************************************
# EXTERNAL LIBRARIES
# check if required external libraries are installed in the system

# ***
# GMP

find_library(GMP_LIB gmp)
if (GMP_LIB)
	message(STATUS "Found gmp: ${GMP_LIB}")
else()
	message(FATAL_ERROR "Error: gmp library not found")
endif()

message(STATUS "C   compiler is ${CMAKE_C_COMPILER}")
message(STATUS "C++ compiler is ${CMAKE_CXX_COMPILER}")

# ******
# OpenMP

if(APPLE)
	if(CMAKE_C_COMPILER_ID MATCHES "Clang")
		set(OpenMP_C "${CMAKE_C_COMPILER}")
		set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
		set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
		set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
		set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
		set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
	endif()
	if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
		set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
		set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
		set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
		set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
		set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
	endif()
endif()

find_package(OpenMP REQUIRED)

# **********************************************************************
# SOURCE FILES FOR COMPILATION

# source files of the library
target_sources(
	${TargetStringLibrary}
	PRIVATE
		ints.cpp
		strings.cpp
	
		# tfm namespace
		# -- heaers
		test_for_mac.hpp
)

# **********************************************************************
# PUBLIC HEADER FILES FOR INSTALLATION

# Public header files of the library (to be installed in the system).
# These are not installed through the usual PUBLIC_HEADER property,
# but via several custom variables
set(LIBTFM_MAIN_HEADER
	test_for_mac.hpp
)

# **********************************************************************
# INSTALLATION DIRECTORIES OF THE LIBRARY

message("-- TFM binaries will be installed in: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
message("-- TFM headers  will be installed in: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/tfm")

install(
	TARGETS ${TargetStringLibrary}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES ${LIBTFM_MAIN_HEADER}			DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tfm)

# **********************************************************************
# COMPILATION FLAGS

# Warning flags
message(STATUS "Adding warning flags")
add_comp_flag(-Wall)
add_comp_flag(-Wextra)
add_comp_flag(-Wshadow)
add_comp_flag(-Wnon-virtual-dtor)
add_comp_flag(-Wold-style-cast)
add_comp_flag(-Wcast-align)
add_comp_flag(-Wunused)
add_comp_flag(-Woverloaded-virtual)
add_comp_flag(-Wpedantic)
add_comp_flag(-Wconversion)
add_comp_flag(-Wsign-conversion)
add_comp_flag(-Wnull-dereference)
add_comp_flag(-Wdouble-promotion)
add_comp_flag(-Wformat=2)
add_comp_flag(-Wduplicated-cond)
add_comp_flag(-Wduplicated-branches)
add_comp_flag(-Wlogical-op)
add_comp_flag(-Wuseless-cast)
add_comp_flag(-Wrestrict)

# OpenMP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

# Optimisation flags
message(STATUS "Adding optimisation flags")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	add_debug_flag(-O3)
	add_debug_flag(-DDEBUG)
	add_debug_flag(-D_GLIBCXX_DEBUG)
else()
	# flags added by default:
	#   -O3
	#   -DNDEBUG
	add_release_flag(-UDEBUG)
endif()

# include path (required by the compiler to find the headers)
target_include_directories(${TargetStringLibrary} PRIVATE ..)

# **********************************************************************
# LINKAGE TO EXTERNAL LIBRARIES

if (APPLE)
	target_link_libraries(${TargetStringLibrary} gmp)
else()
	target_link_libraries(${TargetStringLibrary} gmp)
endif()
