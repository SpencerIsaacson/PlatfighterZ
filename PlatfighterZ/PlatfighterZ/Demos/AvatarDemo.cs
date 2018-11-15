using Engine;
using System;
using System.Drawing;
using System.Windows.Forms;
using static Game;

class AvatarDemo : IDemo
{
    Transform[] avatar;

    public AvatarDemo()
    {
        avatar = new Transform[14];
        transforms = avatar;

        for (int i = 0; i < avatar.Length; i++)
        {
            avatar[i].scale = new Vector3(1, 1, 1);
        }

        avatar[1].position = new Vector3(0, 1, 0); //waist
        avatar[2].position = new Vector3(0, .8f, 0); //neck
        avatar[3].position = new Vector3(0, .3f, 0); //head
        avatar[4].position = new Vector3(-.4f, 0, 0); //right shoulder
        avatar[5].position = new Vector3(-.4f, 0, 0); //right wrist
        avatar[6].position = new Vector3(.4f, 0, 0); //left shoulder
        avatar[7].position = new Vector3(.4f, 0, 0); //left wrist
        avatar[8].position = new Vector3(-.2f, 0, 0); //right leg
        avatar[9].position = new Vector3(0, -.5f, 0); //right knee
        avatar[10].position = new Vector3(0, -.5f, 0); //right foot
        avatar[11].position = new Vector3(.2f, 0, 0); //left leg
        avatar[12].position = new Vector3(0, -.5f, 0); //left knee
        avatar[13].position = new Vector3(0, -.5f, 0); //left foot

        avatar[13].parent = 13;
        avatar[12].parent = 12;
        avatar[11].parent = 2;
        avatar[10].parent = 10;
        avatar[9].parent = 9;
        avatar[8].parent = 2;
        avatar[7].parent = 7;
        avatar[6].parent = 3;
        avatar[5].parent = 5;
        avatar[4].parent = 3;
        avatar[3].parent = 3;
        avatar[2].parent = 2;
        avatar[1].parent = 1;

        avatar[0].rotation.y = (float)-Math.PI / 2;
    }

    public void Update()
    {
        if(keys_down[(int)Keys.D])
            avatar[0].position.x += .01f;
        if (keys_down[(int)Keys.A])
            avatar[0].position.x -= .01f;
        if (keys_down[(int)Keys.Space])
            avatar[0].rotation.y += .01f;

        graphics.FillRectangle(Brushes.Black, window.ClientRectangle);
        
        //Draw Entities
        {
            graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);
            graphics.ScaleTransform(1, -1);

            //Draw Transforms
            for (int i = 0; i < avatar.Length; i++)
            {
                var position = Matrix4x4.TransformVector(Matrix4x4.WorldSpaceMatrix(avatar[i]), new Vector3());
                var d = .75f - position.z / 10f;
                graphics.DrawEllipse(Pens.Blue, position.x / d * PIXELS_PER_UNIT, position.y / d * PIXELS_PER_UNIT, PIXELS_PER_UNIT / (d * 8), PIXELS_PER_UNIT / (d * 8));
            }

            graphics.ResetTransform();
            graphics_buffer.Render();
        }
    }
}