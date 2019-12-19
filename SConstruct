import sys
import os
import excons
from excons.tools import boost
import functools
import re
import pprint


##############################################
#  default env
##############################################

version = "0.19.11"

env = excons.MakeBaseEnv()
out_basedir = excons.OutputBaseDirectory()
out_incdir = os.path.join(out_basedir, "include")
out_libdir = os.path.join(out_basedir, "lib")


##############################################
#  debugging
##############################################

def TODO():
    raise Exception("OOPS! FORGOT SOMETHING!")


##############################################
#  build options
##############################################

staticlib = excons.GetArgument("usd-static", 0, int) != 0
build_viewer = excons.GetArgument("usd-view", 1, int) != 0
build_imaging = excons.GetArgument("usd-imaging", 0, int) != 0
build_test = excons.GetArgument("usd-test", 1, int) != 0
build_python = False

if not build_imaging:
    excons.WarnOnce("Building USD VIEW will be ignored beacuase building USD IMAGING off. If you want to build it please turn it on by 'usd-imaging=1' flag", tool="USD")
    build_viewer = False

rv = excons.ExternalLibRequire("python")
if not rv["require"]:
    excons.WarnOnce("Building USD VIEW will be ignored beacuase extenal lib python is not given, please provide python version by 'with-python=' flag", tool="USD")
    build_viewer = False
## TODO : check GL


##############################################
#  external libs
##############################################

ext_opts = {}
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

# --------------------------------------------
#  boost
# --------------------------------------------

boost_inc = ""
boost_static = 1 if excons.GetArgument("boost-static", 1, int) != 0 else 0

rv = excons.ExternalLibRequire("boost")
if rv["require"]:
    boost_inc = os.path.dirname(rv["incdir"])
else:
    excons.WarnOnce("Boost is require to build USD, please provide root directory using 'with-boost=' flag", tool="USD")
    sys.exit(1)

boost_libs = ["program_options"]
if build_python:
    boost_libs.append("python")


RequireBoost = boost.Require(libs=boost_libs)

# --------------------------------------------
#  tbb
# --------------------------------------------

rv = excons.ExternalLibRequire("tbb")
if not rv["require"]:
    ext_opts["tbb-static"] = 1
    tbb_opts = ext_opts.copy()
    tbb_opts["use-c++11"] = 1
    excons.PrintOnce("USD: Build tbb from sources ...")
    excons.Call("tbb", overrides=tbb_opts, imp=["TBBPath", "TBBMallocPath", "TBBProxyPath", "TBBName", "RequireTBB"])
    ext_opts["with-tbb"] = out_basedir
    ext_opts["tbb-suffix"] = "_static"
    out_tbb.append(TBBPath())
    out_tbb.append(TBBMallocPath())
    out_tbb.append(TBBProxyPath())
else:
    TODO()

# ============================================
#  libs for usd imaging
# ============================================

if build_imaging:
    # --------------------------------------------
    #  zlib
    # --------------------------------------------

    rv = excons.ExternalLibRequire("zlib")
    if not rv["require"]:
        excons.PrintOnce("USD: Build zlib from sources ...")
        ext_opts["zlib-static"] = 1
        excons.Call("zlib", imp=["ZlibPath"], overrides=ext_opts)
        ext_opts["with-zlib"] = out_basedir
        out_zlib.append(ZlibPath(static=True))
        out_zlib.append("{}/zlib.h".format(out_incdir))
    else:
        TODO()

    # --------------------------------------------
    #  libjpeg
    # --------------------------------------------

    rv = excons.ExternalLibRequire("libjpeg")
    if not rv["require"]:
        excons.PrintOnce("USD: Build libjpeg from sources ...")
        ext_opts["libjpeg-static"] = 1
        ext_opts["jpeg-static"] = 1
        excons.Call("libjpeg-turbo", imp=["LibjpegPath"], overrides=ext_opts)
        ext_opts["with-libjpeg"] = out_basedir
        out_jpeg.append(LibjpegPath(static=True))
        out_jpeg.append("{}/jpeglib.h".format(out_incdir))
    else:
        TODO()

    # --------------------------------------------
    #  libtiff
    # --------------------------------------------

    rv = excons.ExternalLibRequire("libtiff")
    if not rv["require"]:
        ext_opts["libtiff-static"] = 1
        ext_opts["libtiff-use-jbig"] = 0
        excons.PrintOnce("USD: Build libtiff from sources ...")
        excons.cmake.AddConfigureDependencies("libtiff", out_zlib + out_jpeg)
        excons.Call("libtiff", overrides=ext_opts, imp=["LibtiffPath"])
        ext_opts["with-libtiff"] = out_basedir
        ext_opts["with-jbig"] = out_basedir
        out_tiff.append(LibtiffPath())
        out_tiff.append("{}/tiff.h".format(out_incdir))
    else:
        TODO()

    # --------------------------------------------
    #  lcms2
    # --------------------------------------------

    rv = excons.ExternalLibRequire("lcms2")
    if not rv["require"]:
        ext_opts["lcms2-static"] = 1
        excons.PrintOnce("USD: Build lcms from sources ...")
        excons.cmake.AddConfigureDependencies("lcms2", out_zlib + out_jpeg + out_tiff)
        excons.Call("Little-cms", overrides=ext_opts, imp=["LCMS2Path"])
        lcms2_path = LCMS2Path()
        ext_opts["with-lcms2"] = out_basedir
        out_lcms2.append(lcms2_path)
        out_lcms2.append("{}/lcms2.h".format(out_incdir))
        ext_opts["LCMS2_LIBRARY"] = LCMS2Path()
    else:
        TODO()

    # --------------------------------------------
    #  openexr
    # --------------------------------------------

    rv = excons.ExternalLibRequire("openexr")
    if not rv["require"]:
        ext_opts["openexr-static"] = 1
        ext_opts["openexr-suffix"] = ""
        ext_opts = ext_opts.copy()
        ext_opts.update({"BOOST_ROOT": boost_root, "Boost_USE_STATIC_LIBS": boost_static})
        exr_imps = ["HalfPath", "IexPath", "ImathPath", "IlmImfPath", "IlmThreadPath", "RequireIlmImf"]
        excons.PrintOnce("USD: Build openexr from sources ...")
        excons.cmake.AddConfigureDependencies("openexr", out_zlib)
        excons.Call("openexr", targets=["ilmbase-static", "openexr-static"], overrides=ext_opts, imp=exr_imps)
        ext_opts["with-openexr"] = out_basedir
        out_exr.append(HalfPath(True))
        out_exr.append(IexPath(True))
        out_exr.append(ImathPath(True))
        out_exr.append(IlmThreadPath(True))
        out_exr.append(IlmImfPath(True))
    else:
        TODO()

    # --------------------------------------------
    #  ocio
    # --------------------------------------------

    rv = excons.ExternalLibRequire("ocio")
    if not rv["require"]:
        ext_opts["ocio-static"] = 1
        ext_opts["yamlcpp-static"] = 1

        ext_opts["tinyxml-static"] = 1
        ocio_opts = ext_opts.copy()
        if sys.platform == "win32":
            ocio_opts["ocio-use-boost"] = 1
        excons.PrintOnce("USD: Build OpenColorIO from sources ...")
        excons.cmake.AddConfigureDependencies("ocio", out_zlib)
        excons.Call("OpenColorIO", targets=["yamlcpp", "tinyxml", "ocio-static"], overrides=ocio_opts, imp=["OCIOPath", "YamlCppPath", "TinyXmlPath", "RequireOCIO"])
        out_ocio.append(OCIOPath(static=True))
        out_ocio.append("{}/OpenColorIO/OpenColorIO.h".format(out_incdir))
        ocio_loc = os.path.dirname(os.path.dirname(OCIOPath(static=True)))
        ext_opts["with-ocio"] = out_basedir
        ext_opts["with-tinyxml"] = out_basedir
        ext_opts["with-yamlcpp"] = out_basedir
        ext_opts["yamlcpp-name"] = "yaml-cpp"
    else:
        TODO()

    # --------------------------------------------
    #  osd
    # --------------------------------------------

    rv = excons.ExternalLibRequire("osd")
    if not rv["require"]:
        ext_opts["osd-static"] = 1
        excons.PrintOnce("USD: Build osd from sources ...")
        excons.cmake.AddConfigureDependencies("osd", out_tbb)
        excons.Call("OpenSubdiv", targets=["osd"], overrides=ext_opts, imp=["OsdCPUPath", "OsdGPUPath", "RequireOsdCPU"])
        out_osd.append(OsdCPUPath(True))
        # TODO : support GPU?
        # TODO : RequireOsdCPU has to add linking of tbb if using static lib
    else:
        TODO()

    # --------------------------------------------
    #  oiio
    # --------------------------------------------

    rv = excons.ExternalLibRequire("oiio")
    if not rv["require"]:
        ext_opts["oiio-static"] = 1
        excons.PrintOnce("USD: Build oiio from sources ...")
        excons.cmake.AddConfigureDependencies("oiio", out_zlib + out_lcms2 + out_tiff + out_jpeg + out_bz2 + out_exr + out_ocio)
        excons.Call("oiio", overrides=ext_opts, imp=["OiioPath", "OiioExtraLibPaths", "OiioVersion", "RequireOiio"])
        out_oiio = [OiioPath(static=True)] + OiioExtraLibPaths()
    else:
        TODO()


##############################################
#  build usd
##############################################

# --------------------------------------------
#  generate header
# --------------------------------------------

def GenerateConfig(target, source, env):
    src = source[0].get_abspath()
    tgt = target[0].get_abspath()

    ver_spl = version.split(".")
    mjr = int(ver_spl[0])
    mnr = int(ver_spl[1])
    ptc = int(ver_spl[2])

    header_def = {"PXR_MAJOR_VERSION": str(mjr),
                  "PXR_MINOR_VERSION": str(mnr),
                  "PXR_PATCH_VERSION": str(ptc),
                  "PXR_VERSION": str(mjr * 10000 + mnr * 100 + ptc),
                  "PXR_EXTERNAL_NAMESPACE": "pxr",
                  "PXR_INTERNAL_NAMESPACE": "pxrInternal_v{}_{}".format(mjr, mnr),
                  "PXR_USE_NAMESPACES": "1",
                  "PXR_PYTHON_SUPPORT_ENABLED": "1" if build_python else "0"}

    update = False
    st_file = os.path.abspath("pxr_config.status")

    if not os.path.isfile(tgt):
        update = True
    elif not os.path.isfile(st_file):
        update = True
    else:
        d = {}
        try:
            with open(st_file, "r") as f:
                l = f.read()
                d = eval(l)
        except:
            pass

        update = header_def != d

    if not update:
        return

    with open(st_file, "w") as f:
        pprint.pprint(header_def, f)

    if not os.path.isdir(os.path.dirname(tgt)):
        os.makedirs(os.path.dirname(tgt))

    with open(src, "r") as f:
        l = f.read()
        for k, v in header_def.items():
            l = l.replace("@{}@".format(k), v)

        with open(tgt, "w") as wf:
            wf.write(l)


GenConfig = env.Command(os.path.join(out_incdir, "pxr/pxr.h"), os.path.abspath("pxr/pxr.h.in"), GenerateConfig)

# --------------------------------------------
#  functions to export
# --------------------------------------------

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

# --------------------------------------------
#  dependencies
# --------------------------------------------

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

# --------------------------------------------
#  build option
# --------------------------------------------

flags = ""
defs = []

if sys.platform != "win32":
    flags += " -std=c++11 -Wall -pthread -Wno-deprecated -Wno-deprecated-declarations -Wno-unused-local-typedefs -Wno-unused-parameter"
else:
    defs += ["_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS", "NOMINMAX", "YY_NO_UNISTD_H"]
    flags += " /EHsc /Zc:rvalueCast /Zc:strictStrings /Zc:inline /W3"
    flags += " /wd4244 /wd4305 /wd4267 /wd4506 /wd4091 /wd4273 /wd4180 /wd4334"
    flags += " /bigobj /Zi /MP /Gm-"
    # /IGNORE:4221

if sys.platform == "darwin":
    flags += " -Wno-unused-command-line-argument"
    flags += " -Wno-missing-field-initializers"
    flags += " -Wno-expansion-to-defined"
    flags += " -Wno-undefined-var-template"
    flags += " -Wno-unused-function"
    flags += " -Wno-unused-variable"
    flags += " -Wno-unneeded-internal-declaration"
    flags += " -Wno-potentially-evaluated-expression"
    flags += " -Wno-instantiation-after-specialization"
    flags += " -Wno-inconsistent-missing-override"
    flags += " -Wno-unused-private-field"
    #flags += " -Wno-unused-lambda-capture"

if build_python:
    defs += ["PXR_PYTHON_SUPPORT_ENABLED", "BOOST_PYTHON_NO_PY_SIGNATURES"]


libs = []
if sys.platform != "win32":
    libs.append("m")
else:
    libs += ["Ws2_32", "Dbghelp"] # base/arch

customs = [RequireBoost, RequireTBB]
prjs = []

prjs_default = {"type": "sharedlib",
                "defs": defs,
                "cppflags": flags,
                "incdirs": [out_incdir, boost_inc],
                "libdirs": [out_libdir],
                "rpath": out_libdir,
                "libs": libs,
                "symvis": "default",
                "custom": customs}

def _fpath(directory, filePaths):
    return map(lambda x: os.path.join(directory, x), filePaths)

# ============================================
#  base
# ============================================

bases = []
# --------------------------------------------
#  arch
# --------------------------------------------

arch_prj = prjs_default.copy()
arch_prj["name"] = "arch"
arch_prj["alias"] = "usd-base-arch"
arch_prj["srcs"] = excons.glob("pxr/base/lib/arch/*.cpp")
arch_prj["install"] = {os.path.join(out_incdir, "pxr/base/arch"): excons.glob("pxr/base/lib/arch/*.h")}
prjs.append(arch_prj)
bases.append("usd-base-arch")

# --------------------------------------------
#  tf
# --------------------------------------------

tfs = ["atomicRenameUtil.cpp", "debugCodes.cpp", "noticeRegistry.cpp",
       "anyUniquePtr.cpp", "anyWeakPtr.cpp", "atomicOfstreamWrapper.cpp",
       "bitUtils.cpp", "debug.cpp", "debugNotice.cpp", "denseHashMap.cpp",
       "denseHashSet.cpp", "diagnostic.cpp", "diagnosticBase.cpp",
       "diagnosticHelper.cpp", "diagnosticMgr.cpp", "dl.cpp", "enum.cpp",
       "envSetting.cpp", "error.cpp", "errorMark.cpp", "errorTransport.cpp",
       "expiryNotifier.cpp", "fastCompression.cpp", "fileUtils.cpp",
       "getenv.cpp", "hash.cpp", "iterator.cpp", "mallocTag.cpp", "notice.cpp",
       "nullPtr.cpp", "ostreamMethods.cpp", "pathUtils.cpp",
       "patternMatcher.cpp", "pointerAndBits.cpp", "pyLock.cpp", "refBase.cpp",
       "refCount.cpp", "refPtr.cpp", "refPtrTracker.cpp", "regTest.cpp",
       "registryManager.cpp", "safeOutputFile.cpp", "scoped.cpp",
       "scopeDescription.cpp", "setenv.cpp", "singleton.cpp", "smallVector.cpp",
       "stackTrace.cpp", "stacked.cpp", "status.cpp", "stl.cpp",
       "stopwatch.cpp", "stringUtils.cpp", "templateString.cpp", "tf.cpp",
       "token.cpp", "traits.cpp", "type.cpp", "typeFunctions.cpp",
       "typeNotice.cpp", "warning.cpp", "weakBase.cpp", "weakPtr.cpp",
       "weakPtrFacade.cpp", "initConfig.cpp", "preprocessorUtils.cpp",
       "pxrDoubleConversion/double-conversion.cc",
       "pxrDoubleConversion/bignum-dtoa.cc", "pxrDoubleConversion/bignum.cc",
       "pxrDoubleConversion/cached-powers.cc", "pxrDoubleConversion/diy-fp.cc",
       "pxrDoubleConversion/fast-dtoa.cc", "pxrDoubleConversion/fixed-dtoa.cc",
       "pxrDoubleConversion/strtod.cc", "pxrLZ4/lz4.cpp"]

tf_prj = prjs_default.copy()
tf_prj["name"] = "tf"
tf_prj["alias"] = "usd-base-tf"
tf_prj["srcs"] = _fpath("pxr/base/lib/tf", tfs)
tf_prj["install"] = {os.path.join(out_incdir, "pxr/base/tf"): excons.glob("pxr/base/lib/tf/*.h"),
                     os.path.join(out_incdir, "pxr/base/tf/pxrDoubleConversion"): excons.glob("pxr/base/lib/tf/pxrDoubleConversion/*.h"),
                     os.path.join(out_incdir, "pxr/base/tf/pxrLZ4"): excons.glob("pxr/base/lib/tf/pxrLZ4/*.h")}
tf_prj["libs"] = libs + ["arch"]
prjs.append(tf_prj)
bases.append("usd-base-tf")

# --------------------------------------------
#  gf
# --------------------------------------------

gfs = ["bbox3d.cpp", "camera.cpp", "frustum.cpp", "gamma.cpp", "half.cpp",
       "homogeneous.cpp", "ilmbase_half.cpp", "interval.cpp", "line.cpp",
       "line2d.cpp", "lineSeg.cpp", "lineSeg2d.cpp", "math.cpp",
       "matrixData.cpp", "matrix2d.cpp", "matrix2f.cpp", "matrix3f.cpp",
       "matrix3d.cpp", "matrix4f.cpp", "matrix4d.cpp", "multiInterval.cpp",
       "plane.cpp", "quatd.cpp", "quatf.cpp", "quath.cpp", "quaternion.cpp",
       "range1d.cpp", "range1f.cpp", "range2d.cpp", "range2f.cpp",
       "range3d.cpp", "range3f.cpp", "ray.cpp", "rect2i.cpp", "rotation.cpp",
       "size2.cpp", "size3.cpp", "transform.cpp", "vec2d.cpp", "vec2f.cpp",
       "vec2h.cpp", "vec2i.cpp", "vec3d.cpp", "vec3f.cpp", "vec3h.cpp",
       "vec3i.cpp", "vec4d.cpp", "vec4f.cpp", "vec4h.cpp", "vec4i.cpp",
       "ostreamHelpers.cpp"]

gf_prj = prjs_default.copy()
gf_prj["name"] = "gf"
gf_prj["alias"] = "usd-base-gf"
gf_prj["srcs"] = _fpath("pxr/base/lib/gf", gfs)
gf_prj["install"] = {os.path.join(out_incdir, "pxr/base/gf"): excons.glob("pxr/base/lib/gf/*.h"),}
gf_prj["libs"] = libs + ["arch", "tf"]
prjs.append(gf_prj)
bases.append("usd-base-gf")

# --------------------------------------------
#  js
# --------------------------------------------

js_prj = prjs_default.copy()
js_prj["name"] = "js"
js_prj["alias"] = "usd-base-js"
js_prj["srcs"] = excons.glob("pxr/base/lib/js/*.cpp")
js_prj["install"] = {os.path.join(out_incdir, "pxr/base/js"): excons.glob("pxr/base/lib/js/*.h"),
                     os.path.join(out_incdir, "pxr/base/js/rapidjson"): excons.glob("pxr/base/lib/js/rapidjson/*")}
js_prj["libs"] = libs + ["arch", "tf"]
prjs.append(js_prj)
bases.append("usd-base-js")

# --------------------------------------------
#  trace
# --------------------------------------------

traces = ["aggregateTree.cpp", "aggregateNode.cpp", "category.cpp",
          "collection.cpp", "collectionNotice.cpp", "collector.cpp",
          "counterAccumulator.cpp", "dataBuffer.cpp", "dynamicKey.cpp",
          "event.cpp", "eventContainer.cpp", "eventData.cpp", "eventList.cpp",
          "eventNode.cpp", "eventTree.cpp", "key.cpp", "reporter.cpp",
          "reporterBase.cpp", "reporterDataSourceBase.cpp",
          "reporterDataSourceCollection.cpp", "reporterDataSourceCollector.cpp",
          "serialization.cpp", "staticKeyData.cpp", "threads.cpp",
          "aggregateTreeBuilder.cpp", "eventTreeBuilder.cpp",
          "jsonSerialization.cpp"]

trace_prj = prjs_default.copy()
trace_prj["name"] = "trace"
trace_prj["alias"] = "usd-base-trace"
trace_prj["srcs"] = _fpath("pxr/base/lib/trace", traces)
trace_prj["install"] = {os.path.join(out_incdir, "pxr/base/trace"): excons.glob("pxr/base/lib/trace/*.h")}
trace_prj["libs"] = libs + ["arch", "tf", "js"]
prjs.append(trace_prj)
bases.append("usd-base-trace")

# --------------------------------------------
#  work
# --------------------------------------------

works = ["arenaDispatcher.cpp", "detachedTask.cpp", "dispatcher.cpp",
         "loops.cpp", "reduce.cpp", "singularTask.cpp", "threadLimits.cpp",
         "utils.cpp"]

work_prj = prjs_default.copy()
work_prj["name"] = "work"
work_prj["alias"] = "usd-base-work"
work_prj["srcs"] = _fpath("pxr/base/lib/work", works)
work_prj["install"] = {os.path.join(out_incdir, "pxr/base/work"): excons.glob("pxr/base/lib/work/*.h")}
work_prj["libs"] = libs + ["tf", "trace"]
prjs.append(work_prj)
bases.append("usd-base-work")

# --------------------------------------------
#  plug
# --------------------------------------------

plugs = ["interfaceFactory.cpp", "notice.cpp", "plugin.cpp", "registry.cpp",
         "staticInterface.cpp", "debugCodes.cpp", "info.cpp",
         "testPlugBase.cpp", "initConfig.cpp"]

plug_prj = prjs_default.copy()
plug_prj["name"] = "plug"
plug_prj["alias"] = "usd-base-plug"
plug_prj["srcs"] = _fpath("pxr/base/lib/plug", plugs)
plug_prj["install"] = {os.path.join(out_incdir, "pxr/base/plug"): excons.glob("pxr/base/lib/plug/*.h")}
plug_prj["libs"] = libs + ["arch", "tf", "js", "trace", "work"]
prjs.append(plug_prj)
bases.append("usd-base-plug")

# --------------------------------------------
#  vt
# --------------------------------------------

vts = ["array.cpp", "dictionary.cpp", "functions.cpp", "hash.cpp",
       "streamOut.cpp", "types.cpp", "value.cpp"]

vt_prj = prjs_default.copy()
vt_prj["name"] = "vt"
vt_prj["alias"] = "usd-base-vt"
vt_prj["srcs"] = _fpath("pxr/base/lib/vt", vts)
vt_prj["install"] = {os.path.join(out_incdir, "pxr/base/vt"): excons.glob("pxr/base/lib/vt/*.h")}
vt_prj["libs"] = libs + ["arch", "tf", "gf", "trace"]
prjs.append(vt_prj)
bases.append("usd-base-vt")


# ============================================
#  usd
# ============================================

usds = []

# --------------------------------------------
#  ar
# --------------------------------------------

ars = ["asset.cpp", "assetInfo.cpp", "filesystemAsset.cpp",
       "packageResolver.cpp", "packageUtils.cpp", "resolver.cpp",
       "resolverContext.cpp", "resolverContextBinder.cpp",
       "resolverScopedCache.cpp", "debugCodes.cpp", "defaultResolver.cpp",
       "defaultResolverContext.cpp"]

ar_prj = prjs_default.copy()
ar_prj["name"] = "ar"
ar_prj["alias"] = "usd-usd-ar"
ar_prj["srcs"] = _fpath("pxr/usd/lib/ar", ars)
ar_prj["install"] = {os.path.join(out_incdir, "pxr/usd/ar"): excons.glob("pxr/usd/lib/ar/*.h")}
ar_prj["libs"] = libs + ["arch", "tf", "plug", "vt", "js"]
prjs.append(ar_prj)
usds.append("usd-usd-ar")

# --------------------------------------------
#  kind
# --------------------------------------------

kinds = ["registry.cpp"]

kind_prj = prjs_default.copy()
kind_prj["name"] = "kind"
kind_prj["alias"] = "usd-usd-kind"
kind_prj["srcs"] = _fpath("pxr/usd/lib/kind", kinds)
kind_prj["install"] = {os.path.join(out_incdir, "pxr/usd/kind"): excons.glob("pxr/usd/lib/kind/*.h")}
kind_prj["libs"] = libs + ["arch", "js", "tf", "plug"]
prjs.append(kind_prj)
usds.append("usd-usd-kind")

# --------------------------------------------
#  sdf
# --------------------------------------------

sdfs = ["abstractData.cpp", "allowed.cpp", "assetPath.cpp", "attributeSpec.cpp",
        "changeBlock.cpp", "changeList.cpp", "children.cpp",
        "childrenPolicies.cpp", "childrenProxy.cpp", "childrenUtils.cpp",
        "childrenView.cpp", "cleanupEnabler.cpp", "copyUtils.cpp", "data.cpp",
        "declareHandles.cpp", "fileFormat.cpp", "identity.cpp", "layer.cpp",
        "layerOffset.cpp", "layerStateDelegate.cpp", "layerTree.cpp",
        "layerUtils.cpp", "listProxy.cpp", "listEditor.cpp",
        "listEditorProxy.cpp", "listOp.cpp", "mapEditProxy.cpp",
        "mapEditor.cpp", "namespaceEdit.cpp", "notice.cpp", "path.cpp",
        "pathNode.cpp", "pathTable.cpp", "payload.cpp", "pool.cpp",
        "primSpec.cpp", "propertySpec.cpp", "proxyPolicies.cpp",
        "proxyTypes.cpp", "pseudoRootSpec.cpp", "reference.cpp",
        "relationshipSpec.cpp", "schema.cpp", "site.cpp", "siteUtils.cpp",
        "spec.cpp", "specType.cpp", "textFileFormat.cpp", "timeCode.cpp",
        "tokens.cpp", "types.cpp", "valueTypeName.cpp", "variantSetSpec.cpp",
        "variantSpec.cpp", "path.tab.cpp", "textFileFormat.tab.cpp",
        "assetPathResolver.cpp", "changeManager.cpp", "cleanupTracker.cpp",
        "connectionListEditor.cpp", "debugCodes.cpp", "fileFormatRegistry.cpp",
        "fileIO.cpp", "fileIO_Common.cpp", "layerRegistry.cpp",
        "listOpListEditor.cpp", "parserHelpers.cpp", "parserValueContext.cpp",
        "pathParser.cpp", "subLayerListEditor.cpp", "textParserContext.cpp",
        "valueTypeRegistry.cpp", "vectorListEditor.cpp", "path.lex.cpp",
        "textFileFormat.lex.cpp"]

sdf_prj = prjs_default.copy()
sdf_prj["name"] = "sdf"
sdf_prj["alias"] = "usd-usd-sdf"
sdf_prj["srcs"] = _fpath("pxr/usd/lib/sdf", sdfs)
sdf_prj["install"] = {os.path.join(out_incdir, "pxr/usd/sdf"): excons.glob("pxr/usd/lib/sdf/*.h")}
sdf_prj["libs"] = libs + ["arch", "tf", "gf", "trace", "vt", "work", "ar", "js", "plug"]

prjs.append(sdf_prj)
usds.append("usd-usd-sdf")

# --------------------------------------------
#  ndr
# --------------------------------------------

ndrs = ["debugCodes.cpp", "declare.cpp", "discoveryPlugin.cpp",
        "filesystemDiscovery.cpp", "filesystemDiscoveryHelpers.cpp",
        "node.cpp", "parserPlugin.cpp", "property.cpp", "registry.cpp"]

ndr_prj = prjs_default.copy()
ndr_prj["name"] = "ndr"
ndr_prj["alias"] = "usd-usd-ndr"
ndr_prj["srcs"] = _fpath("pxr/usd/lib/ndr", ndrs)
ndr_prj["install"] = {os.path.join(out_incdir, "pxr/usd/ndr"): excons.glob("pxr/usd/lib/ndr/*.h")}
ndr_prj["libs"] = libs + ["arch", "tf", "plug", "vt", "work", "ar", "sdf"]

prjs.append(ndr_prj)
usds.append("usd-usd-ndr")

# --------------------------------------------
#  sdr
# --------------------------------------------

sdrs = ["registry.cpp", "shaderMetadataHelpers.cpp", "shaderNode.cpp",
        "shaderProperty.cpp"]

sdr_prj = prjs_default.copy()
sdr_prj["name"] = "sdr"
sdr_prj["alias"] = "usd-usd-sdr"
sdr_prj["srcs"] = _fpath("pxr/usd/lib/sdr", sdrs)
sdr_prj["install"] = {os.path.join(out_incdir, "pxr/usd/sdr"): excons.glob("pxr/usd/lib/sdr/*.h")}
sdr_prj["libs"] = libs + ["arch", "tf", "vt", "ar", "ndr", "sdf", "gf"]

prjs.append(sdr_prj)
usds.append("usd-usd-sdr")

# --------------------------------------------
#  pcp
# --------------------------------------------

pcps = ["arc.cpp", "cache.cpp", "changes.cpp", "composeSite.cpp",
        "dependency.cpp", "dynamicFileFormatContext.cpp",
        "dynamicFileFormatDependencyData.cpp", "errors.cpp", "instanceKey.cpp",
        "iterator.cpp", "layerPrefetchRequest.cpp", "layerStack.cpp",
        "layerStackIdentifier.cpp", "mapExpression.cpp", "mapFunction.cpp",
        "namespaceEdits.cpp", "node.cpp", "pathTranslation.cpp",
        "primIndex.cpp", "propertyIndex.cpp", "site.cpp",
        "strengthOrdering.cpp", "targetIndex.cpp", "types.cpp",
        "debugCodes.cpp", "dependencies.cpp", "diagnostic.cpp",
        "instancing.cpp", "layerStackRegistry.cpp", "node_Iterator.cpp",
        "primIndex_Graph.cpp", "primIndex_StackFrame.cpp", "statistics.cpp",
        "utils.cpp"]

pcp_prj = prjs_default.copy()
pcp_prj["name"] = "pcp"
pcp_prj["alias"] = "usd-usd-pcp"
pcp_prj["srcs"] = _fpath("pxr/usd/lib/pcp", pcps)
pcp_prj["install"] = {os.path.join(out_incdir, "pxr/usd/pcp"): excons.glob("pxr/usd/lib/pcp/*.h")}
pcp_prj["libs"] = libs + ["arch", "tf", "trace", "vt", "sdf", "work", "ar"]

prjs.append(pcp_prj)
usds.append("usd-usd-pcp")

# --------------------------------------------
#  usd
# --------------------------------------------

usds = ["apiSchemaBase.cpp", "attribute.cpp", "clipsAPI.cpp",
        "attributeQuery.cpp", "collectionAPI.cpp",
        "collectionMembershipQuery.cpp", "common.cpp", "crateInfo.cpp",
        "debugCodes.cpp", "editContext.cpp", "editTarget.cpp",
        "flattenUtils.cpp", "inherits.cpp", "interpolation.cpp", "modelAPI.cpp",
        "notice.cpp", "object.cpp", "payloads.cpp", "prim.cpp",
        "primCompositionQuery.cpp", "primData.cpp", "primDataHandle.cpp",
        "primFlags.cpp", "primRange.cpp", "property.cpp", "references.cpp",
        "relationship.cpp", "resolveInfo.cpp", "resolver.cpp", "schemaBase.cpp",
        "schemaRegistry.cpp", "specializes.cpp", "stage.cpp", "stageCache.cpp",
        "stageCacheContext.cpp", "stageLoadRules.cpp",
        "stagePopulationMask.cpp", "timeCode.cpp", "tokens.cpp", "typed.cpp",
        "usdFileFormat.cpp", "usdaFileFormat.cpp", "usdcFileFormat.cpp",
        "usdzFileFormat.cpp", "variantSets.cpp", "zipFile.cpp", "clip.cpp",
        "clipCache.cpp", "crateData.cpp", "crateFile.cpp", "instanceCache.cpp",
        "instanceKey.cpp", "integerCoding.cpp", "interpolators.cpp",
        "usdzResolver.cpp", "valueUtils.cpp"]

usd_prj = prjs_default.copy()
usd_prj["name"] = "usd"
usd_prj["alias"] = "usd-usd-usd"
usd_prj["srcs"] = _fpath("pxr/usd/lib/usd", usds)
usd_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usd"): excons.glob("pxr/usd/lib/usd/*.h")}
usd_prj["libs"] = libs + ["arch", "kind", "pcp", "sdf", "ar", "plug", "tf", "js", "gf", "trace", "vt", "work"]

prjs.append(usd_prj)
usds.append("usd-usd-usd")

# --------------------------------------------
#  usdGeom
# --------------------------------------------

usd_geoms = ["debugCodes.cpp", "tokens.cpp", "bboxCache.cpp",
             "constraintTarget.cpp", "xformCache.cpp", "basisCurves.cpp",
             "boundable.cpp", "boundableComputeExtent.cpp", "camera.cpp",
             "capsule.cpp", "cone.cpp", "cube.cpp", "curves.cpp",
             "cylinder.cpp", "imageable.cpp", "gprim.cpp", "mesh.cpp",
             "metrics.cpp", "modelAPI.cpp", "motionAPI.cpp", "nurbsCurves.cpp",
             "nurbsPatch.cpp", "pointBased.cpp", "pointInstancer.cpp",
             "points.cpp", "primvar.cpp", "primvarsAPI.cpp", "scope.cpp",
             "sphere.cpp", "subset.cpp", "xform.cpp", "xformable.cpp",
             "xformOp.cpp", "xformCommonAPI.cpp", "samplingUtils.cpp"]

usd_geom_prj = prjs_default.copy()
usd_geom_prj["name"] = "usdGeom"
usd_geom_prj["alias"] = "usd-usd-usdGeom"
usd_geom_prj["srcs"] = _fpath("pxr/usd/lib/usdGeom", usd_geoms)
usd_geom_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdGeom"): excons.glob("pxr/usd/lib/usdGeom/*.h")}
usd_geom_prj["libs"] = libs + ["arch", "js", "tf", "gf", "plug", "vt", "sdf", "trace", "usd", "work", "kind"]

prjs.append(usd_geom_prj)
usds.append("usd-usd-usdGeom")

# --------------------------------------------
#  usdVol
# --------------------------------------------

usd_vols = ["volume.cpp", "fieldBase.cpp", "fieldAsset.cpp", "field3DAsset.cpp",
            "openVDBAsset.cpp", "tokens.cpp"]

usd_vol_prj = prjs_default.copy()
usd_vol_prj["name"] = "usdVol"
usd_vol_prj["alias"] = "usd-usd-usdVol"
usd_vol_prj["srcs"] = _fpath("pxr/usd/lib/usdVol", usd_vols)
usd_vol_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdVol"): excons.glob("pxr/usd/lib/usdVol/*.h")}
usd_vol_prj["libs"] = libs + ["tf", "sdf", "usd", "usdGeom"]

prjs.append(usd_vol_prj)
usds.append("usd-usd-usdVol")

# --------------------------------------------
#  usdLux
# --------------------------------------------

usd_luxs = ["blackbody.cpp", "cylinderLight.cpp", "diskLight.cpp",
            "distantLight.cpp", "domeLight.cpp", "geometryLight.cpp",
            "light.cpp", "listAPI.cpp", "shapingAPI.cpp", "shadowAPI.cpp",
            "lightFilter.cpp", "lightPortal.cpp", "rectLight.cpp",
            "sphereLight.cpp", "tokens.cpp"]

usd_lux_prj = prjs_default.copy()
usd_lux_prj["name"] = "usdLux"
usd_lux_prj["alias"] = "usd-usd-usdLux"
usd_lux_prj["srcs"] = _fpath("pxr/usd/lib/usdLux", usd_luxs)
usd_lux_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdLux"): excons.glob("pxr/usd/lib/usdLux/*.h")}
usd_lux_prj["libs"] = libs + ["tf", "vt", "sdf", "usd", "usdGeom"]

prjs.append(usd_lux_prj)
usds.append("usd-usd-usdLux")

# --------------------------------------------
#  usdShade
# --------------------------------------------

usd_shades = ["connectableAPI.cpp", "coordSysAPI.cpp", "input.cpp",
              "material.cpp", "materialBindingAPI.cpp", "output.cpp",
              "shader.cpp", "shaderDefParser.cpp", "shaderDefUtils.cpp",
              "nodeGraph.cpp", "tokens.cpp", "utils.cpp"]

usd_shade_prj = prjs_default.copy()
usd_shade_prj["name"] = "usdShade"
usd_shade_prj["alias"] = "usd-usd-usdShade"
usd_shade_prj["srcs"] = _fpath("pxr/usd/lib/usdShade", usd_shades)
usd_shade_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdShade"): excons.glob("pxr/usd/lib/usdShade/*.h")}
usd_shade_prj["libs"] = libs + ["arch", "tf", "vt", "ndr", "sdf", "ar", "sdr", "pcp", "trace", "work", "usd", "usdGeom"]

prjs.append(usd_shade_prj)
usds.append("usd-usd-usdShade")


# --------------------------------------------
#  usdRender
# --------------------------------------------

usd_renders = ["product.cpp", "settings.cpp", "settingsAPI.cpp",
               "settingsBase.cpp", "spec.cpp", "tokens.cpp", "var.cpp"]

usd_render_prj = prjs_default.copy()
usd_render_prj["name"] = "usdRender"
usd_render_prj["alias"] = "usd-usd-usdRender"
usd_render_prj["srcs"] = _fpath("pxr/usd/lib/usdRender", usd_renders)
usd_render_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdRender"): excons.glob("pxr/usd/lib/usdRender/*.h")}
usd_render_prj["libs"] = libs + ["arch", "gf", "tf", "vt", "sdf", "usd", "usdGeom"]

prjs.append(usd_render_prj)
usds.append("usd-usd-usdRender")

# --------------------------------------------
#  usdHydra
# --------------------------------------------

usd_hydras = ["tokens.cpp", "discoveryPlugin.cpp"]

usd_hydra_prj = prjs_default.copy()
usd_hydra_prj["name"] = "usdHydra"
usd_hydra_prj["alias"] = "usd-usd-usdHydra"
usd_hydra_prj["srcs"] = _fpath("pxr/usd/lib/usdHydra", usd_hydras)
usd_hydra_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdHydra"): excons.glob("pxr/usd/lib/usdHydra/*.h")}
usd_hydra_prj["libs"] = libs + ["ar", "tf", "ndr", "sdf", "plug", "usd", "usdShade"]

prjs.append(usd_hydra_prj)
usds.append("usd-usd-usdHydra")

# --------------------------------------------
#  usdRi (should be optional?)
# --------------------------------------------

usd_ris = ["lightAPI.cpp", "lightFilterAPI.cpp", "lightPortalAPI.cpp",
           "materialAPI.cpp", "pxrAovLight.cpp", "pxrBarnLightFilter.cpp",
           "pxrCookieLightFilter.cpp", "pxrEnvDayLight.cpp",
           "pxrIntMultLightFilter.cpp", "pxrRampLightFilter.cpp",
           "pxrRodLightFilter.cpp", "risBxdf.cpp", "risIntegrator.cpp",
           "risObject.cpp", "risOslPattern.cpp", "risPattern.cpp",
           "rmanUtilities.cpp", "rslShader.cpp", "splineAPI.cpp",
           "statementsAPI.cpp", "textureAPI.cpp", "tokens.cpp", "typeUtils.cpp"]

usd_ri_prj = prjs_default.copy()
usd_ri_prj["name"] = "usdRi"
usd_ri_prj["alias"] = "usd-usd-usdRi"
usd_ri_prj["srcs"] = _fpath("pxr/usd/lib/usdRi", usd_ris)
usd_ri_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdRi"): excons.glob("pxr/usd/lib/usdRi/*.h")}
usd_ri_prj["libs"] = libs + ["tf", "vt", "sdf", "usd", "usdShade", "usdGeom", "usdLux"]

prjs.append(usd_ri_prj)
usds.append("usd-usd-usdRi")

# --------------------------------------------
#  usdSkel
# --------------------------------------------

usd_skels = ["animation.cpp", "animMapper.cpp", "animQuery.cpp",
             "bakeSkinning.cpp", "bindingAPI.cpp", "blendShape.cpp",
             "blendShapeQuery.cpp", "cache.cpp", "debugCodes.cpp",
             "inbetweenShape.cpp", "packedJointAnimation.cpp", "root.cpp",
             "skeleton.cpp", "skeletonQuery.cpp", "skinningQuery.cpp",
             "tokens.cpp", "topology.cpp", "utils.cpp", "animQueryImpl.cpp",
             "cacheImpl.cpp", "skelDefinition.cpp"]

usd_skel_prj = prjs_default.copy()
usd_skel_prj["name"] = "usdSkel"
usd_skel_prj["alias"] = "usd-usd-usdSkel"
usd_skel_prj["srcs"] = _fpath("pxr/usd/lib/usdSkel", usd_skels)
usd_skel_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdSkel"): excons.glob("pxr/usd/lib/usdSkel/*.h")}
usd_skel_prj["libs"] = libs + ["arch", "gf", "tf", "trace", "vt", "work", "sdf", "usd", "usdGeom"]

prjs.append(usd_skel_prj)
usds.append("usd-usd-usdSkel")

# --------------------------------------------
#  usdUI (should be optional?)
# --------------------------------------------

usd_uis = ["backdrop.cpp", "nodeGraphNodeAPI.cpp", "sceneGraphPrimAPI.cpp",
           "tokens.cpp"]

usd_ui_prj = prjs_default.copy()
usd_ui_prj["name"] = "usdUI"
usd_ui_prj["alias"] = "usd-usd-usdUI"
usd_ui_prj["srcs"] = _fpath("pxr/usd/lib/usdUI", usd_uis)
usd_ui_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdUI"): excons.glob("pxr/usd/lib/usdUI/*.h")}
usd_ui_prj["libs"] = libs + ["tf", "vt", "sdf", "usd"]

prjs.append(usd_ui_prj)
usds.append("usd-usd-usdUI")

# --------------------------------------------
#  usdUtils
# --------------------------------------------

usd_uis = ["authoring.cpp", "coalescingDiagnosticDelegate.cpp",
           "debugCodes.cpp", "dependencies.cpp", "flattenLayerStack.cpp",
           "introspection.cpp", "pipeline.cpp", "registeredVariantSet.cpp",
           "sparseValueWriter.cpp", "stageCache.cpp", "stitch.cpp",
           "stitchClips.cpp", "timeCodeRange.cpp"]

usd_ui_prj = prjs_default.copy()
usd_ui_prj["name"] = "usdUtils"
usd_ui_prj["alias"] = "usd-usd-usdUtils"
usd_ui_prj["srcs"] = _fpath("pxr/usd/lib/usdUtils", usd_uis)
usd_ui_prj["install"] = {os.path.join(out_incdir, "pxr/usd/usdUtils"): excons.glob("pxr/usd/lib/usdUtils/*.h")}
usd_ui_prj["libs"] = libs + ["arch", "tf", "gf", "js", "vt", "pcp", "ar", "sdf", "plug", "trace", "kind", "work", "usd", "usdGeom"]

prjs.append(usd_ui_prj)
usds.append("usd-usd-usdUtils")


# excons.AddHelpOptions(USD="""USD OPTIONS
#   usd-static=0|1        : Toggle between static and shared library build [1]""")

# TODO : install resource files

targets = excons.DeclareTargets(env, prjs)

env.Alias("usd-base", bases)
env.Alias("usd-usd", usds)



# Export("UsdName UsdPath RequireUsd")
