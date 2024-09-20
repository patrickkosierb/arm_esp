FROM ubuntu:22.04

WORKDIR /workspace
ENV DEBIAN_FRONTEND=noninteractive

# dependancies
RUN apt-get update -qq && \
    apt-get install -y -qq software-properties-common && \
    apt-add-repository universe && \
    apt-get update -qq && \
    apt-get install -qq -y --no-install-recommends \
    bc \
    bison \
    build-essential \
    curl \
    flex \
    gcc \
    git \
    gperf \
    jq \
    libncurses-dev \
    make \
    python3-dev \
    python3-pip \
    srecord \
    unzip \
    wget \
    xz-utils

# get platformio
RUN python3 -m pip install --upgrade pip setuptools
RUN python3 -m pip install -U platformio
RUN python3 -V
