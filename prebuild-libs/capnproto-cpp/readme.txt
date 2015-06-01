
Building capnproto library with CrystaX NDK in Msys2 on Windows
(this is similar on the other systems)


1. Installing Android NDK Standalone Toolchain, see
<Feographia_Android>/fcore/prebuild-libs/readme.txt


2. Build capnproto library

# unzip capnproto-c++-win32-0.5.2.zip
cp capnproto-tools-win32-0.5.2/capnp.exe /usr/bin

# untar capnproto-c++-0.5.2.tar.gz
cd /local32/capnproto-c++-0.5.2

./configure --host=arm-linux-androideabi --enable-static --disable-shared --prefix=/local32/capnproto-c++-0.5.2_inst --with-external-capnp

make -j8 && make install


3. Copying to project

cp /local32/capnproto-c++-0.5.2_inst/include <Feographia_Android>/fcore/prebuild-libs/capnproto-cpp
cp /local32/capnproto-c++-0.5.2_inst/lib <Feographia_Android>/fcore/prebuild-libs/capnproto-cpp

must be so:

prebuild-libs/capnproto-cpp
    /include
    /lib
    Android.mk
    capnproto-cpp.pri
    readme.txt
