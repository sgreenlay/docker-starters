FROM debian:buster-slim
RUN apt-get update -y && \
    apt-get install -y clang git curl unzip tar make

RUN ["git", "clone", "https://github.com/Microsoft/vcpkg.git", "/vcpkg"]

WORKDIR /vcpkg
RUN "./bootstrap-vcpkg.sh"
RUN ["./vcpkg", "integrate", "install"]

ENV PATH="/vcpkg/downloads/tools/cmake-3.17.2-linux/cmake-3.17.2-Linux-x86_64/bin/:${PATH}"
ENV PATH="/vcpkg/downloads/tools/ninja-1.10.0-linux/:${PATH}"

RUN apt-get install -y python3 gperf
RUN ["/vcpkg/vcpkg", "install", "proxygen"]

RUN mkdir /app 
ADD . /app/

RUN mkdir /app/build
WORKDIR /app/build
RUN ["cmake", "-DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake", "-DCMAKE_BUILD_TYPE=Release", "-GNinja", ".."]
RUN sed -i 's/-lzstd//g' build.ninja
RUN ["ninja"]

EXPOSE 80
CMD ["./app"]