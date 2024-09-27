# docpp CMakeLists.txt
cmake_minimum_required(VERSION 3.1...3.29)

project(docpp VERSION 0.1.0
    DESCRIPTION "C++ library for generating XML, HTML and CSS."
    HOMEPAGE_URL "https://speedie.site/docpp"
    LANGUAGES CXX
)

add_compile_definitions(DOCPP_VERSION="${PROJECT_VERSION}")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

if (APPLE)
    set(INSTALL_RPATH_USE_LINK_PATH ON)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} SHARED
        include/docpp/except.hpp
        include/docpp/types.hpp
        include/docpp/version.hpp
        include/docpp/CSS/CSS.hpp
        include/docpp/CSS/element.hpp
        include/docpp/CSS/formatting_enum.hpp
        include/docpp/CSS/property.hpp
        include/docpp/CSS/stylesheet.hpp
        include/docpp/HTML/document.hpp
        include/docpp/HTML/element.hpp
        include/docpp/HTML/formatting_enum.hpp
        include/docpp/HTML/HTML.hpp
        include/docpp/HTML/properties.hpp
        include/docpp/HTML/property.hpp
        include/docpp/HTML/section.hpp
        include/docpp/HTML/tag.hpp
        include/docpp/HTML/type_enum.hpp
        src/CSS/element.cpp
        src/CSS/property.cpp
        src/CSS/stylesheet.cpp
        src/HTML/document.cpp
        src/HTML/element.cpp
        src/HTML/properties.cpp
        src/HTML/property.cpp
        src/HTML/section.cpp
        src/HTML/tag.cpp)

target_sources(${PROJECT_NAME} PRIVATE
    "src/version.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")
include_directories(include)

set(PUBLIC_HEADERS
        include/docpp/CSS/CSS.hpp
        include/docpp/CSS/element.hpp
        include/docpp/CSS/formatting_enum.hpp
        include/docpp/CSS/property.hpp
        include/docpp/CSS/stylesheet.hpp
        include/docpp/HTML/document.hpp
        include/docpp/HTML/element.hpp
        include/docpp/HTML/formatting_enum.hpp
        include/docpp/HTML/HTML.hpp
        include/docpp/HTML/properties.hpp
        include/docpp/HTML/property.hpp
        include/docpp/HTML/section.hpp
        include/docpp/HTML/tag.hpp
        include/docpp/HTML/type_enum.hpp
        include/docpp/docpp.hpp
        include/docpp/except.hpp
        include/docpp/types.hpp
        include/docpp/version.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "${PUBLIC_HEADERS}"
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

    add_custom_command(
         TARGET ${PROJECT_NAME}_test
         COMMENT "Run tests"
         POST_BUILD
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
         COMMAND ${PROJECT_NAME}_test
    )
endif()