﻿using Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using static Game;
using static Engine.Global;

class GameplayDemo : IDemo
{
    bool view_debug = false;

    //Game World
    Transform camera = new Transform();
    List<Transform> entities = new List<Transform>();
    Player[] players = new Player[PLAYER_COUNT];

    //Play variables
    const int PLAYER_COUNT = 4; //currently capped at 4, as control mappings aren't yet flexible enough to handle arbitrary numbers of players
    int winner = 0;
    bool game_over = false;
    float initial_time = 99;
    float time_remaining;
    float max_health = 10;

    Color[] player_colors = new Color[]{Color.Red,Color.Green,Color.Blue,Color.Purple};
    public GameplayDemo()
    {
        ResetGame();
    }

    public void Update()
    {
        //Update
        {
            //Execute Play Logic
            {
                if (!game_over)
                {
                    for (int i = 0; i < PLAYER_COUNT; i++)
                    {
                        Transform playerEntity = entities[players[i].entity_ID];
                        Vector3 velocity = Vector3.Zero;
                        if (playerEntity.position.y > 0)
                        {
                            var gravity = 10;
                            players[i].y_velocity -= gravity * time_step;
                        }

                        if (!players[i].defeated)
                        {
                            bool moving = false;
                            if (keys_down[control_mappings[i, 0]])
                            {
                                playerEntity.rotation.y = (float)Math.PI;
                                moving = true;
                            }
                            if (keys_down[control_mappings[i, 1]])
                            {
                                playerEntity.rotation.y = 0;
                                moving = true;
                            }

                            if (moving)
                            {
                                var rotation = playerEntity.rotation;
                                var playerSpeed = 5f;
                                velocity.x = TransformVector(Rotation(rotation.x, rotation.y, rotation.z), Vector3.Right).x * playerSpeed;
                            }

                            if (playerEntity.position.y == 0 && keys_down[control_mappings[i, 3]])
                                players[i].y_velocity = 10;


                            //AnimatePlayer
                            {
                                //TODO
                            }

                        }

                        //MovePlayer
                        {
                            velocity.y = players[i].y_velocity;
                            velocity *= time_step;
                            playerEntity.position += velocity;

                            if (playerEntity.position.y < 0)
                            {
                                playerEntity.position.y = 0;
                                players[i].y_velocity = 0;
                            }

                            entities[players[i].entity_ID] = playerEntity;
                        }

						// //Hurt Player
						// {
						// 	players[i].health -= time_step * (6*i + 1);

						// 	if(players[i].health <= 0)
						// 	{
						// 		players[i].stock--;
						// 		if(players[i].stock > 0)
						// 			players[i].health = max_health;
						// 		else
						// 			players[i].defeated = true;
						// 	}
						// }
                    }

                    //Update Camera
                    {
                        float average_x = 0;
                        foreach (var player in players)
                        {
                            average_x += entities[player.entity_ID].position.x;
                        }
                        average_x /= PLAYER_COUNT;

                        camera.position.x = camera.position.x + time_step * (-average_x - camera.position.x);
                    }

                    //Check if the game is ongoing
                    {
                        int remaining_players = 0;

                        //Check Winner
                        {

                            for (int i = 0; i < PLAYER_COUNT; i++)
                            {
                                if (!players[i].defeated)
                                {
                                    winner = i + 1;
                                    remaining_players++;
                                    if (remaining_players != 1)
                                        winner = 0;
                                }
                            }
                        }

                        //Check Match Complete
                        {
                            game_over = winner != 0 || remaining_players == 0;
                            time_remaining -= time_step;
                            if (time_remaining <= 0)
                            {
                                game_over = true;
                            }
                        }
                    }
                }
            }

            //Get Debug Input
            {
                if (KeyDownFresh(Keys.G))
                    view_debug = !view_debug;

                if (KeyDownFresh(Keys.R))
                    ResetGame();

                if (KeyDownFresh(Keys.F))
                    fixed_framerate = !fixed_framerate;
            }
        }

        //Render
        {
            //Draw Background
            {
                if(view_debug)
                    graphics.FillRectangle(Brushes.Gray, window.ClientRectangle);
                else
                    graphics.FillRectangle(new SolidBrush(Color.FromArgb(255,30,30,40)), window.ClientRectangle);                    
                graphics.FillRectangle(Brushes.DarkSlateGray, 0, HEIGHT - PIXELS_PER_UNIT, WIDTH, PIXELS_PER_UNIT);
            }

            //Draw Entities
            {
                graphics.ResetTransform();
                graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);
                graphics.ScaleTransform(1, -1);
                for (int i = 0; i < entities.Count; i++)
                {
                    //DrawTransform
                    {
                        Transform t = entities[i];
                        Matrix4x4 m = GetMatrix(t);
                        m = Concat(m, GetMatrix(camera));

                        Vector3 center = TransformVector(m, Vector3.Zero) * PIXELS_PER_UNIT;
                        graphics.FillEllipse(new SolidBrush(player_colors[i]), center.x - PIXELS_PER_UNIT / 8, center.y - PIXELS_PER_UNIT / 8, PIXELS_PER_UNIT / 4, PIXELS_PER_UNIT / 4);
                    }
                }
                graphics.ResetTransform();
            }

            //Draw Heads-Up Display
            {
				var available_space = WIDTH / PLAYER_COUNT;
				Point indent = new Point(30, 10);
				Pen stroke = new Pen(Color.Black, 3f);
                int healthWidth = available_space - indent.X * 2;
                int healthHeight = 15;

                for (int player = 0; player < PLAYER_COUNT; player++)
                {
					//Draw HealthBar
                    {
                        float percent = (float)(players[player].health) / max_health;                        
                        int myWidth = (int)(percent * (float)healthWidth);
						Rectangle rect = new Rectangle(indent.X, indent.Y, healthWidth, healthHeight);

                        graphics.FillRectangle(Brushes.Red, rect);
						rect.Width = myWidth;
                        graphics.FillRectangle(Brushes.Green, rect);
						rect.Width = healthWidth;
						graphics.DrawRectangle(stroke, rect);
                    }

					//Draw Stocks
					{
						Rectangle rect = new Rectangle(indent.X, 30, 20, 20);

						for (int stock = 0; stock < players[player].stock; stock++)
						{
							graphics.FillEllipse(new SolidBrush(player_colors[player]), rect);
							graphics.DrawEllipse(stroke, rect);
							graphics.FillEllipse(new SolidBrush(ControlPaint.Light(player_colors[player])), rect.X + 4, rect.Y + 4, 10, 10);
							rect.X += 25;
						}
					}

                    graphics.TranslateTransform(available_space, 0);                    
                }

                graphics.ResetTransform();

                //Draw Timer
                {
                    graphics.TranslateTransform(WIDTH / 2 -2, 0);
                    graphics.ScaleTransform(2f, 2f);
                    graphics.DrawString(string.Format("{0:F0}", time_remaining), Control.DefaultFont, Brushes.White, -6, 5);
                    graphics.ScaleTransform(.5f, .5f);
                }

                if (game_over)
                {
                    //Draw Game End Message
                    {
                        Point offset = new Point(-40, -20);
                        string message = (winner == 0) ? "TIE!" : ("PLAYER " + winner + " WINS!");
                        graphics.TranslateTransform(0, HEIGHT / 2);
                        graphics.ScaleTransform(4, 4);
                        graphics.DrawString(message, Control.DefaultFont, Brushes.Black, offset.X-1, offset.Y+1);
                        graphics.DrawString(message, Control.DefaultFont, Brushes.Yellow, offset.X, offset.Y);
                        graphics.ScaleTransform(.25f, .25f);
                    }
                }

                graphics.ResetTransform();
            }

            if (view_debug)
            {
                //Draw Grid
                {
                    var pen = new Pen(Color.FromArgb(90, 50, 50, 50));
                    for (int x = 0; x < WIDTH / PIXELS_PER_UNIT; x++)
                        graphics.DrawLine(pen, x * PIXELS_PER_UNIT, 0, x * PIXELS_PER_UNIT, HEIGHT);
                    for (int y = 0; y < HEIGHT / PIXELS_PER_UNIT; y++)
                        graphics.DrawLine(pen, 0, y * PIXELS_PER_UNIT, WIDTH, y * PIXELS_PER_UNIT);
                }

                //Display Game Stats
                {
                    graphics.DrawString(string.Format("FPS: {0:F2}", frames_per_second), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 50);
                    graphics.DrawString(string.Format("delta_time: {0:F9}", delta_time), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 65);
                    graphics.DrawString(string.Format("current_second: {0:F3}", portion_of_current_second_complete), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 80);
                    graphics.DrawString(string.Format("entities: {0}", entities.Count), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 95);
                }
            }

            graphics_buffer.Render();
        }
    }

    void ResetGame()
    {
        game_over = false;
        time_remaining = initial_time;
        entities.Clear();

        float distance_apart = 3.5f;
        float leftmost_position = -(PLAYER_COUNT - 1) * distance_apart / 2;

        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            Transform entity = new Transform();
            entity.position.x = leftmost_position + i * distance_apart;
            entity.scale = Vector3.One;

            players[i].health = max_health;
            players[i].defeated = false;
            players[i].entity_ID = entities.Count;
			players[i].stock = 5;
            entities.Add(entity);
        }

        for (int i = 0; i < keys_stale.Length; i++)
        {
            keys_stale[i] = false;
        }

        camera.position = new Vector3 { x = 0, y = -3, z = 0 };
        camera.scale = Vector3.One;
        stopwatch.Start();
    }
}
