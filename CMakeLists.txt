cmake_minimum_required ( VERSION 3.28 )

project ( Foo )

add_library( Foo STATIC )

target_sources( Foo 
    PRIVATE 
      foo.cpp
)

install ( TARGETS Foo
         RUNTIME  DESTINATION bin
         LIBRARY  DESTINATION lib
         ARCHIVE  DESTINATION lib
)

install ( FILES foo.h DESTINATION include )