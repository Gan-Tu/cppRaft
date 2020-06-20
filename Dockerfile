# Use pre-built image of ubuntu with bazel
FROM tugan0329/bazel-linux:latest
WORKDIR /app
RUN apt-get install -y python python3

# BUILD dependencies
COPY WORKSPACE ./
COPY src/third_party/build_rules ./src/third_party/build_rules

# Scripts
COPY scripts ./scripts

# Source Code
COPY src/ ./src/
RUN bazel build src/...

# Build and cache the rest of the code
COPY . .
RUN bazel build ...