FROM alpine:3.17.2 AS builder

RUN apk update && apk add --no-cache \
    binutils cmake curl gcc g++ git libtool make tar build-base linux-headers

RUN apk add --no-cache wget

RUN wget http://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.gz
RUN tar -xf boost_1_58_0.tar.gz
RUN cd boost_1_58_0/; \
    ./bootstrap.sh --prefix=/usr/; 

RUN cd boost_1_58_0/; ./b2 install; exit 0

COPY prog /prog
RUN cd prog; \
    mkdir build; \
    cd build; \
    cmake ..; \
    make

FROM alpine:3.17.2
COPY --from=builder /usr/lib/libboost_system.so.1.58.0 /usr/lib
COPY --from=builder /usr/lib/libstdc++.so.6 /usr/lib
COPY --from=builder /usr/lib/libgcc_s.so.1 /usr/lib
COPY --from=builder /prog/build/diagnostic /prog/build/
CMD ["/prog/build/diagnostic"]