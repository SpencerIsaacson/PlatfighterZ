using Engine;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using static Game;
using static System.Math;

static class DrawingLibrary
{
    public static bool maximized = false;

    public static uint[] pixels;
    public static GCHandle pixel_handle;
    public static Bitmap rendered_image;


    public const uint red = 0xFF_FF_00_00;
    public const uint green = 0xFF_00_FF_00;
    public const uint blue = 0xFF_00_00_FF;

    public const uint cyan = green | blue;
    public const uint magenta = red | blue;
    public const uint yellow = red | green;

    public const uint black = 0xFF_00_00_00;
    public const uint white = red | green | blue;

    public const uint brown = 0xFF_A5_2A_2A;
    public const uint purple = 0xFF_80_00_80;

    [DllImport("SGL.dll")]
    public static extern void InitMeshDemo(float field_of_view, int WIDTH, int HEIGHT, uint[] pixels); //TODO rename
    [DllImport("SGL.dll")]
    public static unsafe extern void FillVerticalGradient(uint color1, uint color2);
    [DllImport("SGL.dll")]
    public static extern uint Darker(uint color);
    [DllImport("SGL.dll")]
    public static extern void Flatten();
    [DllImport("SGL.dll")]
    public static extern void FillRectangle_Blend(uint color, int x, int y, int width, int height);
    [DllImport("SGL.dll")]
    public static extern void  DrawHorizontal_Blend(uint color, int y);
    [DllImport("SGL.dll")]
    public static extern void DrawVertical_Blend(uint color, int x);
    [DllImport("SGL.dll")]
    public static extern void DrawLine(uint color, float x1, float y1, float x2, float y2);
    [DllImport("SGL.dll")]
    public static extern uint BlendColor(uint s, uint d);
    [DllImport("SGL.dll")]
    public static extern void DrawHorizontal(uint color, int y);
    [DllImport("SGL.dll")]
    public static extern void DrawVertical(uint color, int x);
    [DllImport("SGL.dll")]
    public static extern void DrawGrid_ScreenSpace(int unit_size);
    [DllImport("SGL.dll")]
    public static extern void DrawHorizontalSegment(uint color, int y, int x1, int x2);
    [DllImport("SGL.dll")]
    public static extern void DrawVerticalSegment(uint color, int x, int y1, int y2);
    [DllImport("SGL.dll")]
    public static extern void DrawRectangle(uint color, float x, float y, float width, float height);
    [DllImport("SGL.dll")]
    public static extern void FillRectangle(uint color, float x, float y, float width, float height);
    [DllImport("SGL.dll")]
    public static extern void Draw_Circle(uint color, float x, float y, float radius, float stroke);
    [DllImport("SGL.dll")]
    public static extern void FillCircle(uint color, float x, float y, float radius);
    [DllImport("SGL.dll")]
    public static extern void Blend_Circle(uint color, float x, float y, float radius);    
    [DllImport("SGL.dll")]
    public static extern void FillTriangle(uint color, int x1, int y1, int x2, int y2, int x3, int y3);
    [DllImport("SGL.dll")]
    public static extern void PutPixel(uint color, int x, int y);
    [DllImport("SGL.dll")]
    public static extern void PutPixel_ByIndex(uint color, int i);

    public static void ToggleFullScreen()
    {
        maximized = !maximized;
        if (maximized)
            ToFullScreenView();
        else
            ToWindowedView();
    }
    
    public static void ToFullScreenView()
    {
        WIDTH = Screen.PrimaryScreen.Bounds.Width;
        HEIGHT = Screen.PrimaryScreen.Bounds.Height;
        window.FormBorderStyle = FormBorderStyle.None;
        window.WindowState = FormWindowState.Maximized;
        InitGraphics();
    }

    public static void ToWindowedView()
    {
        WIDTH = 1024;
        HEIGHT = 576;
        window.FormBorderStyle = FormBorderStyle.FixedSingle;
        window.WindowState = FormWindowState.Normal;
        InitGraphics();
    }

    public static void InitGraphics()
    {
        window.ClientSize = new Size(WIDTH, HEIGHT);
        pixels = new uint[WIDTH * HEIGHT];
        if (pixel_handle.IsAllocated)
            pixel_handle.Free();
        pixel_handle = GCHandle.Alloc(pixels, GCHandleType.Pinned);
        rendered_image = new Bitmap(WIDTH, HEIGHT, WIDTH * 4, PixelFormat.Format32bppPArgb, pixel_handle.AddrOfPinnedObject());
        buffered_graphics = BufferedGraphicsManager.Current.Allocate(window.CreateGraphics(), window.DisplayRectangle);
        graphics = buffered_graphics.Graphics;
        InitMeshDemo(Global.Tau / 4, WIDTH, HEIGHT, pixels);
    }

    public static void OutputRender()
    {
        graphics.DrawImage(rendered_image, 0, 0); //TODO find something faster than this! Perhaps you can access the contents of the GDI drawing surface directly?
    }

    #region Text

    static char[] char_dict = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' ', '.', ':', ',', '_', '[', ']', '-', };
    static CharSprite[] font_set = new CharSprite[]
    {
        new CharSprite()
        {
            row1 = 0b01111110,
            row2 = 0b11111111,
            row3 = 0b11000011,
            row4 = 0b11000011,
            row5 = 0b11111111,
            row6 = 0b11000011,
            row7 = 0b11000011,
            row8 = 0b11000011,
        },
        new CharSprite()
        {
            row1 = 0b11111110,
            row2 = 0b11111111,
            row3 = 0b11000011,
            row4 = 0b11111110,
            row5 = 0b11111110,
            row6 = 0b11000011,
            row7 = 0b11111111,
            row8 = 0b11111110,
        },

        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b11000000,
            row4 = 0b11000000,
            row5 = 0b11000000,
            row6 = 0b11000000,
            row7 = 0b11111111,
            row8 = 0b11111111,
        },
        new CharSprite()
        {
            row1 = 0b11111100,
            row2 = 0b11111110,
            row3 = 0b11000111,
            row4 = 0b11000011,
            row5 = 0b11000011,
            row6 = 0b11000111,
            row7 = 0b11111110,
            row8 = 0b11111100,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b11000000,
            row4 = 0b11111100,
            row5 = 0b11111100,
            row6 = 0b11000000,
            row7 = 0b11111111,
            row8 = 0b11111111,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b11000000,
            row4 = 0b11111000,
            row5 = 0b11111000,
            row6 = 0b11000000,
            row7 = 0b11000000,
            row8 = 0b11000000,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b11000000,
            row4 = 0b11001111,
            row5 = 0b11001111,
            row6 = 0b11000011,
            row7 = 0b11111111,
            row8 = 0b11111111,
        },
        new CharSprite()
        {
            row1 = 0,
            row2 = 0,
            row3 = 0,
            row4 = 0,
            row5 = 0,
            row6 = 0,
            row7 = 0,
            row8 = 0,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b00011000,
            row4 = 0b00011000,
            row5 = 0b00011000,
            row6 = 0b00011000,
            row7 = 0b11111111,
            row8 = 0b11111111,
        },
        new CharSprite()
        {
            row1 = 0,
            row2 = 0,
            row3 = 0,
            row4 = 0,
            row5 = 0,
            row6 = 0,
            row7 = 0,
            row8 = 0,
        },
        new CharSprite()
        {
            row1 = 0,
            row2 = 0,
            row3 = 0,
            row4 = 0,
            row5 = 0,
            row6 = 0,
            row7 = 0,
            row8 = 0,
        },
        new CharSprite()
        {
            row1 = 0b11000000,
            row2 = 0b11000000,
            row3 = 0b11000000,
            row4 = 0b11000000,
            row5 = 0b11000000,
            row6 = 0b11000000,
            row7 = 0b11111111,
            row8 = 0b11111111,
        },
        new CharSprite()
        {
            row1 = 0b11000011,
            row2 = 0b11000011,
            row3 = 0b11100111,
            row4 = 0b11100111,
            row5 = 0b11011011,
            row6 = 0b11011011,
            row7 = 0b11000011,
            row8 = 0b11000011,
        },
        new CharSprite()
        {
            row1 = 0b11000011,
            row2 = 0b11100011,
            row3 = 0b11110011,
            row4 = 0b11111011,
            row5 = 0b11011111,
            row6 = 0b11001111,
            row7 = 0b11000111,
            row8 = 0b11000011,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b11000011,
            row4 = 0b11000011,
            row5 = 0b11000011,
            row6 = 0b11000011,
            row7 = 0b11111111,
            row8 = 0b11111111,
        },
        new CharSprite()
        {
            row1 = 0b11111100,
            row2 = 0b11111110,
            row3 = 0b11000011,
            row4 = 0b11111110,
            row5 = 0b11111100,
            row6 = 0b11000000,
            row7 = 0b11000000,
            row8 = 0b11000000,
        },
        new CharSprite()
        {
            row1 = 0,
            row2 = 0,
            row3 = 0,
            row4 = 0,
            row5 = 0,
            row6 = 0,
            row7 = 0,
            row8 = 0,
        },
        new CharSprite()
        {
            row1 = 0b11111100,
            row2 = 0b11111110,
            row3 = 0b11000011,
            row4 = 0b11111110,
            row5 = 0b11111100,
            row6 = 0b11000110,
            row7 = 0b11000011,
            row8 = 0b11000011,
        },
        new CharSprite()
        {
            row1 = 0b01111110,
            row2 = 0b11111111,
            row3 = 0b11000000,
            row4 = 0b11111100,
            row5 = 0b00111111,
            row6 = 0b00000011,
            row7 = 0b11111111,
            row8 = 0b01111100,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b00011000,
            row4 = 0b00011000,
            row5 = 0b00011000,
            row6 = 0b00011000,
            row7 = 0b00011000,
            row8 = 0b00011000,
        },
        new CharSprite()
        {
            row1 = 0b11000011,
            row2 = 0b11000011,
            row3 = 0b11000011,
            row4 = 0b11000011,
            row5 = 0b11000011,
            row6 = 0b11000011,
            row7 = 0b11000011,
            row8 = 0b01111110,
        },
        new CharSprite()
        {
            row1 = 0b11000011,
            row2 = 0b11000011,
            row3 = 0b11000011,
            row4 = 0b11000011,
            row5 = 0b11000011,
            row6 = 0b11000011,
            row7 = 0b01100110,
            row8 = 0b00011000,
        },
        new CharSprite()
        {
            row1 = 0,
            row2 = 0,
            row3 = 0,
            row4 = 0,
            row5 = 0,
            row6 = 0,
            row7 = 0,
            row8 = 0,
        },
        new CharSprite()
        {
            row1 = 0,
            row2 = 0,
            row3 = 0,
            row4 = 0,
            row5 = 0,
            row6 = 0,
            row7 = 0,
            row8 = 0,
        },
        new CharSprite()
        {
            row1 = 0b11000011,
            row2 = 0b11000011,
            row3 = 0b11000011,
            row4 = 0b01100110,
            row5 = 0b00011000,
            row6 = 0b00011000,
            row7 = 0b00011000,
            row8 = 0b00011000,
        },
        new CharSprite()
        {
            row1 = 0,
            row2 = 0,
            row3 = 0,
            row4 = 0,
            row5 = 0,
            row6 = 0,
            row7 = 0,
            row8 = 0,
        },
        new CharSprite()
        {
            row1 = 0b01111000,
            row2 = 0b00011000,
            row3 = 0b00011000,
            row4 = 0b00011000,
            row5 = 0b00011000,
            row6 = 0b00011000,
            row7 = 0b11111111,
            row8 = 0b11111111,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b00000011,
            row4 = 0b11111111,
            row5 = 0b11111111,
            row6 = 0b11000000,
            row7 = 0b11111111,
            row8 = 0b11111111,
        },
        new CharSprite()
        {
            row1 = 0b11111110,
            row2 = 0b11111111,
            row3 = 0b00000011,
            row4 = 0b00111100,
            row5 = 0b00111100,
            row6 = 0b00000011,
            row7 = 0b11111111,
            row8 = 0b11111110,
        },
        new CharSprite()
        {
            row1 = 0b11000011,
            row2 = 0b11000011,
            row3 = 0b11000011,
            row4 = 0b11111111,
            row5 = 0b11111111,
            row6 = 0b00000011,
            row7 = 0b00000011,
            row8 = 0b00000011,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b11000000,
            row4 = 0b11111100,
            row5 = 0b11111111,
            row6 = 0b00000011,
            row7 = 0b11111110,
            row8 = 0b11111100,
        },
        new CharSprite()
        {
            row1 = 0b00111110,
            row2 = 0b01111111,
            row3 = 0b11000000,
            row4 = 0b11111100,
            row5 = 0b11111111,
            row6 = 0b11000011,
            row7 = 0b01111110,
            row8 = 0b00111100,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b00000110,
            row4 = 0b00001100,
            row5 = 0b00110000,
            row6 = 0b00110000,
            row7 = 0b11000000,
            row8 = 0b11000000,
        },
        new CharSprite()
        {
            row1 = 0b11111111,
            row2 = 0b11111111,
            row3 = 0b11000011,
            row4 = 0b11111111,
            row5 = 0b11111111,
            row6 = 0b11000011,
            row7 = 0b11111111,
            row8 = 0b11111111,
        },
        new CharSprite()
        {
            row1 = 0b00111100,
            row2 = 0b01111110,
            row3 = 0b11000011,
            row4 = 0b11111111,
            row5 = 0b11111111,
            row6 = 0b00000011,
            row7 = 0b11111110,
            row8 = 0b01111100,
        },
        new CharSprite()
        {
            row1 = 0b00111100,
            row2 = 0b01100110,
            row3 = 0b11000011,
            row4 = 0b11000011,
            row5 = 0b11000011,
            row6 = 0b11000011,
            row7 = 0b01100110,
            row8 = 0b00111100,
        } ,
        new CharSprite()
        {
            row1 = 0b00000000,
            row2 = 0b00000000,
            row3 = 0b00000000,
            row4 = 0b00000000,
            row5 = 0b00000000,
            row6 = 0b00000000,
            row7 = 0b00000000,
            row8 = 0b00000000,
        },
        new CharSprite()
        {
            row1 = 0b00000000,
            row2 = 0b00000000,
            row3 = 0b00000000,
            row4 = 0b00000000,
            row5 = 0b00000000,
            row6 = 0b00000000,
            row7 = 0b00011000,
            row8 = 0b00011000,
        },
        new CharSprite()
        {
            row1 = 0b00000000,
            row2 = 0b00011000,
            row3 = 0b00011000,
            row4 = 0b00000000,
            row5 = 0b00000000,
            row6 = 0b00011000,
            row7 = 0b00011000,
            row8 = 0b00000000,
        },
        new CharSprite()
        {
            row1 = 0b00000000,
            row2 = 0b00000000,
            row3 = 0b00000000,
            row4 = 0b00000000,
            row5 = 0b00000000,
            row6 = 0b00110000,
            row7 = 0b00110000,
            row8 = 0b00010000,
        },
        new CharSprite()
        {
            row1 = 0b00000000,
            row2 = 0b00000000,
            row3 = 0b00000000,
            row4 = 0b00000000,
            row5 = 0b00000000,
            row6 = 0b00000000,
            row7 = 0b00000000,
            row8 = 0b00000000,
        },
        new CharSprite()
        {
            row1 = 0b11100000,
            row2 = 0b11100000,
            row3 = 0b11000000,
            row4 = 0b11000000,
            row5 = 0b11000000,
            row6 = 0b11000000,
            row7 = 0b11100000,
            row8 = 0b11100000,
        },
        new CharSprite()
        {
            row1 = 0b00000111,
            row2 = 0b00000111,
            row3 = 0b00000011,
            row4 = 0b00000011,
            row5 = 0b00000011,
            row6 = 0b00000011,
            row7 = 0b00000111,
            row8 = 0b00000111,
        },
        new CharSprite()
        {
            row1 = 0b00000000,
            row2 = 0b00000000,
            row3 = 0b00000000,
            row4 = 0b01111110,
            row5 = 0b01111110,
            row6 = 0b00000000,
            row7 = 0b00000000,
            row8 = 0b00000000,
        },
    };

    public static void DrawString(string s, int x, int y)
    {
        s = s.ToLower();
        for (int i = 0; i < s.Length; i++)
        {
            for(int o = 0; o < char_dict.Length; o++)
            {
                if(s[i] == char_dict[o])
                    DrawCharacter(font_set[o], x + i * 9, y);
            }
        }
    }

    public static unsafe void DrawCharacter(CharSprite sprite, int x, int y)
    {
        byte* p = &sprite.row1;
        for (int row = 0; row < 8; row++, p++)
        {
            for (int col = 0; col < 8; col++)
            {
                bool pixel_active = ((*p << col) & 0b10000000) == 0b10000000;
                if (pixel_active)
                    PutPixel(white, col + x, row + y);
            }
        }
    }

    #endregion
}