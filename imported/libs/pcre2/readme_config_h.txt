
Make automatically configuring of config.h of pcre2 library with CrystaX NDK in Msys2 on Windows for Android
(this is similar on the other systems)


1. Installing Android NDK Standalone Toolchain and variables, see
<Feographia_Android>/fcore/imported/libs_prebuilt/readme.txt


2. Get sources
Download from: http://pcre.org/

tar xvjf pcre2-10.21.tar.bz2
cd /local32/pcre2-10.21

./configure --host=arm-linux-androideabi --disable-shared --prefix=/local32/pcre2-10.21_inst


3. Copying to project

cp /local32/pcre2-10.21/config.h <Feographia_Android>/fcore/imported/libs/pcre2/src
