#!/bin/bash

cp touchless.xml ~/.touchless

gdbus-codegen-glibmm3 \
        --interface-prefix="com.thelvm." \
        --generate-cpp-code=touchless_gdbus \
        touchless.xml
