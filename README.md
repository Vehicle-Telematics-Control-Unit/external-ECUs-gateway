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


## create network bridge
```
sudo docker network create --subnet=172.18.0.0/16 vsomeip_bridge
```

## how to run 
```
sudo docker run -it --net vsomeip_bridge --ip 172.18.0.3 -p 5001:5001/udp -v /tmp:/tmp:z udp_server_alpine
```