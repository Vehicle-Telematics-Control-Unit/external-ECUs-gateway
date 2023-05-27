FROM vsomeip_build:v0 as builder

COPY ../src src

RUN cd src; \
    mkdir build; \
    cd build; \
    cmake ..; \
    make