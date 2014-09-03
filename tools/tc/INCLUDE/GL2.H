
#ifndef                 __GL_2_Def
#define                 __GL_2_Def

#include <stdio.h>
#include <stdarg.h>

#define Black_Edge      1
#define DEFAULT_TERMINATOR      3
#define ESC             0x1B
#define Font_Spacing    2
#define FTYPE_Cross_Hatch       4
#define FTYPE_GL2_User_Defined  11
#define FTYPE_Hatching          3
#define FTYPE_PCL_Cross_Hatch   21
#define FTYPE_PCL_User_Defined  22
#define FTYPE_Shading           10
#define FTYPE_Solid_Black       1       /* or 2 */
#define GL2_Bitmapped   1
#define GL2_Scalable    0
#define Height          4
#define Ignore_Option           0
#define MaxP1   8128
#define MaxP2   10160
#define MinP1   0
#define MinP2   0
#define Normal          0
#define No_Edge         0
#define OFF    0
#define ON     1
#define PCLMOD_GL2_Cursor       1
#define PCLMOD_PCL_Cursor       0
#define PEN_Black       1
#define PEN_White       0
#define Pitch           3
#define PlotterUnit     1016            /* 1 inches */
#define POLYGON_Close   2
#define POLYGON_Enter   0
#define POLYGON_Set     1
#define Posture         5
#define SOLID   66
#define Stroke_Weight   6
#define Symbol_Set      1
#define Transparent     1
#define Typeface        7

extern char _gl2_label_terminator = DEFAULT_TERMINATOR;

void GL2_Absolute_Arc_Three_Point (signed int xi, signed int yi,
                signed int xe, signed int ye);
void GL2_Absolute_Character_Size (float width, float height);
void GL2_Absolute_Direction (float run, float rise);
void GL2_Alternate_Font_Definition (int kind, float value);
void GL2_Anchor_Corner (signed int x, signed int y);
void GL2_Arc_Absolute (signed int x, signed int y, signed int sangle);
void GL2_Arc_Relative (signed int xi, signed int yi, signed int sangle);
void GL2_Bezier_Absolute (unsigned x1, unsigned y1, unsigned x2, unsigned y2,
                unsigned x3, unsigned y3);
void GL2_Bezier_Relative (unsigned x1, unsigned y1, unsigned x2, unsigned y2,
                unsigned x3, unsigned y3);
void GL2_Character_Fill_Mode (int mode, int edge);
void GL2_Character_Plot (float spaces, float lines);
void GL2_Character_Slant (float tangent);
void GL2_Circle (unsigned int radius);
void GL2_Default_Values (void);
void GL2_Define_Label_Terminator (char lbterm);
void GL2_Define_Variable_Text_Path (int path, int line);
void GL2_Edge_Polygon (void);
void GL2_Edge_Rectangle_Absolute (signed int x, signed int y);
void GL2_Edge_Rectangle_Relative (signed int xi, signed int yi);
void GL2_Edge_Wedge (signed int radius, signed int sangle, signed int wangle);
void GL2_Enter_PCL_Mode (int cursor);
void GL2_Extra_Space (float width, float height);
void GL2_Factor_Scale (signed int x1, float xfactor, signed int y1,
                float yfactor);
void GL2_Fill_Polygon (void);
void GL2_Fill_Rectangle_Absolute (signed int x, signed int y);
void GL2_Fill_Rectangle_Relative (signed int xi, signed int yi);
void GL2_Fill_Type (int type, unsigned option1, signed option2);
void GL2_Fill_Wedge (signed int radius, signed int sangle, signed int wangle);
void GL2_Initialize (void);
void GL2_Input_P1_And_P2 (signed int p1x, signed int p1y, signed int p2x,
                signed int p2y);
void GL2_Input_Relative_P1_And_P2 (signed int p1x, signed int p1y,
                signed int p2x, signed int p2y);
void GL2_Input_Window (signed int xll, signed int yll, signed int xur,
                signed int yur);
void GL2_Label (char *s);
void GL2_Label_Origin (int position);
void GL2_Line_Attribute (unsigned int kind, float value);
void GL2_Line_Type (int type);
void GL2_Pen_Down (void);
void GL2_Pen_Up (void);
void GL2_Pen_Width (float width);
void GL2_Pen_Width_Unit_Selection (int type);
void GL2_Plot_Absolute (signed int x, signed int y);
void GL2_Plot_Relative (signed int x, signed int y);
void GL2_Polygon_Mode (int mode);
void GL2_Polyline_Encoded (char *s1, unsigned char *s2, unsigned char *s3);
void GL2_Primary_Font (int font_id);
void GL2_Raster_Fill_Definition (int index, int width, int height,
                char *PatternStr);
void GL2_Regular_Polygon (unsigned side, unsigned radius);
void GL2_Relative_Arc_Three_Point (signed int xi, signed int yi,
                signed int xe, signed int ye);
void GL2_Relative_Character_Size (float width, float height);
void GL2_Relative_Direction (float run, float rise);
void GL2_Reset_P1_And_P2 (void);
void GL2_Reset_Window (void);
void GL2_Rotate_Coordinate_System (int angle);
void GL2_Scalable_Or_Bitmapped_Fonts (int font);
void GL2_Scale (signed int x1, signed int x2, signed int y1, signed int y2,
                int type, int left, int bottom);
void GL2_Screened_Vectors (int type, int option1, int option2);
void GL2_Secondary_Font (int font_id);
void GL2_Select_Alternate_Font (void);
void GL2_Select_Pen (int color);
void GL2_Select_Standard_Font (void);
void GL2_Set_Plotter_Unit (int x1, int xfactor, int y1, int yfactor);
void GL2_Simple_Scale (signed int x1, signed int x2, signed int y1,
                signed int y2);
void GL2_Standard_Font_Definition (int kind, float value);
void GL2_Symbol_Mode (unsigned char cc);
void GL2_Transparency_Mode (int mode);
void GL2_Transparent_Data (int mode);
void GL2_User_Defined_Line_Type (int index, char *GapStr);

#endif          /* of #ifndef on the top of file */

