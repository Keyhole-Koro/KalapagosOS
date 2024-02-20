FROM ubuntu:latest

WORKDIR /app

# Install required packages
RUN apt-get update && \
    apt-get install -y \
    sudo \
    build-essential \
    qemu-system-x86 \
    nasm \
    make \
    isal \
    uuid-dev \
    git