# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/ProyectoLimpio;C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/ProyectoLimpio/cmake-build-debug")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
set(CPACK_DEBIAN_PACKAGE_DEBUG "OFF")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libasio-dev")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "CrowCpp")
set(CPACK_DEBIAN_PACKAGE_SECTION "libdevel")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "C:/Program Files/JetBrains/CLion 2023.2.2/bin/cmake/win/x64/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "ProyectoLimpio built using CMake")
set(CPACK_GENERATOR "7Z;ZIP")
set(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_INSTALLED_DIRECTORIES "C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/ProyectoLimpio;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/ProyectoLimpio")
set(CPACK_MODULE_PATH "C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/ProyectoLimpio/crow/cmake")
set(CPACK_NSIS_DISPLAY_NAME "Crow 0.1.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "Crow 0.1.1")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "C:/Program Files/JetBrains/CLion 2023.2.2/bin/mingw/bin/objcopy.exe")
set(CPACK_OBJDUMP_EXECUTABLE "C:/Program Files/JetBrains/CLion 2023.2.2/bin/mingw/bin/objdump.exe")
set(CPACK_OUTPUT_CONFIG_FILE "C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/ProyectoLimpio/cmake-build-debug/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION "A Fast and Easy to use C++ microframework for the web.")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files/JetBrains/CLion 2023.2.2/bin/cmake/win/x64/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ProyectoLimpio built using CMake")
set(CPACK_PACKAGE_FILE_NAME "Crow-0.1.1-Source")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://crowcpp.org")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Crow 0.1.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Crow 0.1.1")
set(CPACK_PACKAGE_NAME "Crow")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "CrowCpp")
set(CPACK_PACKAGE_VERSION "0.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_READELF_EXECUTABLE "C:/Program Files/JetBrains/CLion 2023.2.2/bin/mingw/bin/readelf.exe")
set(CPACK_RESOURCE_FILE_LICENSE "C:/Program Files/JetBrains/CLion 2023.2.2/bin/cmake/win/x64/share/cmake-3.26/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "C:/Program Files/JetBrains/CLion 2023.2.2/bin/cmake/win/x64/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files/JetBrains/CLion 2023.2.2/bin/cmake/win/x64/share/cmake-3.26/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/ProyectoLimpio;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/ProyectoLimpio/cmake-build-debug/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "Crow-0.1.1-Source")
set(CPACK_SOURCE_TOPLEVEL_TAG "win64-Source")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win64-Source")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/ProyectoLimpio/cmake-build-debug/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
