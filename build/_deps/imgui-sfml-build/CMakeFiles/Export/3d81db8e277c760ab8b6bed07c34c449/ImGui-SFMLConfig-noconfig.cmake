#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ImGui-SFML::ImGui-SFML" for configuration ""
set_property(TARGET ImGui-SFML::ImGui-SFML APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ImGui-SFML::ImGui-SFML PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib64/libImGui-SFML.a"
  )

list(APPEND _cmake_import_check_targets ImGui-SFML::ImGui-SFML )
list(APPEND _cmake_import_check_files_for_ImGui-SFML::ImGui-SFML "${_IMPORT_PREFIX}/lib64/libImGui-SFML.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
