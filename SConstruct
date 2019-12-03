import sys
import os
import excons
import functools
import re


env = excons.MakeBaseEnv()
out_basedir = excons.OutputBaseDirectory()
out_incdir = os.path.join(out_basedir, "include")
out_libdir = os.path.join(out_basedir, "lib")
staticlib = excons.GetArgument("usd-static", 0, int) != 0


usd_opts = {}

# USD
usd_opts["BUILD_SHARED_LIBS"] = 0 if staticlib else 1

## tbb
usd_opts["TBB_INCLUDE_DIR"] = ""
usd_opts["TBB_LIBRARY"] = ""
usd_opts["TBB_LIB_SUFFIX"] = ""
usd_opts["TBB_NO_IMPLICIT_LINKAGE"] = 1

## boost
usd_opts["BOOST_ROOT"] = ""
usd_opts["Boost_USE_STATIC_LIBS"] = 1 if excons.GetArgument("boost-static", 1, int) != 0 else 0

# imaging
usd_opts["PXR_BUILD_IMAGING"] = 1
usd_opts["PXR_BUILD_OPENIMAGEIO_PLUGIN"] = 1
usd_opts["PXR_BUILD_OPENCOLORIO_PLUGIN"] = 1
# TODO : build glew
usd_opts["PXR_ENABLE_GL_SUPPORT"] = 0
usd_opts["PXR_ENABLE_PTEX_SUPPORT"] = 0
usd_opts["PXR_BUILD_EMBREE_PLUGIN"] = 0

# usd view
usd_opts["PXR_BUILD_USDVIEW"] = 0

# plugins
usd_opts["PXR_BUILD_KATANA_PLUGIN"] = 0
usd_opts["PXR_BUILD_MAYA_PLUGIN"] = 0
usd_opts["PXR_BUILD_HOUDINI_PLUGIN"] = 0
usd_opts["PXR_BUILD_PRMAN_PLUGIN"] = 0
usd_opts["PXR_BUILD_ALEMBIC_PLUGIN"] = 0

# python
usd_opts["PXR_ENABLE_PYTHON_SUPPORT"] = 1

third_opts = {}
out_zlib = []
out_lcms2 = []
out_tiff = []
out_jpeg = []
out_bz2 = []
out_exr = []
out_ocio = []
out_oiio = []
out_tbb = []
out_osd = []


rv = excons.ExternalLibRequire("boost")
if rv["require"]:
    usd_opts["BOOST_ROOT"] = os.path.dirname(rv["libdir"])
else:
    excons.WarnOnce("Boost is require to build USD, please provide root directory using 'with-boost=' flag", tool="USD")
    sys.exit(1)

rv = excons.ExternalLibRequire("zlib")
if not rv["require"]:
    excons.PrintOnce("USD: Build zlib from sources ...")
    third_opts["zlib-static"] = 1
    excons.Call("zlib", imp=["ZlibPath"], overrides=third_opts)
    third_opts["with-zlib"] = os.path.dirname(out_incdir)
    out_zlib.append(ZlibPath(static=True))
    out_zlib.append("{}/zlib.h".format(out_incdir))

rv = excons.ExternalLibRequire("libjpeg")
if not rv["require"]:
    excons.PrintOnce("USD: Build libjpeg from sources ...")
    third_opts["libjpeg-static"] = 1
    third_opts["jpeg-static"] = 1
    excons.Call("libjpeg-turbo", imp=["LibjpegPath"], overrides=third_opts)
    third_opts["with-libjpeg"] = os.path.dirname(out_incdir)
    out_jpeg.append(LibjpegPath(static=True))
    out_jpeg.append("{}/jpeglib.h".format(out_incdir))

rv = excons.ExternalLibRequire("libtiff")
if not rv["require"]:
    third_opts["libtiff-static"] = 1
    third_opts["libtiff-use-jbig"] = 0
    excons.PrintOnce("USD: Build libtiff from sources ...")
    excons.cmake.AddConfigureDependencies("libtiff", out_zlib + out_jpeg)
    excons.Call("libtiff", overrides=third_opts, imp=["LibtiffPath"])
    third_opts["with-libtiff"] = os.path.dirname(os.path.dirname(LibtiffPath()))
    third_opts["with-jbig"] = os.path.dirname(os.path.dirname(LibtiffPath()))
    out_tiff.append(LibtiffPath())
    out_tiff.append("{}/tiff.h".format(out_incdir))

rv = excons.ExternalLibRequire("lcms2")
if not rv["require"]:
    third_opts["lcms2-static"] = 1
    excons.PrintOnce("USD: Build lcms from sources ...")
    excons.cmake.AddConfigureDependencies("lcms2", out_zlib + out_jpeg + out_tiff)
    excons.Call("Little-cms", overrides=third_opts, imp=["LCMS2Path"])
    lcms2_path = LCMS2Path()
    third_opts["with-lcms2"] = os.path.dirname(os.path.dirname(lcms2_path))
    out_lcms2.append(lcms2_path)
    out_lcms2.append("{}/lcms2.h".format(out_incdir))
    third_opts["LCMS2_LIBRARY"] = LCMS2Path()

rv = excons.ExternalLibRequire("openexr")
if not rv["require"]:
    third_opts["openexr-static"] = 1
    third_opts["openexr-suffix"] = ""
    third_opts = third_opts.copy()
    third_opts.update({"BOOST_ROOT": usd_opts["BOOST_ROOT"], "Boost_USE_STATIC_LIBS": usd_opts["Boost_USE_STATIC_LIBS"]})
    exr_imps = ["HalfPath", "IexPath", "IexMathPath", "ImathPath", "IlmThreadPath", "IlmImfPath", "IlmImfUtilPath", "PyIexPath", "PyImathPath"]
    excons.PrintOnce("USD: Build openexr from sources ...")
    excons.cmake.AddConfigureDependencies("openexr", out_zlib)
    excons.Call("openexr", targets=["ilmbase-static", "openexr-static"], overrides=third_opts, imp=exr_imps)
    third_opts["with-openexr"] = os.path.dirname(os.path.dirname(HalfPath(True)))
    out_exr.append(HalfPath(True))
    out_exr.append(IexPath(True))
    out_exr.append(ImathPath(True))
    out_exr.append(IlmThreadPath(True))
    out_exr.append(IlmImfPath(True))
    usd_opts["FOUND_OPENEXR"] = 1
    usd_opts["OPENEXR_INCLUDE_DIRS"] = out_incdir
    usd_opts["OPENEXR_LIBRARIES"] = ";".join(out_zlib + [HalfPath(True), IexPath(True), ImathPath(True), IlmThreadPath(True), IlmImfPath(True)])

    exr_ver_m = 0
    exr_ver_n = 0
    exr_ver_p = 0

    with open(os.path.abspath("openexr/OpenEXR/CMakeLists.txt"), "r") as f:
        for l in f.readlines():
            mr = re.search("^set[(]OPENEXR_VERSION_MAJOR ([0-9]+)[)]$", l)
            if mr:
                exr_ver_m = mr.group(1)

            nr = re.search("^set[(]OPENEXR_VERSION_MINOR ([0-9]+)[)]$", l)
            if nr:
                exr_ver_n = nr.group(1)

            pr = re.search("^set[(]OPENEXR_VERSION_PATCH ([0-9]+)[)]$", l)
            if pr:
                exr_ver_p = pr.group(1)

    usd_opts["OPENEXR_VERSION"] = "{}.{}.{}".format(exr_ver_m, exr_ver_n, exr_ver_p)
else:
    usd_opts["OPENEXR_LOCATION"] = os.path.dirname(rv["incdir"])

rv = excons.ExternalLibRequire("ocio")
if not rv["require"]:
    third_opts["ocio-static"] = 1
    third_opts["yamlcpp-static"] = 1
    
    third_opts["tinyxml-static"] = 1
    ocio_opts = third_opts.copy()
    if sys.platform == "win32":
        ocio_opts["ocio-use-boost"] = 1
    excons.PrintOnce("USD: Build OpenColorIO from sources ...")
    excons.cmake.AddConfigureDependencies("ocio", out_zlib)
    excons.Call("OpenColorIO", targets=["yamlcpp", "tinyxml", "ocio-static"], overrides=ocio_opts, imp=["OCIOPath", "YamlCppPath", "TinyXmlPath"])
    out_ocio.append(OCIOPath(static=True))
    out_ocio.append("{}/OpenColorIO/OpenColorIO.h".format(out_incdir))
    ocio_loc = os.path.dirname(os.path.dirname(OCIOPath(static=True)))
    third_opts["with-ocio"] = ocio_loc
    third_opts["with-tinyxml"] = os.path.dirname(os.path.dirname(TinyXmlPath()))    
    third_opts["with-yamlcpp"] = os.path.dirname(os.path.dirname(YamlCppPath()))
    third_opts["yamlcpp-name"] = "yaml-cpp"

    ocio_ver_m = 0
    ocio_ver_n = 0
    ocio_ver_p = 0
    with open(os.path.abspath("OpenColorIO/CMakeLists.txt"), "r") as f:
        for l in f.readlines():
            mr = re.search("^set[(]OCIO_VERSION_MAJOR ([0-9]+)[)]$", l)
            if mr:
                ocio_ver_m = mr.group(1)

            nr = re.search("^set[(]OCIO_VERSION_MINOR ([0-9]+)[)]$", l)
            if nr:
                ocio_ver_n = nr.group(1)

            pr = re.search("^set[(]OCIO_VERSION_PATCH ([0-9]+)[)]$", l)
            if pr:
                ocio_ver_p = pr.group(1)

    usd_opts["OCIO_FOUND"] = 1
    usd_opts["OCIO_LIBRARIES"] = ";".join([TinyXmlPath(), YamlCppPath(), OCIOPath(static=True)])
    usd_opts["OCIO_INCLUDE_DIRS"] = out_incdir
    usd_opts["OCIO_VERSION"] = "{}.{}.{}".format(ocio_ver_m, ocio_ver_n, ocio_ver_p)
else:
    # find by FindOpenColorIO.cmake
    usd_opts["OCIO_LOCATION"] = os.path.dirname(rv["incdir"])

rv = excons.ExternalLibRequire("tbb")
if not rv["require"]:
    third_opts["tbb-static"] = 1
    tbb_opts = third_opts.copy()
    tbb_opts["use-c++11"] = 1
    excons.PrintOnce("USD: Build tbb from sources ...")
    excons.Call("tbb", overrides=tbb_opts, imp=["TBBPath", "TBBMallocPath", "TBBProxyPath", "TBBName"])
    third_opts["with-tbb"] = os.path.dirname(os.path.dirname(TBBPath()))
    third_opts["tbb-suffix"] = "_static"
    out_tbb.append(TBBPath())
    out_tbb.append(TBBMallocPath())
    out_tbb.append(TBBProxyPath())
    usd_opts["TBB_FOUND"] = 1
    usd_opts["TBB_tbb_LIBRARY"] = TBBPath()
    usd_opts["TBB_INCLUDE_DIRS"] = out_incdir
    usd_opts["TBB_LIBRARIES"] = ";".join([TBBPath(), TBBMallocPath(), TBBProxyPath()])
    usd_opts["TBB_DEFINITIONS"] = "-D __TBB_NO_IMPLICIT_LINKAGE"
    if excons.GetArgument("debug", 0, int):
        usd_opts["TBB_DEFINITIONS"] += " -DTBB_USE_DEBUG=1"

    tbb_major = 1
    tbb_minor = 1
    with open(os.path.abspath("tbb/include/tbb/tbb_stddef.h"), "r") as f:
        for l in f.readlines():
            mr = re.search(".*#define TBB_VERSION_MAJOR ([0-9]+).*", l)
            if mr:
                tbb_major = mr.group(1)
            nr = re.search(".*#define TBB_VERSION_MINOR ([0-9]+).*", l)
            if nr:
                rbb_minor = nr.group(1)
    usd_opts["TBB_VERSION"] = "{}.{}".format(tbb_major, tbb_minor)
else:
    # find by FindTBB.cmake
    usd_opts["TBB_INCLUDE_DIR"] = rv["incdir"]
    usd_opts["TBB_LIBRARY"] = rv["libdir"]
    usd_opts["TBB_LIB_SUFFIX"] = excons.GetArgument("tbb-suffix", "")

rv = excons.ExternalLibRequire("osd")
if not rv["require"]:
    third_opts["osd-static"] = 1
    excons.PrintOnce("USD: Build osd from sources ...")
    excons.cmake.AddConfigureDependencies("osd", out_tbb)
    excons.Call("OpenSubdiv", targets=["osd"], overrides=third_opts, imp=["OsdCPUPath", "OsdGPUPath"])
    out_osd.append(OsdCPUPath(True))

    usd_opts["OPENSUBDIV_FOUND"] = 1
    usd_opts["OPENSUBDIV_INCLUDE_DIR"] = out_incdir
    usd_opts["OPENSUBDIV_LIBRARIES"] = OsdCPUPath(True)

    with open(os.path.abspath("OpenSubdiv/opensubdiv/version.h")) as f:
        for l in f.readlines():
            r = re.search("^#define OPENSUBDIV_VERSION v([0-9]+)[_]([0-9]+)[_]([0-9]+)$", l)
            if r:
                usd_opts["OPENSUBDIV_VERSION"] = "{}.{}.{}".format(r.group(1), r.group(2), r.group(3))
                break

    if usd_opts["PXR_ENABLE_GL_SUPPORT"]:
        out_osd.append(OsdGPUPath(True))
        usd_opts["OPENSUBDIV_LIBRARIES"] += ";" + OsdGPUPath(True)

else:
    # find by FindOpenSubdiv.cmake
    usd_opts["OPENSUBDIV_ROOT_DIR"] = os.path.dirname(rv["incdir"])

rv = excons.ExternalLibRequire("oiio")
if not rv["require"]:
    third_opts["oiio-static"] = 1
    excons.PrintOnce("USD: Build oiio from sources ...")
    excons.cmake.AddConfigureDependencies("oiio", out_zlib + out_lcms2 + out_tiff + out_jpeg + out_bz2 + out_exr + out_ocio)
    excons.Call("oiio", overrides=third_opts, imp=["OiioPath", "OiioExtraLibPaths", "OiioVersion"])
    out_oiio = [OiioPath(static=True)] + OiioExtraLibPaths()
    usd_opts["OIIO_FOUND"] = 1
    usd_opts["OIIO_LIBRARIES"] = ";".join(out_oiio)
    usd_opts["OIIO_INCLUDE_DIRS"] = out_incdir
    usd_opts["OIIO_VERSION"] = OiioVersion()
else:
    # find by FindOpenImageIO.cmake
    usd_opts["OIIO_LOCATION"] = os.path.dirname(rv["incdir"])

def _name(libname, static=False):
    return libname

def _path(libname, static=False):
    libpath = _name(libname, static=static)
    if sys.platform == "win32":
        libpath = libname + ".lib"
    else:
        libpath = "lib" + libname + (".a" if static else excons.SharedLibraryLinkExt())

    return os.path.join(out_libdir, libpath)

def _require(pathFunc, static=False):
    env.Append(CPPPATH=[out_incdir])
    excons.Link(env, pathFunc(static), static=static, force=True, silent=True)


UsdName = functools.partial(_name, "usd")
UsdPath = functools.partial(_path, "usd")
RequireUsd = functools.partial(_require, "usd")
# TODO : provide other libs

dependencies = []
dependencies += out_zlib
dependencies += out_lcms2
dependencies += out_tiff
dependencies += out_jpeg
dependencies += out_bz2
dependencies += out_exr
dependencies += out_ocio
dependencies += out_oiio
dependencies += out_tbb
dependencies += out_osd


prjs = []
prjs.append({"name": "usd",
             "type": "cmake",
             "cmake-opts": usd_opts,
             "cmake-cfgs": ["CMakeLists.txt"] + dependencies,
             "cmake-srcs": excons.CollectFiles(["pxr"], patterns=["*.cc", "*.h"], recursive=True),
             # TODO : check other libs
             "cmake-outputs": [UsdPath(static=staticlib)]})


excons.AddHelpOptions(USD="""USD OPTIONS
  usd-static=0|1        : Toggle between static and shared library build [1]""")

excons.DeclareTargets(env, prjs)


Default("usd")

Export("UsdName UsdPath RequireUsd")
