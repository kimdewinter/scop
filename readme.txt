To remove Linux elements:
- in Makefile, remove src file "glad" from SRC_FILES
- in Makefile, remove header file "glad" and "khrplatform" from HDR_FILES
- in Makefile, add "-framework OpenGL" to LDFLAGS