FROM alpine:3.20

RUN apk add --no-cache gcc libc-dev make

WORKDIR /app
COPY server.c /app/
RUN gcc -o server server.c

# EXPOSE 9054
CMD ["./server"]