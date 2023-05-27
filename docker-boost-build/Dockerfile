FROM alpine:3.17.2 AS builder

RUN apk update && apk add --no-cache \
    binutils cmake curl gcc g++ git libtool make tar build-base linux-headers

RUN apk add --no-cache wget

RUN wget http://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.gz
RUN tar -xf boost_1_58_0.tar.gz
RUN cd boost_1_58_0/; \
    ./bootstrap.sh --prefix=/usr/; 

RUN cd boost_1_58_0/; ./b2 install; exit 0