/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Header only. Includes globais e defines.
 */

#ifndef INCLUDES_HPP_
#define INCLUDES_HPP_

#define APP_NAME  "Checkers 3D"

/* Remove the comment bellow to see white spheres on light sources */
#define LIGHT_SPHERE_ENABLED

/* Std c++ includes */
#include <iostream>
#include <cmath>
#include <cstdio>
#include <deque>
#include <climits>
#include <string>
#include <sstream>
#include <fstream>

#include <list>
#include <vector>
#include <limits>
#include <stack>

/* Boost includes */
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

/* OpenGL includes */

/* If not in windows define libs as static (they are still static under M$ Windows check config) */
#ifndef WIN32
#define GLEW_STATIC
#define FREEGLUT_STATIC
#endif

#include <GL/glew.h>
#include <GL\freeglut.h>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

/* Libpng wrapper png++ */
#include <png++/png.hpp>

/* Internal project includes */
#include "hoConstants.hpp"
#include "hoStructs.hpp"
#include "geException.hpp"
#include "checkersSettings.hpp"
#include "geSharedMethods.hpp"

/* Win32 Hacks */
#ifdef WIN32
#define M_PI   3.14159265358979323846264338327950288
#endif

#endif

//            .:oxkOOOkxo:.
//         ,kNWKkoc:::coxKWNk:
//       ;0Wx;.            ,xNX:
//      dMX,,;            ,l;.0Mx
//     ,MW'.XX'           o0d .NM;
//     cMX.   oKOkxdddxkO0:    OMd
//     .XMx.   ..',,,,''..     cMX
//      .KM0:.                 .NM:
//        :KWKkl,.      ..      lMK                                .;ldxO0KKKKKK0kdl:'.
//          'lkXWWNKKKXWWX,      0Md                          .:d0NX0kdolc:::;::cloxOKWKx,.
//               ..'lMNl.        .NW'                    .,cd0MMMN0xdolcc:::::clodxOKX0dXMMN0xl;.
//                  .NWc.         :MK               .:d0WWKkokMK.,:ldxO0KXXXXXK0kdl;.   dMKcoxOXWW0o,
//                   xMx.          oMx          .lkNNOd;.    ;MK                       .kMK..,,;:lx0NWOl'
//                   ,M0,           kMd      ,dXWOl'         'MWx:'                .;o0WXx,    ..,,;;lkXMKc.
//                    KWc.          .KMo  .dXWk:.             .:dOXWX0kxdolllodxOXNN0d:.           .',;;ckNWx'
//                    :Mk,           .KMxOW0:                       .,:coddddolc;..                   .,;;:xNMO.
//                     KWc.           oMM0,                                                             .,;;:xNNc
//                     cM0;.        .0M0,                                                                 .,;;:KMO.
//                      KMd,       :NN:                                                                    .,;;;0MX.
//                      'WNl,.    xMO.                                                                       ',,;kMX.
//                       :WNc,. .0Mk                                                                          .;;;OMK
//                        cWXc,,KMd                                                                            ';;;KMo
//                         ;NWdKMx                                                                              ,;,lWN.
//                          .OMM0                                                                               .;;;0Ml
//                           .NW.                                                                                ,;;oM0
//                           lMO.                                                                                .;;oWW.
//                           cMMWXOd:.                                                                        .;lkXWMMk
//                           'MX:oxOKNWXOxl;'.                                                        ..;cdkKNWXOkdlNMo
//                           ,MO  ..'',OMXxOXWWXOxoc;'..                                     .',:ldOKNWNKOMM0:;,'...xM0
//                           ,MO       :MX    .';coxO0XNNXK0Oxddolcc::;;;;;;;;:::cloodxkOKXNNXKOkdl:,..  .WMx       lMN
//                           ,MO       ;MN               ..,;:clodxxkkOOOOOOOOkkxxdollc;,'..              XM0       cMN
//                           .KWo,...  dMk                                                                cWMOooolll0M0
//                             lOXNWMNNWN'                                                                 .oxkOOOOOkl
//                                  .....
