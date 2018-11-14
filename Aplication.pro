TEMPLATE = subdirs
CONFIG += ordered



SUBDIRS +=     core \
    volumeplugin \
    echoplugin

unix:!mac:  APPLICATIONPREFIX = $$(PWD)/../..
unix:!mac: EXECUTABLEPATH = $$APPLICATIONPREFIX/ApplicationPackage
target.path = $$EXECUTABLEPATH/application


