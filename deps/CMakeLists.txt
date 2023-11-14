include(FetchContent)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG c6e0284ac58b3f205c95365478888f7b53b077e2
)
FetchContent_MakeAvailable(imgui)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 11b73743c42cf7ecd7c596ba83fdbf1150ffa96c
)

FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
  GIT_TAG de565ac8f2b795dedc0307b60830cb006afd2ecd
)
add_subdirectory(imgui-sfml)


