using System;

namespace utils
{
    class Colors
    {
        // Colors
        public static readonly (int, int, int) RED = (255, 0, 0);
        public static readonly (int, int, int) GREEN = (0, 255, 0);
        public static readonly (int, int, int) BLUE = (0, 0, 255);
        public static readonly (int, int, int) WHITE = (255, 255, 255);
        public static readonly (int, int, int) BLACK = (0, 0, 0);
        public static readonly (int, int, int) YELLOW = (255, 255, 0);
        public static readonly (int, int, int) PURPLE = (255, 0, 255);
        public static readonly (int, int, int) CYAN = (0, 255, 255);
        public static readonly (int, int, int) ORANGE = (255, 165, 0);
        public static readonly (int, int, int) PINK = (255, 192, 203);

        // Pick a random color from the list
        public static (int, int, int) RandomColor()
        {
            Random random = new Random();
            (int, int, int)[] colors = { RED, GREEN, BLUE, WHITE, YELLOW, PURPLE, CYAN, ORANGE, PINK };
            return colors[random.Next(0, colors.Length)];
        }

        // Pick a random color rgb
        public static (int, int, int) RandomRGB()
        {
            Random random = new Random();
            return (random.Next(0, 255), random.Next(0, 255), random.Next(0, 255));
        }

        // Pick a random color hex
        public static string RandomHex()
        {
            Random random = new Random();
            return String.Format("#{0:X6}", random.Next(0x1000000));
        }
    }
}
