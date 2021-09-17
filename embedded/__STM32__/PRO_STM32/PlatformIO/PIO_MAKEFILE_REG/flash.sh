#!/bin/bash

make
cd output
st-flash write main.bin 0x8000000







