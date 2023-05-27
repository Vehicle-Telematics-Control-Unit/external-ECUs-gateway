FROM boost_build:v0 as build

LABEL description="Build vsomeip"

COPY vsomeip vsomeip

RUN cd vsomeip; \
     mkdir build; \
     cd build; \
     cmake .. ; \
     make; \
     make install;
