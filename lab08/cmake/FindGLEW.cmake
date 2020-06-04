# Sets the following variables

# GLEW_INCLUDE_DIRS - include directories for GLEW
# GLEW_LIBRARIES - libraries to link against GLEW
# GLEW_FOUND - true if GLEW has been found and can be used

SET(GLEW_FOUND "NO")

# default search dirs
SET(_glew_SEARCH_DIRS
	"./libs/glew"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glew"
    "/usr/include"
	"/usr"
	"/usr/local/include"
	"/opt"
	"/Library/Frameworks"
	"~/Library/Frameworks"
    )

# check environment variable
SET(_glew_ENV_ROOT_DIR "$ENV{GLEW_ROOT_DIR}")

# set GLEW ROOT if needed
IF(NOT GLEW_ROOT_DIR AND _glew_ENV_ROOT_DIR)
    SET(GLEW_ROOT_DIR "${_glew_ENV_ROOT_DIR}")
ENDIF(NOT GLEW_ROOT_DIR AND _glew_ENV_ROOT_DIR)

IF(GLEW_ROOT_DIR)
    SET(_glew_SEARCH_DIRS "${GLEW_ROOT_DIR}"
                                "${GLEW_ROOT_DIR}"
                                 ${_glew_SEARCH_DIRS})
ENDIF(GLEW_ROOT_DIR)


FIND_PATH(GLEW_INCLUDE_DIRS
		GL/glew.h glew.h 
		${_glew_SEARCH_DIRS}/include
		DOC "GLEW include directory"
)

FIND_LIBRARY(GLEW_LIBRARIES
	NAMES	glew GLEW glew32 glew32s
	PATHS	${_glew_SEARCH_DIRS}
	PATH_SUFFIXES
		lib
		lib64
		lib/x86
		lib/x64
	DOC "GLEW library"
)

IF (GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
	SET(GLEW_FOUND TRUE )
	MESSAGE(STATUS "GLEW_INCLUDE_DIRS = ${GLEW_INCLUDE_DIRS}")
ELSE ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
	SET( GLEW_FOUND FALSE )
	MESSAGE(STATUS "GLEW not found")
ENDIF ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )