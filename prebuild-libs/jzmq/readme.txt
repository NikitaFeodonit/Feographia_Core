
Building jzmq library with CrystaX NDK in Msys2 on Windows for Android
(this is similar on the other systems)


1. Build ZeroMQ library, see
<Feographia_Android>/fcore/prebuild-libs/zeromq/readme.txt


2. Get sources of jzmq library
(All variables are set by 1st step)

cd /local32
git clone https://github.com/zeromq/jzmq.git
cd jzmq


3. patch sources

cp <Feographia_Android>/fcore/prebuild-libs/jzmq/patch-all ./
patch -p1 <patch-all


4. Building

./autogen.sh

./configure --host=arm-linux-androideabi --enable-static --disable-shared --prefix=/local32/jzmq_inst --with-zeromq=$OUTPUT_DIR CPPFLAGS="-fPIC -I$OUTPUT_DIR/include" LDFLAGS="-L$OUTPUT_DIR/lib" --disable-version

make && make install


5. Copying to project

cp /local32/jzmq_inst/lib <Feographia_Android>/fcore/prebuild-libs/jzmq

# must be like so:
# <Feographia_Android>/fcore/prebuild-libs/jzmq
#     /lib
#     Android.mk
#     jzmq.pri
#     readme.txt


cp /local32/jzmq/src/main/java <Feographia_Android>/jzmq/src/main

# must be like so:
# <Feographia_Android>/jzmq/src/main
#     /java
#     res
#     AndroidManifest.xml
