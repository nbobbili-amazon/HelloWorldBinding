/*
 * Copyright (C) 2016 "IoT.bzh"
 * Author Fulup Ar Foll <fulup@iot.bzh>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, something express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Reference:
 *   Json load using json_unpack https://jansson.readthedocs.io/en/2.9/apiref.html#parsing-and-validating-values
 */

#ifndef _CTL_CONFIG_INCLUDE_
#define _CTL_CONFIG_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "ctl-plugin.h"
#include <filescan-utils.h>
#include <wrap-json.h>

#ifdef CONTROL_SUPPORT_LUA
  #include "ctl-lua.h"
#endif

#ifndef CONTROL_MAXPATH_LEN
  #define CONTROL_MAXPATH_LEN 255
#endif

#ifndef CONTROL_CONFIG_PRE
  #define CONTROL_CONFIG_PRE "onload"
#endif

#ifndef CTL_PLUGIN_EXT
  #define CTL_PLUGIN_EXT ".ctlso"
  #define CTL_SCRIPT_EXT ".lua"
#endif

#define LUA_ACTION_PREFIX "lua://"
#define API_ACTION_PREFIX "api://"
#define PLUGIN_ACTION_PREFIX "plugin://"

typedef struct ConfigSectionS {
  const char *key;
  const char *uid;
  const char *info;
  const char *prefix;
  int (*loadCB)(AFB_ApiT apihandle, struct ConfigSectionS *section, json_object *sectionJ);
  void *handle;
  CtlActionT *actions;
} CtlSectionT;

typedef struct {
    const char *api;
    const char *uid;
    const char *info;
    const char *version;
    const char *author;
    const char *date;
    const char *prefix;
    json_object *configJ;
    json_object *requireJ;
    CtlSectionT *sections;
    CtlPluginT *ctlPlugins;
    void *external;
} CtlConfigT;

// This should not be global as application may want to define their own sections
typedef enum {
  CTL_SECTION_PLUGIN,
  CTL_SECTION_ONLOAD,
  CTL_SECTION_CONTROL,
  CTL_SECTION_EVENT,
  CTL_SECTION_HAL,

  CTL_SECTION_ENDTAG,
} SectionEnumT;

// ctl-action.c
extern int AddActionsToSection(AFB_ApiT apiHandle, CtlSectionT *section, json_object *actionsJ, int exportApi);
extern CtlActionT *ActionConfig(AFB_ApiT apiHandle, json_object *actionsJ,  int exportApi);
extern void ActionExecUID(AFB_ReqT request, CtlConfigT *ctlConfig, const char *uid, json_object *queryJ);
extern int ActionExecOne( CtlSourceT *source, CtlActionT* action, json_object *queryJ);
extern int ActionLoadOne(AFB_ApiT apiHandle, CtlActionT *action, json_object *, int exportApi);
extern int ActionLabelToIndex(CtlActionT* actions, const char* actionLabel);

// ctl-config.c
extern int CtlConfigMagicNew();
extern void* getExternalData(CtlConfigT *ctlConfig);
extern void setExternalData(CtlConfigT *ctlConfig, void *data);
extern json_object* CtlConfigScan(const char *dirList, const char *prefix) ;
extern char* ConfigSearch(AFB_ApiT apiHandle, json_object *responseJ);
extern char* CtlConfigSearch(AFB_ApiT apiHandle, const char *dirList, const char *prefix) ;
extern void DispatchRequireApi(AFB_ApiT apiHandle, json_object * requireJ);
extern int CtlConfigExec(AFB_ApiT apiHandle, CtlConfigT *ctlConfig) ;
extern CtlConfigT *CtlLoadMetaDataJson(AFB_ApiT apiHandle,json_object *ctlConfigJ, const char *prefix) ;
extern CtlConfigT *CtlLoadMetaDataUsingPrefix(AFB_ApiT apiHandle,const char* filepath, const char *prefix) ;
extern int CtlLoadSections(AFB_ApiT apiHandle, CtlConfigT *ctlHandle, CtlSectionT *sections);
#define CtlLoadMetaData(api, filepath) CtlLoadMetaDataUsingPrefix(api, filepath, NULL)

// ctl-event.c
extern int EventConfig(AFB_ApiT apihandle, CtlSectionT *section, json_object *actionsJ);
extern void CtrlDispatchApiEvent (AFB_ApiT apiHandle, const char *evtLabel, struct json_object *eventJ);
extern void CtrlDispatchV2Event(const char *evtLabel, json_object *eventJ);

// ctl-control.c
extern int ControlConfig(AFB_ApiT apiHandle, CtlSectionT *section, json_object *actionsJ);

// ctl-onload.c
extern int OnloadConfig(AFB_ApiT apiHandle, CtlSectionT *section, json_object *actionsJ);

// ctl-plugin.c
extern int PluginConfig(AFB_ApiT UNUSED_ARG(apiHandle), CtlSectionT *section, json_object *pluginsJ);
extern int PluginGetCB (AFB_ApiT apiHandle, CtlActionT *action , json_object *callbackJ);
extern void* getPluginContext(CtlPluginT *plugin);
extern void setPluginContext(CtlPluginT *plugin, void *context);
#ifdef __cplusplus
}
#endif

#endif /* _CTL_CONFIG_INCLUDE_ */