FROM alpine:3.20

RUN apk add --no-cache gcc libc-dev make

WORKDIR /app
COPY . /app/
RUN gcc -o main main.c ./tcp/tcp_listener.c

# EXPOSE 9054
CMD ["./main"]