FROM gcc
RUN apt update
RUN apt -y install cmake valgrind git
