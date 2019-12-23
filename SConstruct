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

build_viewer = excons.GetArgument("usd-view", 1, int) != 0
build_imaging = excons.GetArgument("usd-imaging", 0, int) != 0
support_python = excons.GetArgument("usd-python", 1, int) != 0
boost_static = excons.GetArgument("boost-static", 0, int) != 0
combine_pys = False

if not build_imaging:
    excons.WarnOnce("Building USD VIEW will be ignored beacuase building USD IMAGING off. If you want to build it please turn it on by 'usd-imaging=1' flag", tool="USD")
    build_viewer = False

if not support_python:
    excons.WarnOnce("Building USD VIEW will be ignored beacuase python binding off. If you want to build it please turn it on by 'usd-python=1' flag", tool="USD")
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
combine_pys = boost_static = 1
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
                  "PXR_PYTHON_SUPPORT_ENABLED": "1" if support_python else "0"}

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
if combine_pys:
    defs.append("USD_PY_AS_ONE_MODULE")

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
if support_python:
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

def _filterModuleCpps(srcs):
    new_srcs = []
    for x in srcs:
        if os.path.basename(x) in ["module.cpp", "moduleDeps.cpp"]:
            continue

        new_srcs.append(x)

    return new_srcs

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

    prj["srcs"] = srcs

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
combined_modules = []

def _addPyPrj(name, group, srcs, libs=None, install=None, combinePys=False):
    srcdir = "pxr/{}/lib/{}".format(group, name)
    # TODO : get it from pxr macro
    pydir = "lib/python/pxr/{}{}".format(name[0].upper(), name[1:])
    pyfiles = {pydir: excons.glob(os.path.join(srcdir, "*.py"))}

    if install:
        pyfiles.update(install)

    if combinePys:
        combined_modules.append("{}{}".format(name[0].upper(), name[1:]))
        # TODO : generate each submodules in _usdCombined's initializing
        pyfiles[pydir].append(os.path.abspath("pxr/combined/_{}.py".format(name)))
        combined_srcs[name] = srcs
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
        prj["srcs"] = srcs

        if libs:
            prj["libs"] = prj["libs"] + libs

        prj["install"] = pyfiles

        prjs.append(prj)


pxr_lib_args = ["PUBLIC_CLASSES", "PUBLIC_HEADERS", "PRIVATE_CLASSES", "PRIVATE_HEADERS", "CPPFILES", "LIBRARIES", "INCLUDE_DIRS", "RESOURCE_FILES", "PYTHON_PUBLIC_CLASSES", "PYTHON_PRIVATE_CLASSES", "PYTHON_PUBLIC_HEADERS", "PYTHON_PRIVATE_HEADERS", "PYTHON_CPPFILES", "PYMODULE_CPPFILES", "PYMODULE_FILES", "PYSIDE_UI_FILES"]

def _buildLib(name, group, libs=None, install=None, buildPython=False):
    lines = []
    dirname = os.path.abspath("pxr/{}/lib/{}".format(group, name))
    cmakefile = "{}/CMakeLists.txt".format(dirname)

    with open(cmakefile, "r") as f:
        lines = f.read().split("\n")

    re_lib_st = re.compile("pxr_library[(]{}".format(name))
    re_lib_end = re.compile("[)]")

    defs = {}
    cur = None

    in_def = False
    for l in lines:
        l = l.strip()
        if l.startswith("#"):
            continue

        if re_lib_st.search(l):
            in_def = True

        if not in_def:
            continue

        if re_lib_end.search(l):
            in_def = False

        if not in_def:
            continue

        ar = None
        for a in pxr_lib_args:
            if a == l:
                ar = a
                break
        if ar:
            cur = []
            defs[ar] = cur
            continue

        if cur is None or not l:
            continue

        cur.append(l)

    cpps = map(lambda x: os.path.join(dirname, x + ".cpp"), defs.get("PUBLIC_CLASSES", []) + defs.get("PRIVATE_CLASSES", []))
    cpps += map(lambda x: os.path.join(dirname, x), defs.get("CPPFILES", []))

    # TODO : install resource files
    # TODO : install header files
    # TODO : install python files

    if not buildPython:
        _addPrj(name, group, cpps, libs=libs, install=install)
    else:
        cpps += map(lambda x: os.path.join(dirname, x + ".cpp"), defs.get("PYTHON_PUBLIC_CLASSES", []) + defs.get("PYTHON_PRIVATE_CLASSES", []))
        cpps += map(lambda x: os.path.join(dirname, x), defs.get("PYTHON_CPPFILES", []))
        pycpps = map(lambda x: os.path.join(dirname, x), defs.get("PYMODULE_CPPFILES", []))
        if combine_pys:
            cpps = _filterModuleCpps(cpps)
            pycpps = _filterModuleCpps(pycpps)

        _addPrj(name, group, cpps, libs=libs, install=install)
        _addPyPrj(name, group, pycpps, libs=(libs + [name]) if libs else [name], combinePys=combine_pys)


# ============================================
#  base
# ============================================

_buildLib("arch",
          "base",
          buildPython=support_python)

_buildLib("tf",
          "base",
          libs=["arch"],
          install={os.path.join(out_incdir, "pxr/base/tf/pxrDoubleConversion"): excons.glob("pxr/base/lib/tf/pxrDoubleConversion/*.h"),
                 os.path.join(out_incdir, "pxr/base/tf/pxrLZ4"): excons.glob("pxr/base/lib/tf/pxrLZ4/*.h")},
          buildPython=support_python)

_buildLib("gf",
          "base",
          libs=["arch", "tf"],
          buildPython=support_python)

_buildLib("js",
          "base",
          libs=["arch", "tf"],
          install={os.path.join(out_incdir, "pxr/base/js/rapidjson"): excons.glob("pxr/base/lib/js/rapidjson/*")},
          buildPython=support_python)

_buildLib("trace",
          "base",
          libs=["arch", "tf", "js"],
          buildPython=support_python)

_buildLib("work",
          "base",
          libs=["tf", "trace"],
          buildPython=support_python)

_buildLib("plug",
          "base",
          libs=["arch", "tf", "trace", "js", "work"],
          buildPython=support_python)

_buildLib("vt",
          "base",
          libs=["arch", "tf", "gf", "trace"],
          buildPython=support_python)

# ============================================
#  usd
# ============================================

_buildLib("ar",
          "usd",
          libs=["arch", "tf", "js", "plug", "vt"],
          buildPython=support_python)

_buildLib("kind",
          "usd",
          libs=["arch", "tf", "js", "plug"],
          buildPython=support_python)

_buildLib("sdf",
          "usd",
          libs=["arch", "tf", "gf", "js", "trace", "vt", "work", "plug", "ar"],
          buildPython=support_python)

_buildLib("ndr",
          "usd",
          libs=["arch", "tf", "work", "plug", "vt", "ar", "sdf"],
          buildPython=support_python)

_buildLib("sdr",
          "usd",
          libs=["arch", "tf", "gf", "vt", "ar", "ndr", "sdf"],
          buildPython=support_python)

_buildLib("pcp",
          "usd",
          libs=["arch", "tf", "trace", "work", "vt", "ar", "sdf"],
          buildPython=support_python)

_buildLib("usd",
          "usd",
          libs=["arch", "tf", "gf", "js", "trace", "work", "plug", "vt", "ar", "kind", "sdf", "pcp"],
          buildPython=support_python)

_buildLib("usdGeom",
          "usd",
          libs=["arch", "tf", "gf", "js", "trace", "work", "plug", "vt", "kind", "sdf", "usd"],
          buildPython=support_python)

_buildLib("usdVol",
          "usd",
          libs=["tf", "sdf", "usd", "usdGeom"],
          buildPython=support_python)

_buildLib("usdLux",
          "usd",
          libs=["tf", "vt", "sdf", "usd", "usdGeom"],
          buildPython=support_python)

_buildLib("usdShade",
          "usd",
          libs=["arch", "tf", "trace", "work", "vt", "ar", "ndr", "sdr", "sdf", "pcp", "usd", "usdGeom"],
          buildPython=support_python)

_buildLib("usdRender",
          "usd",
          libs=["arch", "tf", "gf", "vt", "sdf", "usd", "usdGeom"],
          buildPython=support_python)

_buildLib("usdHydra",
          "usd",
          libs=["ar", "tf", "plug", "ndr", "sdf", "usd", "usdShade"],
          buildPython=support_python)

_buildLib("usdRi",
          "usd",
          libs=["tf", "vt", "sdf", "usd", "usdGeom", "usdShade", "usdLux"],
          buildPython=support_python)

_buildLib("usdSkel",
          "usd",
          libs=["arch", "tf", "gf", "trace", "work", "vt", "sdf", "usd", "usdGeom"],
          buildPython=support_python)

_buildLib("usdUI",
          "usd",
          libs=["tf", "vt", "sdf", "usd"],
          buildPython=support_python)

_buildLib("usdUtils",
          "usd",
          libs=["arch", "tf", "gf", "js", "trace", "plug", "work", "vt", "ar", "sdf", "pcp", "kind", "usd", "usdGeom"],
          buildPython=support_python)

# --------------------------------------------
#  combined module
# --------------------------------------------
def GenPy(target, source, env):
    tgt = target[0].get_abspath()
    dgt = os.path.dirname(tgt)
    if not os.path.isdir(dgt):
        os.makedirs(dgt)

    with open(tgt, "w") as f:
        f.write("__all__ = {}".format(str(combined_modules)))
        pass

if support_python and combine_pys:
    combined_srcs["combined"] = ["pxr/combined/combined.cpp"]
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


targets = excons.DeclareTargets(env, prjs)
for k, v in groups.items():
    env.Alias(k, v)


# Export("UsdName UsdPath RequireUsd")
