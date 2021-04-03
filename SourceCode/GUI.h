int GetID(string message) // TODO replace naive "hash" with 32 bit cycle redundancy check
{
	int id = 0;
	{
		for (int i = 0; i < message.length; ++i)
		{
			id += message.characters[i];
		}

		id %= message.length;
	}

	return id;
}


bool Button(char* text, int x, int y, int width, int height)
{
	static int selected_button = -1;
	bool in_rectangle;
	bool is_active = false;
	in_rectangle = mousestate.position.x > x && mousestate.position.x < x+width && mousestate.position.y > y && mousestate.position.y < y+height;


	string message = WrapString(text);
	int id = GetID(message);

	if(selected_button == -1 && mousestate.leftbutton_down && !mousestate.leftbutton_was_down && in_rectangle) 
	{
		selected_button = id;
	}

	is_active = selected_button == id;

	Color color = (is_active) ? 0x666666 : 0xAAAAAA;

	if(is_active)
	{
		x-=2;
		y+=2;
	}

	FillRectangle(color, x, y, width, height);
	DrawRectangle(black, x, y, width, height);
	DrawString(message, x + width/2 - message.length*9/2, y + height/2 - 8/2); //TODO get rid of magic numbers

	if(!mousestate.leftbutton_down && is_active)
		selected_button = -1;
	return is_active && !mousestate.leftbutton_down;
}


float Slider(char* text, float min, float max, int x, int y, int width, float* value)
{
	static int selected_slider = -1;
	string message = WrapString(text);
	int id = GetID(message);

	float scrubber_radius = 10;
	float range = max-min;

	bool in_scrubber = v2_Distance(mousestate.position, (v2){x+((*value)/range*width),y}) < scrubber_radius;
	Color scrubber_color = (in_scrubber | selected_slider == id) ? red : 0xFF333333;
	if(selected_slider == -1 && mousestate.leftbutton_down && !mousestate.leftbutton_was_down && in_scrubber) 
		selected_slider = id;

	if(mousestate.leftbutton_down && selected_slider == id)
	{
		*value = (mousestate.position.x-x)/width*range;
	}

	if(*value < min)
		*value = min;
	if(*value > max)
		*value = max;

	float scaled_value = (*value)/range;
	
	scaled_value*=width;
	
	FillRectangle(0xFF555555,x,y, width, 10);
	FillCircle(scrubber_color,x+scaled_value,y+5,scrubber_radius);
	DrawString(message,x + width/2 - message.length*9/2, y- 8/2);
	char chars[40];
	sprintf(chars, "%f", *value);
	DrawString(WrapString(chars),x,y+10);
	if(!mousestate.leftbutton_down)
		selected_slider = -1;
	
	return *value;
}