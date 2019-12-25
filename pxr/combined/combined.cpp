#include <boost/python.hpp>
#include <set>
using namespace boost::python;


#ifdef TF_EXPORTS
    #define MFB_PACKAGE_NAME tf
    #define MFB_ALT_PACKAGE_NAME tf
    #define MFB_PACKAGE_MODULE Tf
    #include "pxr/base/lib/tf/module.cpp"
#endif // TF_EXPORTS

#ifdef GF_EXPORTS
    #define MFB_PACKAGE_NAME gf
    #define MFB_ALT_PACKAGE_NAME gf
    #define MFB_PACKAGE_MODULE Gf
    #include "pxr/base/lib/gf/module.cpp"
#endif // GF_EXPORTS

#ifdef TRACE_EXPORTS
    #define MFB_PACKAGE_NAME trace
    #define MFB_ALT_PACKAGE_NAME trace
    #define MFB_PACKAGE_MODULE Trace
    #include "pxr/base/lib/trace/module.cpp"
#endif // TRACE_EXPORTS

#ifdef WORK_EXPORTS
    #define MFB_PACKAGE_NAME work
    #define MFB_ALT_PACKAGE_NAME work
    #define MFB_PACKAGE_MODULE Work
    #include "pxr/base/lib/work/module.cpp"
#endif // WORK_EXPORTS

#ifdef PLUG_EXPORTS
    #define MFB_PACKAGE_NAME plug
    #define MFB_ALT_PACKAGE_NAME plug
    #define MFB_PACKAGE_MODULE Plug
    #include "pxr/base/lib/plug/module.cpp"
#endif // PLUG_EXPORTS

#ifdef VT_EXPORTS
    #define MFB_PACKAGE_NAME vt
    #define MFB_ALT_PACKAGE_NAME vt
    #define MFB_PACKAGE_MODULE Vt
    #include "pxr/base/lib/vt/module.cpp"
#endif // VT_EXPORTS

#ifdef AR_EXPORTS
    #define MFB_PACKAGE_NAME ar
    #define MFB_ALT_PACKAGE_NAME ar
    #define MFB_PACKAGE_MODULE Ar
    #include "pxr/usd/lib/ar/module.cpp"
#endif // AR_EXPORTS

#ifdef KIND_EXPORTS
    #define MFB_PACKAGE_NAME kind
    #define MFB_ALT_PACKAGE_NAME kind
    #define MFB_PACKAGE_MODULE Kind
    #include "pxr/usd/lib/kind/module.cpp"
#endif // KIND_EXPORTS

#ifdef SDF_EXPORTS
    #define MFB_PACKAGE_NAME sdf
    #define MFB_ALT_PACKAGE_NAME sdf
    #define MFB_PACKAGE_MODULE Sdf
    #include "pxr/usd/lib/sdf/module.cpp"
#endif // SDF_EXPORTS

#ifdef NDR_EXPORTS
    #define MFB_PACKAGE_NAME ndr
    #define MFB_ALT_PACKAGE_NAME ndr
    #define MFB_PACKAGE_MODULE Ndr
    #include "pxr/usd/lib/ndr/module.cpp"
#endif // NDR_EXPORTS

#ifdef SDR_EXPORTS
    #define MFB_PACKAGE_NAME sdr
    #define MFB_ALT_PACKAGE_NAME sdr
    #define MFB_PACKAGE_MODULE Sdr
    #include "pxr/usd/lib/sdr/module.cpp"
#endif // SDR_EXPORTS

#ifdef PCP_EXPORTS
    #define MFB_PACKAGE_NAME pcp
    #define MFB_ALT_PACKAGE_NAME pcp
    #define MFB_PACKAGE_MODULE Pcp
    #include "pxr/usd/lib/pcp/module.cpp"
#endif // PCP_EXPORTS

#ifdef USD_EXPORTS
    #define MFB_PACKAGE_NAME usd
    #define MFB_ALT_PACKAGE_NAME usd
    #define MFB_PACKAGE_MODULE Usd
    #include "pxr/usd/lib/usd/module.cpp"
#endif // USD_EXPORTS

#ifdef USDGEOM_EXPORTS
    #define MFB_PACKAGE_NAME usdGeom
    #define MFB_ALT_PACKAGE_NAME usdGeom
    #define MFB_PACKAGE_MODULE UsdGeom
    #include "pxr/usd/lib/usdGeom/module.cpp"
#endif // USDGEOM_EXPORTS

#ifdef USDVOL_EXPORTS
    #define MFB_PACKAGE_NAME usdVol
    #define MFB_ALT_PACKAGE_NAME usdVol
    #define MFB_PACKAGE_MODULE UsdVol
    #include "pxr/usd/lib/usdVol/module.cpp"
#endif // USDVOL_EXPORTS

#ifdef USDLUX_EXPORTS
    #define MFB_PACKAGE_NAME usdLux
    #define MFB_ALT_PACKAGE_NAME usdLux
    #define MFB_PACKAGE_MODULE UsdLux
    #include "pxr/usd/lib/usdLux/module.cpp"
#endif // USDLUX_EXPORTS

#ifdef USDSHADE_EXPORTS
    #define MFB_PACKAGE_NAME usdShade
    #define MFB_ALT_PACKAGE_NAME usdShade
    #define MFB_PACKAGE_MODULE UsdShade
    #include "pxr/usd/lib/usdShade/module.cpp"
#endif // USDSHADE_EXPORTS

#ifdef USDRENDER_EXPORTS
    #define MFB_PACKAGE_NAME usdRender
    #define MFB_ALT_PACKAGE_NAME usdRender
    #define MFB_PACKAGE_MODULE UsdRender
    #include "pxr/usd/lib/usdRender/module.cpp"
#endif // USDRENDER_EXPORTS

#ifdef USDHYDRA_EXPORTS
    #define MFB_PACKAGE_NAME usdHydra
    #define MFB_ALT_PACKAGE_NAME usdHydra
    #define MFB_PACKAGE_MODULE UsdHydra
    #include "pxr/usd/lib/usdHydra/module.cpp"
#endif // USDHYDRA_EXPORTS

#ifdef USDRI_EXPORTS
    #define MFB_PACKAGE_NAME usdRi
    #define MFB_ALT_PACKAGE_NAME usdRi
    #define MFB_PACKAGE_MODULE UsdRi
    #include "pxr/usd/lib/usdRi/module.cpp"
#endif // USDRI_EXPORTS

#ifdef USDSKEL_EXPORTS
    #define MFB_PACKAGE_NAME usdSkel
    #define MFB_ALT_PACKAGE_NAME usdSkel
    #define MFB_PACKAGE_MODULE UsdSkel
    #include "pxr/usd/lib/usdSkel/module.cpp"
#endif // USDSKEL_EXPORTS

#ifdef USDUI_EXPORTS
    #define MFB_PACKAGE_NAME usdUI
    #define MFB_ALT_PACKAGE_NAME usdUI
    #define MFB_PACKAGE_MODULE UsdUI
    #include "pxr/usd/lib/usdUI/module.cpp"
#endif // USDUI_EXPORTS

#ifdef USDUTILS_EXPORTS
    #define MFB_PACKAGE_NAME usdUtils
    #define MFB_ALT_PACKAGE_NAME usdUtils
    #define MFB_PACKAGE_MODULE UsdUtils
    #include "pxr/usd/lib/usdUtils/module.cpp"
#endif // USDUTILS_EXPORTS

#ifdef GARCH_EXPORTS
    #define MFB_PACKAGE_NAME garch
    #define MFB_ALT_PACKAGE_NAME garch
    #define MFB_PACKAGE_MODULE Garch
    #include "pxr/imaging/lib/garch/module.cpp"
#endif // GARCH_EXPORTS

#ifdef CAMERAUTIL_EXPORTS
    #define MFB_PACKAGE_NAME cameraUtil
    #define MFB_ALT_PACKAGE_NAME cameraUtil
    #define MFB_PACKAGE_MODULE CameraUtil
    #include "pxr/imaging/lib/cameraUtil/module.cpp"
#endif // CAMERAUTIL_EXPORTS

#ifdef PXOSD_EXPORTS
    #define MFB_PACKAGE_NAME pxOsd
    #define MFB_ALT_PACKAGE_NAME pxOsd
    #define MFB_PACKAGE_MODULE PxOsd
    #include "pxr/imaging/lib/pxOsd/module.cpp"
#endif // PXOSD_EXPORTS

#ifdef GLF_EXPORTS
    #define MFB_PACKAGE_NAME glf
    #define MFB_ALT_PACKAGE_NAME glf
    #define MFB_PACKAGE_MODULE Glf
    #include "pxr/imaging/lib/glf/module.cpp"
#endif // GLF_EXPORTS

#ifdef USDIMAGINGGL_EXPORTS
    #define MFB_PACKAGE_NAME usdImagingGL
    #define MFB_ALT_PACKAGE_NAME usdImagingGL
    #define MFB_PACKAGE_MODULE UsdImagingGL
    #include "pxr/usdImaging/lib/usdImagingGL/module.cpp"
#endif // USDIMAGINGGL_EXPORTS

#ifdef USDAPPUTILS_EXPORTS
    #define MFB_PACKAGE_NAME usdAppUtils
    #define MFB_ALT_PACKAGE_NAME usdAppUtils
    #define MFB_PACKAGE_MODULE UsdAppUtils
    #include "pxr/usdImaging/lib/usdAppUtils/module.cpp"
#endif // USDAPPUTILS_EXPORTS

#ifdef USDVIEWQ_EXPORTS
    #define MFB_PACKAGE_NAME usdviewq
    #define MFB_ALT_PACKAGE_NAME usdviewq
    #define MFB_PACKAGE_MODULE Usdviewq
    #include "pxr/usdImaging/lib/usdviewq/module.cpp"
#endif // USDVIEWQ_EXPORTS


#define WRAP_MODULE(x) class BOOST_PP_CAT(_, x) {}; \
{ \
    boost::python::scope BOOST_PP_CAT(_scope_, x) = boost::python::class_<BOOST_PP_CAT(_, x)>(BOOST_PP_STRINGIZE(BOOST_PP_CAT(_, x)), boost::python::no_init); \
    BOOST_PP_CAT(x, _WrapModule) (); \
};


BOOST_PYTHON_MODULE(_combined)
{
    boost::python::scope module;
    #ifdef TF_EXPORTS
        WRAP_MODULE(tf)
    #endif
    #ifdef GF_EXPORTS
        WRAP_MODULE(gf)
    #endif
    #ifdef TRACE_EXPORTS
        WRAP_MODULE(trace)
    #endif
    #ifdef WORK_EXPORTS
        WRAP_MODULE(work)
    #endif
    #ifdef PLUG_EXPORTS
        WRAP_MODULE(plug)
    #endif
    #ifdef VT_EXPORTS
        WRAP_MODULE(vt)
    #endif
    #ifdef AR_EXPORTS
        WRAP_MODULE(ar)
    #endif
    #ifdef KIND_EXPORTS
        WRAP_MODULE(kind)
    #endif
    #ifdef SDF_EXPORTS
        WRAP_MODULE(sdf)
    #endif
    #ifdef NDR_EXPORTS
        WRAP_MODULE(ndr)
    #endif
    #ifdef SDR_EXPORTS
        WRAP_MODULE(sdr)
    #endif
    #ifdef PCP_EXPORTS
        WRAP_MODULE(pcp)
    #endif
    #ifdef USD_EXPORTS
        WRAP_MODULE(usd)
    #endif
    #ifdef USDGEOM_EXPORTS
        WRAP_MODULE(usdGeom)
    #endif
    #ifdef USDVOL_EXPORTS
        WRAP_MODULE(usdVol)
    #endif
    #ifdef USDLUX_EXPORTS
        WRAP_MODULE(usdLux)
    #endif
    #ifdef USDSHADE_EXPORTS
        WRAP_MODULE(usdShade)
    #endif
    #ifdef USDRENDER_EXPORTS
        WRAP_MODULE(usdRender)
    #endif
    #ifdef USDHYDRA_EXPORTS
        WRAP_MODULE(usdHydra)
    #endif
    #ifdef USDRI_EXPORTS
        WRAP_MODULE(usdRi)
    #endif
    #ifdef USDSKEL_EXPORTS
        WRAP_MODULE(usdSkel)
    #endif
    #ifdef USDUI_EXPORTS
        WRAP_MODULE(usdUI)
    #endif
    #ifdef USDUTILS_EXPORTS
        WRAP_MODULE(usdUtils)
    #endif
    #ifdef GARCH_EXPORTS
        WRAP_MODULE(garch)
    #endif
    #ifdef CAMERAUTIL_EXPORTS
        WRAP_MODULE(cameraUtil)
    #endif
    #ifdef PXOSD_EXPORTS
        WRAP_MODULE(pxOsd)
    #endif
    #ifdef GLF_EXPORTS
        WRAP_MODULE(glf)
    #endif
    #ifdef USDIMAGINGGL_EXPORTS
        WRAP_MODULE(usdImagingGL)
    #endif
    #ifdef USDAPPUTILS_EXPORTS
        WRAP_MODULE(usdAppUtils)
    #endif
    #ifdef USDVIEWQ_EXPORTS
        WRAP_MODULE(usdviewq)
    #endif
}
