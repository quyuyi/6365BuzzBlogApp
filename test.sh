#!/bin/bash

service=recommendation

export PYTHONPATH=app/$service/service/tests/site-packages/
python3 app/$service/service/tests/test_$service.py

python3 app/apigateway/tests/test_api.py