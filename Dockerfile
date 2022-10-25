FROM ubuntu:latest

MAINTAINER base

RUN apt-get update

RUN apt-get -y install g++
RUN apt-get -y install cmake
RUN apt-get -y install libgtest-dev
RUN apt-get -y install valgrind
