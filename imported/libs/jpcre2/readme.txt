
Preparing jpcre2 library with CrystaX NDK in Msys2 on Windows for Android
(this is similar on the other systems)


1. Get sources
git clone https://github.com/jpcre2/jpcre2.git


2. Copying to project

cp jpcre2/src/<list> <Feographia_Android>/fcore/imported/libs/jpcre2/src

<list>:

jpcre2.h
jpcre2.cpp
jpcre2_match.cpp
jpcre2_replace.cpp


# must be like so:
# <Feographia_Android>/fcore/imported/libs/jpcre2/src
#     jpcre2.h
#     jpcre2.cpp
#     jpcre2_match.cpp
#     jpcre2_replace.cpp
