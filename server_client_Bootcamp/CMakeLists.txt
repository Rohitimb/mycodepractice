ADD_EXECUTABLE(BootcampServer
  BootcampServerDaemon.cpp
  BootcampServer.cpp
  ${PROTO_CC_DEST}/BootcampDeviceInfo.pb.cc
  ${PROTO_CC_DEST}/BootcampMessageIds.pb.cc
  ${PROTO_CC_DEST}/BootcampMisc.pb.cc
  ${PROTO_CC_DEST}/BootcampServiceInfo.pb.cc
  ${PROTO_CC_DEST}/BootcampVersion.pb.cc
)
INSTALL(TARGETS BootcampServer DESTINATION ${OUTPUT_BIN_DIR})

ADD_EXECUTABLE(BootcampClient
  BootcampClientDaemon.cpp
  BootcampClient.cpp
  ${PROTO_CC_DEST}/BootcampDeviceInfo.pb.cc
  ${PROTO_CC_DEST}/BootcampMessageIds.pb.cc
  ${PROTO_CC_DEST}/BootcampMisc.pb.cc
  ${PROTO_CC_DEST}/BootcampServiceInfo.pb.cc
  ${PROTO_CC_DEST}/BootcampVersion.pb.cc
)
INSTALL(TARGETS BootcampClient DESTINATION ${OUTPUT_BIN_DIR})
