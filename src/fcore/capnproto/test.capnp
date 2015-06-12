@0xaa83ce2a56454c96;

using Java = import "/capnp/java.capnp";
$Java.package("ru.feographia.capnproto");
$Java.outerClassname("Test");

struct Request {
  id @0 :UInt32;
  name @1 :Text;
}

struct Reply {
  idReply @0 :UInt32;
  nameReply @1 :Text;
}
