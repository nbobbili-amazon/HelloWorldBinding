# Controller

* Object: Generic Controller to handle Policy, Small Business Logic, Glue in
 between components, ...
* Status: Release Candidate
* Author: Fulup Ar Foll fulup@iot.bzh
* Date  : May-2018

## Features

* Create a controller application from a JSON config file.
* A controller could be considered as a collection of actions that could be
  mapped to a dynamically created verb or when receiving an event from any other
  API.
* Actions can either be:
  * Invocation of an other binding API, either internal or external (eg: a
    policy service, Alsa UCM, ...)
  * C routines from a user provided plugin (eg: policy routine, proprietary code
    , ...)
  * Lua script function. Lua provides access to every AGL appfw functionality
    and can be extended by plugins written in C.

## Installation

* Controller can easily be included as a git submodule in any AGL service or
  application binder.
* Dependencies: the only dependencies are [AGL application framework](https://gerrit.automotivelinux.org/gerrit/p/src/app-framework-binder.git)
  and [app-afb-helpers-submodule](https://gerrit.automotivelinux.org/gerrit/p/apps/app-afb-helpers-submodule.git).
* Controller relies on Lua-5.3, when not needed Lua might be removed at
  compilation time.

## Monitoring

* The default test HTML page expect the monitoring HTML page to be accessible
 under /monitoring with the --monitoring option.
* The monitoring HTML pages are installed with the app framework binder in a
 subdirectory called monitoring.
* The monitoring is accessible at `http://localhost:1234/monitoring`.
* You can add other HTML pages with the alias options i.e:

```bash
afb-daemon --name afb-my-binding --port=1234 --monitoring --alias=/path1/to/htmlpages:/path2/to/htmlpages --ldpaths=. --workdir=. --roothttp=../htdocs
```
