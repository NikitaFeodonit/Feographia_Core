
Preparing sqlite library with CrystaX NDK in Msys2 on Windows for Android
(this is similar on the other systems)


1. Get sources
git clone https://github.com/SRombauts/SQLiteCpp.git


2. Copying to project

cp SQLiteCpp/src/*.cpp <Feographia_Android>/fcore/libs/SQLiteCpp/src
cp SQLiteCpp/include <Feographia_Android>/fcore/libs/SQLiteCpp/src

# must be like so:
# <Feographia_Android>/fcore/libs/sqlite/src
#     /include/SQLiteCpp
#         Assertion.h
#         Column.h
#         Database.h
#         Exception.h
#         SQLiteCpp.h
#         Statement.h
#         Transaction.h
#     .gitignore
#     Column.cpp
#     Database.cpp
#     Statement.cpp
#     Transaction.cpp
