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
RUN apt install -y environment-modules
RUN apt install -y wget

RUN mkdir /opt/armie-25.0_install/
#COPY ARMIE-BN-UBUNT-r25p0-00rel0.tgz /opt/armie-25.0_install/
RUN wget http://perso.lip6.fr/adrien.cassagne/data/armie/ARMIE-BN-UBUNT-r25p0-00rel0.tgz
RUN mv ARMIE-BN-UBUNT-r25p0-00rel0.tgz /opt/armie-25.0_install/
RUN cd /opt/armie-25.0_install/ && tar xf ARMIE-BN-UBUNT-r25p0-00rel0.tgz
RUN cd /opt/armie-25.0_install/arm-instruction-emulator_25.0_Ubuntu-22.04 && ./arm-instruction-emulator_25.0_Ubuntu-22.04.sh -a -i /opt/armie-25.0

ENV MODULEPATH="${MODULEPATH}:/opt/armie-25.0/modulefiles/"

CMD [""]
