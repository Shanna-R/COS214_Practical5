FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install compilers, debuggers, static analysis, lcov, and documentation tools
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    gdb \
    valgrind \
    lcov \
    doxygen \
    graphviz \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy repository contents into the container
COPY . .

# Build and execute the matching executable name from the Makefile
CMD ["bash", "-c", "make clean && make && ./CampusGuard"]