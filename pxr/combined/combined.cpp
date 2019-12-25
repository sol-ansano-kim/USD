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


class Categorizer
{
    public:
        Categorizer()
        {
            list items = extract<list>(m_module.attr("__dict__").attr("items")());
            size_t length = len(items);
            for (size_t i = 0; i < length; ++i)
            {
                const char* n = PyString_AS_STRING(object(items[i][0]).ptr());
                m_prev.insert(n);
            }
        }

        ~Categorizer() {};

        void categorize(const char *name)
        {
            dict copy_items;

            list items = extract<list>(m_module.attr("__dict__").attr("items")());
            size_t length = len(items);
            for (size_t i = 0; i < length; ++i)
            {
                const char* n = PyString_AS_STRING(object(items[i][0]).ptr());

                std::set<const char *>::iterator it = m_prev.find(n);
                if (it == m_prev.end())
                {
                    m_prev.insert(n);
                    copy_items[n] = object(items[i][1]);
                }
            }

            m_module.attr(name) = copy_items;

            items = extract<list>(m_module.attr("__dict__").attr("keys")());
            length = len(items);

            for (size_t i = 0; i < length; ++i)
            {
                const char* n = PyString_AS_STRING(object(items[i]).ptr());
                std::set<const char *>::iterator it = m_prev.find(n);
                if (it == m_prev.end())
                {
                    m_prev.insert(n);
                }
            }
        }

    private:
        std::set<const char*> m_prev;
        scope m_module;
};


BOOST_PYTHON_MODULE(_combined)
{
    Categorizer ct;

    #ifdef TF_EXPORTS
        tf_WrapModule();
        ct.categorize("__Contents_Tf");
    #endif // TF_EXPORTS
    #ifdef GF_EXPORTS
        gf_WrapModule();
        ct.categorize("__Contents_Gf");
    #endif // GF_EXPORTS
    #ifdef TRACE_EXPORTS
        trace_WrapModule();
        ct.categorize("__Contents_Trace");
    #endif // TRACE_EXPORTS
    #ifdef WORK_EXPORTS
        work_WrapModule();
        ct.categorize("__Contents_Work");
    #endif // WORK_EXPORTS
    #ifdef PLUG_EXPORTS
        plug_WrapModule();
        ct.categorize("__Contents_Plug");
    #endif // PLUG_EXPORTS
    #ifdef VT_EXPORTS
        vt_WrapModule();
        ct.categorize("__Contents_Vt");
    #endif // VT_EXPORTS
    #ifdef AR_EXPORTS
        ar_WrapModule();
        ct.categorize("__Contents_Ar");
    #endif // AR_EXPORTS
    #ifdef KIND_EXPORTS
        kind_WrapModule();
        ct.categorize("__Contents_Kind");
    #endif // KIND_EXPORTS
    #ifdef SDF_EXPORTS
        sdf_WrapModule();
        ct.categorize("__Contents_Sdf");
    #endif // SDF_EXPORTS
    #ifdef NDR_EXPORTS
        ndr_WrapModule();
        ct.categorize("__Contents_Ndr");
    #endif // NDR_EXPORTS
    #ifdef SDR_EXPORTS
        sdr_WrapModule();
        ct.categorize("__Contents_Sdr");
    #endif // SDR_EXPORTS
    #ifdef PCP_EXPORTS
        pcp_WrapModule();
        ct.categorize("__Contents_Pcp");
    #endif // PCP_EXPORTS
    #ifdef USD_EXPORTS
        usd_WrapModule();
        ct.categorize("__Contents_Usd");
    #endif // USD_EXPORTS
    #ifdef USDGEOM_EXPORTS
        usdGeom_WrapModule();
        ct.categorize("__Contents_UsdGeom");
    #endif // USDGEOM_EXPORTS
    #ifdef USDVOL_EXPORTS
        usdVol_WrapModule();
        ct.categorize("__Contents_UsdVol");
    #endif // USDVOL_EXPORTS
    #ifdef USDLUX_EXPORTS
        usdLux_WrapModule();
        ct.categorize("__Contents_UsdLux");
    #endif // USDLUX_EXPORTS
    #ifdef USDSHADE_EXPORTS
        usdShade_WrapModule();
        ct.categorize("__Contents_UsdShade");
    #endif // USDSHADE_EXPORTS
    #ifdef USDRENDER_EXPORTS
        usdRender_WrapModule();
        ct.categorize("__Contents_UsdRender");
    #endif // USDRENDER_EXPORTS
    #ifdef USDHYDRA_EXPORTS
        usdHydra_WrapModule();
        ct.categorize("__Contents_UsdHydra");
    #endif // USDHYDRA_EXPORTS
    #ifdef USDRI_EXPORTS
        usdRi_WrapModule();
        ct.categorize("__Contents_UsdRi");
    #endif // USDRI_EXPORTS
    #ifdef USDSKEL_EXPORTS
        usdSkel_WrapModule();
        ct.categorize("__Contents_UsdSkel");
    #endif // USDSKEL_EXPORTS
    #ifdef USDUI_EXPORTS
        usdUI_WrapModule();
        ct.categorize("__Contents_UsdUI");
    #endif // USDUI_EXPORTS
    #ifdef USDUTILS_EXPORTS
        usdUtils_WrapModule();
        ct.categorize("__Contents_UsdUtils");
    #endif // USDUTILS_EXPORTS
    #ifdef GARCH_EXPORTS
        garch_WrapModule();
        ct.categorize("__Contents_Garch");
    #endif // GARCH_EXPORTS
    #ifdef CAMERAUTIL_EXPORTS
        cameraUtil_WrapModule();
        ct.categorize("__Contents_CameraUtil");
    #endif // CAMERAUTIL_EXPORTS
    #ifdef PXOSD_EXPORTS
        pxOsd_WrapModule();
        ct.categorize("__Contents_PxOsd");
    #endif // PXOSD_EXPORTS
    #ifdef GLF_EXPORTS
        glf_WrapModule();
        ct.categorize("__Contents_Glf");
    #endif // GLF_EXPORTS
}
