# Use Ubuntu as base image
FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages for C++ development
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    gdb \
    cmake \
    clang \
    llvm \
    qemu-system-x86 \
    nasm \
    make \
    isal \
    uuid-dev \
    git \
    clang \
    lld \
    && rm -rf /var/lib/apt/lists/*

# Set the default shell to bash
SHELL ["/bin/bash", "-c"]

# Set the working directory
WORKDIR /workspace