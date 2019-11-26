import sys
import os
import excons
import functools


env = excons.MakeBaseEnv()
out_basedir = excons.OutputBaseDirectory()
out_incdir = os.path.join(out_basedir, "include")
out_libdir = os.path.join(out_basedir, "lib")
staticlib = excons.GetArgument("usd-static", 0, int) != 0


usd_opts = {}
usd_opts["TBB_INCLUDE_DIR"] = ""
usd_opts["TBB_LIBRARY"] = ""
usd_opts["TBB_LIB_SUFFIX"] = ""
usd_opts["BOOST_ROOT"] = ""
usd_opts["PXR_ENABLE_PYTHON_SUPPORT"] = 0
usd_opts["PXR_BUILD_IMAGING"] = 0
usd_opts["PXR_BUILD_USDVIEW"] = 0
usd_opts["PXR_BUILD_KATANA_PLUGIN"] = 0
usd_opts["PXR_BUILD_MAYA_PLUGIN"] = 0
usd_opts["PXR_BUILD_HOUDINI_PLUGIN"] = 0
usd_opts["PXR_BUILD_PRMAN_PLUGIN"] = 0
usd_opts["PXR_BUILD_ALEMBIC_PLUGIN"] = 0
usd_opts["BUILD_SHARED_LIBS"] = 0 if staticlib else 1
usd_opts["Boost_USE_STATIC_LIBS"] = 1 if excons.GetArgument("boost-static", 1, int) != 0 else 0
usd_opts["TBB_NO_IMPLICIT_LINKAGE"] = 1

dependencies = []


rv = excons.ExternalLibRequire("boost")
if rv["require"]:
    usd_opts["BOOST_ROOT"] = os.path.dirname(rv["libdir"])
else:
    excons.WarnOnce("Boost is require to build USD, please provide root directory using 'with-boost=' flag", tool="USD")
    sys.exit(1)

rv = excons.ExternalLibRequire("tbb")
if not rv["require"]:
    tbb_opts = {"tbb-static": 1, "use-c++11": 1}
    excons.PrintOnce("USD: Build tbb from sources ...")
    excons.Call("tbb", overrides=tbb_opts, imp=["TBBPath", "TBBMallocPath", "TBBProxyPath", "TBBName"])
    dependencies.append(TBBPath())
    dependencies.append(TBBMallocPath())
    dependencies.append(TBBProxyPath())

    usd_opts["TBB_INCLUDE_DIR"] = os.path.abspath(os.path.join(TBBPath(), "../../include"))
    usd_opts["TBB_LIBRARY"] = os.path.dirname(TBBPath())
    usd_opts["TBB_LIB_SUFFIX"] = TBBName().split("tbb")[-1]
else:
    usd_opts["TBB_INCLUDE_DIR"] = rv["incdir"]
    usd_opts["TBB_LIBRARY"] = rv["libdir"]
    usd_opts["TBB_LIB_SUFFIX"] = excons.GetArgument("tbb-suffix", "")


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
