cmake_minimum_required(VERSION 3.16)

set(KF_VERSION "6.18.0") # handled by release scripts
set(KF_DEP_VERSION "6.17.0") # handled by release scripts
project(KBookmarks VERSION ${KF_VERSION})

include(FeatureSummary)
find_package(ECM 6.17.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://commits.kde.org/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)


set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(KDEGitCommitHooks)
include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)

include(ECMGenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMGenerateQDoc)

include(ECMPoQmTools)

set(EXCLUDE_DEPRECATED_BEFORE_AND_AT 0 CACHE STRING "Control the range of deprecated API excluded from the build [default=0].")

set(kbookmarks_version_header "${CMAKE_CURRENT_BINARY_DIR}/src/kbookmarks_version.h")
ecm_setup_version(PROJECT
                  VARIABLE_PREFIX KBOOKMARKS
                  VERSION_HEADER "${kbookmarks_version_header}"
                  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6BookmarksConfigVersion.cmake"
                  SOVERSION 6)

# Dependencies
set(REQUIRED_QT_VERSION 6.7.0)

find_package(Qt6 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Widgets Xml)

find_package(KF6Config ${KF_DEP_VERSION} REQUIRED)
find_package(KF6CoreAddons ${KF_DEP_VERSION} REQUIRED)
find_package(KF6WidgetsAddons ${KF_DEP_VERSION} REQUIRED)

ecm_install_po_files_as_qm(poqm)
ecm_set_disabled_deprecation_versions(
    QT 6.10.0
    KF 6.16.0
)


add_subdirectory(src)
if (BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6Bookmarks")

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF6BookmarksConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF6BookmarksConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF6BookmarksConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF6BookmarksConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF6BookmarksTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF6BookmarksTargets.cmake NAMESPACE KF6:: )

install(FILES
   ${kbookmarks_version_header}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KBookmarks COMPONENT Devel
)

include(ECMFeatureSummary)
ecm_feature_summary(WHAT ALL   FATAL_ON_MISSING_REQUIRED_PACKAGES)

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
