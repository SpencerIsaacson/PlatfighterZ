using Engine;
using System.Collections.Generic;
using static Engine.Global;

static class DefinedAnimations
{
    public static List<AnimationCurve> walk_curves = new List<AnimationCurve>
        {
            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 1,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -0.25f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = -0.25f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 2, //chest 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -0.5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = +0.5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4, //left shoulder 
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/6 },
                    new KeyFrame {frame = 32, value = Tau/6 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4, //left shoulder 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -0.5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = 0.5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 5, //left elbow 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .5f },
                    new KeyFrame {frame = 60, value = .5f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6, //right shoulder 
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/6 },
                    new KeyFrame {frame = 32, value = -Tau/6 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6, //right shoulder 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -0.5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = 0.5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 7, //right elbow 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -.5f },
                    new KeyFrame {frame = 32, value = -.5f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 8, //left hip 
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -.5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = .5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 9, //left knee 
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 16, value = .5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 11, //right hip 
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = .5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = -.5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 12, //right knee 
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = 0 },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = .5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
        };
    public static List<AnimationCurve> punch_curves = new List<AnimationCurve>
    {
        new AnimationCurve()
        {
            transform_index = 1, //core 
            property_tag = 1,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 0 },
                new KeyFrame {frame = 30, value = 0 },
            },
        },
        new AnimationCurve()
        {
            transform_index = 1, //core
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = .3f },
                new KeyFrame {frame = 30, value = .3f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 2, //chest
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = .0f },
                new KeyFrame {frame = 15, value = -.9f },
                new KeyFrame {frame = 30, value = .0f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 4,
            property_tag = 5,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = Tau/4f },
                new KeyFrame {frame = 30, value = Tau/4f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 4,
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = Tau/6f },
                new KeyFrame {frame = 15, value = -Tau/9f },
                new KeyFrame {frame = 30, value = Tau/6f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 5,
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = Tau/4f },
                new KeyFrame {frame = 30, value = Tau/4f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 6,
            property_tag = 5,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = -Tau/4f },
                new KeyFrame {frame = 15, value = 0 },
                new KeyFrame {frame = 30, value = -Tau/4f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 6,
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = -Tau/6f },
                new KeyFrame {frame = 15, value = -Tau/4 },
                new KeyFrame {frame = 30, value = -Tau/6f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 7,
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = -Tau/4f },
                new KeyFrame {frame = 15, value = 0 },
                new KeyFrame {frame = 30, value = -Tau/4f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 8,
            property_tag = 3,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 0f },
                new KeyFrame {frame = 30, value = 0f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 9,
            property_tag = 3,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 0f },
                new KeyFrame {frame = 30, value = 0f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 11,
            property_tag = 3,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 0.3f },
                new KeyFrame {frame = 30, value = 0.3f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 12,
            property_tag = 3,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 0f },
                new KeyFrame {frame = 30, value = 0f },
            },
        },
    };
    public static List<AnimationCurve> idle_curves = new List<AnimationCurve>
        {
            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 1,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = -.07f },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 1, //core
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .3f },
                    new KeyFrame {frame = 60, value = .3f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 2, //chest
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .0f },
                    new KeyFrame {frame = 30, value = .3f },
                    new KeyFrame {frame = 60, value = .0f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4,
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/4f },
                    new KeyFrame {frame = 30, value = Tau/5f },
                    new KeyFrame {frame = 60, value = Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4,
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/6f },
                    new KeyFrame {frame = 30, value = Tau/8f },
                    new KeyFrame {frame = 60, value = Tau/6f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 5,
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/4f },
                    new KeyFrame {frame = 30, value = Tau/3f },
                    new KeyFrame {frame = 60, value = Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6,
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/4f },
                    new KeyFrame {frame = 30, value = -Tau/5f },
                    new KeyFrame {frame = 60, value = -Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6,
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/6f },
                    new KeyFrame {frame = 30, value = -Tau/8f },
                    new KeyFrame {frame = 60, value = -Tau/6f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 7,
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/4f },
                    new KeyFrame {frame = 30, value = -Tau/3f },
                    new KeyFrame {frame = 60, value = -Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 8,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = -0.3f },
                    new KeyFrame {frame = 60, value = 0f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 9,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = 0.6f },
                    new KeyFrame {frame = 60, value = 0f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 11,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0.3f },
                    new KeyFrame {frame = 30, value = 0.0f },
                    new KeyFrame {frame = 60, value = 0.3f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 12,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = 0.6f },
                    new KeyFrame {frame = 60, value = 0f },
                },
            },
        };
    public static List<AnimationCurve> jump_curves = new List<AnimationCurve>
        {
            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 1,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 27, value = -0.75f },
                    new KeyFrame {frame = 30, value = -0.5f },
                    new KeyFrame {frame = 45, value = 0f },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 8,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = -0.5f },
                    new KeyFrame {frame = 40, value = 0 },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 9,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = 1f },
                    new KeyFrame {frame = 40, value = 0 },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 11,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = -0.5f },
                    new KeyFrame {frame = 40, value = 0 },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 12,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = 1f },
                    new KeyFrame {frame = 40, value = 0 },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4,
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 1/4f*Tau },
                    new KeyFrame {frame = 30, value = 1/8f*Tau },
                    new KeyFrame {frame = 40, value = 1/4f*Tau },
                    new KeyFrame {frame = 60, value = 1/4f*Tau },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6,
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -1/4f*Tau },
                    new KeyFrame {frame = 30, value = -1/8f*Tau },
                    new KeyFrame {frame = 40, value = -1/4f*Tau },
                    new KeyFrame {frame = 60, value = -1/4f*Tau },
                },
            },
        };

    public static Animation idle_animation = new Animation() { curves = idle_curves };
    public static Animation walk_animation = new Animation() { curves = walk_curves };
    public static Animation punch_animation = new Animation()
    {
        curves = punch_curves,
        attackbox_keys = new int[][]
        {
            new int[] { 1 },
            new int[] { 1, 5, 20 },
        },
        attackbox_values = new bool[][]
        {
            new bool[]{ false },
            new bool[]{ false, true, false },
        }
    };
    public static Animation jump_animation = new Animation() { curves = jump_curves };
}