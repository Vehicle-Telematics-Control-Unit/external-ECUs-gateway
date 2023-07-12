# if you dont access use this 
# FROM vsomeip_build:v0 as builder
FROM registry.digitalocean.com/vehicle-plus/tcu_builder_packs:v8 as builder


RUN apk update && apk add --no-cache --virtual .second_build_dependency \
    binutils cmake curl gcc g++ git libtool make tar build-base linux-headers


COPY src src

RUN cd src; \
    rm -rf build; \
    mkdir build; \
    cd build; \
    cmake ..; \
    make

FROM alpine:3.17.2
COPY --from=builder /src/build /src/build
COPY --from=builder /usr/local/lib/libvsomeip3.so.3 /usr/local/lib
COPY --from=builder /usr/local/lib/libvsomeip3-cfg.so.3 /usr/local/lib
COPY --from=builder /usr/local/lib/libvsomeip3-sd.so.3 /usr/local/lib
COPY --from=builder /usr/lib/libstdc++.so.6 /usr/lib
COPY --from=builder /usr/lib/libboost_thread.so.1.63.0 /usr/lib
COPY --from=builder /usr/lib/libboost_system.so.1.63.0 /usr/lib
COPY --from=builder /usr/lib/libgcc_s.so.1 /usr/lib
COPY --from=builder /usr/lib/libboost_filesystem.so.1.63.0 /usr/lib

WORKDIR /src/build
ENTRYPOINT [ "./server_udp" ]

# COPY vsomeip.json /etc/vsomeip