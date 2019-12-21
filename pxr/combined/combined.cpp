#include <boost/python.hpp>


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

#include <iostream> 
BOOST_PYTHON_MODULE(_usdCombined)
{
    #ifdef TF_EXPORTS
        tf_WrapModule();
    #endif
    #ifdef GF_EXPORTS
        gf_WrapModule();
    #endif
    #ifdef TRACE_EXPORTS
        trace_WrapModule();
    #endif
    #ifdef WORK_EXPORTS
        work_WrapModule();
    #endif
    #ifdef PLUG_EXPORTS
        plug_WrapModule();
    #endif
    #ifdef VT_EXPORTS
        vt_WrapModule();
    #endif
    #ifdef AR_EXPORTS
        ar_WrapModule();
    #endif
    #ifdef KIND_EXPORTS
        kind_WrapModule();
    #endif
    #ifdef SDF_EXPORTS
        sdf_WrapModule();
    #endif
    #ifdef NDR_EXPORTS
        ndr_WrapModule();
    #endif
    #ifdef SDR_EXPORTS
        sdr_WrapModule();
    #endif
    #ifdef PCP_EXPORTS
        pcp_WrapModule();
    #endif
    #ifdef USD_EXPORTS
        usd_WrapModule();
    #endif
    #ifdef USDGEOM_EXPORTS
        usdGeom_WrapModule();
    #endif
    #ifdef USDVOL_EXPORTS
        usdVol_WrapModule();
    #endif
    #ifdef USDLUX_EXPORTS
        usdLux_WrapModule();
    #endif
    #ifdef USDSHADE_EXPORTS
        usdShade_WrapModule();
    #endif
    #ifdef USDRENDER_EXPORTS
        usdRender_WrapModule();
    #endif
    #ifdef USDHYDRA_EXPORTS
        usdHydra_WrapModule();
    #endif
    #ifdef USDRI_EXPORTS
        usdRi_WrapModule();
    #endif
    #ifdef USDSKEL_EXPORTS
        usdSkel_WrapModule();
    #endif
    #ifdef USDUI_EXPORTS
        usdUI_WrapModule();
    #endif
    #ifdef USDUTILS_EXPORTS
        usdUtils_WrapModule();
    #endif
}
