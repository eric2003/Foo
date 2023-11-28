cmake_minimum_required ( VERSION 3.28 )

project ( Foo )

add_library( foo STATIC )

target_sources( foo 
    PRIVATE 
      foo.cpp
)
