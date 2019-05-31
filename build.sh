#!/usr/bin/env sh

set -eo pipefail

rm -rf bootstrap 
docker build . --tag opiumserver -f ./Dockerfile
docker rm server || true
docker create --name server opiumserver
docker cp server:/app/bootstrap bootstrap 

cd $root_path
