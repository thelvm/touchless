#!/bin/bash

cp touchless.xml ~/.touchless

gdbus-codegen-glibmm3 \
        --generate-cpp-code=touchless_gdbus \
        touchless.xml
