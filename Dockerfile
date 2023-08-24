FROM debian
LABEL authors="alla"




RUN   apt-get update;
RUN   apt-get install -y cmake libzmq3-dev;
RUN   apt-get install -y  libsqlite3-dev;
RUN   apt-get install -y libboost-all-dev;
RUN   apt-get install -y libvlc-dev git-all;
RUN   apt-get install -y vlc;
RUN apt-get install -y gcc g++;
RUN git clone https://github.com/oatpp/oatpp.git && \
    cd oatpp && \
    mkdir build && cd build && \
    cmake ./.. && \
    make install;

RUN git clone https://github.com/oatpp/oatpp-swagger && \
    cd oatpp-swagger && \
    mkdir build && cd build && \
    cmake ./.. && \
    make && \
    make install


ARG VLC_UID="1000"
ARG VLC_GID="1000"

RUN groupadd -g "${VLC_GID}" vlc && \
    useradd -m -d /usr/src/valravn -s /bin/sh -u "${VLC_UID}" -g "${VLC_GID}" vlc && \
    apt-get upgrade -y;

RUN   apt-get install -y ffmpeg;
COPY . /usr/src/valravn

RUN set -ex;              \
    cd /usr/src/valravn;  \
    cmake .; make;

EXPOSE 8000

CMD ["/usr/src/valravn/Valravn_run"]