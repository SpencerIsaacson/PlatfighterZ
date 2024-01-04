typedef struct Timing
{
	//Timing
	float TIME_RECALCULATION_INTERVAL; //1.0f
	float TARGET_FRAMERATE;// 60.0f
	float STANDARD_TIMESTEP;// 1 / TARGET_FRAMERATE
	clock_t previous_time;
	float delta_time;
	float time_since_last_frame;
	float time_scale; //1f
	float frames_per_second;
	float time_since_timing_recalculated;
	bool fixed_framerate; //false
	int frames_since_last_second;
} Timing;

Timing timing;

void InitTiming()
{
	timing.TIME_RECALCULATION_INTERVAL = .5f;
	timing.TARGET_FRAMERATE = 30.0f;
	timing.STANDARD_TIMESTEP = 1 / timing.TARGET_FRAMERATE;
	timing.time_scale = 1.0f;
	timing.fixed_framerate = false;
}