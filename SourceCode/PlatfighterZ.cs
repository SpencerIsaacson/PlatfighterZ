using Engine;
using static Engine.Global;
using static Game;

unsafe struct PlatfighterZ
{
    public static FixedBuffer buffer = new FixedBuffer();

    static void Main()
    {
        fixed (byte* start = buffer.bytes)
        {
            Transform* p = (Transform*)start;

            for (int i = 0; i < 10; i++)
            {
                (*p).position = Vector3.Forward;
                (*p).rotation = new Vector3(0, Tau / 4, 0);
                (*p).parent = 2;
            }
        }
    }
}

unsafe struct FixedBuffer
{
    public fixed byte bytes[1024];
}