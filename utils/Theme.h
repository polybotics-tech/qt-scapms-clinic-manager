#ifndef THEME_H
#define THEME_H

namespace SCAPMS {
    namespace Theme {

        //--colors
        constexpr auto COLOR_BG_PRIMARY = "#0D9B83";
        constexpr auto COLOR_BG_ACCENT = "#2563eb";
        constexpr auto COLOR_BG_WHITE = "#ffffff";
        constexpr auto COLOR_BG_BLACK = "#121736";
        constexpr auto COLOR_BG_GRAY100 = "#e0e6eb";
        constexpr auto COLOR_BG_GRAY50 = "#f5f6f7";
        constexpr auto COLOR_TEXT_PRIMARY = "#49b3a2";
        constexpr auto COLOR_TEXT_BLACK = "#121736";
        constexpr auto COLOR_TEXT_GRAY200 = "#3a3e58";
        constexpr auto COLOR_TEXT_GRAY100 = "#8996a3";
        constexpr auto COLOR_TEXT_GRAY50 = "#d2dbd9";
        constexpr auto COLOR_TEXT_WHITE = "#fffdf7";
        constexpr auto COLOR_ERROR = "#dc2b2b";
        constexpr auto COLOR_WARNING = "#ee9229";
        constexpr auto COLOR_SUCCESS = "#49b3a2";
        constexpr auto COLOR_ERROR_FADED = "rgba(220, 43, 43, 0.1)";
        constexpr auto COLOR_WARNING_FADED = "rgba(238, 146, 41, 0.1)";
        constexpr auto COLOR_SUCCESS_FADED = "rgba(73, 179, 162, 0.1)";

        //--font sizes
        constexpr int FONT_XS = 11;
        constexpr int FONT_S = 13;
        constexpr int FONT_M = 16;
        constexpr int FONT_B = 20;
        constexpr int FONT_XB = 24;
        constexpr int FONT_XXB = 28;

        //--padding
        constexpr int PADDING_XS = 8;
        constexpr int PADDING_S = 12;
        constexpr int PADDING_M = 16;
        constexpr int PADDING_B = 24;
        constexpr int PADDING_XB = 32;

        //--gap
        constexpr int GAP_XS = 4;
        constexpr int GAP_S = 8;
        constexpr int GAP_M = 16;
        constexpr int GAP_B = 24;
        constexpr int GAP_XB = 48;

        //--border radius
        constexpr int RADIUS_XS = 8;
        constexpr int RADIUS_S = 12;
        constexpr int RADIUS_M = 16;
        constexpr int RADIUS_B = 24;
        constexpr int RADIUS_ROUND = 24;
    }
}

#endif