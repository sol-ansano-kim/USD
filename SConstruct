import sys
import os
import excons
from excons.tools import boost
from excons.tools import python
from excons.tools import gl
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
build_imaging = excons.GetArgument("usd-imaging", 1, int) != 0
support_python = excons.GetArgument("usd-python", 1, int) != 0
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

# TODO : external?
tbb_static = excons.GetArgument("tbb-static", 1, int)
exr_static = excons.GetArgument("openexr-static", 1, int)
ocio_static = excons.GetArgument("ocio-static", 1, int)
osd_static = excons.GetArgument("osd-static", 1, int)
oiio_static = excons.GetArgument("oiio-static", 1, int)

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
    boost_inc = rv["incdir"]
    boost_root = os.path.dirname(boost_inc)
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
        ext_opts["openexr-static"] = exr_static
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
        ext_opts["ocio-static"] = ocio_static
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
        ext_opts["osd-static"] = osd_static
        excons.PrintOnce("USD: Build osd from sources ...")
        excons.cmake.AddConfigureDependencies("osd", out_tbb)
        excons.Call("OpenSubdiv", targets=["osd"], overrides=ext_opts, imp=["OsdCPUPath", "OsdGPUPath", "RequireOsdCPU", "RequireOsdGPU"])
        out_osd.append(OsdCPUPath(True))
        out_osd.append(OsdGPUPath(True))
        # TODO : support GPU?
        # TODO : RequireOsdCPU has to add linking of tbb if using static lib
    else:
        TODO()

    # --------------------------------------------
    #  oiio
    # --------------------------------------------

    rv = excons.ExternalLibRequire("oiio")
    if not rv["require"]:
        ext_opts["oiio-static"] = oiio_static
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

config_files = env.Command(os.path.join(out_incdir, "pxr/pxr.h"), os.path.abspath("pxr/pxr.h.in"), GenerateConfig)

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
linkflags = ""
defs = ["__TBB_NO_IMPLICIT_LINKAGE"]
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
                "linkflags": linkflags,
                "incdirs": [out_incdir, boost_inc],
                "libdirs": [out_libdir],
                "rpath": out_libdir,
                "libs": libs,
                "deps": config_files,
                "symvis": "default",
                "custom": customs}
py_default = {"type": "dynamicmodule",
              "defs": defs + pydefs,
              "ext": python.ModuleExtension(),
              "cppflags": flags,
              "linkflags": linkflags,
              "incdirs": [out_incdir, boost_inc],
              "libdirs": [out_libdir],
              "rpath": out_libdir,
              "libs": libs,
              "deps": config_files,
              "symvis": "default",
              "custom": customs + [RequireBoostPy]}
bin_default = prjs_default.copy()
bin_default["type"] = "program"
bin_default["custom"] = [RequireBoost, python.Require]

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

def _addPrj(name, group, srcs, libs=None, linkflags=None, customs=None, install=None):
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

    if install:
        prj["install"] = install

    if linkflags:
        prj["linkflags"] = linkflags + prj["linkflags"]

    if customs:
        prj["custom"] = prj["custom"] + customs

    prjs.append(prj)

combined_srcs = {}
combined_install = {}
combined_defs = []
combined_libs = []
combined_deps = []
combined_modules = []
combined_fake_pys = []

def GenSubmodule(target, source, env):
    tgt = target[0].get_abspath()
    dgt = os.path.dirname(tgt)
    if not os.path.isdir(dgt):
        os.makedirs(dgt)

    mod_name = os.path.splitext(os.path.basename(tgt))[0][1:]

    with open(tgt, "w") as f:
        f.write("import pxr._combined\n")
        f.write("lcls = locals()\n")
        f.write("for k, v in pxr._combined._{}.__dict__.items():\n".format(mod_name))
        f.write("    if k in [\"__module__\", \"__doc__\", \"__reduce__\", \"__init__\"]:\n")
        f.write("        continue\n")
        f.write("    lcls[k] = v\n")
        f.write("locals().pop(\"lcls\")\n")
        f.write("locals().pop(\"pxr\")\n")
        f.write("locals().pop(\"k\")\n")
        f.write("locals().pop(\"v\")\n")

def GenUIFile(target, source, env):
    tgt = target[0].get_abspath()
    src = source[0].get_abspath()
    dgt = os.path.dirname(tgt)
    if not os.path.isdir(dgt):
        os.makedirs(dgt)

    ui_name = os.path.basename(src).replace("UI.ui", "")
    ui_name = "{}{}".format(ui_name[0].upper(), ui_name[1:])

    with open(tgt, "w") as f:
        f.write("import Qt\n")
        f.write("import os\n")
        f.write("def Ui_{}(parent=None):\n".format(ui_name))
        f.write("  ui_file = os.path.splitext(__file__)[0] + \".ui\"\n")
        f.write("  return Qt.QtCompat.loadUi(ui_file, parent)\n")

def _addPyPrj(name, group, srcs, libs=None, linkflags=None, customs=None, install=None, uiFiles=None, combinePys=False):
    if not srcs:
        return

    srcdir = "pxr/{}/lib/{}".format(group, name)
    pydir = "lib/python/pxr/{}{}".format(name[0].upper(), name[1:])

    if combinePys:
        submod_name = "{}{}".format(name[0].upper(), name[1:])
        combined_modules.append(submod_name)
        combined_fake_pys.extend(env.Command(os.path.abspath(os.path.join(out_libdir, "python/pxr/{}/_{}.py").format(submod_name, name)), "", GenSubmodule))
        combined_srcs[name] = srcs
        if install:
            combined_install.update(install)
        combined_defs.extend(_addDefs(name, []))
        if libs:
            combined_libs.extend(libs)
        if uiFiles:
            combined_deps.extend(uiFiles)

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

        if install:
            prj["install"] = install

        if linkflags:
            prj["linkflags"] = prj["linkflags"] + linkflags

        if customs:
            prj["custom"] = prj["custom"] + customs

        if uiFiles:
            prj["deps"] = prj["deps"] + uiFiles

        prjs.append(prj)

pxr_lib_args = ["PUBLIC_CLASSES", "PUBLIC_HEADERS", "PRIVATE_CLASSES", "PRIVATE_HEADERS", "CPPFILES", "LIBRARIES", "INCLUDE_DIRS", "RESOURCE_FILES", "PYTHON_PUBLIC_CLASSES", "PYTHON_PRIVATE_CLASSES", "PYTHON_PUBLIC_HEADERS", "PYTHON_PRIVATE_HEADERS", "PYTHON_CPPFILES", "PYMODULE_CPPFILES", "PYMODULE_FILES", "PYSIDE_UI_FILES"]

def _addInstall(sources, dirname, prefix, result, suffix=None):
    for r in sources:
        pdirs = []
        pre = None
        if ":" in r:
            r, pp = r.split(":")
            pdirs.append(os.path.dirname(pp))

        if os.path.basename(r) != r:
            pdirs.insert(0, os.path.dirname(r))

        key = os.path.join(prefix, *pdirs)

        if key not in result:
            result[key] = []

        if suffix:
            r += suffix

        result[key].append(os.path.join(dirname, r))

def _resolveEnvs(srcs, envs):
    reenv = re.compile("\$\{([^}{$]+)\}")
    if not envs:
        return srcs

    new_srcs = []
    for src in srcs:
        if reenv.search(src):
            encd = {}
            for k in reenv.findall(src):
                src = src.replace("${" + k + "}", envs.get(k, ""))

        if not src:
            continue

        new_srcs.append(src)

    return new_srcs

def _buildLib(name, group, libs=None, linkflags=None, customs=None, buildPython=False, envs=None):
    if envs is None:
        envs = {}

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

    for k in defs.keys():
        defs[k] = _resolveEnvs(defs[k], envs)

    cpps = map(lambda x: os.path.join(dirname, x + ".cpp"), defs.get("PUBLIC_CLASSES", []) + defs.get("PRIVATE_CLASSES", []))
    cpps += map(lambda x: os.path.join(dirname, x), defs.get("CPPFILES", []))

    install = {}
    pyinstall = {}
    ui_files = []

    _addInstall(defs.get("PUBLIC_HEADERS", []), dirname, os.path.join(out_incdir, "pxr/{}/{}".format(group, name)), install)
    _addInstall(defs.get("PRIVATE_HEADERS", []), dirname, os.path.join(out_incdir, "pxr/{}/{}".format(group, name)), install)
    _addInstall(defs.get("PUBLIC_CLASSES", []), dirname, os.path.join(out_incdir, "pxr/{}/{}".format(group, name)), install, suffix=".h")
    _addInstall(defs.get("PRIVATE_CLASSES", []), dirname, os.path.join(out_incdir, "pxr/{}/{}".format(group, name)), install, suffix=".h")
    _addInstall(defs.get("RESOURCE_FILES", []), dirname, os.path.join(out_libdir, "usd/{}/resources".format(name)), install)

    if not buildPython:
        _addPrj(name, group, cpps, libs=libs, linkflags=linkflags, customs=customs, install=install)
    else:
        py_dest = os.path.join(out_libdir, "python/pxr/{}{}".format(name[0].upper(), name[1:]))
        _addInstall(defs.get("PYTHON_PUBLIC_HEADERS", []), dirname, os.path.join(out_incdir, "pxr/{}/{}".format(group, name)), install)
        _addInstall(defs.get("PYTHON_PRIVATE_HEADERS", []), dirname, os.path.join(out_incdir, "pxr/{}/{}".format(group, name)), install)
        _addInstall(defs.get("PYTHON_PUBLIC_CLASSES", []), dirname, os.path.join(out_incdir, "pxr/{}/{}".format(group, name)), install, suffix=".h")
        _addInstall(defs.get("PYTHON_PRIVATE_CLASSES", []), dirname, os.path.join(out_incdir, "pxr/{}/{}".format(group, name)), install, suffix=".h")
        _addInstall(defs.get("PYMODULE_FILES", []), dirname, py_dest, pyinstall)
        _addInstall(defs.get("PYSIDE_UI_FILES", []), dirname, py_dest, pyinstall)

        for ui in defs.get("PYSIDE_UI_FILES", []):
            ui_py = os.path.splitext(ui)[0] + ".py"
            ui_files += env.Command(os.path.join(py_dest, ui_py), os.path.join(dirname, ui), GenUIFile)

        cpps += map(lambda x: os.path.join(dirname, x + ".cpp"), defs.get("PYTHON_PUBLIC_CLASSES", []) + defs.get("PYTHON_PRIVATE_CLASSES", []))
        cpps += map(lambda x: os.path.join(dirname, x), defs.get("PYTHON_CPPFILES", []))
        pycpps = map(lambda x: os.path.join(dirname, x), defs.get("PYMODULE_CPPFILES", []))
        if combine_pys:
            cpps = _filterModuleCpps(cpps)
            pycpps = _filterModuleCpps(pycpps)

        _addPrj(name, group, cpps, libs=libs, linkflags=linkflags, customs=customs, install=install)
        _addPyPrj(name, group, pycpps, libs=(libs + [name]) if libs else [name], install=pyinstall, uiFiles=ui_files, combinePys=combine_pys)

# --------------------------------------------
#  envs
# --------------------------------------------
envs = {}

if sys.platform == "darwin":
    envs["GARCH_GLPLATFORMCONTEXT"] = "glPlatformContextDarwin"
    envs["GARCH_GLPLATFORMDEBUGWINDOW"] = "glPlatformDebugWindowDarwin"
    envs["GARCH_SOURCE_EXTENSION"] = "mm"
elif sys.platform == "win32":
    envs["GARCH_GLPLATFORMCONTEXT"] = "glPlatformContextWindows"
    envs["GARCH_GLPLATFORMDEBUGWINDOW"] = "glPlatformDebugWindowWindows"
    envs["GARCH_SOURCE_EXTENSION"] = "cpp"
else:
    envs["GARCH_GLPLATFORMCONTEXT"] = "glPlatformContextGLX"
    envs["GARCH_GLPLATFORMDEBUGWINDOW"] = "glPlatformDebugWindowGLX"
    envs["GARCH_SOURCE_EXTENSION"] = "cpp"

# --------------------------------------------
#  base
# --------------------------------------------

_buildLib("arch",
          "base",
          buildPython=support_python,
          envs=envs)

_buildLib("tf",
          "base",
          libs=["arch"],
          buildPython=support_python,
          envs=envs)

_buildLib("gf",
          "base",
          libs=["arch", "tf"],
          buildPython=support_python,
          envs=envs)

_buildLib("js",
          "base",
          libs=["arch", "tf"],
          buildPython=support_python,
          envs=envs)

_buildLib("trace",
          "base",
          libs=["arch", "tf", "js"],
          buildPython=support_python,
          envs=envs)

_buildLib("work",
          "base",
          libs=["tf", "trace"],
          buildPython=support_python,
          envs=envs)

_buildLib("plug",
          "base",
          libs=["arch", "tf", "trace", "js", "work"],
          buildPython=support_python,
          envs=envs)

_buildLib("vt",
          "base",
          libs=["arch", "tf", "gf", "trace"],
          buildPython=support_python,
          envs=envs)

# --------------------------------------------
#  usd
# --------------------------------------------

_buildLib("ar",
          "usd",
          libs=["arch", "tf", "js", "plug", "vt"],
          buildPython=support_python,
          envs=envs)

_buildLib("kind",
          "usd",
          libs=["arch", "tf", "js", "plug"],
          buildPython=support_python,
          envs=envs)

_buildLib("sdf",
          "usd",
          libs=["arch", "tf", "gf", "js", "trace", "vt", "work", "plug", "ar"],
          buildPython=support_python,
          envs=envs)

_buildLib("ndr",
          "usd",
          libs=["arch", "tf", "work", "plug", "vt", "ar", "sdf"],
          buildPython=support_python,
          envs=envs)

_buildLib("sdr",
          "usd",
          libs=["arch", "tf", "gf", "vt", "ar", "ndr", "sdf"],
          buildPython=support_python,
          envs=envs)

_buildLib("pcp",
          "usd",
          libs=["arch", "tf", "trace", "work", "vt", "ar", "sdf"],
          buildPython=support_python,
          envs=envs)

_buildLib("usd",
          "usd",
          libs=["arch", "tf", "gf", "js", "trace", "work", "plug", "vt", "ar", "kind", "sdf", "pcp"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdGeom",
          "usd",
          libs=["arch", "tf", "gf", "js", "trace", "work", "plug", "vt", "kind", "sdf", "usd"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdVol",
          "usd",
          libs=["tf", "sdf", "usd", "usdGeom"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdLux",
          "usd",
          libs=["tf", "vt", "sdf", "usd", "usdGeom"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdShade",
          "usd",
          libs=["arch", "tf", "trace", "work", "vt", "ar", "ndr", "sdr", "sdf", "pcp", "usd", "usdGeom"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdRender",
          "usd",
          libs=["arch", "tf", "gf", "vt", "sdf", "usd", "usdGeom"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdHydra",
          "usd",
          libs=["ar", "tf", "plug", "ndr", "sdf", "usd", "usdShade"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdRi",
          "usd",
          libs=["tf", "vt", "sdf", "usd", "usdGeom", "usdShade", "usdLux"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdSkel",
          "usd",
          libs=["arch", "tf", "gf", "trace", "work", "vt", "sdf", "usd", "usdGeom"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdUI",
          "usd",
          libs=["tf", "vt", "sdf", "usd"],
          buildPython=support_python,
          envs=envs)

_buildLib("usdUtils",
          "usd",
          libs=["arch", "tf", "gf", "js", "trace", "plug", "work", "vt", "ar", "sdf", "pcp", "kind", "usd", "usdGeom"],
          buildPython=support_python,
          envs=envs)

if build_imaging:
    # --------------------------------------------
    #  imaging
    # --------------------------------------------

    # TODO
    glew_libs = ["GLEW"]

    garch_linkflags = ""
    garch_libs = ["tf", "gf"] + glew_libs
    if sys.platform == "darwin":
        garch_linkflags = " -framework AppKit"
        garch_libs.append("objc")

    _buildLib("garch",
              "imaging",
              libs=garch_libs,
              linkflags=garch_linkflags,
              customs=[gl.Require],
              buildPython=support_python,
              envs=envs)

    _buildLib("hf",
              "imaging",
              libs=["tf", "trace", "plug"],
              buildPython=support_python,
              envs=envs)

    _buildLib("hio",
              "imaging",
              libs=["arch", "tf", "trace", "vt", "hf"],
              buildPython=support_python,
              envs=envs)

    _buildLib("cameraUtil",
              "imaging",
              libs=["tf", "gf"],
              buildPython=support_python,
              envs=envs)

    _buildLib("pxOsd",
              "imaging",
              libs=["tf", "gf", "vt"],
              customs=[lambda x: (RequireOsdCPU(x, static=osd_static)),
                       lambda x: (RequireOsdGPU(x, static=osd_static))],
              buildPython=support_python,
              envs=envs)

    glfenvs = envs.copy()
    if sys.platform != "win32" and sys.platform != "darwin":
        glfenvs["optionalPublicClasses"] = "testGLContext"

    glfenvs["optionalCppFiles"] = "oiioImage.cpp"

    _buildLib("glf",
              "imaging",
              libs=glew_libs + ["arch", "tf", "gf", "js", "plug", "trace", "ar", "sdf", "garch", "hf"],
              buildPython=support_python,
              customs=[lambda x: (RequireIlmImf(x, static=exr_static)),
                       lambda x: (RequireOiio(x, static=oiio_static))],
              envs=glfenvs)

    _buildLib("hgi",
              "imaging",
              libs=["tf", "gf"],
              buildPython=support_python,
              envs=envs)

    _buildLib("hgiGL",
              "imaging",
              libs=glew_libs + ["arch", "tf", "trace", "hgi"],
              buildPython=support_python,
              envs=envs)

    _buildLib("hd",
              "imaging",
              libs=["tf", "trace", "work", "plug", "vt", "sdf", "hf", "cameraUtil", "pxOsd"],
              buildPython=support_python,
              envs=envs)

    _buildLib("hdSt",
              "imaging",
              libs=glew_libs + ["tf", "trace", "sdr", "garch", "hio", "glf", "hd", "hgiGL"],
              buildPython=support_python,
              customs=[lambda x: (RequireOsdCPU(x, static=osd_static)),
                       lambda x: (RequireOsdGPU(x, static=osd_static))],
              envs=envs)

    _buildLib("hdx",
              "imaging",
              libs=glew_libs + ["tf", "gf", "plug", "work", "vt", "sdf","garch", "cameraUtil", "glf", "pxOsd", "hd", "hdSt", "hgi"],
              buildPython=support_python,
              customs=[lambda x: (RequireOCIO(x, static=ocio_static))],
              envs=envs)

    # --------------------------------------------
    #  usd imaging
    # --------------------------------------------

    _buildLib("usdImaging",
              "usdImaging",
              libs=["tf", "gf", "trace", "work", "plug", "vt", "ar", "sdf", "usd", "usdGeom", "usdLux", "usdShade", "usdVol", "hd", "pxOsd"],
              buildPython=support_python,
              envs=envs)

    _buildLib("usdImagingGL",
              "usdImaging",
              libs=glew_libs + ["tf", "gf", "trace", "work", "plug", "vt", "ar", "sdf", "sdr", "usd", "usdGeom", "usdHydra", "usdShade", "garch", "glf", "hio", "hd", "hdx", "pxOsd", "usdImaging"],
              buildPython=support_python,
              customs=[gl.Require],
              envs=envs)

    _buildLib("usdSkelImaging",
              "usdImaging",
              libs=["hd", "hio", "usdImaging", "usdSkel"],
              buildPython=support_python,
              envs=envs)

    _buildLib("usdVolImaging",
              "usdImaging",
              libs=["usdImaging"],
              buildPython=support_python,
              envs=envs)

    _buildLib("usdAppUtils",
              "usdImaging",
              libs=["tf", "gf", "sdf", "usd", "usdGeom", "garch", "glf", "usdImagingGL"],
              buildPython=support_python,
              envs=envs)

    _buildLib("usdviewq",
              "usdImaging",
              libs=["tf", "usd", "usdGeom"],
              buildPython=support_python,
              envs=envs)


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

if support_python and combine_pys:
    combined_srcs["combined"] = ["pxr/combined/combined.cpp"]
    prj = py_default.copy()
    prj["name"] = "_combined"
    prj["alias"] = "usd-py-combined"
    prj["defs"] = prj["defs"] + combined_defs
    prj["cppflags"] = prj["cppflags"] + " -Wno-macro-redefined"
    prj["prefix"] = "lib/python/pxr"
    prj["srcs"] = combined_srcs
    prj["incdirs"] = prj["incdirs"] + [os.path.abspath(".")]
    prj["libs"] = prj["libs"] + combined_libs
    prj["install"] = combined_install
    prj["deps"] = prj["deps"] + combined_fake_pys + env.Command(os.path.join(out_libdir, "python/pxr/__init__.py"), "", GenPy) + combined_deps
    prjs.append(prj)
    groups["usd-py-combined"] = ["_combined"]

# --------------------------------------------
#  bin
# --------------------------------------------

groups["usd-bin"] = []

prj = bin_default.copy()
prj["name"] = "sdfdump"
prj["srcs"] = ["pxr/usd/bin/sdfdump/sdfdump.cpp"]
prj["libs"] = ["arch", "tf", "plug", "sdf", "vt"]
groups["usd-bin"].append("sdfdump")
prjs.append(prj)

prj = bin_default.copy()
prj["name"] = "sdffilter"
prj["srcs"] = ["pxr/usd/bin/sdffilter/sdffilter.cpp"]
prj["libs"] = ["arch", "tf", "sdf", "vt"]
groups["usd-bin"].append("sdffilter")
prjs.append(prj)

def GenBin(target, source, env):
    src = source[0].get_abspath()
    tgt = target[0].get_abspath()
    dgt = os.path.dirname(tgt)
    if not os.path.isdir(dgt):
        os.makedirs(dgt)

    with open(src, 'r') as s:
        with open(tgt, 'w') as d:
            for line in s:
                d.write(line.replace('/pxrpythonsubst', "/usr/bin/env python"))
    os.chmod(tgt, 0775)

py_bins = excons.glob("pxr/usd/bin/*/*.py")
if build_imaging:
    py_bins += excons.glob("pxr/usdImaging/bin/*/*.py")

for py in py_bins:
    name = os.path.splitext(os.path.basename(py))[0]
    tg = env.Command(os.path.join(out_basedir, "bin", name), py, GenBin)
    groups["usd-bin"].append(tg[0])


# --------------------------------------------
#  project
# --------------------------------------------

excons.AddHelpOptions(USD="""USD OPTIONS
  usd-view=0|1          : include usd view building [1]
  usd-view=0|1          : include usd imaging building [1]
  usd-python=0|1        : include usd python building [1]""")

# TODO : plugins

targets = excons.DeclareTargets(env, prjs)

for k, v in groups.items():
    env.Alias(k, v)
    env.Default(k)

# Export("UsdName UsdPath RequireUsd")
