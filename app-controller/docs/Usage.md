# Usage

## 1) Add app-controller-submodule as a submodule to include in your project

```bash
git submodule add https://gerrit.automotivelinux.org/gerrit/apps/app-controller-submodule
```

## 2) Add app-controller-submodule as a static library to your binding

```cmake
    # Library dependencies (include updates automatically)
    TARGET_LINK_LIBRARIES(${TARGET_NAME}
        ctl-utilities
        ... other dependencies ....
    )
```

## 3) Declare your controller config section in your binding

```C
// CtlSectionT syntax:
// key: "section name in config file"
// loadCB: callback to process section
// handle: a void* pass to callback when processing section
static CtlSectionT ctlSections[]= {
    {.key="plugins" , .loadCB= PluginConfig, .handle= &halCallbacks},
    {.key="onload"  , .loadCB= OnloadConfig},
    {.key="halmap"  , .loadCB= MapConfigLoad},
    {.key=NULL}
};

```

## 4) Do the controller config parsing at binding pre-init

```C
   // check if config file exist
    const char *dirList= getenv("CTL_CONFIG_PATH");
    if (!dirList) dirList=CONTROL_CONFIG_PATH;

    const char *configPath = CtlConfigSearch(apiHandle, dirList, "prefix");
    if(!confiPath) return -1;

    ctlConfig = CtlConfigLoad(dirList, ctlSections);
    if (!ctlConfig) return -1;
```

## 5) Execute the controller config during binding init

```C
  int err = CtlConfigExec (ctlConfig);
```