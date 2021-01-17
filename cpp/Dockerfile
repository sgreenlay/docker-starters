FROM debian:buster-slim as builder
RUN apt-get update -y && \
    apt-get install -y clang git curl unzip tar make

RUN ["git", "clone", "https://github.com/Microsoft/vcpkg.git", "/vcpkg"]

WORKDIR /vcpkg
RUN ./bootstrap-vcpkg.sh
RUN ./vcpkg integrate install

RUN apt-get install -y python3 gperf pkg-config zip unzip

RUN mkdir /app
WORKDIR /app

ADD . .

RUN mkdir /app/build
WORKDIR /app/build

ENV VCPKG_FEATURE_FLAGS="manifests,versions"

RUN --mount=type=cache,target=/root/.cache/vcpkg/archives/ `/vcpkg/vcpkg fetch cmake` -DCMAKE_MAKE_PROGRAM=`/vcpkg/vcpkg fetch ninja` -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release -GNinja ..
RUN --mount=type=cache,target=/root/.cache/vcpkg/archives/ `/vcpkg/vcpkg fetch ninja`

FROM debian:buster-slim
RUN apt-get update -y && \
    apt-get install -y libatomic1
COPY --from=builder /app/build/app /app/
WORKDIR /app
EXPOSE 80
CMD ["./app"]