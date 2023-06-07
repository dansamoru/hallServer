FROM ubuntu:18.04

LABEL author="Samoilov 221-329"

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install qt5-default -y
RUN apt-get install qtbase5-dev -y
RUN apt-get install qt5-qmake
RUN apt-get install build-essential -y

WORKDIR /Samoilov_221-329
COPY *.cpp .
COPY *.h .
COPY *.pro .

RUN mkdir build
RUN cmake ..
RUN make


ENTRYPOINT ["./hallServer"]