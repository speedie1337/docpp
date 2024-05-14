# docpp CMakeLists.txt
cmake_minimum_required(VERSION 3.1...3.29)

project(docpp VERSION 0.0.1
    DESCRIPTION "C++ library for generating XML, HTML and CSS."
    HOMEPAGE_URL "https://speedie.site/docpp"
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
    "src/docpp.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    PUBLIC_HEADER "include/docpp.hpp"
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    FILE_SET HEADERS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/docpp
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE docpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(FILES "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

if (NOT WIN32 AND NOT APPLE)
    configure_file(${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}.pc.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY
    )

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()

    find_package(Catch2 3 REQUIRED)

    add_executable(${PROJECT_NAME}_test
        tests/test.cpp
    )

    target_include_directories(${PROJECT_NAME}_test PRIVATE
        "${PROJECT_SOURCE_DIR}"
    )

    target_link_libraries(${PROJECT_NAME}_test PRIVATE
        Catch2::Catch2WithMain
    )

    include(CTest)
    include(Catch)
    catch_discover_tests(${PROJECT_NAME}_test)

    add_custom_command(
         TARGET ${PROJECT_NAME}_test
         COMMENT "Run tests"
         POST_BUILD
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
         COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --rerun-failed -C
         $<CONFIGURATION> -R "^${PROJECT_NAME}_test$"
    )
endif()

if (NOT WIN32)
    if (EXISTS "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}.PKGBUILD.in" AND
            GENERATE_PKGBUILD)
        configure_file(${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}.PKGBUILD.in
            ${CMAKE_CURRENT_BINARY_DIR}/PKGBUILD @ONLY
        )
    endif()

    if (BUILD_TARBALL OR GENERATE_EBUILD)
        add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Create tarball"
            POST_BUILD
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMAND scripts/${PROJECT_NAME}_make dist && mv ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}.tar.gz* ${CMAKE_BINARY_DIR}
        )
    endif()

    if (EXISTS "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}.ebuild.in" AND
            GENERATE_EBUILD )
        configure_file(${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}.ebuild.in
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}.ebuild @ONLY
        )
        add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Copy ebuild and generate manifest"
            POST_BUILD
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND cp
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}.ebuild
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-9999.ebuild &&
            ${PROJECT_SOURCE_DIR}/scripts/generate_manifest
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}.tar.gz
            > ${CMAKE_CURRENT_BINARY_DIR}/Manifest
        )
    endif()
endif()
