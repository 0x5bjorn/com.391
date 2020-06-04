
# Sets the following variables

# SDL2_LIBRARY, the name of the library to link against
# SDL2_FOUND, if false, do not try to link to SDL2
# SDL2_INCLUDE_DIR, where to find SDL.h



SET(SDL2_SEARCH_DIRS
	"/usr/include"
	"/usr"
	"/usr/local/include"
	"/opt"
	"/Library/Frameworks"
	"~/Library/Frameworks"
	)

# check environment variable
SET(_SDL2_ENV_ROOT_DIR "$ENV{SDL2_ROOT_DIR}")

# set SDL2 ROOT if needed
IF(NOT SDL2_ROOT_DIR AND _SDL2_ENV_ROOT_DIR)
    SET(SDL2_ROOT_DIR "${_SDL2_ENV_ROOT_DIR}")
ENDIF(NOT SDL2_ROOT_DIR AND _SDL2_ENV_ROOT_DIR)

IF(SDL2_ROOT_DIR)
    SET(_SDL2_HEADER_SEARCH_DIRS "${SDL2_ROOT_DIR}"
                                "${SDL2_ROOT_DIR}"
                                 ${SDL2_SEARCH_DIRS})
ENDIF(SDL2_ROOT_DIR)



FIND_PATH(SDL2_INCLUDE_DIR
		SDL.h
		include/SDL2 include
		PATHS ${SDL2_SEARCH_DIRS}
		DOC "SDL2 include directory"
)

FIND_LIBRARY(SDL2_LIBRARY
	NAMES	SDL2
	PATH_SUFFIXES lib lib64 lib/x86 lib/x64
	PATHS	${SDL2_SEARCH_DIRS}
	
	DOC "SDL2 library"
)


IF (SDL2_INCLUDE_DIR AND SDL2_LIBRARY )
	SET(SDL2_FOUND TRUE )
	MESSAGE(STATUS "SDL2_INCLUDE_DIR = ${SDL2_INCLUDE_DIR}")
ELSE ( SDL2_INCLUDE_DIR AND SDL2_LIBRARY )
	SET( SDL2_FOUND FALSE )
	MESSAGE(STATUS "SDL2 not found")
ENDIF ( SDL2_INCLUDE_DIR AND SDL2_LIBRARY )