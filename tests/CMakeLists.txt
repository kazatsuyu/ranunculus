function(ranunculus_add_test name)
    add_executable(${name}_test ${ARGN} test_main.cpp)
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}_test>)
endfunction()

include_directories(../submodules/iutest/include)

ranunculus_add_test(integer_sequence integer_sequence_test.cpp)
ranunculus_add_test(type_sequence type_sequence_test.cpp)
ranunculus_add_test(bitcount bitcount_test.cpp)
ranunculus_add_test(operators operators_test.cpp)
ranunculus_add_test(array_view array_view_test.cpp)
