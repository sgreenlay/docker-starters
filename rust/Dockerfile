FROM rust as builder
ADD . /build/
WORKDIR /build 
RUN cargo install --path .
FROM debian:buster-slim
COPY --from=builder /usr/local/cargo/bin/app /app/
WORKDIR /app
EXPOSE 80
CMD ["./app"]