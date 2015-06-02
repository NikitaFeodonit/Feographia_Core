
Building prebuilt libraries with CrystaX NDK in Msys2 on Windows for Android
(this is similar on the other systems)


1. Installing Android NDK Standalone Toolchain

# If you use C11 standard library features,
# you MUST specify using the gnustl C library (as opposed to STLport)
# or compilation will fail.

mount e:/Dev/Tools/Android/crystax-ndk-10.1.0 /local32/crystax-ndk-10.1.0
export ANDROID_NDK_ROOT=/local32/crystax-ndk-10.1.0

# if use window 7/8 64bit add additional options: --system=windowx86_64
$ANDROID_NDK_ROOT/build/tools/make-standalone-toolchain.sh --platform=android-9 --toolchain=arm-linux-androideabi-4.9 --stl=gnustl --system=windows-x86_64 --install-dir=$ANDROID_NDK_ROOT/standalone_toolchain/android-9/arm-linux-androideabi-4.9

export NDK_STANDALONE_TOOLCHAIN_ROOT=$ANDROID_NDK_ROOT/standalone_toolchain/android-9/arm-linux-androideabi-4.9
export PATH=$PATH:$NDK_STANDALONE_TOOLCHAIN_ROOT/bin:$NDK_STANDALONE_TOOLCHAIN_ROOT/arm-linux-androideabi/bin


2. For build prebuild-libs see <lib>/readme.txt
