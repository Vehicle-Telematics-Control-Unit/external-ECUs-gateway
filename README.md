# UDP-Server-Service


## build boost

```
cd UDP_Server_Service/docker-boost-build
docker build -t boost_build:v0 .
```

## build vsomeip

```
cd UDP_Server_Service/docker-vsomeip-build
docker build -t vsomeip_build:v0 .
```



## how to run 
```
docker run --name ECUs_gateway -it --network host -v /tmp:/tmp:z udp_server_alpine
```