// SFML_Test.cpp : snake game 

#include <SFML/Graphics.hpp>   //using namespace sf 

#include <time.h> 

//New: Making the timer global
float timer = 0.0f, delay = 0.1f;


//dimensions for window size and background 

int num_vertBox = 30, num_horzBox = 20;

int size = 16; //number of pixels 

int w = size * num_horzBox;  //background number of pixels in width 

int h = size * num_vertBox;    //background number of pixels in height 



//Snake variables to dertermine length and direction 

int direction;    //direction the snake is moving  

int snake_length = 4; //initial size is 4  
int snake_length1 = 4;



//Actual Snake in game is an array of x,y coordinates of sprite2 

struct Snake
{
	int x, y;        //each sprite of snake needs an x,y coordinate 
}s[100];

struct Snake2
{
	int x, y;
}s1[100];



//***NEW*** this is the fruit or food that the snake will eat 

struct Fruit
{
	int x, y;    // only need one sprite needed for one food item 
}food;



//move snake head based on user input and body by incrementing  

//forward by iterating through arrays previous position 

void move() {


	//1st update body so everything updates in proper order 

	//move the body only!  s[0] = head will not be changed here 

	for (int i = snake_length; i > 0; i--)

	{

		s[i].x = s[i - 1].x;

		s[i].y = s[i - 1].y;

	}
	for (int i = snake_length1; i > 0; i--)
	{
		s1[i].x = s1[i - 1].x;

		s1[i].y = s1[i - 1].y;
	}

	//2nd update the head 

	//Head of snake, s[0] depends on direction user inputs  

	//if user presses up 

	if (direction == 0)

		s[0].y -= 1;
	//if user presses down 

	if (direction == 1)

		s[0].y += 1;

	//if user presses left 

	if (direction == 2)

		s[0].x -= 1;

	//if user presses right 

	if (direction == 3)

		s[0].x += 1;

	//if user2 presses w 

	if (direction == 4)

		s1[0].y -= 1;

	//if user2 presses s 

	if (direction == 5)

		s1[0].y += 1;

	//if user2 presses a 

	if (direction == 6)

		s1[0].x -= 1;

	//if user2 presses d

	if (direction == 7)

		s1[0].x += 1;



	//***NEW*** If Snake eats food it should grow 

	//check if snake head = food location 

	if (((s[0].x) == food.x) && ((s[0].y) == food.y))

	{

		//increment snake 

		snake_length++;

		//New: Increases the speed of the game after snake eats food
		delay=delay-.01;

		//Randomly place food somewhere else 

		food.x = rand() % num_horzBox;

		food.y = rand() % num_vertBox;

	}
	if (((s1[0].x) == food.x) && ((s1[0].y) == food.y))

	{

		//increment snake 

		snake_length1++;

		//New: Increases the speed of the game after snake eats food
		delay = delay - .01;

		//Randomly place food somewhere else 

		food.x = rand() % num_horzBox;

		food.y = rand() % num_vertBox;

	}



	//***NEW*** Boundary Checking snake as is hits screen end 

	//loop snake back on other side 

	//LEFT and RIGHT 

	if (s[0].x > num_horzBox)

		s[0].x = 0;

	if (s[0].x < 0)

		s[0].x = num_horzBox;

	//TOP and BOTTOM 

	if (s[0].y > num_vertBox)

		s[0].y = 0;

	if (s[0].y < 0)

		s[0].y = num_vertBox;
	//Left and Right
	if (s1[0].x > num_horzBox)

		s1[0].x = 0;

	if (s1[0].x < 0)

		s1[0].x = num_horzBox;

	//TOP and BOTTOM 

	if (s1[0].y > num_vertBox)

		s1[0].y = 0;

	if (s1[0].y < 0)

		s1[0].y = num_vertBox;


	//***NEW*** Check if you eat body of snake 

	for (int i = 1; i < snake_length; i++)

	{

		//Cut Snake body from place eaten 

		if (s[0].x == s[i].x && s[0].y == s[i].y)

		{
			snake_length = i;
			
			//New: Resets the delay after snake eats part of itself 
			delay = 0.1f;
		}
	}
	for (int i = 1; i < snake_length1; i++)
	{
		if (s1[0].x == s1[i].x && s1[0].y == s1[i].y)

		{
			snake_length1 = i;

			//New: Resets the delay after snake eats part of itself 
			delay = 0.1f;
		}
	}

}



int main()

{

	//Setting pseudorandom time,   

	srand(time(0));



	//Window that we can play the game in  

	sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");



	//Textures load an image into the GPU Memory 

	sf::Texture t1, t2, t3, t4;

	t1.loadFromFile("white.png");

	t2.loadFromFile("red.png");

	t3.loadFromFile("pineapple.png");

	t4.loadFromFile("green.png");



	//Sprite has physical dimmensions that can be set in  

	//coordinate system, setPosition(x,y), and drawn on screen 

	sf::Sprite sprite1(t1);

	sf::Sprite sprite2(t2);

	sf::Sprite sprite3(t3);

	sf::Sprite sprite4(t4);



	//***NEW*** initially place food somewhere on screen 

	food.x = 10;

	food.y = 10;



	sf::Clock clock;

	//float timer = 0.0f, delay = 0.1f;

	while (window.isOpen())

	{

		float time = clock.getElapsedTime().asSeconds();

		clock.restart();

		timer += time;



		//Allow us to check when a user does something 

		sf::Event e;



		//Check when the window is closed 

		while (window.pollEvent(e))

		{

			//If user presses x in the top right, Windows, top left, Mac,  close the window 

			if (e.type == sf::Event::Closed)

			{

				window.close();

			}

		}



		//Control for Snake by User 

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = 2;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = 3;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction = 4;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction = 5;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = 6;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = 7;



		if (timer > delay)

		{

			timer = 0; //reset timer 

			move();    //move Snake one sprite forward 

		}

		/*****************

		//Draw in window

		*****************/

		window.clear();    //clear the window so new frame can be drawn in 



		//NOTE: Order matters as we will draw over items listed first.  

		//Hence the background should be the first thing you will always do 

		//1st: Draw Background first 

		for (int i = 0; i < num_horzBox; i++)

		{

			for (int j = 0; j < num_vertBox; j++)

			{

				//Set position of sprite1 one at a time 

				sprite1.setPosition(i * size, j * size);

				//Draw sprite1 but, do not show it on screen.  

				window.draw(sprite1);

			}

		}



		//2nd: Then Draw snake otherwise background will be drawn over snake if order was reversed with background 

		for (int i = 0; i < snake_length; i++)

		{

			//position sprite2 one at a time 

			sprite2.setPosition(s[i].x * size, s[i].y * size);
			//sprite4.setPosition(s1[i].x* size, s1[i].y* size);

			//Draw sprite2 one at a time by drawing over background 

			window.draw(sprite2);
			//window.draw(sprite4);

		}
		for (int i = 0; i < snake_length1; i++)

		{

			//position sprite4 one at a time 

			sprite4.setPosition(s1[i].x * size, s1[i].y * size);

			//Draw sprite4 one at a time by drawing over background 

			window.draw(sprite4);

		}



		//***NEW*** 3rd: Draw Fruit 

		sprite3.setPosition(food.x * size, food.y * size);

		window.draw(sprite3);



		//Show everything we have drawn on the screen 

		window.display();

	}

	return 0;

}