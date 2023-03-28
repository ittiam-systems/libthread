function(defineInterfaces)
  add_library("${projName}CompileOptions" INTERFACE)

  if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    target_compile_options(
      "${projName}CompileOptions"
      INTERFACE /INCREMENTAL:NO
                /Oi
                /GL
                /Os
                /MP
                /W4
                /WX)
    # WIN32_LEAN_AND_MEAN and _CRT_HAS_CXX17 defined to constrain features
    # imported from windows.h
    target_compile_definitions(
      "${projName}CompileOptions" INTERFACE WINDOWS WIN32_LEAN_AND_MEAN
                                            _CRT_HAS_CXX17=0)
  else()
    target_compile_options(
      "${projName}CompileOptions" INTERFACE -Wall -Wextra -Wpedantic
                                            -Wconversion -Werror)

    if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
      target_compile_definitions("${projName}CompileOptions" INTERFACE MACOS)
    else()
      target_compile_definitions("${projName}CompileOptions" INTERFACE LINUX)
    endif()

    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64")
      target_compile_options("${projName}CompileOptions"
                             INTERFACE -march=armv8-a)
    else()
      target_compile_options("${projName}CompileOptions"
                             INTERFACE -march=native)
    endif()
  endif()
endfunction()
