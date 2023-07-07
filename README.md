# UDP-Server-Service



## build with
```bash
$ docker buildx build --push \
--platform linux/amd64,linux/arm64 \
--tag registry.digitalocean.com/vehicle-plus/tcu_ecu-ethernet-gateway:v0 .
```
## how to run 
```
$ docker run --name ecus_ethernet_gateway -it --rm --privileged --net host -v /tmp:/tmp:z registry.digitalocean.com/vehicle-plus/tcu_ecu-ethernet-gateway:v0
```

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


