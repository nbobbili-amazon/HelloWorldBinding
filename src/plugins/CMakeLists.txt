###########################################################################
# Copyright 2017-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###########################################################################

PROJECT_TARGET_ADD(helloworld-api)

    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set(HELLOWORLD_LIB_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorldApi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorldApi.h
    )

    # Define targets
    ADD_LIBRARY(${TARGET_NAME} MODULE
        ${HELLOWORLD_LIB_SRC}
    )

    # Hello World plugin properties
    SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES
        LABELS "PLUGIN"
        PREFIX ""
        SUFFIX ".ctlso"
        OUTPUT_NAME ${TARGET_NAME}
    )

    # Define target includes
    TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME}
        PUBLIC ${GLIB_PKG_INCLUDE_DIRS}
        PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}"
        PRIVATE "${CMAKE_SOURCE_DIR}/app-controller/ctl-lib"
    )

    # Library dependencies (include updates automatically)
    TARGET_LINK_LIBRARIES(${TARGET_NAME}
        afb-helpers
        ${GLIB_PKG_LIBRARIES}
        ${link_libraries}
    )