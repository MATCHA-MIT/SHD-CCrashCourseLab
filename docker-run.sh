#!/bin/bash

docker build . -t shd-lab0
docker run -v $(pwd):/lab0 -it shd-lab0 /bin/bash
