#!/bin/bash

cd docker-boost-build
sudo docker build -t boost_build:v0 .
cd ..

cd docker-vsomeip-build
sudo docker build -t vsomeip_build:v0 .
cd ..

sudo docker build -t server_udp_service:v0 .