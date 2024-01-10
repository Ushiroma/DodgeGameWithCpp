#include "raylib.h"



int main()
{
    //Window
    int width{550},height{400}; 
    
    //Circle   
    int circle_x = width/2;
    int circle_y =300;
    int r = 10;
    //Circle boundaries
    int l_circle_x{circle_x - r}, r_circle_x{circle_x + r}, t_circle_y{circle_y - r}, b_circle_y{circle_y + r};

    //Rectangle
    int axe_x{400}, axe_y{0}, axe_length{50}, axe_width{50};
    int direction{10};
    //Rectangle boundaries
    int l_axe{axe_x}, r_axe{axe_x + axe_length}, t_axe{axe_y}, b_axe{axe_y + axe_length};

    //Collision bool
    bool Collision = (b_axe >= t_circle_y) && (t_axe <= b_circle_y) && (l_axe <= r_circle_x) && r_axe >= l_circle_x;

    //Random Value
    int randValue = GetRandomValue(1, 380);
    unsigned int framesCounter = 0;

    //High Score
    int score{0};

    SetTargetFPS(90);

    InitWindow(width, height, "Flags");
    while (WindowShouldClose() == false)
    {
        //Count Frames
        framesCounter++;

        // Every two seconds (120 frames) a new random value is generated
        if (((framesCounter/60)%2) == 1)
        {
            randValue = GetRandomValue(50, (width - 50));
            framesCounter = 0;
            axe_x = randValue;
        }

        BeginDrawing(); //Setup Canvas
        ClearBackground(WHITE); //Clears the canvas
        

        //Collision
        if(Collision == true)
        {
            DrawText("Game Over!", 250, 100, 20, RED);
            DrawText(TextFormat("%s %i", "Score:",score), 250, 150, 20, BLACK);
        }

        else //Game logic
        {
            //Update Circle Position
            l_circle_x = circle_x - r;
            r_circle_x = circle_x + r;
            t_circle_y = circle_y - r;
            b_circle_y = circle_y + r;

            //Update Axe Position
            l_axe =axe_x;
            r_axe = axe_x + axe_length;
            t_axe = axe_y;
            b_axe = axe_y + axe_length;

            //Update Collision
            Collision = (b_axe >= t_circle_y) && (t_axe <= b_circle_y) && (l_axe <= r_circle_x) && r_axe >= l_circle_x;

            DrawCircle(circle_x, circle_y, r, RED);
            DrawRectangle(axe_x,axe_y,axe_length,axe_width,RED);

            //Move axe down
            axe_y += direction;

            if(axe_y > (height+200))
            {
                score++;
                DrawRectangle(axe_x,axe_y,axe_length,axe_width,RED);
                direction = 10;
                axe_y = 0;
                 //DrawText(TextFormat("%i", randValue), 360, 180, 80, BLACK);
            }

            //Move circle to the left
            if(IsKeyDown(KEY_A) && circle_x > 0)
            {
                circle_x = circle_x - 5;
            }
            //Move circle right
            if(IsKeyDown(KEY_D) && circle_x < width)
            {
                circle_x = circle_x + 5;
            }
        }
        
        EndDrawing(); //Destroy Canvas
    }
    
    return 0;
}