import sys
import os
import excons
from excons.tools import boost
from excons.tools import python
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
build_python = True
boost_static = excons.GetArgument("boost-static", 0, int) != 0

if not build_imaging:
    excons.WarnOnce("Building USD VIEW will be ignored beacuase building USD IMAGING off. If you want to build it please turn it on by 'usd-imaging=1' flag", tool="USD")
    build_viewer = False

py_v = excons.GetArgument("with-python")
if not py_v:
    build_python = False
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

RequireBoost = boost.Require(libs=["program_options"])
RequireBoostPy = boost.Require(libs=["python"])

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

# TODO : add this to each dependencies
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
pydefs = ["BOOST_PYTHON_NO_PY_SIGNATURES"]

if sys.platform != "win32":
    flags += " -std=c++11 -Wall -pthread -Wno-deprecated -Wno-deprecated-declarations -Wno-unused-local-typedefs -Wno-unused-parameter"
    flags += " -Wno-missing-field-initializers"
    if sys.platform == "darwin":
        flags += " -Wno-unused-command-line-argument"
        flags += " -Wno-expansion-to-defined"
        flags += " -Wno-undefined-var-template"
        flags += " -Wno-unused-function"
        flags += " -Wno-unused-variable"
        flags += " -Wno-unneeded-internal-declaration"
        flags += " -Wno-potentially-evaluated-expression"
        flags += " -Wno-instantiation-after-specialization"
        flags += " -Wno-inconsistent-missing-override"
        flags += " -Wno-unused-private-field"
        flags += " -Wno-unused-lambda-capture"
        flags += " -Wno-format"
        flags += " -Wno-self-assign-overloaded"
    else:
        flags += " -Wno-ignored-qualifiers"
        flags += " -Wno-extra"
        flags += " -Wno-type-limits"

else:
    defs += ["_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS", "NOMINMAX", "YY_NO_UNISTD_H"]
    flags += " /EHsc /Zc:rvalueCast /Zc:strictStrings /Zc:inline /W3"
    flags += " /wd4244 /wd4305 /wd4267 /wd4506 /wd4091 /wd4273 /wd4180 /wd4334"
    flags += " /bigobj /Zi /MP /Gm-"
    # /IGNORE:4221

libs = []
if sys.platform != "win32":
    libs.append("m")
else:
    # TODO
    libs += []

customs = [RequireBoost, RequireTBB]
if build_python:
    customs += [RequireBoostPy, python.SoftRequire]

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
py_default = {"type": "dynamicmodule",
              "defs": defs + pydefs,
              "ext": python.ModuleExtension(),
              "cppflags": flags,
              "incdirs": [out_incdir, boost_inc],
              "libdirs": [out_libdir],
              "rpath": out_libdir,
              "libs": libs,
              "symvis": "default",
              "custom": customs + [RequireBoostPy]}

def _fpath(directory, filePaths):
    return map(lambda x: os.path.join(directory, x), filePaths)

def _addDefs(name, currentDefs):
    return ["{}_EXPORTS=1".format(name.upper()), "{}_EXPORTS".format(name)] + currentDefs

def _addPyDefs(name, currentDefs):
    return ["MFB_PACKAGE_NAME={}".format(name), "MFB_ALT_PACKAGE_NAME={}".format(name), "MFB_PACKAGE_MODULE={}{}".format(name[0].upper(), name[1:])] + _addDefs(name, currentDefs)

# TODO
# PXR_PLUGINPATH_NAME
# PXR_BUILD_LOCATION
# PXR_PLUGIN_BUILD_LOCATION

groups = {}

def _addPrj(name, group, srcs, libs=None, install=None):
    alias = "usd-{}-{}".format(group, name)
    grpname = "usd-{}".format(group)
    if grpname not in groups:
        groups[grpname] = []
    groups[grpname].append(alias)

    prj = prjs_default.copy()
    prj["name"] = name
    prj["alias"] = alias
    prj["defs"] = _addDefs(name, prj["defs"])

    srcdir = "pxr/{}/lib/{}".format(group, name)
    prj["srcs"] = map(lambda x: os.path.join(srcdir, x), srcs)

    if libs:
        prj["libs"] = prj["libs"] + libs

    headers = {os.path.join(out_incdir, "pxr/{}/{}".format(group, name)): excons.glob("pxr/{}/lib/{}/*.h".format(group, name))}
    if install:
        headers.update(install)

    prj["install"] = headers

    prjs.append(prj)

combined_srcs = {}
combined_install = {}
combined_defs = []
combined_libs = []

def _addPyPrj(name, group, srcs, libs=None, install=None):
    if boost_static:
        srcs = filter(lambda x: x not in ["module.cpp", "moduleDeps.cpp"], srcs)

    srcdir = "pxr/{}/lib/{}".format(group, name)
    srcfiles = map(lambda x: os.path.join(srcdir, x), srcs)
    pydir = "lib/python/pxr/{}{}".format(name[0].upper(), name[1:])
    pyfiles = {pydir: excons.glob(os.path.join(srcdir, "*.py"))}

    if install:
        pyfiles.update(install)

    if boost_static:
        pyfiles[pydir].append(os.path.abspath("pxr/combined/_{}.py".format(name)))
        combined_srcs[name] = srcfiles
        combined_install.update(pyfiles)
        combined_defs.extend(_addDefs(name, []))
        if libs:
            combined_libs.extend(libs)

    else:
        alias = "usd-py-{}-{}".format(group, name)
        grpname = "usd-py-{}".format(group)

        if grpname not in groups:
            groups[grpname] = []
        groups[grpname].append(alias)

        prj = py_default.copy()
        prj["name"] = "_" + name
        prj["alias"] = alias
        prj["defs"] = _addPyDefs(name, prj["defs"])
        prj["prefix"] = pydir
        prj["srcs"] = srcfiles

        if libs:
            prj["libs"] = prj["libs"] + libs

        prj["install"] = pyfiles

        prjs.append(prj)

# ============================================
#  base
# ============================================

# --------------------------------------------
#  arch
# --------------------------------------------
archs = ["assumptions.cpp", "attributes.cpp", "daemon.cpp", "debugger.cpp",
         "demangle.cpp", "env.cpp", "errno.cpp", "error.cpp", "fileSystem.cpp",
         "function.cpp", "hash.cpp", "initConfig.cpp", "library.cpp",
         "mallocHook.cpp", "regex.cpp", "stackTrace.cpp", "symbols.cpp",
         "systemInfo.cpp", "threads.cpp", "timing.cpp", "virtualMemory.cpp",
         "vsnprintf.cpp"]

_addPrj("arch", "base", archs)

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

_addPrj("tf",
        "base",
        tfs,
        libs=["arch"],
        install={os.path.join(out_incdir, "pxr/base/tf/pxrDoubleConversion"): excons.glob("pxr/base/lib/tf/pxrDoubleConversion/*.h"),
                 os.path.join(out_incdir, "pxr/base/tf/pxrLZ4"): excons.glob("pxr/base/lib/tf/pxrLZ4/*.h")})

tf_pys = ["makePyConstructor.cpp", "pyAnnotatedBoolResult.cpp", "pyArg.cpp",
          "pyCall.cpp", "pyCallContext.cpp", "pyClassMethod.cpp",
          "pyContainerConversions.cpp", "pyEnum.cpp", "pyError.cpp",
          "pyExceptionState.cpp", "pyFunction.cpp", "pyIdentity.cpp",
          "pyInterpreter.cpp", "pyModule.cpp", "pyModuleNotice.cpp",
          "pyNoticeWrapper.cpp", "pyObjectFinder.cpp", "pyObjWrapper.cpp",
          "pyOptional.cpp", "pyOverride.cpp", "pyPolymorphic.cpp",
          "pyPtrHelpers.cpp", "pyResultConversions.cpp", "pySingleton.cpp",
          "pyTracing.cpp", "pyUtils.cpp", "pyWeakObject.cpp",
          "pyWrapContext.cpp", "scriptModuleLoader.cpp", "wrapTypeHelpers.cpp",
          "pyErrorInternal.cpp", "wrapAnyWeakPtr.cpp", "wrapCallContext.cpp",
          "wrapDebug.cpp", "wrapDiagnostic.cpp", "wrapDiagnosticBase.cpp",
          "wrapEnum.cpp", "wrapEnvSetting.cpp", "wrapError.cpp",
          "wrapFileUtils.cpp", "wrapFunction.cpp", "wrapMallocTag.cpp",
          "wrapNotice.cpp", "wrapPathUtils.cpp",
          "wrapPyContainerConversions.cpp", "wrapPyModuleNotice.cpp",
          "wrapPyObjWrapper.cpp", "wrapPyOptional.cpp", "wrapRefPtrTracker.cpp",
          "wrapScopeDescription.cpp", "wrapScriptModuleLoader.cpp",
          "wrapSingleton.cpp", "wrapStackTrace.cpp", "wrapStatus.cpp",
          "wrapStopwatch.cpp", "wrapStringUtils.cpp", "wrapTemplateString.cpp",
          "wrapTestPyAnnotatedBoolResult.cpp",
          "wrapTestPyContainerConversions.cpp", "wrapTestPyStaticTokens.cpp",
          "wrapTestTfPython.cpp", "wrapTestTfPyOptional.cpp", "wrapToken.cpp",
          "wrapType.cpp", "wrapWarning.cpp", "module.cpp", "moduleDeps.cpp"]

if build_python:
    _addPyPrj("tf", "base", tf_pys, libs=["tf"])

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

_addPrj("gf", "base", gfs, libs=["arch", "tf"])

gf_pys = ["pyBufferUtils.cpp", "moduleDeps.cpp", "module.cpp", "wrapBBox3d.cpp",
          "wrapCamera.cpp", "wrapFrustum.cpp", "wrapGamma.cpp", "wrapHalf.cpp",
          "wrapHomogeneous.cpp", "wrapInterval.cpp", "wrapLimits.cpp",
          "wrapLine.cpp", "wrapLineSeg.cpp", "wrapMath.cpp", "wrapMatrix2d.cpp",
          "wrapMatrix2f.cpp", "wrapMatrix3f.cpp", "wrapMatrix3d.cpp",
          "wrapMatrix4f.cpp", "wrapMatrix4d.cpp", "wrapMultiInterval.cpp",
          "wrapPlane.cpp", "wrapQuaternion.cpp", "wrapQuatd.cpp",
          "wrapQuatf.cpp", "wrapQuath.cpp", "wrapRange1d.cpp",
          "wrapRange1f.cpp", "wrapRange2d.cpp", "wrapRange2f.cpp",
          "wrapRange3d.cpp", "wrapRange3f.cpp", "wrapRay.cpp", "wrapRect2i.cpp",
          "wrapRotation.cpp", "wrapSize2.cpp", "wrapSize3.cpp",
          "wrapTransform.cpp", "wrapVec2d.cpp", "wrapVec2f.cpp",
          "wrapVec2h.cpp", "wrapVec2i.cpp", "wrapVec3d.cpp", "wrapVec3f.cpp",
          "wrapVec3h.cpp", "wrapVec3i.cpp", "wrapVec4d.cpp", "wrapVec4f.cpp",
          "wrapVec4h.cpp", "wrapVec4i.cpp"]

if build_python:
    _addPyPrj("gf", "base", gf_pys, libs=["gf"])

# --------------------------------------------
#  js
# --------------------------------------------

jss = ["json.cpp", "value.cpp", "utils.cpp"]

_addPrj("js",
        "base",
        jss,
        libs=["arch", "tf"],
        install={os.path.join(out_incdir, "pxr/base/js/rapidjson"): excons.glob("pxr/base/lib/js/rapidjson/*")})

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

_addPrj("trace", "base", traces, libs=["arch", "tf", "js"])

trace_pys = ["moduleDeps.cpp", "module.cpp", "wrapAggregateNode.cpp",
             "wrapCollector.cpp", "wrapReporter.cpp", "wrapTestTrace.cpp"]

if build_python:
    _addPyPrj("trace", "base", trace_pys, libs=["trace"])

# --------------------------------------------
#  work
# --------------------------------------------

works = ["arenaDispatcher.cpp", "detachedTask.cpp", "dispatcher.cpp",
         "loops.cpp", "reduce.cpp", "singularTask.cpp", "threadLimits.cpp",
         "utils.cpp"]

_addPrj("work", "base", works, libs=["tf", "trace"])

work_pys = ["moduleDeps.cpp", "module.cpp", "wrapThreadLimits.cpp"]

if build_python:
    _addPyPrj("work", "base", work_pys, libs=["work"])

# --------------------------------------------
#  plug
# --------------------------------------------

plugs = ["interfaceFactory.cpp", "notice.cpp", "plugin.cpp", "registry.cpp",
         "staticInterface.cpp", "debugCodes.cpp", "info.cpp",
         "testPlugBase.cpp", "initConfig.cpp"]

_addPrj("plug", "base", plugs, libs=["arch", "tf", "js", "trace", "work"])

plug_pys = ["moduleDeps.cpp", "module.cpp", "wrapNotice.cpp", "wrapPlugin.cpp",
            "wrapRegistry.cpp", "wrapTestPlugBase.cpp"]

if build_python:
    _addPyPrj("plug", "base", plug_pys, libs=["plug"])

# --------------------------------------------
#  vt
# --------------------------------------------

vts = ["array.cpp", "dictionary.cpp", "functions.cpp", "hash.cpp",
       "streamOut.cpp", "types.cpp", "value.cpp"]

_addPrj("vt", "base", vts, libs=["arch", "tf", "gf", "trace"])

vt_pys = ["arrayPyBuffer.cpp", "valueFromPython.cpp", "wrapArray.cpp",
          "moduleDeps.cpp", "module.cpp", "wrapArrayBase.cpp",
          "wrapArrayFloat.cpp", "wrapArrayIntegral.cpp", "wrapArrayMatrix.cpp",
          "wrapArrayQuaternion.cpp", "wrapArrayRange.cpp",
          "wrapArrayString.cpp", "wrapArrayToken.cpp", "wrapArrayVec.cpp",
          "wrapDictionary.cpp", "wrapValue.cpp"]

if build_python:
    _addPyPrj("vt", "base", vt_pys, libs=["vt"])

# ============================================
#  usd
# ============================================

# --------------------------------------------
#  ar
# --------------------------------------------

ars = ["asset.cpp", "assetInfo.cpp", "filesystemAsset.cpp",
       "packageResolver.cpp", "packageUtils.cpp", "resolver.cpp",
       "resolverContext.cpp", "resolverContextBinder.cpp",
       "resolverScopedCache.cpp", "debugCodes.cpp", "defaultResolver.cpp",
       "defaultResolverContext.cpp"]

_addPrj("ar", "usd", ars, libs=["arch", "tf", "plug", "vt", "js"])

ar_pys = ["pyResolverContext.cpp", "moduleDeps.cpp", "module.cpp",
          "wrapDefaultResolver.cpp", "wrapDefaultResolverContext.cpp",
          "wrapPackageUtils.cpp", "wrapResolver.cpp", "wrapResolverContext.cpp",
          "wrapResolverContextBinder.cpp", "wrapResolverScopedCache.cpp"]

if build_python:
    _addPyPrj("ar", "usd", ar_pys, libs=["ar"])

# --------------------------------------------
#  kind
# --------------------------------------------

kinds = ["registry.cpp"]

_addPrj("kind", "usd", kinds, libs=["arch", "js", "tf", "plug"])

kind_pys = ["moduleDeps.cpp", "module.cpp", "wrapRegistry.cpp", "wrapTokens.cpp"]

if build_python:
    _addPyPrj("kind", "usd", kind_pys, libs=["kind"])

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

_addPrj("sdf", "usd", sdfs, libs=["arch", "tf", "gf", "trace", "vt", "work", "ar", "js", "plug"])

sdf_pys = ["pyChildrenProxy.cpp", "pyChildrenView.cpp", "pyListEditorProxy.cpp",
           "pyListOp.cpp", "pyListProxy.cpp", "pyMapEditProxy.cpp",
           "pySpec.cpp", "pyUtils.cpp", "moduleDeps.cpp", "module.cpp",
           "wrapArrayAssetPath.cpp", "wrapArrayTimeCode.cpp",
           "wrapAssetPath.cpp", "wrapAttributeSpec.cpp", "wrapChangeBlock.cpp",
           "wrapCleanupEnabler.cpp", "wrapCopyUtils.cpp", "wrapFileFormat.cpp",
           "wrapLayer.cpp", "wrapLayerOffset.cpp", "wrapLayerTree.cpp",
           "wrapNamespaceEdit.cpp", "wrapNotice.cpp", "wrapPath.cpp",
           "wrapPayload.cpp", "wrapPrimSpec.cpp", "wrapPropertySpec.cpp",
           "wrapPseudoRootSpec.cpp", "wrapRelationshipSpec.cpp",
           "wrapReference.cpp", "wrapSpec.cpp", "wrapTimeCode.cpp",
           "wrapTypes.cpp", "wrapValueTypeName.cpp", "wrapVariantSpec.cpp",
           "wrapVariantSetSpec.cpp"]

if build_python:
    _addPyPrj("sdf", "usd", sdf_pys, libs=["sdf"])

# --------------------------------------------
#  ndr
# --------------------------------------------

ndrs = ["debugCodes.cpp", "declare.cpp", "discoveryPlugin.cpp",
        "filesystemDiscovery.cpp", "filesystemDiscoveryHelpers.cpp",
        "node.cpp", "parserPlugin.cpp", "property.cpp", "registry.cpp"]

_addPrj("ndr", "usd", ndrs, libs=["arch", "tf", "plug", "vt", "work", "ar", "sdf"])

ndr_pys = ["moduleDeps.cpp", "module.cpp", "wrapDeclare.cpp",
           "wrapDiscoveryPlugin.cpp", "wrapFilesystemDiscovery.cpp",
           "wrapFilesystemDiscoveryHelpers.cpp", "wrapNode.cpp",
           "wrapNodeDiscoveryResult.cpp", "wrapProperty.cpp",
           "wrapRegistry.cpp"]

if build_python:
    _addPyPrj("ndr", "usd", ndr_pys, libs=["ndr"])

# --------------------------------------------
#  sdr
# --------------------------------------------

sdrs = ["registry.cpp", "shaderMetadataHelpers.cpp", "shaderNode.cpp",
        "shaderProperty.cpp"]

_addPrj("sdr", "usd", sdrs, libs=["arch", "tf", "vt", "ar", "ndr", "sdf", "gf"])

sdr_pys = ["moduleDeps.cpp", "module.cpp", "wrapRegistry.cpp",
           "wrapShaderNode.cpp", "wrapShaderProperty.cpp"]

if build_python:
    _addPyPrj("sdr", "usd", sdr_pys, libs=["sdr"])

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

_addPrj("pcp", "usd", pcps, libs=["arch", "tf", "trace", "vt", "sdf", "work", "ar"])

pcp_pys = ["pyUtils.cpp", "moduleDeps.cpp", "module.cpp", "wrapCache.cpp",
           "wrapDependency.cpp", "wrapDynamicFileFormatDependencyData.cpp",
           "wrapErrors.cpp", "wrapInstanceKey.cpp", "wrapPrimIndex.cpp",
           "wrapLayerStack.cpp", "wrapLayerStackIdentifier.cpp",
           "wrapMapExpression.cpp", "wrapMapFunction.cpp", "wrapNode.cpp",
           "wrapPathTranslation.cpp", "wrapPropertyIndex.cpp", "wrapSite.cpp",
           "wrapTestChangeProcessor.cpp", "wrapTypes.cpp"]

if build_python:
    _addPyPrj("pcp", "usd", pcp_pys, libs=["pcp"])

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

_addPrj("usd", "usd", usds, libs=["arch", "kind", "pcp", "sdf", "ar", "plug", "tf", "js", "gf", "trace", "vt", "work"])

usd_pys = ["pyEditContext.cpp", "pyConversions.cpp", "moduleDeps.cpp",
           "module.cpp", "wrapAPISchemaBase.cpp", "wrapAttribute.cpp",
           "wrapAttributeQuery.cpp", "wrapClipsAPI.cpp",
           "wrapCollectionAPI.cpp", "wrapCollectionMembershipQuery.cpp",
           "wrapCommon.cpp", "wrapCrateInfo.cpp", "wrapEditContext.cpp",
           "wrapEditTarget.cpp", "wrapFlattenUtils.cpp", "wrapInherits.cpp",
           "wrapInterpolation.cpp", "wrapModelAPI.cpp", "wrapNotice.cpp",
           "wrapObject.cpp", "wrapPayloads.cpp", "wrapPrim.cpp",
           "wrapPrimCompositionQuery.cpp", "wrapPrimFlags.cpp",
           "wrapPrimRange.cpp", "wrapProperty.cpp", "wrapReferences.cpp",
           "wrapRelationship.cpp", "wrapResolveInfo.cpp", "wrapSchemaBase.cpp",
           "wrapSchemaRegistry.cpp", "wrapSpecializes.cpp", "wrapStage.cpp",
           "wrapStageCache.cpp", "wrapStageCacheContext.cpp",
           "wrapStageLoadRules.cpp", "wrapStagePopulationMask.cpp",
           "wrapTokens.cpp", "wrapTimeCode.cpp", "wrapTyped.cpp",
           "wrapUtils.cpp", "wrapVariantSets.cpp", "wrapVersion.cpp",
           "wrapZipFile.cpp"]

if build_python:
    _addPyPrj("usd", "usd", usd_pys, libs=["usd"])

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

_addPrj("usdGeom", "usd", usd_geoms, libs=["arch", "js", "tf", "gf", "plug", "vt", "sdf", "trace", "usd", "work", "kind"])

usd_geom_pys = ["moduleDeps.cpp", "module.cpp", "wrapBBoxCache.cpp",
                "wrapBasisCurves.cpp", "wrapBoundable.cpp", "wrapCamera.cpp",
                "wrapConstraintTarget.cpp", "wrapCapsule.cpp", "wrapCone.cpp",
                "wrapCube.cpp", "wrapCurves.cpp", "wrapCylinder.cpp",
                "wrapGprim.cpp", "wrapImageable.cpp", "wrapMesh.cpp",
                "wrapMetrics.cpp", "wrapModelAPI.cpp", "wrapMotionAPI.cpp",
                "wrapNurbsCurves.cpp", "wrapNurbsPatch.cpp",
                "wrapPointBased.cpp", "wrapPointInstancer.cpp",
                "wrapPoints.cpp", "wrapPrimvar.cpp", "wrapPrimvarsAPI.cpp",
                "wrapScope.cpp", "wrapSphere.cpp", "wrapSubset.cpp",
                "wrapTokens.cpp", "wrapXform.cpp", "wrapXformCache.cpp",
                "wrapXformable.cpp", "wrapXformOp.cpp",
                "wrapXformCommonAPI.cpp"]

if build_python:
    _addPyPrj("usdGeom", "usd", usd_geom_pys, libs=["usdGeom"])

# --------------------------------------------
#  usdVol
# --------------------------------------------

usd_vols = ["volume.cpp", "fieldBase.cpp", "fieldAsset.cpp", "field3DAsset.cpp",
            "openVDBAsset.cpp", "tokens.cpp"]

_addPrj("usdVol", "usd", usd_vols, libs=["tf", "sdf", "usd", "usdGeom"])

usd_vol_pys = ["moduleDeps.cpp", "module.cpp", "wrapVolume.cpp",
               "wrapFieldBase.cpp", "wrapFieldAsset.cpp",
               "wrapField3DAsset.cpp", "wrapOpenVDBAsset.cpp", "wrapTokens.cpp"]

if build_python:
    _addPyPrj("usdVol", "usd", usd_vol_pys, libs=["usdVol"])

# --------------------------------------------
#  usdLux
# --------------------------------------------

usd_luxs = ["blackbody.cpp", "cylinderLight.cpp", "diskLight.cpp",
            "distantLight.cpp", "domeLight.cpp", "geometryLight.cpp",
            "light.cpp", "listAPI.cpp", "shapingAPI.cpp", "shadowAPI.cpp",
            "lightFilter.cpp", "lightPortal.cpp", "rectLight.cpp",
            "sphereLight.cpp", "tokens.cpp"]

_addPrj("usdLux", "usd", usd_luxs, libs=["tf", "vt", "sdf", "usd", "usdGeom"])

usd_lux_pys = ["module.cpp", "wrapCylinderLight.cpp", "wrapDiskLight.cpp",
               "wrapDistantLight.cpp", "wrapDomeLight.cpp",
               "wrapLightPortal.cpp", "wrapGeometryLight.cpp", "wrapLight.cpp",
               "wrapListAPI.cpp", "wrapShapingAPI.cpp", "wrapShadowAPI.cpp",
               "wrapLightFilter.cpp", "wrapRectLight.cpp",
               "wrapSphereLight.cpp", "wrapTokens.cpp", "moduleDeps.cpp"]

if build_python:
    _addPyPrj("usdLux", "usd", usd_lux_pys, libs=["usdLux"])

# --------------------------------------------
#  usdShade
# --------------------------------------------

usd_shades = ["connectableAPI.cpp", "coordSysAPI.cpp", "input.cpp",
              "material.cpp", "materialBindingAPI.cpp", "output.cpp",
              "shader.cpp", "shaderDefParser.cpp", "shaderDefUtils.cpp",
              "nodeGraph.cpp", "tokens.cpp", "utils.cpp"]

_addPrj("usdShade", "usd", usd_shades, libs=["arch", "tf", "vt", "ndr", "sdf", "ar", "sdr", "pcp", "trace", "work", "usd", "usdGeom"])

usd_shade_pys = ["moduleDeps.cpp", "module.cpp", "wrapConnectableAPI.cpp",
                 "wrapCoordSysAPI.cpp", "wrapInput.cpp", "wrapMaterial.cpp",
                 "wrapMaterialBindingAPI.cpp", "wrapOutput.cpp",
                 "wrapShader.cpp", "wrapShaderDefParser.cpp",
                 "wrapShaderDefUtils.cpp", "wrapNodeGraph.cpp",
                 "wrapTokens.cpp", "wrapUtils.cpp"]

if build_python:
    _addPyPrj("usdShade", "usd", usd_shade_pys, libs=["usdShade"])

# --------------------------------------------
#  usdRender
# --------------------------------------------

usd_renders = ["product.cpp", "settings.cpp", "settingsAPI.cpp",
               "settingsBase.cpp", "spec.cpp", "tokens.cpp", "var.cpp"]

_addPrj("usdRender", "usd", usd_renders, libs=["arch", "gf", "tf", "vt", "sdf", "usd", "usdGeom"])

usd_render_pys = ["moduleDeps.cpp", "module.cpp", "wrapProduct.cpp", "wrapSettingsAPI.cpp", "wrapSettingsBase.cpp", "wrapSettings.cpp", "wrapTokens.cpp", "wrapVar.cpp"]

if build_python:
    _addPyPrj("usdRender", "usd", usd_render_pys, libs=["usdRender"])

# --------------------------------------------
#  usdHydra
# --------------------------------------------

usd_hydras = ["tokens.cpp", "discoveryPlugin.cpp"]

_addPrj("usdHydra", "usd", usd_hydras, libs=["ar", "tf", "ndr", "sdf", "plug", "usd", "usdShade"])

usd_hydra_pys = ["moduleDeps.cpp", "module.cpp", "wrapTokens.cpp"]

if build_python:
    _addPyPrj("usdHydra", "usd", usd_hydra_pys, libs=["usdHydra"])

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

_addPrj("usdRi", "usd", usd_ris, libs=["tf", "vt", "sdf", "usd", "usdShade", "usdGeom", "usdLux"])

usd_ri_pys = ["moduleDeps.cpp", "module.cpp", "wrapLightAPI.cpp",
              "wrapLightFilterAPI.cpp", "wrapLightPortalAPI.cpp",
              "wrapMaterialAPI.cpp", "wrapPxrAovLight.cpp",
              "wrapPxrBarnLightFilter.cpp", "wrapPxrCookieLightFilter.cpp",
              "wrapPxrEnvDayLight.cpp", "wrapPxrIntMultLightFilter.cpp",
              "wrapPxrRampLightFilter.cpp", "wrapPxrRodLightFilter.cpp",
              "wrapRisBxdf.cpp", "wrapRisIntegrator.cpp", "wrapRisObject.cpp",
              "wrapRisOslPattern.cpp", "wrapRisPattern.cpp",
              "wrapRmanUtilities.cpp", "wrapRslShader.cpp", "wrapSplineAPI.cpp",
              "wrapStatementsAPI.cpp", "wrapTextureAPI.cpp", "wrapTokens.cpp"]

if build_python:
    _addPyPrj("usdRi", "usd", usd_ri_pys, libs=["usdRi"])

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

_addPrj("usdSkel", "usd", usd_skels, libs=["arch", "gf", "tf", "trace", "vt", "work", "sdf", "usd", "usdGeom"])

usd_skel_pys = ["moduleDeps.cpp", "module.cpp", "wrapAnimation.cpp",
                "wrapAnimMapper.cpp", "wrapAnimQuery.cpp",
                "wrapBakeSkinning.cpp", "wrapBlendShapeQuery.cpp",
                "wrapBinding.cpp", "wrapBindingAPI.cpp", "wrapBlendShape.cpp",
                "wrapCache.cpp", "wrapInbetweenShape.cpp",
                "wrapPackedJointAnimation.cpp", "wrapRoot.cpp",
                "wrapSkeleton.cpp", "wrapSkeletonQuery.cpp",
                "wrapSkinningQuery.cpp", "wrapTokens.cpp", "wrapTopology.cpp",
                "wrapUtils.cpp"]

if build_python:
    _addPyPrj("usdSkel", "usd", usd_skel_pys, libs=["usdSkel"])

# --------------------------------------------
#  usdUI (should be optional?)
# --------------------------------------------

usd_uis = ["backdrop.cpp", "nodeGraphNodeAPI.cpp", "sceneGraphPrimAPI.cpp",
           "tokens.cpp"]

_addPrj("usdUI", "usd", usd_uis, libs=["tf", "vt", "sdf", "usd"])

usd_ui_pys = ["moduleDeps.cpp", "module.cpp", "wrapBackdrop.cpp",
              "wrapNodeGraphNodeAPI.cpp", "wrapSceneGraphPrimAPI.cpp",
              "wrapTokens.cpp"]

if build_python:
    _addPyPrj("usdUI", "usd", usd_ui_pys, libs=["usdUI"])

# --------------------------------------------
#  usdUtils
# --------------------------------------------

usd_utils = ["authoring.cpp", "coalescingDiagnosticDelegate.cpp",
             "debugCodes.cpp", "dependencies.cpp", "flattenLayerStack.cpp",
             "introspection.cpp", "pipeline.cpp", "registeredVariantSet.cpp",
             "sparseValueWriter.cpp", "stageCache.cpp", "stitch.cpp",
             "stitchClips.cpp", "timeCodeRange.cpp"]

_addPrj("usdUtils", "usd", usd_utils, libs=["arch", "tf", "gf", "js", "vt", "pcp", "ar", "sdf", "plug", "trace", "kind", "work", "usd", "usdGeom"])

usd_util_pys = ["moduleDeps.cpp", "module.cpp", "wrapAuthoring.cpp",
                "wrapCoalescingDiagnosticDelegate.cpp", "wrapDependencies.cpp",
                "wrapFlattenLayerStack.cpp", "wrapIntrospection.cpp",
                "wrapPipeline.cpp", "wrapRegisteredVariantSet.cpp",
                "wrapSparseValueWriter.cpp", "wrapStageCache.cpp",
                "wrapStitch.cpp", "wrapStitchClips.cpp",
                "wrapTimeCodeRange.cpp"]

if build_python:
    _addPyPrj("usdUtils", "usd", usd_util_pys, libs=["usdUtils"])


# --------------------------------------------
#  combined module
# --------------------------------------------
def GenPy(target, source, env):
    tgt = target[0].get_abspath()
    dgt = os.path.dirname(tgt)
    if not os.path.isdir(dgt):
        os.makedirs(dgt)

    with open(tgt, "w") as wf:
        pass

if build_python and boost_static:
    combined_srcs["combined"] = ["pxr/combined/combined.cpp"]
    combined_defs.append("USD_PY_AS_ONE_MODULE")
    prj = py_default.copy()
    prj["name"] = "_usdCombined"
    prj["alias"] = "usd-py-combined"
    prj["defs"] = prj["defs"] + combined_defs
    prj["cppflags"] = prj["cppflags"] + " -Wno-macro-redefined"
    prj["prefix"] = "lib/python/pxr"
    prj["srcs"] = combined_srcs
    prj["incdirs"] = prj["incdirs"] + [os.path.abspath(".")]
    prj["libs"] = prj["libs"] + combined_libs
    prj["install"] = combined_install
    prj["deps"] = env.Command(os.path.join(out_libdir, "python/pxr/__init__.py"), "", GenPy)
    prjs.append(prj)


# excons.AddHelpOptions(USD="""USD OPTIONS
#   usd-static=0|1        : Toggle between static and shared library build [1]""")

# TODO : install resource files


targets = excons.DeclareTargets(env, prjs)
for k, v in groups.items():
    env.Alias(k, v)


# Export("UsdName UsdPath RequireUsd")
