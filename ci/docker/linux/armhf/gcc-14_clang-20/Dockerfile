FROM ubuntu:24.04

ENV TZ=Europe/Paris
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update

RUN apt install -y git
RUN apt install -y make
RUN apt install -y cmake
RUN apt install -y g++-14
RUN apt install -y clang-20
RUN apt install -y valgrind
RUN apt install -y cppcheck
RUN apt install -y python3.12
RUN apt install -y python3.12-venv
RUN apt install -y python3-pip
RUN apt install -y doxygen
RUN apt install -y catch2

CMD [""]
