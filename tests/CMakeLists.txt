add_executable(integer_sequence_test
               integer_sequence_test.cpp)
add_executable(type_sequence_test
               type_sequence_test.cpp)
add_test(NAME integer_sequence
         COMMAND $<TARGET_FILE:integer_sequence_test>)
add_test(NAME type_sequence
         COMMAND $<TARGET_FILE:type_sequence_test>)


