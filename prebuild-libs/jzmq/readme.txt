
Building jzmq library with CrystaX NDK in Msys2 on Windows
(this is similar on the other systems)


1. Build ZeroMQ library, see
<Feographia_Android>/fcore/prebuild-libs/zeromq/readme.txt


2. Build jzmq library
(All variables are set by 1st step)

cd /local32
git clone https://github.com/zeromq/jzmq.git
cd jzmq

# patch sources, C++ and Java

./autogen.sh

# patch Makefiles

./configure --host=arm-linux-androideabi --enable-static --disable-shared --prefix=/local32/jzmq_inst --with-zeromq=$OUTPUT_DIR CPPFLAGS="-fPIC -I$OUTPUT_DIR/include" LDFLAGS="-L$OUTPUT_DIR/lib" --disable-version

make -j8 && make install


# As a last word, if the generated binary us too huge (between 2.3 and 2.7 Mb) a good move is to strio/optimize it.
# To be straightforward, that means at least running

arm-linux-androideabi-strip --strip-all libjzmq.so

# which reduces the binary size to about 600Kb,
# but you can also gain a few more Kb if using
# -ffunction-sections -fdata-sections -Wl,—gc-sections
# as additionnal CPPFLAGS.


3. Copying to project

cp /local32/jzmq_inst/lib <Feographia_Android>/fcore/prebuild-libs/jzmq

must be so:

prebuild-libs/jzmq
    /lib
    Android.mk
    jzmq.pri
    readme.txt


cp /local32/jzmq/src/main/java <Feographia_Android>/jzmq/src/main
