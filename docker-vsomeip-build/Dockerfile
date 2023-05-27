FROM boost_build:v0 as build

LABEL description="Build vsomeip"

COPY vSomeIP vSomeIP

 RUN cd vSomeIP; \
     mkdir build; \
     cd build; \
     cmake .. ; \
     make; \
     make install;
