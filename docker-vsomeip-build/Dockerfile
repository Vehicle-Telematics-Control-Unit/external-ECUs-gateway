FROM boost_build:v0 as build

LABEL description="Build vsomeip"

COPY vsomeip vsomeip

RUN cd vsomeip; \
     rm -rf build; \
     mkdir build; \
     cd build; \
     cmake .. ; \
     make -j $(echo $(nproc --all) | grep -o '[0-9]*');\
     make install;
