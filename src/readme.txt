TODO: first run
cd ./fcore/capnproto
./capnp-main.cmd


For building in the QtCreator


Warning: to build the project uses the android-nkd/jni/Android.mk,
         the pro-file is for the QtCreator itself only


For building in the QtCreator make following for project configuration in QtCreator:


in Project -> Build Settings -> Add -> Build -> name "ndk-build"
Shadow build == true
Build dir (relative to the main project) == E:\Dev\projects\Android\Feographia_Android\fcore\android-nkd


Build Steps -- all delete and disable. Add build step -- Custom process step
Command: (relative to the Crystax NDK) E:\Dev\Tools\Android\crystax-ndk-10.2.1\ndk-build.cmd
Arguments:
Working dir: %{buildDir}


Clean steps -- all delete and disable. Add clean step -- Custom process step
Command: (relative to the Crystax NDK) E:\Dev\Tools\Android\crystax-ndk-10.2.1\ndk-build.cmd
Arguments: clean
Working dir: %{buildDir}
