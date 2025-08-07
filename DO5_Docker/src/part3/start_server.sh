#!/bin/bash

mv nginx.conf /etc/nginx/nginx.conf
gcc main.c -lfcgi -o server
spawn-fcgi -p 8080 server
service nginx start
/bin/bash