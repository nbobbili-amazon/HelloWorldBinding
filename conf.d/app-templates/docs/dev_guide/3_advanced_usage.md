# Build a widget

## config.xml.in file

To build a widget you need a _config.xml_ file describing what is your apps and
how Application Framework would launch it. This repo provide a simple default
file _config.xml.in_ that should work for simple application without
interactions with others bindings.

It is recommended that you use the sample one which is more complete. You can
find it at the same location under the name _config.xml.in.sample_ (stunning
isn't it). Just copy the sample file to your _conf.d/wgt_ directory and name it
_config.xml.in_, then edit it to fit your needs.

> ***CAUTION*** : The default file is only meant to be use for a
> simple widget app, more complicated ones which needed to export
> their api, or ship several app in one widget need to use the provided
> _config.xml.in.sample_ which had all new Application Framework
> features explained and examples.

## Using cmake template macros

To leverage all cmake templates features, you have to specify ***properties***
on your targets. Some macros will not works without specifying which is the
target type.

As the type is not always specified for some custom targets, like an ***HTML5***
application, macros make the difference using ***LABELS*** property.

Choose between:

- **BINDING**: Shared library that be loaded by the AGL Application Framework
- **BINDINGV2**: Shared library that be loaded by the AGL Application Framework
 This has to be accompagnied with a JSON file named like the
 *${OUTPUT_NAME}-apidef* of the target that describes the API with OpenAPI
 syntax (e.g: *mybinding-apidef*).
 Or Alternatively, you can choose the name, without the extension, using macro
 **set_openapi_filename**. If you use C++, you have to set **PROJECT_LANGUAGES**
 to *CXX*.
- **BINDINGV3**: Shared library that be loaded by the AGL Application Framework
 This has to be accompagnied with a JSON file named like the
 *${OUTPUT_NAME}-apidef* of the target that describes the API with OpenAPI
 syntax (e.g: *mybinding-apidef*).
 Or Alternatively, you can choose the name, without the extension, using macro
 **set_openapi_filename**. If you use C++, you have to set **PROJECT_LANGUAGES**
 to *CXX*.
- **PLUGIN**: Shared library are meant to be used as a binding plugin. A binding
 would load it as a plugin to extend its functionnalities. It should be named
 with a special extension that you choose with SUFFIX cmake target property or
 it'd be **.ctlso** by default.
- **HTDOCS**: Root directory of a web app. This target has to build its
 directory and puts its files in the ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}
- **DATA**: Resources used by your application. This target has to build its
 directory and puts its files in the ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}
- **EXECUTABLE**: Entry point of your application executed by the AGL
 Application Framework
- **LIBRARY**: An external 3rd party library bundled with the binding for its
 own purpose because platform doesn't provide it.
- **BINDING-CONFIG**: Any files used as configuration by your binding.

Optional **LABELS** are available to define which resources type your test
materials are:

- **TEST-CONFIG**: JSON configuration files that will be used by the afb-test
 binding to know how to execute tests.
- **TEST-DATA**: Resources used to test your binding. It is at least your test
 plan and also could be fixtures and any needed files by your tests. These files
 will appear in a separate test widget.
- **TEST-PLUGIN**: Shared library are meant to be used as a binding
 plugin. A binding would load it as a plugin to extend its functionalities. It
 should be named with a special extension that you choose with SUFFIX cmake
 target property or it'd be **.ctlso** by default.
- **TEST-HTDOCS**: Root directory of a web app. This target has to build its
 directory and put its files in the ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}
- **TEST-EXECUTABLE**: Entry point of your application executed by the AGL
 Application Framework
- **TEST-LIBRARY**: An external 3rd party library bundled with the binding for its
 own use in case of platform doesn't provide it.

Here is a mapping between LABELS and directories where files will be placed in
the widget:

- **EXECUTABLE** : \<wgtrootdir\>/bin
- **BINDING-CONFIG** : \<wgtrootdir\>/etc
- **BINDING** | **BINDINGV2** | **BINDINGV3** | **LIBRARY** : \<wgtrootdir\>/lib
- **PLUGIN** : \<wgtrootdir\>/lib/plugins
- **HTDOCS** : \<wgtrootdir\>/htdocs
- **BINDING-DATA** : \<wgtrootdir\>/var
- **DATA** : \<wgtrootdir\>/var

And about test dedicated **LABELS**:

- **TEST-EXECUTABLE** : \<wgtrootdir\>/bin
- **TEST-CONFIG** : \<TESTwgtrootdir\>/etc
- **TEST-PLUGIN** : \<wgtrootdir\>/lib/plugins
- **TEST-HTDOCS** : \<wgtrootdir\>/htdocs
- **TEST-DATA** : \<TESTwgtrootdir\>/var

> **TIP** you should use the prefix _afb-_ with your **BINDING* targets which
> stand for **Application Framework Binding**.

Example:

```cmake
SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES
		LABELS "HTDOCS"
		OUTPUT_NAME dist.prod
	)
```

> **NOTE**: You doesn't need to specify an **INSTALL** command for these
> targets. This is already handle by template and will be installed in the
> following path : **${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}**

> **NOTE**: if you want to set and use `rpath` with your target you should use
> and set the target property `INSTALL_RPATH`.

## Add external 3rd party library

### Build, link and ship external library with the project

You could need to include an external library that isn't shipped in the
platform. Then you have to bundle the required library in the `lib` widget
directory.

Templates includes some facilities to help you to do so. Classic way to do so
is to declare as many CMake ExternalProject as library you need.

An ExternalProject is a special CMake module that let you define how to:
download, update, patch, configure, build and install an external project. It
doesn't have to be a CMake project and custom step could be added for special
needs using ExternalProject step. More informations on CMake [ExternalProject
documentation site](https://cmake.org/cmake/help/v3.5/module/ExternalProject.html?highlight=externalproject).

Example to include `mxml` library for [unicens2-binding](https://github.com/iotbzh/unicens2-binding)
project:

```cmake
set(MXML external-mxml)
set(MXML_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mxml)
ExternalProject_Add(${MXML}
    GIT_REPOSITORY https://github.com/michaelrsweet/mxml.git
    GIT_TAG release-2.10
    SOURCE_DIR ${MXML_SOURCE_DIR}
    CONFIGURE_COMMAND ./configure --build x86_64 --host aarch64
    BUILD_COMMAND make libmxml.so.1.5
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)

PROJECT_TARGET_ADD(mxml)

add_library(${TARGET_NAME} SHARED IMPORTED GLOBAL)

SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES
    LABELS LIBRARY
    IMPORTED_LOCATION ${MXML_SOURCE_DIR}/libmxml.so.1
    INTERFACE_INCLUDE_DIRECTORIES ${MXML_SOURCE_DIR}
)

add_dependencies(${TARGET_NAME} ${MXML})
```

Here we define an external project that drive the build of the library then we
define new CMake target of type **IMPORTED**. Meaning that this target hasn't
been built using CMake but is available at the location defined in the target
property *IMPORTED_LOCATION*.

You could want to build the library as *SHARED* or *STATIC* depending on your needs
and goals. Then you only have to modify the external project configure step and change
filename used by **IMPORTED** library target defined after external project.

Then target *LABELS* property is set to **LIBRARY** to ship it in the widget.

Unicens project also need some header from this library, so we use the target
property *INTERFACE_INCLUDE_DIRECTORIES*. Setting that when another target link
to that imported target, it can access to the include directories.

We bound the target to the external project using a CMake dependency at last.

Then this target could be use like any other CMake target and be linked etc.

### Only link and ship external library with the project

If you already have a binary version of the library that you want to use and you
can't or don't want to build the library then you only have to add an **IMPORTED**
library target.

So, taking the above example, `mxml` library inclusion would be:

```cmake
PROJECT_TARGET_ADD(mxml)

add_library(${TARGET_NAME} SHARED IMPORTED GLOBAL)

SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES
    LABELS LIBRARY
    IMPORTED_LOCATION /path/to/library/libmxml.so.1
    INTERFACE_INCLUDE_DIRECTORIES /path/to/mxml/include/dir
)
```

Finally, you can link any other lib or executable target with this imported
library like any other target.

## Macro reference

### PROJECT_TARGET_ADD

Typical usage would be to add the target to your project using macro
`PROJECT_TARGET_ADD` with the name of your target as parameter.

Example:

```cmake
PROJECT_TARGET_ADD(low-can-demo)
```

> ***NOTE***: This will make available the variable `${TARGET_NAME}`
> set with the specificied name. This variable will change at the next call
> to this macros.

### project_subdirs_add

This macro will search in all subfolder any `CMakeLists.txt` file. If found then
it will be added to your project. This could be use in an hybrid application by
example where the binding lay in a sub directory.

Usage :

```cmake
project_subdirs_add()
```

You also can specify a globbing pattern as argument to filter which folders
will be looked for.

To filter all directories that begin with a number followed by a dash the
anything:

```cmake
project_subdirs_add("[0-9]-*")
```

### set_openapi_filename

Used with a target labelized **BINDINGV2** to define the file name, and
possibly a relative path with the current *CMakeLists.txt*.

If you don't use that macro to specify the name of your definition file
then the default one will be used, *${OUTPUT_NAME}-apidef* with
**OUTPUT_NAME** as the [target property].

> **CAUTION** you must only specify the name **WITHOUT** the extension.

```cmake
set_openapi_filename('binding/mybinding_definition')
```

[target property]: https://cmake.org/cmake/help/v3.6/prop_tgt/OUTPUT_NAME.html "OUTPUT_NAME property documentation"

### add_input_files

Create custom target dedicated for HTML5 and data resource files. This macro
provides syntax and schema verification for differents languages which are
about now: LUA, JSON and XML.

You could change the tools used to check files with the following variables:

- XML_CHECKER: set to use **xmllint** provided with major linux distribution.
- LUA_CHECKER: set to use **luac** provided with major linux distribution.
- JSON_CHECKER: no tools found at the moment.

```cmake
add_input_file("${MY_FILES_LIST}")
```

> **NOTE**: an issue at the check step on a file will stop at the build step.
