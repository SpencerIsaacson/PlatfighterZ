﻿using Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using static Game;

class GameplayDemo : IDemo
{
    bool view_debug = false;

    //Game World
    Transform camera = new Transform();
    List<Entity> entities = new List<Entity>();
    Player[] players = new Player[PLAYER_COUNT];

    //Play variables
    const int PLAYER_COUNT = 4; //currently capped at 4, as control mappings aren't yet flexible enough to handle arbitrary numbers of players
    int winner = 0;
    bool game_over = false;
    float initial_time = 99;
    float time_remaining;
    float max_health = 10;

    public static Transform[] avatar;

    public GameplayDemo()
    {
        ResetGame();
    }

    public void Update()
    {
        //Set Time_Step
        {
            if (fixed_framerate)
                time_step = STANDARD_TIMESTEP;
            else
                time_step = delta_time;
        }

        if (!fixed_framerate || time_since_last_frame > STANDARD_TIMESTEP)
        {
            frames_since_last_second++;

            //Update
            {
                //Execute Play Logic
                {
                    if (!game_over)
                    {
                        for (int i = 0; i < PLAYER_COUNT; i++)
                        {
                            Vector3 velocity = Vector3.Zero;
                            if (players[i].avatar.transform.position.y > 0)
                            {
                                var gravity = 10;
                                players[i].y_velocity -= gravity * time_step;
                            }

                            if (!players[i].defeated)
                            {
                                bool moving = false;
                                if (keys_down[control_mappings[i, 0]])
                                {
                                    players[i].avatar.transform.rotation.y = (float)Math.PI;
                                    moving = true;
                                }
                                if (keys_down[control_mappings[i, 1]])
                                {
                                    players[i].avatar.transform.rotation.y = 0;
                                    moving = true;
                                }

                                if (moving)
                                {
                                    var rotation = players[i].avatar.transform.rotation;
                                    var playerSpeed = 5f;
                                    velocity.x = Matrix4x4.TransformVector(Matrix4x4.Rotation(rotation.x, rotation.y, rotation.z), Vector3.Right).x * playerSpeed;
                                }

                                if (players[i].avatar.transform.position.y == 0 && keys_down[control_mappings[i, 3]])
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
                                players[i].avatar.transform.position += velocity;

                                if (players[i].avatar.transform.position.y < 0)
                                {
                                    players[i].avatar.transform.position.y = 0;
                                    players[i].y_velocity = 0;
                                }
                            }
                        }

                        //Update Camera
                        {
                            float average_x = 0;
                            foreach (var player in players)
                            {
                                average_x += player.avatar.transform.position.x;
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

                //Set Stale Keys
                {
                    for (int i = 0; i < keys_stale.Length; i++)
                    {
                        if (keys_down[i])
                            keys_stale[i] = true;
                    }
                }
            }

            //Render
            {
                //Draw Background
                {
                    graphics.FillRectangle(Brushes.Gray, window.ClientRectangle);
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
                            Transform t = entities[i].transform;
                            Matrix4x4 m = t.GetMatrix();
                            m = Matrix4x4.Concat(m, camera.GetMatrix());

                            Vector3 center = Matrix4x4.TransformVector(m, Vector3.Zero) * PIXELS_PER_UNIT;
                            graphics.DrawEllipse(Pens.Blue, center.x - PIXELS_PER_UNIT / 8, center.y - PIXELS_PER_UNIT / 8, PIXELS_PER_UNIT / 4, PIXELS_PER_UNIT / 4);
                        }
                    }
                    graphics.ResetTransform();
                }

                //Draw Heads-Up Display
                {
                    for (int i = 0; i < PLAYER_COUNT; i++)
                    {
                        //DrawHealthBar
                        {
                            graphics.TranslateTransform(i * WIDTH / PLAYER_COUNT, 0);
                            float percent = (float)(Math.Truncate(players[i].health) / max_health);
                            float indent = 10;
                            float healthWidth = WIDTH / PLAYER_COUNT - indent * 2;
                            float healthHeight = 10;
                            float myWidth = percent * healthWidth;
                            graphics.FillRectangle(Brushes.Red, indent, indent, healthWidth, healthHeight);
                            graphics.FillRectangle(Brushes.Green, indent, indent, myWidth, healthHeight);
                            graphics.ResetTransform();
                        }
                    }

                    //Draw Timer
                    {
                        graphics.TranslateTransform(WIDTH / 2, 0);
                        graphics.DrawString(string.Format("{0:F0}", time_remaining), Control.DefaultFont, Brushes.White, -6, 25);
                    }

                    if (game_over)
                    {
                        //Draw Game End Message
                        {
                            graphics.TranslateTransform(0, HEIGHT / 2);
                            Point offset = new Point(24, -4);
                            string message;
                            message = (winner == 0) ? "Tie!" : ("Player " + winner + " wins!");
                            graphics.DrawString(message, Control.DefaultFont, Brushes.Red, offset.X, offset.Y);
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
                        graphics.DrawString(string.Format("FPS: {0:F2}", frames_per_second), Control.DefaultFont, Brushes.DarkBlue, PIXELS_PER_UNIT / 2, 32);
                        graphics.DrawString(string.Format("delta_time: {0:F9}", time_since_last_frame), Control.DefaultFont, Brushes.DarkBlue, PIXELS_PER_UNIT / 2, 48);
                        graphics.DrawString(string.Format("current_second: {0:F3}", portion_of_current_second_complete), Control.DefaultFont, Brushes.DarkBlue, PIXELS_PER_UNIT / 2, 64);
                        graphics.DrawString(string.Format("entities: {0}", entities.Count), Control.DefaultFont, Brushes.DarkBlue, PIXELS_PER_UNIT / 2, 80);
                    }

                    //Display Player Stats
                    {
                        for (int i = 0; i < PLAYER_COUNT; i++)
                        {
                            var p = players[i];
                            graphics.DrawString(
                                string.Format("pos: {0}\ndefeated: {1}\nhealth: {2}\nyvel: {3:F2}",
                                    p.avatar.transform.position,
                                    p.defeated,
                                    p.health,
                                    p.y_velocity),
                                Control.DefaultFont, Brushes.DarkBlue, WIDTH / PLAYER_COUNT * i + 32, PIXELS_PER_UNIT * 2f);
                        }
                        graphics.ResetTransform();
                    }
                }

                graphics_buffer.Render();
            }

            time_since_last_frame = 0;
        }

        //Update Timing
        {
            delta_time = (float)(stopwatch.Elapsed.TotalSeconds - previous_time);
            portion_of_current_second_complete += delta_time;
            time_since_last_frame += delta_time;
            if (portion_of_current_second_complete >= 1)
            {
                frames_per_second = frames_since_last_second / portion_of_current_second_complete;
                portion_of_current_second_complete = frames_since_last_second = 0;
            }
            previous_time = (float)stopwatch.Elapsed.TotalSeconds;
        }
    }

    private static bool KeyDownFresh(Keys key) { return keys_down[(int)key] && !keys_stale[(int)key]; }

    void ResetGame()
    {
        game_over = false;
        time_remaining = initial_time;
        entities.Clear();

        float distance_apart = 3.5f;
        float leftmost_position = -(PLAYER_COUNT - 1) * distance_apart / 2;
        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            players[i].health = max_health;
            players[i].defeated = false;
            players[i].avatar = new Entity();
            players[i].avatar.transform.position.x = leftmost_position + i * distance_apart;
            players[i].avatar.transform.scale = Vector3.One;
            entities.Add(players[i].avatar);
        }

        for (int i = 0; i < keys_stale.Length; i++)
        {
            keys_stale[i] = false;
        }
        camera.position = new Vector3(0, -3, 0);
        camera.scale = Vector3.One;
        stopwatch.Start();
    }
}