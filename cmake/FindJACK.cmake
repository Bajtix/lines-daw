include(FeatureSummary)
set_package_properties(jack PROPERTIES
   URL "http://www.jackaudio.org/"
   DESCRIPTION "JACK Audio Connection Kit")

find_package(PkgConfig)
pkg_check_modules(PC_JACK QUIET JACK)
find_path(JACK_INCLUDE_DIRS NAMES jack/jack.h HINTS ${PC_JACK_INCLUDE_DIRS})
find_library(JACK_LIBRARIES NAMES jack HINTS ${PC_JACK_LIBRARY_DIRS})

set(JACK_DEFINITIONS ${PC_JACK_CFLAGS_OTHER})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JACK DEFAULT_MSG JACK_LIBRARIES JACK_INCLUDE_DIRS)
mark_as_advanced(JACK_LIBRARIES JACK_INCLUDE_DIRS JACK_DEFINITIONS)