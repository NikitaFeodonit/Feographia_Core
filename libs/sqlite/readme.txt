
Preparing sqlite library with CrystaX NDK in Msys2 on Windows for Android
(this is similar on the other systems)


1. Get sources
https://www.sqlite.org/download.html
Download "C source code as an amalgamation, version 3.x.xx.x".


2. Copying to project

cp sqlite-amalgamation-3xxxxxx.zip/sqlite-amalgamation-3081101/* <Feographia_Android>/fcore/libs/sqlite/src

# must be like so:
# <Feographia_Android>/fcore/libs/sqlite/src
#     .gitignore
#     shell.c
#     sqlite3.c
#     sqlite3.h
#     sqlite3ext.h
