/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#ifndef CONFIG_H
#define CONFIG_H

namespace ace {

    namespace cfg {

        const float screenwidth   = 640;
        const float screenheight  = 480;
        const float fov           = 70;
        const float aspectratio   = 1.0;
        const bool  fullscreen    = false;

        const int   rgbbits       = 8;
        const int   depthbits     = 8;
        const int   stencilbits   = 8;

        const float cam_speed_fwd_rwn = 0.1;
        const float cam_speed_lft_rgt = 0.1;
        const float mouse_speed       = 0.001;

        // shader attributes
        enum { 
            // input variables
            ACE_ATTRIB_VERT = 0,
            ACE_ATTRIB_UV   = 1,
            ACE_ATTRIB_NORM = 2,
        };

        enum {
            // output variables
            ACE_OUT_COLOR   = 0,
            ACE_OUT_POS     = 1,
            ACE_OUT_NORMAL  = 2,
            ACE_OUT_DEPTH   = 3
        };

        // camera directions
        enum {
            CAM_DIR_OFF,
            CAM_DIR_FWD,
            CAM_DIR_RWN,
            CAM_DIR_LFT,
            CAM_DIR_RGT
        };
    }
}

#endif // CONFIG_H
