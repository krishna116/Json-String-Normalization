add_executable(test01
test01.cpp
)

target_link_libraries(test01 PRIVATE
JsonSringNormalizationLib
)

add_executable(test02
test02.cpp
)

target_link_libraries(test02 PRIVATE
JsonSringNormalizationLib
)