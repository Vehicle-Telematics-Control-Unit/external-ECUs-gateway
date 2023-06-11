#!/bin/bash

echo "[INFO] building boost image"
cd docker-boost-build
sudo docker build -t boost_build:v0 .

cd ..

echo "[INFO] building vsomeip image"
cd docker-vsomeip-build
sudo docker build -t vsomeip_build:v0 .

cd ..

echo "[INFO] building server_udp_service image"
sudo docker build -t server_udp_service:v0 .

