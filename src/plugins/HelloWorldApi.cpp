/*
 * Copyright 2018-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */
#include "HelloWorldApi.h"

#include <list>

using namespace std;

CTLP_CAPI_REGISTER("helloworld-api");

CTLP_ONLOAD(plugin, ret) {
    if (plugin->api == nullptr) {
        return -1;
    }

    return 0;
}


CTLP_CAPI(ping, source, argsJ, eventJ) {
    AFB_ReqSuccess(
        source->request, json_object_new_string("Ping call success."), NULL);
    return 0;
}