@0xddd08a9a8cb53659;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("FCoreMessages");

using Java = import "/capnp/java.capnp";
$Java.package("ru.feographia.capnproto");
$Java.outerClassname("FCoreMessages");


struct LoadFileReq {
  path @0 :Text;
}
