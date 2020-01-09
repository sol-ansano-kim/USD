#include <boost/python.hpp>
#include <set>
#include "pxr/base/tf/pyWrapContext.h"

using namespace boost::python;


#ifdef COMBINE_TF
    #define MFB_PACKAGE_NAME tf
    #define MFB_ALT_PACKAGE_NAME tf
    #define MFB_PACKAGE_MODULE Tf
    #include "pxr/base/lib/tf/module.cpp"
#endif // COMBINE_TF

#ifdef COMBINE_GF
    #define MFB_PACKAGE_NAME gf
    #define MFB_ALT_PACKAGE_NAME gf
    #define MFB_PACKAGE_MODULE Gf
    #include "pxr/base/lib/gf/module.cpp"
#endif // COMBINE_GF

#ifdef COMBINE_TRACE
    #define MFB_PACKAGE_NAME trace
    #define MFB_ALT_PACKAGE_NAME trace
    #define MFB_PACKAGE_MODULE Trace
    #include "pxr/base/lib/trace/module.cpp"
#endif // COMBINE_TRACE

#ifdef COMBINE_WORK
    #define MFB_PACKAGE_NAME work
    #define MFB_ALT_PACKAGE_NAME work
    #define MFB_PACKAGE_MODULE Work
    #include "pxr/base/lib/work/module.cpp"
#endif // COMBINE_WORK

#ifdef COMBINE_PLUG
    #define MFB_PACKAGE_NAME plug
    #define MFB_ALT_PACKAGE_NAME plug
    #define MFB_PACKAGE_MODULE Plug
    #include "pxr/base/lib/plug/module.cpp"
#endif // COMBINE_PLUG

#ifdef COMBINE_VT
    #define MFB_PACKAGE_NAME vt
    #define MFB_ALT_PACKAGE_NAME vt
    #define MFB_PACKAGE_MODULE Vt
    #include "pxr/base/lib/vt/module.cpp"
#endif // COMBINE_VT

#ifdef COMBINE_AR
    #define MFB_PACKAGE_NAME ar
    #define MFB_ALT_PACKAGE_NAME ar
    #define MFB_PACKAGE_MODULE Ar
    #include "pxr/usd/lib/ar/module.cpp"
#endif // COMBINE_AR

#ifdef COMBINE_KIND
    #define MFB_PACKAGE_NAME kind
    #define MFB_ALT_PACKAGE_NAME kind
    #define MFB_PACKAGE_MODULE Kind
    #include "pxr/usd/lib/kind/module.cpp"
#endif // COMBINE_KIND

#ifdef COMBINE_SDF
    #define MFB_PACKAGE_NAME sdf
    #define MFB_ALT_PACKAGE_NAME sdf
    #define MFB_PACKAGE_MODULE Sdf
    #include "pxr/usd/lib/sdf/module.cpp"
#endif // COMBINE_SDF

#ifdef COMBINE_NDR
    #define MFB_PACKAGE_NAME ndr
    #define MFB_ALT_PACKAGE_NAME ndr
    #define MFB_PACKAGE_MODULE Ndr
    #include "pxr/usd/lib/ndr/module.cpp"
#endif // COMBINE_NDR

#ifdef COMBINE_SDR
    #define MFB_PACKAGE_NAME sdr
    #define MFB_ALT_PACKAGE_NAME sdr
    #define MFB_PACKAGE_MODULE Sdr
    #include "pxr/usd/lib/sdr/module.cpp"
#endif // COMBINE_SDR

#ifdef COMBINE_PCP
    #define MFB_PACKAGE_NAME pcp
    #define MFB_ALT_PACKAGE_NAME pcp
    #define MFB_PACKAGE_MODULE Pcp
    #include "pxr/usd/lib/pcp/module.cpp"
#endif // COMBINE_PCP

#ifdef COMBINE_USD
    #define MFB_PACKAGE_NAME usd
    #define MFB_ALT_PACKAGE_NAME usd
    #define MFB_PACKAGE_MODULE Usd
    #include "pxr/usd/lib/usd/module.cpp"
#endif // COMBINE_USD

#ifdef COMBINE_USDGEOM
    #define MFB_PACKAGE_NAME usdGeom
    #define MFB_ALT_PACKAGE_NAME usdGeom
    #define MFB_PACKAGE_MODULE UsdGeom
    #include "pxr/usd/lib/usdGeom/module.cpp"
#endif // COMBINE_USDGEOM

#ifdef COMBINE_USDVOL
    #define MFB_PACKAGE_NAME usdVol
    #define MFB_ALT_PACKAGE_NAME usdVol
    #define MFB_PACKAGE_MODULE UsdVol
    #include "pxr/usd/lib/usdVol/module.cpp"
#endif // COMBINE_USDVOL

#ifdef COMBINE_USDLUX
    #define MFB_PACKAGE_NAME usdLux
    #define MFB_ALT_PACKAGE_NAME usdLux
    #define MFB_PACKAGE_MODULE UsdLux
    #include "pxr/usd/lib/usdLux/module.cpp"
#endif // COMBINE_USDLUX

#ifdef COMBINE_USDSHADE
    #define MFB_PACKAGE_NAME usdShade
    #define MFB_ALT_PACKAGE_NAME usdShade
    #define MFB_PACKAGE_MODULE UsdShade
    #include "pxr/usd/lib/usdShade/module.cpp"
#endif // COMBINE_USDSHADE

#ifdef COMBINE_USDRENDER
    #define MFB_PACKAGE_NAME usdRender
    #define MFB_ALT_PACKAGE_NAME usdRender
    #define MFB_PACKAGE_MODULE UsdRender
    #include "pxr/usd/lib/usdRender/module.cpp"
#endif // COMBINE_USDRENDER

#ifdef COMBINE_USDHYDRA
    #define MFB_PACKAGE_NAME usdHydra
    #define MFB_ALT_PACKAGE_NAME usdHydra
    #define MFB_PACKAGE_MODULE UsdHydra
    #include "pxr/usd/lib/usdHydra/module.cpp"
#endif // COMBINE_USDHYDRA

#ifdef COMBINE_USDRI
    #define MFB_PACKAGE_NAME usdRi
    #define MFB_ALT_PACKAGE_NAME usdRi
    #define MFB_PACKAGE_MODULE UsdRi
    #include "pxr/usd/lib/usdRi/module.cpp"
#endif // COMBINE_USDRI

#ifdef COMBINE_USDSKEL
    #define MFB_PACKAGE_NAME usdSkel
    #define MFB_ALT_PACKAGE_NAME usdSkel
    #define MFB_PACKAGE_MODULE UsdSkel
    #include "pxr/usd/lib/usdSkel/module.cpp"
#endif // COMBINE_USDSKEL

#ifdef COMBINE_USDUI
    #define MFB_PACKAGE_NAME usdUI
    #define MFB_ALT_PACKAGE_NAME usdUI
    #define MFB_PACKAGE_MODULE UsdUI
    #include "pxr/usd/lib/usdUI/module.cpp"
#endif // COMBINE_USDUI

#ifdef COMBINE_USDUTILS
    #define MFB_PACKAGE_NAME usdUtils
    #define MFB_ALT_PACKAGE_NAME usdUtils
    #define MFB_PACKAGE_MODULE UsdUtils
    #include "pxr/usd/lib/usdUtils/module.cpp"
#endif // COMBINE_USDUTILS

#ifdef COMBINE_GARCH
    #define MFB_PACKAGE_NAME garch
    #define MFB_ALT_PACKAGE_NAME garch
    #define MFB_PACKAGE_MODULE Garch
    #include "pxr/imaging/lib/garch/module.cpp"
#endif // COMBINE_GARCH

#ifdef COMBINE_CAMERAUTIL
    #define MFB_PACKAGE_NAME cameraUtil
    #define MFB_ALT_PACKAGE_NAME cameraUtil
    #define MFB_PACKAGE_MODULE CameraUtil
    #include "pxr/imaging/lib/cameraUtil/module.cpp"
#endif // COMBINE_CAMERAUTIL

#ifdef COMBINE_PXOSD
    #define MFB_PACKAGE_NAME pxOsd
    #define MFB_ALT_PACKAGE_NAME pxOsd
    #define MFB_PACKAGE_MODULE PxOsd
    #include "pxr/imaging/lib/pxOsd/module.cpp"
#endif // COMBINE_PXOSD

#ifdef COMBINE_GLF
    #define MFB_PACKAGE_NAME glf
    #define MFB_ALT_PACKAGE_NAME glf
    #define MFB_PACKAGE_MODULE Glf
    #include "pxr/imaging/lib/glf/module.cpp"
#endif // COMBINE_GLF

#ifdef COMBINE_USDIMAGINGGL
    #define MFB_PACKAGE_NAME usdImagingGL
    #define MFB_ALT_PACKAGE_NAME usdImagingGL
    #define MFB_PACKAGE_MODULE UsdImagingGL
    #include "pxr/usdImaging/lib/usdImagingGL/module.cpp"
#endif // COMBINE_USDIMAGINGGL

#ifdef COMBINE_USDAPPUTILS
    #define MFB_PACKAGE_NAME usdAppUtils
    #define MFB_ALT_PACKAGE_NAME usdAppUtils
    #define MFB_PACKAGE_MODULE UsdAppUtils
    #include "pxr/usdImaging/lib/usdAppUtils/module.cpp"
#endif // COMBINE_USDAPPUTILS

#ifdef COMBINE_USDVIEWQ
    #define MFB_PACKAGE_NAME usdviewq
    #define MFB_ALT_PACKAGE_NAME usdviewq
    #define MFB_PACKAGE_MODULE Usdviewq
    #include "pxr/usdImaging/lib/usdviewq/module.cpp"
#endif // COMBINE_USDVIEWQ


#define WRAP_MODULE(x) class BOOST_PP_CAT(_, x) {}; \
{ \
    Tf_PyWrapContextManager::GetInstance().PushContext(BOOST_PP_STRINGIZE(x)); \
    boost::python::scope BOOST_PP_CAT(_scope_, x) = boost::python::class_<BOOST_PP_CAT(_, x)>(BOOST_PP_STRINGIZE(BOOST_PP_CAT(_, x)), boost::python::no_init); \
    BOOST_PP_CAT(x, _WrapModule) (); \
    Tf_PyWrapContextManager::GetInstance().PopContext(); \
};


BOOST_PYTHON_MODULE(_combined)
{
    boost::python::scope module;
    #ifdef COMBINE_TF
        WRAP_MODULE(Tf)
    #endif
    #ifdef COMBINE_GF
        WRAP_MODULE(Gf)
    #endif
    #ifdef COMBINE_TRACE
        WRAP_MODULE(Trace)
    #endif
    #ifdef COMBINE_WORK
        WRAP_MODULE(Work)
    #endif
    #ifdef COMBINE_PLUG
        WRAP_MODULE(Plug)
    #endif
    #ifdef COMBINE_VT
        WRAP_MODULE(Vt)
    #endif
    #ifdef COMBINE_AR
        WRAP_MODULE(Ar)
    #endif
    #ifdef COMBINE_KIND
        WRAP_MODULE(Kind)
    #endif
    #ifdef COMBINE_SDF
        WRAP_MODULE(Sdf)
    #endif
    #ifdef COMBINE_NDR
        WRAP_MODULE(Ndr)
    #endif
    #ifdef COMBINE_SDR
        WRAP_MODULE(Sdr)
    #endif
    #ifdef COMBINE_PCP
        WRAP_MODULE(Pcp)
    #endif
    #ifdef COMBINE_USD
        WRAP_MODULE(Usd)
    #endif
    #ifdef COMBINE_USDGEOM
        WRAP_MODULE(UsdGeom)
    #endif
    #ifdef COMBINE_USDVOL
        WRAP_MODULE(UsdVol)
    #endif
    #ifdef COMBINE_USDLUX
        WRAP_MODULE(UsdLux)
    #endif
    #ifdef COMBINE_USDSHADE
        WRAP_MODULE(UsdShade)
    #endif
    #ifdef COMBINE_USDRENDER
        WRAP_MODULE(UsdRender)
    #endif
    #ifdef COMBINE_USDHYDRA
        WRAP_MODULE(UsdHydra)
    #endif
    #ifdef COMBINE_USDRI
        WRAP_MODULE(UsdRi)
    #endif
    #ifdef COMBINE_USDSKEL
        WRAP_MODULE(UsdSkel)
    #endif
    #ifdef COMBINE_USDUI
        WRAP_MODULE(UsdUI)
    #endif
    #ifdef COMBINE_USDUTILS
        WRAP_MODULE(UsdUtils)
    #endif
    #ifdef COMBINE_GARCH
        WRAP_MODULE(Garch)
    #endif
    #ifdef COMBINE_CAMERAUTIL
        WRAP_MODULE(CameraUtil)
    #endif
    #ifdef COMBINE_PXOSD
        WRAP_MODULE(PxOsd)
    #endif
    #ifdef COMBINE_GLF
        WRAP_MODULE(Glf)
    #endif
    #ifdef COMBINE_USDIMAGINGGL
        WRAP_MODULE(UsdImagingGL)
    #endif
    #ifdef COMBINE_USDAPPUTILS
        WRAP_MODULE(UsdAppUtils)
    #endif
    #ifdef COMBINE_USDVIEWQ
        WRAP_MODULE(Usdviewq)
    #endif
}
