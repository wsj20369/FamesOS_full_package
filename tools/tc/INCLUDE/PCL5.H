
#ifndef                 __PCL_5_Def
#define                 __PCL_5_Def

#include <math.h>
#include <stdio.h>

#define ASC_CR          13
#define ASC_FF          12
#define ASC_LF          10
#define COLUMNS         0
#define COMPMOD_Adaptive                5
#define COMPMOD_Delta_Row               3
#define COMPMOD_Repl_Delta_Row          9
#define COMPMOD_Run_Length              1
#define COMPMOD_TIFF                    2
#define COMPMOD_Unencoded               0
#define DECIPOINTS      2
#define DEPLETION_25            2
#define DEPLETION_50            3
#define DEPLETION_Gamma_25      4
#define DEPLETION_Gamma_50      5
#define DEPLETION_None          1
#define DOTS            1
#define DSPFUNC_OFF     0x5A
#define DSPFUNC_ON      0x59
#define ENDGRA_Old              0x42
#define ENDGRA_Preferred        0x43
#define ENTGL2_GL2_Cursor       0
#define ENTGL2_PCL_Cursor       1
#define ENTPCL_GL2_Cursor       1
#define ENTPCL_PCL_Cursor       0
#define EOLWRAP_Disabled        1
#define EOLWRAP_Enabled         0
#define ESC             0x1B
#define FILL_Cross_Hatched_Fill         3
#define FILL_Current_Pattern            5
#define FILL_Erase                      1
#define FILL_Shaded_Fill                2
#define FILL_Solid_Black                0
#define FILL_User_Defined               4
#define FLUSH_All_Complete_Page         0
#define FLUSH_All_Page_Data             1
#define FNTCTRL_Assign_Current          6
#define FNTCTRL_Delete_All_Fonts        0
#define FNTCTRL_Delete_All_Temp         1
#define FNTCTRL_Delete_Last_Char        3
#define FNTCTRL_Delete_Last_Font        2
#define FNTCTRL_Make_Permanent          5
#define FNTCTRL_Make_Temporary          4
#define FONT_Primary            0
#define FONT_Secondary          1
#define GRYBAL_Default          0
#define GRYBAL_Disable          2
#define GRYBAL_Enable           1
#define ID_Primary              0x28
#define ID_Secondary            0x29
#define INQ_Font                        0
#define INQ_Font_Extended               4
#define INQ_Macro                       1
#define INQ_Symbol_Set                  3
#define INQ_User_Defined_Pattern        2
#define LNTERM_000              0
#define LNTERM_011              2
#define LNTERM_100              1
#define LNTERM_111              3
#define MACRO_Call                      3
#define MACRO_Delete                    6
#define MACRO_Delete_All_Temp           7
#define MACRO_Delete_Macro_ID           8
#define MACRO_Disable_Overlay           5
#define MACRO_Enable_Overlay            4
#define MACRO_Execute                   2
#define MACRO_Make_Perm                 10
#define MACRO_Make_Temp                 9
#define MACRO_Start                     0
#define MACRO_Stop                      1
#define ORI_Landscape           1
#define ORI_Portrait            0
#define ORI_Reverse_Landscape   3
#define ORI_Reverse_Portrait    2
#define PATREF_Orientation      0
#define PATREF_Physical         1
#define PATTERN_Cross                   3
#define PATTERN_Shading                 2
#define PATTERN_Solid_Black             0
#define PATTERN_Solid_White             1
#define PATTERN_User_Defined            4
#define PERSKIP_Disable         0
#define PERSKIP_Enable          1
#define PITCH_100       0
#define PITCH_120       4
#define PITCH_165       2
#define PLANES_Black     0
#define PLANES_Black1   -1
#define PLANES_Black2    1
#define PLANES_CMY      -3
#define PLANES_KCMY     -4
#define PLANES_RGB      +3
#define POSI_POP        1
#define POSI_PUSH       0
#define PTNCTRL_Delete_All              0
#define PTNCTRL_Delete_All_Temp         1
#define PTNCTRL_Delete_Current          2
#define PTNCTRL_Make_Perm               5
#define PTNCTRL_Make_Temp               4
#define PTNCTRL_Reserved                3
#define PTN_Diagonal_Grid       6
#define PTN_Diagonal_Left       3
#define PTN_Diagonal_Right      4
#define PTN_Horizontal          1
#define PTN_Opaque              1
#define PTN_Square_Grid         5
#define PTN_Transparent         0
#define PTN_Vertical            2
#define ROWS            0
#define RSTMOD_Bidirect         1
#define RSTMOD_Default          0
#define RSTMOD_LeftToRight      2
#define RSTMOD_RightToLeft      3
#define RSTMOD_SmartBidirect    4
#define RSTPRE_Orient           0x30
#define RSTPRE_Physical         0x33
#define RSTQUAL_Draft           1
#define RSTQUAL_High            2
#define RSTQUAL_Keypad          0
#define SET_DeskTop                     7
#define SET_ISO_11                      20
#define SET_ISO_15                      5
#define SET_ISO_17                      21
#define SET_ISO_21                      4
#define SET_ISO_4                       1
#define SET_ISO_6                       24
#define SET_ISO_60                      0
#define SET_ISO_69                      3
#define SET_ISO_8859_1                  17
#define SET_ISO_8859_2                  18
#define SET_ISO_8859_9                  19
#define SET_Legal                       25
#define SET_Math_8                      15
#define SET_MC_Text                     9
#define SET_Microsoft_Publishing        6
#define SET_PC_8                        28
#define SET_PC_850                      30
#define SET_PC_852                      32
#define SET_PC_8_DN                     29
#define SET_PC_Turkish                  23
#define SET_Pi_Font                     31
#define SET_PS_Math                     13
#define SET_PS_Text                     8
#define SET_Roman_8                     26
#define SET_Symbol                      16
#define SET_Ventura_International       10
#define SET_Ventura_Math                14
#define SET_Ventura_US                  11
#define SET_Windows_30_Latin_1          27
#define SET_Windows_31_Latin_1          33
#define SET_Windows_31_Latin_2          2
#define SET_Windows_31_Latin_5          22
#define SET_Wingdings                   12
#define SHINGLING_2     1
#define SHINGLING_4     2
#define SHINGLING_None  0
#define SIZE_A4         26
#define SIZE_B5         100
#define SIZE_C5         91
#define SIZE_COM10      81
#define SIZE_DL         90
#define SIZE_Executive  1
#define SIZE_Legal      3
#define SIZE_Letter     2
#define SIZE_Monarch    80
#define SPC_Fixed               0
#define SPC_Proportional        1
#define SRC_Eject_Page                  0
#define SRC_Envelope_Feeder             6
#define SRC_Lower_Optional_500_Sheet    5
#define SRC_Lower_Paper_Cassette        1
#define SRC_Manual_Envelope_Feed        3
#define SRC_Manual_Feed                 2
#define SRC_MP_Tray                     4
#define SRC_Opaque              1
#define SRC_Transparent         0
#define STRAST_Current_Cursor   1
#define STRAST_Left_Raster      0
#define STROK_Black                     5
#define STROK_Bold                      3
#define STROK_Demi_Bold                 2
#define STROK_Demi_Light                -2
#define STROK_Extra_Black               6
#define STROK_Extra_Bold                4
#define STROK_Extra_Light               -4
#define STROK_Extra_Thin                -6
#define STROK_Light                     -3
#define STROK_MAX                       15
#define STROK_Medium                    0
#define STROK_Semi_Bold                 1
#define STROK_Semi_Light                -1
#define STROK_Thin                      -5
#define STROK_Ultra_Black               7
#define STROK_Ultra_Thin                -7
#define STUSTPE_All_Location            2
#define STUSTPE_Cartridge               5
#define STUSTPE_Currently_Selected      1
#define STUSTPE_Downloaded              4
#define STUSTPE_Internal                3
#define STUSTPE_Invalid_Location        0
#define STUSTPE_SIMM_ROM                7
#define STUS_All_Entities               0
#define STUS_Entity_1                   1
#define STUS_Entity_2                   2
#define STUS_Entity_3                   3
#define STUS_Entity_4                   4
#define STYLE_Compressed                8
#define STYLE_Condensed                 4
#define STYLE_Condensed_Italic          5
#define STYLE_Expanded                  24
#define STYLE_Inline                    64
#define STYLE_Italic                    1
#define STYLE_MAX                       10
#define STYLE_Outline                   32
#define STYLE_Outline_Shadowed          160
#define STYLE_Shadowed                  128
#define STYLE_Upright                   0
#define SYMCTRL_Delete_All_Symbol               0
#define SYMCTRL_Delete_All_Temp                 1
#define SYMCTRL_Delete_Current                  2
#define SYMCTRL_Make_Current_Perm               5
#define SYMCTRL_Make_Current_Temp               4
#define SYMSET_MAX                      34
#define TYPFAC_Albertus                 4362
#define TYPFAC_Antique_Olive            4168
#define TYPFAC_Arial                    16602
#define TYPFAC_Brush                    32   /* Optional */
#define TYPFAC_CG_Century               23   /* Optional */
#define TYPFAC_CG_Omega                 4113
#define TYPFAC_CG_Times                 4101
#define TYPFAC_Clarendon                4140
#define TYPFAC_Coronet                  4116
#define TYPFAC_Courier                  4099
#define TYPFAC_Dom_Casual               61   /* Optional */
#define TYPFAC_Elite                    2    /* Optional */
#define TYPFAC_Garamond_Antiqua         4197
#define TYPFAC_Helvetica                4    /* Optional */
#define TYPFAC_Letter_Gothic            4102
#define TYPFAC_Line_Printer             0
#define TYPFAC_Marigold                 4297
#define TYPFAC_Old_Courier              3
#define TYPFAC_Pica                     1    /* Optional */
#define TYPFAC_Presentations            11   /* Optional */
#define TYPFAC_Prestige                 8    /* Optional */
#define TYPFAC_Script                   7    /* Optional */
#define TYPFAC_Symbol                   16686
#define TYPFAC_Times_New_Roman          16901
#define TYPFAC_Times_Roman              5    /* Optional */
#define TYPFAC_Univers                  4148
#define TYPFAC_Wingdings                31402
#define UNDERLINE_Dbl_Fixed     3
#define UNDERLINE_Dbl_Floating  4
#define UNDERLINE_Disable       2
#define UNDERLINE_Fixed         0
#define UNDERLINE_Floating      1

typedef struct strINTELLIFONT1
{
   unsigned char    Format;
            char    Continuation;
   unsigned char    DescriptorSize;
   unsigned char    Class;
   unsigned char    Reserved1;
   unsigned char    Checksum;
} INTELLIFONT1;

typedef struct strINTELLIFONT2
{
   unsigned int     ContourSize;
     signed int     MetricOffset;
     signed int     IntellifontOffset;
     signed int     ContourTreeOffset;
     signed int     XYDataOffset;
} INTELLIFONT2;

typedef struct strINTELLIFONT3
{
   unsigned char    Format;
            char    Continuation;
   unsigned char    Reserved1;
   unsigned char    Checksum;
} INTELLIFONT3;

typedef struct strINTELLIFONT4
{
   unsigned char    Format;
            char    Continuation;
   unsigned char    DescriptorSize;
   unsigned char    Class;
     signed int     CompoundEscapment;
   unsigned int     CompoundNumber;
   unsigned char    Reserved1;
   unsigned char    Checksum;
} INTELLIFONT4;

typedef struct strINTELLIFONT5
{
   unsigned int     CharCode;
     signed int     XOffset;
     signed int     YOffset;
} INTELLIFONT5;

typedef struct strINTELLIFONTFONT
{
   unsigned char    iFontData [112];
} INTELLIFONTFONT;

/* 有限制的 Intellifont 可調整字型 */
typedef struct strINTELLIFONTBOUNDFONTS
{
   unsigned int     HeaderSize;
   unsigned char    HeaderFormat;
   unsigned char    FontType;
   unsigned char    StyleMSB;
   unsigned char    Reserved1;
   unsigned int     BaselinePosition;
   unsigned int     CellWidth;
   unsigned int     CellHeight;
   unsigned char    Orientation;
            char    Spacing;
   unsigned int     SymbolSet;
   unsigned int     Pitch;
   unsigned int     Height;
   unsigned int     xHeight;
   signed   char    WidthType;
   unsigned char    StyleLSB;
   signed   char    StrokeWeight;
   unsigned char    TypefaceLSB;
   unsigned char    TypefaceMSB;
   unsigned char    SerifStyle;
   unsigned char    Quality;
   signed   char    Placement;
   signed   char    UnderlinePosition;
   unsigned char    UnderlineThickness;
   unsigned int     TextHeight;
   unsigned int     TextWidth;
   unsigned int     FirstCode;
   unsigned int     LastCode;
   unsigned char    PitchExtended;
   unsigned char    HeightExtended;
   unsigned int     CapHeight;
   unsigned long    FontNumber;
   unsigned char    FontName [16];
   unsigned int     ScaleFactor;
   unsigned int     XResolution;
   unsigned int     YResolution;
   signed   int     MasterUnderlinePosi;
   unsigned int     MasterUnderlineThick;
   unsigned int     ORThreshold;
   signed   int     ItalicAngle;
   unsigned int     IntellifontDataSize;
   INTELLIFONTFONT  IntellifontData;
   unsigned char    Copyright [32];
   unsigned char    Reserved2;
   unsigned char    Checksum;
} INTELLIFONTBOUNDFONTS;

/* 未限制的 Intellifont 可縮放字型 */
typedef struct strINTELLIFONTUNBOUNDFONTS
{
   unsigned int     HeaderSize;
   unsigned char    HeaderFormat;
   unsigned char    FontType;
   unsigned char    StyleMSB;
   unsigned char    Reserved1;
   unsigned int     BaselinePosition;
   unsigned int     CellWidth;
   unsigned int     CellHeight;
   unsigned char    Orientation;
            char    Spacing;
   unsigned int     SymbolSet;
   unsigned int     Pitch;
   unsigned int     Height;
   unsigned int     xHeight;
   signed   char    WidthType;
   unsigned char    StyleLSB;
   signed   char    StrokeWeight;
   unsigned char    TypefaceLSB;
   unsigned char    TypefaceMSB;
   unsigned char    SerifStyle;
   unsigned char    Quality;
   signed   char    Placement;
   signed   char    UnderlinePosition;
   unsigned char    UnderlineThickness;
   unsigned int     TextHeight;
   unsigned int     TextWidth;
   unsigned int     Reserved2;
   unsigned int     NumberOfContours;
   unsigned char    PitchExtended;
   unsigned char    HeightExtended;
   unsigned int     CapHeight;
   unsigned long    FontNumber;
   unsigned char    FontName [16];
   unsigned int     ScaleFactor;
   unsigned int     XResolution;
   unsigned int     YResolution;
   signed   int     MasterUnderlinePosi;
   unsigned int     MasterUnderlineThick;
   unsigned int     ORThreshold;
   signed   int     ItalicAngle;
   unsigned char    CharacterComplement [8];
   unsigned int     IntellifontDataSize;
   INTELLIFONTFONT  IntellifontData;
   unsigned char    Copyright [32];
   unsigned char    Reserved3;
   unsigned char    Checksum;
} INTELLIFONTUNBOUNDFONTS;

typedef struct strPCLBITMAP1
{
   unsigned char    Format;
            char    Continuation;
   unsigned char    DescriptorSize;
   unsigned char    Class;
   unsigned char    Orientation;
   unsigned char    Reserved1;
     signed int     LeftOffset;
     signed int     TopOffset;
   unsigned int     CharWidth;
   unsigned int     CharHeight;
     signed int     DeltaX;
} PCLBITMAP1;

typedef struct strPCLBITMAP2
{
   unsigned char    Format;
            char    Continuation;
} PCLBITMAP2;

typedef struct strPCLBITMAPPEDFONTS
{
   unsigned int     HeaderSize;
   unsigned char    HeaderFormat;
   unsigned char    FontType;
   unsigned char    StyleMSB;
   unsigned char    Reserved1;
   unsigned int     BaselinePosition;
   unsigned int     CellWidth;
   unsigned int     CellHeight;
   unsigned char    Orientation;
            char    Spacing;
   unsigned int     SymbolSet;
   unsigned int     Pitch;
   unsigned int     Height;
   unsigned int     xHeight;
   signed   char    WidthType;
   unsigned char    StyleLSB;
   signed   char    StrokeWeight;
   unsigned char    TypefaceLSB;
   unsigned char    TypefaceMSB;
   unsigned char    SerifStyle;
   unsigned char    Quality;
   signed   char    Placement;
   signed   char    UnderlinePosition;
   unsigned char    UnderlineThickness;
   unsigned int     TextHeight;
   unsigned int     TextWidth;
   unsigned int     FirstCode;
   unsigned int     LastCode;
   unsigned char    PitchExtended;
   unsigned char    HeightExtended;
   unsigned int     CapHeight;
   unsigned long    FontNumber;
   unsigned char    FontName [16];
   unsigned char    Copyright [32];
} PCLBITMAPPEDFONTS;

typedef struct strRESOLUTIONSPECIFIEDFONTS
{
   unsigned int     HeaderSize;
   unsigned char    HeaderFormat;
   unsigned char    FontType;
   unsigned char    StyleMSB;
   unsigned char    Reserved1;
   unsigned int     BaselinePosition;
   unsigned int     CellWidth;
   unsigned int     CellHeight;
   unsigned char    Orientation;
            char    Spacing;
   unsigned int     SymbolSet;
   unsigned int     Pitch;
   unsigned int     Height;
   unsigned int     xHeight;
   signed   char    WidthType;
   unsigned char    StyleLSB;
   signed   char    StrokeWeight;
   unsigned char    TypefaceLSB;
   unsigned char    TypefaceMSB;
   unsigned char    SerifStyle;
   unsigned char    Quality;
   signed   char    Placement;
   signed   char    UnderlinePosition;
   unsigned char    UnderlineThickness;
   unsigned int     TextHeight;
   unsigned int     TextWidth;
   unsigned int     FirstCode;
   unsigned int     LastCode;
   unsigned char    PitchExtended;
   unsigned char    HeightExtended;
   unsigned int     CapHeight;
   unsigned long    FontNumber;
   unsigned char    FontName [16];
   unsigned int     XResolution;
   unsigned int     YResolution;
   unsigned char    Copyright [32];
} RESOLUTIONSPECIFIEDFONTS;

typedef struct strSEGMENTEDDATA
{
   unsigned int     SegIdentifier;
   unsigned int     SegSize;
   unsigned char    DataSegment [32];   /* 大小為暫定 */
} SEGMENTEDDATA;

typedef struct strSYMBOLSET
{
   unsigned int    HeaderSize;
   unsigned int    ID;
   unsigned char   Format;
   unsigned char   Type;
   unsigned int    FirstCode;
   unsigned int    LastCode;
   unsigned char   Requirement [8];
} SYMBOLSET;

typedef struct strTRUETYPE1
{
   unsigned char    Format;
            char    Continuation;
   unsigned char    DescriptorSize;
   unsigned char    Class;
   unsigned char    AdditionalData [32];
   unsigned int     CharDataSize;
   unsigned int     GlyphID;
   unsigned char    Reserved1;
   unsigned char    Checksum;
} TRUETYPE1;

typedef struct strTRUETYPE2
{
   unsigned char    Format;
            char    Continuation;
   unsigned char    DescriptorSize;
   unsigned char    Class;
   unsigned char    AdditionalData [32];
   unsigned int     CharDataSize;
   unsigned int     GlyphID;
} TRUETYPE2;

typedef struct strTRUETYPE3
{
   unsigned char    Format;
            char    Continuation;
   unsigned char    Reserved1;
   unsigned char    Checksum;
} TRUETYPE3;

typedef struct strTRUETYPEFONTS
{
   unsigned int     HeaderSize;
   unsigned char    HeaderFormat;
   unsigned char    FontType;
   unsigned char    StyleMSB;
   unsigned char    Reserved1;
   unsigned int     BaselinePosition;
   unsigned int     CellWidth;
   unsigned int     CellHeight;
   unsigned char    Orientation;
            char    Spacing;
   unsigned int     SymbolSet;
   unsigned int     Pitch;
   unsigned int     Height;
   unsigned int     xHeight;
   signed   char    WidthType;
   unsigned char    StyleLSB;
   signed   char    StrokeWeight;
   unsigned char    TypefaceLSB;
   unsigned char    TypefaceMSB;
   unsigned char    SerifStyle;
   unsigned char    Quality;
   signed   char    Placement;
   signed   char    UnderlinePosition;
   unsigned char    UnderlineThickness;
   unsigned int     TextHeight;
   unsigned int     TextWidth;
   unsigned int     FirstCode;
   unsigned int     LastCode;
   unsigned char    PitchExtended;
   unsigned char    HeightExtended;
   unsigned int     CapHeight;
   unsigned long    FontNumber;
   unsigned char    FontName [16];
   unsigned int     ScaleFactor;
   signed   int     MasterUnderlinePosi;
   unsigned int     MasterUnderlineThick;
   unsigned char    ScalingTechnology;
   unsigned char    Variety;
   unsigned char    AdditionalData [32];
        /* 暫定區段字形結構數目為 10 */
   SEGMENTEDDATA    SegmentedFontData [10];
   unsigned char    Reserved2;
   unsigned char    Checksum;
} TRUETYPEFONTS;

void PCL_Assign_Font_ID (unsigned int id);
void PCL_Call_Macro (void);
void PCL_Character_Code (unsigned int code);
void PCL_Clear_Horizontal_Margins (void);
void PCL_Define_Pattern (unsigned int bytes);
void PCL_Define_Symbol_Set (unsigned int bytes);
void PCL_Delete_All_Macros (void);
void PCL_Delete_All_Temp_Macros (void);
void PCL_Delete_Macro (void);
void PCL_Disable_Macro_Overlay (void);
void PCL_Display_Functions (int mode);
void PCL_Download_Character (unsigned int bytes);
void PCL_Echo (signed int evalue);
void PCL_Enable_Macro_Overlay (void);
void PCL_End_Of_Line_Wrap (int mode);
void PCL_End_Raster_Graphics (unsigned char mode);
void PCL_Enter_HP_GL2_Mode (int position);
void PCL_Enter_PCL_Mode (int position);
void PCL_Execute_Macro (void);
void PCL_Fill_Rectangular_Area (int mode);
void PCL_Flush_All_Pages (int function);
void PCL_Font_And_Character_Control (int function);
void PCL_Font_Default (int type);
void PCL_Font_Descriptor (unsigned int bytes);
void PCL_Form_Feed (void);
void PCL_Free_Memory_Space (void);
void PCL_Half_Line_Feed (void);
void PCL_Horizontal_Motion_Index (unsigned int incre);
void PCL_Horizontal_Position (int type, int posi);
void PCL_HP_GL2_Plot_Horizontal_Size (float size);
void PCL_HP_GL2_Plot_Vertical_Size (float size);
void PCL_Inquire_Readback_Entity (int function);
void PCL_Left_Margin (unsigned int columns);
void PCL_Line_Feed (int lines);
void PCL_Line_Spacing (unsigned int lines);
void PCL_Line_Termination (int function);
void PCL_Line_Termination (int);;
void PCL_Long_Edge_Offset_Registration (int decipoints);
void PCL_Macro_Control (int function);
void PCL_Make_Macro_Permanent (void);
void PCL_Make_Macro_Temporary (void);
void PCL_Number_Of_Copies (unsigned int copies);
void PCL_Orientation (unsigned int orient);
void PCL_Page_Length (unsigned int lines);
void PCL_Page_Size (unsigned int size);
void PCL_Paper_Source (unsigned int source);
void PCL_Pattern (unsigned int type);
void PCL_Pattern_ID (unsigned int id);
void PCL_Pattern_Transparency_Mode (int mode);
void PCL_Perforation_Skip (int type);
void PCL_Picture_Frame_Horizontal_Size (int decipoints);
void PCL_Picture_Frame_Vertical_Size (int decipoints);
void PCL_Primary_Font_Stroke_Weight (signed int weight);
void PCL_Primary_Height (float points);
void PCL_Primary_Pitch (float pitch);
void PCL_Primary_Spacing (unsigned int type);
void PCL_Primary_Style (unsigned int style);
void PCL_Primary_Symbol_Set (unsigned int type);
void PCL_Print_Direction (unsigned int direct);
void PCL_Push_Pop_Position (unsigned int type);
void PCL_Raster_Graphics_Presentation (char follows);
void PCL_Raster_Height (unsigned int rrows);
void PCL_Raster_Resolution (unsigned int resolution);
void PCL_Raster_Width (unsigned int pixels);
void PCL_Raster_Y_Offset (unsigned int lines);
void PCL_Rectangle_Height (int unit, unsigned int size);
void PCL_Rectangle_Width (int unit, unsigned int size);
void PCL_Relative_Horizontal_Position (int type, signed int posi);
void PCL_Relative_Vertical_Position (int type, signed int posi);
void PCL_Reset (void);
void PCL_Right_Margin (unsigned int columns);
void PCL_Seed_Row_Source (int mode);
void PCL_Select_Current_Pattern (unsigned int pattern);
void PCL_Select_Font (int type, unsigned int font);
void PCL_Select_Primary_Font (unsigned int id);
void PCL_Select_Secondary_Font (unsigned int id);
void PCL_Set_Depletion (int mode);
void PCL_Set_Graphics_Print_Mode (int mode);
void PCL_Set_Graphics_Quality (int mode);
void PCL_Set_Gray_Balance (int mode);
void PCL_Set_Macro_ID (unsigned int id);
void PCL_Set_Pattern_Reference_Point (int function);
void PCL_Set_Picture_Frame_Anchor_Point (void);
void PCL_Set_Pitch_Mode (unsigned int mode);
void PCL_Set_Planes_Per_Row (signed int p);
void PCL_Set_Raster_Compression_Mode (int mode);
void PCL_Set_Readback_Location_Type (int function);
void PCL_Set_Readback_Location_Unit (int function);
void PCL_Set_Shingling (int mode);
void PCL_Set_Symbol_Set (unsigned int id);
void PCL_Shading (unsigned int percent);
void PCL_Short_Edge_Offset_Registration (int decipoints);
void PCL_Source_Transparency_Mode (int mode);
void PCL_Start_Macro_Def (void);
void PCL_Start_Raster_Graphics (int position);
void PCL_Stop_Macro_Def (void);
void PCL_Symbol_Set_Control (int function);
void PCL_Text_Length (unsigned int lines);
void PCL_Top_Margin (unsigned int lines);
void PCL_Transfer_Color_Data (unsigned int bytes);
void PCL_Transfer_Raster_Data_By_Row (unsigned int bytes);
void PCL_Transparent_Print_Data (unsigned int bytes);
void PCL_Typeface_Family (unsigned int type);
void PCL_Underline (int type);
void PCL_Unit_Of_Measure (unsigned int upi);
void PCL_User_Defined_Pattern_Control (int function);
void PCL_Vertical_Motion_Index (unsigned int incre);
void PCL_Vertical_Position (int type, int posi);

#endif          /* of #ifndef on top of the file */

