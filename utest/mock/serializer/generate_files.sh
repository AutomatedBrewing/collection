#!/bin/sh

# Copyright (c) 2021 Fraunhofer AISEC. See the COPYRIGHT
# file at the top-level directory of this distribution.

# Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
# http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
# <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
# option. This file may not be copied, modified, or distributed
# except according to those terms.

echo Generating CBOR encoding and decoding functions...  

rm *.h
rm *.c

ZCBOR_PATH="../../../ext/zcbor/zcbor"
###   Structures   ###
python3 $ZCBOR_PATH/zcbor/zcbor.py -c $ZCBOR_PATH/tests/cases/pet.cddl code -e -d -t Pet --oc serializer_pet.c --oh serializer_pet.h
