#define Tau 6.28318530717958f
#define Pi 3.14159265358979f
float GetMin3(float a, float b, float c)
{
    float r = (a < b) ? a : b;
    return (r < c) ? r : c;
}

float GetMax3(float a, float b, float c)
{
    float r = (a > b) ? a : b;
    return (r > c) ? r : c;
}

void Clamp(int* value, int low, int high)
{
    if(*value < low)
        *value = low;
    if(*value > high)
        *value = high;
}

void Clamp_Float(float* value, float low, float high)
{
    if(*value < low)
        *value = low;
    if(*value > high)
        *value = high;
}

string WrapString(char* message)
{
    return (string){.characters = message, .length = strlen(message)};
}

v2 Lerp_v2(v2 a, v2 b, float t)
{
    v2 v;
    v.x = a.x + (t * (b.x - a.x));
    v.y = a.y + (t * (b.y - a.y));
    return v;
}

float Lerp_Float(float a, float b, float t)
{
    return a + t * (b - a);
}

float Sample(KeyFrame a, KeyFrame b, float frame)
{
    float t = .5f;
    float step = .25f;
    v2 c1 = { a.frame, a.value };
    v2 c2 = { a.frame + a.right_handle_x, a.value + a.right_handle_y };
    v2 c3 = { b.frame + b.left_handle_x, b.value + b.left_handle_y };
    v2 c4 = { b.frame, b.value };

    while (true)
    {
        v2 d = Lerp_v2(c1, c2, t);
        v2 e = Lerp_v2(c2, c3, t);
        v2 f = Lerp_v2(c3, c4, t);
        v2 g = Lerp_v2(d, e, t);
        v2 h = Lerp_v2(e, f, t);
        v2 i = Lerp_v2(g, h, t);

        if (i.x > frame)
            t -= step;
        else
            t += step;

        step /= 2;

        if (fabs(i.x - frame) < .001f)
            return i.y;
    }
}

v2 Sample2_v2(v2 c1, v2 c2, v2 c3, v2 c4, float x)
{
    float t = (x - c1.x) / (c4.x - c1.x);

    v2 d = Lerp_v2(c1, c2, t);
    v2 e = Lerp_v2(c2, c3, t);
    v2 f = Lerp_v2(c3, c4, t);

    v2 g = Lerp_v2(d, e, t);
    v2 h = Lerp_v2(e, f, t);
    
    v2 i = Lerp_v2(g, h, t);

    return i;
}


void AnimateProperty(AnimationCurve curve, float frame, float* property)
{
    for (size_t o = 0; o < curve.keyframes_count; o++)
    {
        KeyFrame keyframe = curve.keyframes[o];
    }

    int n = curve.keyframes_count;
    for (int i = 0; i < n - 1; i++)
    {
        KeyFrame a = curve.keyframes[i];
        KeyFrame b = curve.keyframes[i + 1];
        if (frame >= a.frame && frame <= b.frame)
        {
            *property = Sample(a, b, frame);
            return;
        }
    }
}


int set_parent(Entity* child, Entity* parent)
{
    #define child_of_self_error -1
    Entity* parpar = parent;

    while(parpar != NULL)
    {
        if(parpar == child)
            return child_of_self_error;
        parpar = parpar->parent;
    }

    child->parent = parent;
    return 0;
}