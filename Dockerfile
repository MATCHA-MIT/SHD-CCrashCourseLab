FROM ubuntu:22.04

RUN apt update &&  apt install -y build-essential libfmt-dev vim libasan8 libubsan1 valgrind python3 gdb curl
RUN bash -c "$(curl -fsSL https://gef.blah.cat/sh)"
