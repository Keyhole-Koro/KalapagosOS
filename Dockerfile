FROM ubuntu:latest

WORKDIR /app

# Update package lists and install required packages
RUN apt-get update && \
    apt-get install -y \
    sudo \
    build-essential \
    qemu-system-x86 \
    nasm \
    make \
    isal \
    uuid-dev \
    git \
    wget \
    gnupg \
    clang-format \
    clang \
    lld \
    cppcheck

# Add additional commands if needed

# Define target stage if you are doing a multi-stage build
# Example:
# FROM base_image as stage_name
# COPY --from=previous_stage /path/to/copy/from /path/to/copy/to
