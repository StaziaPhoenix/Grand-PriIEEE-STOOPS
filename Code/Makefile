CC=g++
CXXFLAGS=-std=c++11 -g -O3 -mfpu=neon-vfpv4 -mfloat-abi=hard `pkg-config --clags --libs opencv` -lm -lrt
LDFLAGS=-g

i2c: ImageAnalyzer
colorTrack.cpp -o colorTrack -O3 -mfpu=neon-vfpv4 -mfloat-abi=hard `pkg-config --cflags --libs opencv` -lm -lrt
