FROM debian
WORKDIR /
RUN apt update
RUN apt -y install gcc
RUN apt -y install git
RUN apt -y install cmake
RUN apt -y install valgrind
RUN apt -y install rpm
RUN mkdir /working-dir
WORKDIR /working-dir
