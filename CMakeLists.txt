cmake_minimum_required(VERSION 4.0)
project(Xadrez C)

set(CMAKE_C_STANDARD 11)

add_executable(Xadrez main.c
        tabuleiro.h
        tabuleiro.c)
