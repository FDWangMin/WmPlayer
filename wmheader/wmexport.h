#ifndef WMXPORT_H
#define WMXPORT_H

#pragma once

#include <qglobal.h>

#if defined(WM_EXPORT_DLL)
#  define WM_EXPORT_DLL Q_DECL_EXPORT
#else
#  define WM_EXPORT_DLL Q_DECL_IMPORT
#endif

#endif // WMCOMMONEXPORT_H
