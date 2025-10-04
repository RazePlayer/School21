#!/bin/bash

scp ./cat/s21_cat admin1@192.168.64.10:/usr/local/bin/
scp ./grep/s21_grep admin1@192.168.64.10:/usr/local/bin/
ssh admin1@192.168.64.10 ls /usr/local/bin
