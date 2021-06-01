### CMake file for cyan 
###
###     Author : glaconbleu@codices.org
###
###############################################################################

cmake_minimum_required (VERSION 2.6)

project (cyan)
set (cyan_VERSION_MAJOR 0)
set (cyan_VERSION_MINOR 1)
set (cyan_VERSION_PATCH 1)
set (cyan_VERSION
	${cyan_VERSION_MAJOR}.${cyan_VERSION_MINOR}.${cyan_VERSION_PATCH} )

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )
set ( INSTALL_DATASETS_PATH "${CMAKE_INSTALL_PREFIX}/share/cyan/datasets" )

### Options ###

option(ENABLE_GETTEXT "Use the gettext library for int18n" ON)
option(BUILD_TOOLS  "Build and install cyan tools" ON)
option(BUILD_TEST   "Build cyan tests" ON)
option(INSTALL_DATASETS  "Install Datasets" ON)
option(CFG_VERBOSE_ERRORS   "Error output on stderr" ON)

### Cyan options processing

if (CFG_VERBOSE_ERRORS)
    set ( CYAN_CFG_VERBOSE_ERRORS 1)
else()
    set ( CYAN_CFG_VERBOSE_ERRORS 0)
endif()

### LIBS

find_package(libzip REQUIRED)

### Search for gettext

if (ENABLE_GETTEXT)
    find_package(Gettext)
    if (GETTEXT_FOUND)
        set ( HAVE_GETTEXT 1)
    else()
        set ( HAVE_GETTEXT 0)
        message( FATAL_ERROR "Cannot find gettext lib.")
    endif()
else()
    message("Not using gettext. Messages will be displayed in english only")
    set ( HAVE_GETTEXT 0 )
endif()

### Config File

configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in"
		         "${PROJECT_SOURCE_DIR}/include/cyan/common/config.h" )

### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	                 "${CMAKE_CURRENT_BINARY_DIR}" 
                      )

### File lists

file( GLOB src  "src/*.c"  
                "src/3dmodel/*.c"
                "src/color/*.c"
                "src/common/*.c" 
                "src/image/*.c"
                "src/file/*.c" 
                "src/utils/*.c" )

file( GLOB hdr         "include/cyan/*.h"  )
file( GLOB hdr_image   "include/cyan/image/*.h"  )
file( GLOB hdr_color   "include/cyan/color/*.h"  )
file( GLOB hdr_vision  "include/cyan/vision/*.h"  )
file( GLOB hdr_3dmodel "include/cyan/3dmodel/*.h"  )
file( GLOB hdr_common  "include/cyan/common/*.h"  )
file( GLOB hdr_utils   "include/cyan/utils/*.h"  )

### Targets

add_library( "cyan" SHARED ${src} ) 

set_target_properties(cyan PROPERTIES VERSION ${cyan_VERSION}
                                    SOVERSION ${cyan_VERSION_MAJOR})

### Linking

target_link_libraries( "cyan" "m" )
if (LIBNETPBM_FOUND)
    target_link_libraries( "cyan" ${LIBTIRPC_LIBRARY} )
endif()

target_link_libraries("cyan" libzip::zip )

### Cmake file

configure_file(cyanConfig.cmake.in "${PROJECT_BINARY_DIR}/cyanConfig.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/cyanConfig.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/cmake/cyan" COMPONENT dev )  

### Install 

install( TARGETS "cyan"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
        ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )

install( FILES ${hdr}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/${name} 
        COMPONENT main )

install( FILES ${hdr_image}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/image/${name}
	    COMPONENT main )

install( FILES ${hdr_color}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/color/${name}
	    COMPONENT main )

install( FILES ${hdr_vision}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/vision/${name}
	    COMPONENT main )

install( FILES ${hdr_3dmodel}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/3dmodel/${name}
	    COMPONENT main )

install( FILES ${hdr_common}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/common/${name}
	    COMPONENT main )

install( FILES ${hdr_utils}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/utils/${name}
	    COMPONENT main )

# Datasets

if (INSTALL_DATASETS)
    add_subdirectory(datasets)
endif()

# Build Tools

if (BUILD_TOOLS)
    add_subdirectory(tools)
endif()

# Regression tests

if (BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

# Int18n

if (ENABLE_GETTEXT)
    add_subdirectory(po)
endif()


# Cpack specifics

set (CPACK_PACKAGE_CONTACT "seb@homedruon.com")
include(CPack)

### Pretty Display :

MESSAGE(STATUS "*********************************************************")
MESSAGE(STATUS "")
MESSAGE(STATUS "Build type:        " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "")
MESSAGE(STATUS "ENABLE_GETTTEXT:   " ${ENABLE_GETTEXT})
MESSAGE(STATUS "BUILD_TOOLS:       " ${BUILD_TOOLS})
MESSAGE(STATUS "BUILD_TEST:        " ${BUILD_TEST})
MESSAGE(STATUS "INSTALL_DATASETS:  " ${INSTALL_DATASETS})
MESSAGE(STATUS "")
MESSAGE(STATUS "CYAN_CFG_VERBOSE_ERRORS:        " ${CFG_VERBOSE_ERRORS})
MESSAGE(STATUS "")
MESSAGE(STATUS "*********************************************************")
