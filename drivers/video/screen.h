#define VGA_BLACK 0x0
#define VGA_BLUE 0x1
#define VGA_GREEN 0x2
#define VGA_CYAN 0x3
#define VGA_RED 0x4
#define VGA_MAGENTA 0x5
#define VGA_BROWN 0x6
#define VGA_LIGHTGRAY 0x7
#define VGA_DARKGRAY 0x8
#define VGA_LIGHTBLUE 0x9
#define VGA_LIGHTGREEN 0xA
#define VGA_LIGHTCYAN 0xB
#define VGA_LIGHTRED 0xC
#define VGA_LIGHTMAGENTA 0xD
#define VGA_YELLOW 0xE
#define VGA_WHITE 0xF

#define VGA_MAX_ROW 25
#define VGA_MAX_COL 80

#define VGA_VIDEO_MEM 0xb8000

#define VGA_SCREEN_CTRL 0x3d4
#define VGA_SCREEN_DATA 0x3d5

void VGA_clear_screen();
void VGA_print(char* msg);
void VGA_print_color(char* msg, char color);
void VGA_print_at(char* msg, int row, int col);
void VGA_print_color_at(char* msg, char color, int col, int row);
char VGA_create_bg_fg_color(char bg, char fg);
