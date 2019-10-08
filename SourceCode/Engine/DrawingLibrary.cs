using static Game;
using static FullScreener;

static class DrawingLibrary
{
    public const uint red = 0xFF_FF_00_00;
    public const uint green = 0xFF_00_FF_00;
    public const uint blue = 0xFF_00_00_FF;

    public const uint cyan = green | blue;
    public const uint magenta = red | blue;
    public const uint yellow = red | green;

    public const uint black = 0xFF_00_00_00;
    public const uint white = red | green | blue;


    public static void Phil(uint color)
    {
        for (int i = 0; i < pixels.Length; i++)
        {
            pixels[i] = color;
        }
    }


    public static uint Darker(uint color)
    {
        uint r = (color & red ^ black) >> 17 << 16;
        uint g = (color & (green ^ black)) >> 9 << 8;
        uint b = (color & blue ^ black) >> 1;
        return black | r | g | b;
    }


    public static void DrawHorizontal(uint color, int y)
    {
        for (int i = y * WIDTH; i < y * WIDTH + WIDTH; i++)
            pixels[i] = color;
    }


    public static void DrawVertical(uint color, int x)
    {
        for (int i = x; i < pixels.Length - WIDTH - x; i += WIDTH)
        {
            pixels[i] = color;
        }
    }


    public static void DrawGrid_ScreenSpace(int unit_size)
    {
        for (int x = 0; x < WIDTH; x += unit_size)
        {
            DrawVertical(green, x);
        }

        for (int y = 0; y < HEIGHT; y += unit_size)
        {
            DrawHorizontal(green, y);
        }
    }


    public static void DrawHorizontalSegment(uint color, int y, int x1, int x2)
    {
        var pixel_row = y * WIDTH;

        for (int i = pixel_row + x1; i <= pixel_row + x2; i++)
        {
            int x = i - pixel_row;
            if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
                pixels[i] = color;
        }
    }


    public static void DrawVerticalSegment(uint color, int x, int y1, int y2)
    {
        for (int i = x + (y1 * WIDTH); i <= x + (y2 * WIDTH); i += WIDTH)
            pixels[i] = color;
    }


    public static void Phil_Rectangle(uint color, int x, int y, int width, int height)
    {

        int start = y * WIDTH + x;
        int end = (y + height) * WIDTH + (x + width);
        int line_end = start + width;

        for (int i = start; i <= end; i++)
        {
            pixels[i] = color;

            if (i == line_end)
            {
                i += (WIDTH - width) - 1;
                line_end += WIDTH;
            }
        }
    }


    public static void Phil_Circle(uint color, int x, int y, int radius)
    {
        int x_min = (x - radius);
        int x_max = (x + radius);
        int y_min = (y - radius);
        int y_max = (y + radius);

        for (int _x = x_min; _x <= x_max; _x++)
        {
            for (int _y = y_min; _y <= y_max; _y++)
            {
                int dx = _x - x;
                int dy = _y - y;

                bool distance_less_than_radius = dx * dx + dy * dy <= radius * radius;
                bool pixel_within_screen_bounds = _x >= 0 && _x < WIDTH && _y >= 0 && _y < HEIGHT;

                if (distance_less_than_radius && pixel_within_screen_bounds)
                    pixels[(_y * WIDTH + _x)] = color;
            }
        }

    }


    public static void Phil_FlatTop(uint color, int top, int left, int right, int bottom, int middle)
    {
        float dy = bottom - top;

        float inverted_slope1 = (middle - left) / dy;
        float inverted_slope2 = (middle - right) / dy;

        float l = left;
        float r = right;
        for (int scanline = top; scanline <= bottom; scanline++)
        {
            DrawHorizontalSegment(color, scanline, (int)(l), (int)(r));
            l += inverted_slope1;
            r += inverted_slope2;
        }
    }


    public static void Phil_FlatBottom(uint color, int bottom, int left, int right, int top, int middle)
    {
        float dy = bottom - top;

        float inverted_slope1 = (middle - left) / dy;
        float inverted_slope2 = (middle - right) / dy;

        float l = left;
        float r = right;

        for (int scanline = bottom; scanline >= top; scanline--)
        {
            DrawHorizontalSegment(color, scanline, (int)(l), (int)(r));
            l += inverted_slope1;
            r += inverted_slope2;
        }
    }


    /// <summary>
    /// Our good friend Phil Triangle here loves to draw. He draws small triangles much faster than large triangles.
    /// </summary>
    public static void Phil_Triangle(uint color, int x1, int y1, int x2, int y2, int x3, int y3)
    {
        if (y1 == y2 && y2 == y3)
            return;
        //Sort Points
        int temp;
        if (y1 > y2)
        {
            temp = y1;
            y1 = y2;
            y2 = temp;
            temp = x1;
            x1 = x2;
            x2 = temp;
        }
        if (y1 > y3)
        {
            temp = y1;
            y1 = y3;
            y3 = temp;
            temp = x1;
            x1 = x3;
            x3 = temp;
        }
        if (y2 > y3)
        {
            temp = y2;
            y2 = y3;
            y3 = temp;
            temp = x2;
            x2 = x3;
            x3 = temp;
        }

        int split = (int)(x1 + ((y2 - y1) / (float)(y3 - y1)) * (x3 - x1));

        if (x2 < split) // major right
        {
            Phil_FlatBottom(color, y2, x2, split, y1, x1);
            Phil_FlatTop(color, y2, x2, split, y3, x3);
        }
        else //major left
        {
            Phil_FlatBottom(color, y2, split, x2, y1, x1);
            Phil_FlatTop(color, y2, split, x2, y3, x3);
        }
    }
}
