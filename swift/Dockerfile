FROM swift as builder
RUN apt update
RUN apt install libssl-dev libcurl4-openssl-dev
RUN mkdir /build 
ADD . /build/
WORKDIR /build 
RUN swift build -c release
FROM swift:slim
COPY --from=builder /build/.build/release/app /app/
WORKDIR /app
EXPOSE 80
CMD ["./app"]