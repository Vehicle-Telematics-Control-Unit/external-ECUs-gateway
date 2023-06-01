FROM vsomeip_build:v0 as builder

COPY src src

RUN cd src; \
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
COPY --from=builder /usr/lib/libboost_thread.so.1.58.0 /usr/lib
COPY --from=builder /usr/lib/libboost_system.so.1.58.0 /usr/lib
COPY --from=builder /usr/lib/libgcc_s.so.1 /usr/lib
COPY --from=builder /usr/lib/libboost_filesystem.so.1.58.0 /usr/lib
# COPY vsomeip.json /etc/vsomeip