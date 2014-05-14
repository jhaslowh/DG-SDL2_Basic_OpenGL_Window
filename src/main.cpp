#ifdef WIN32
//pragma to remove extra console window under windows
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#include "main.h"

using namespace std;

/**
* Called at the begining of the game to load resources 
*/
int init_resources()
{
	printf("Loading Resources...\n");

	// Set up shaders 
	if (mgl.load(SCREEN_WIDTH, SCREEN_HEIGHT) == 0){
		cout << "Error setting up OpenGL\n";
		return 0;
	}
	glUseProgram(mgl.program);
	// Setup ortho matrix
	mgl.setOrthoMatrix(SCREEN_WIDTH, SCREEN_HEIGHT);
	// Setup basic testing projection matrix 
	mgl.setCamera3DMatrix(glm::vec3(0,20,50), glm::vec3(0,0,0), SCREEN_WIDTH/SCREEN_HEIGHT);
	// Set view matrix to identity to avoid rendering problems
	mgl.setViewMatrix(glm::mat4());

	// Setup gl states 
	mgl.setupGL();

	sprite.setup(64.0f,64.0f,"testimage.png");
	sprite.setOrigin(32.0f, 32.0f);
	sprite.setPosition(60.0f, 60.0f);
	cube.setTexture("testimage.png");
	cube.setScale(5.0f);

	printf("Resources loaded\n");
	return 1;
}

/**
* Called when finished to free resources 
*/
void free_resources()
{
	printf("Free Resources...\n");

	// Wait for update thread to finish
	SDL_WaitThread(thread, NULL);

	// Unload program
	glUseProgram(0);
	// Disable gl states 
	mgl.endGL();

	printf("Resources Freed\n");
}

/** 
 * Update game state 
 */
void onUpdate(){
	// Figure out delta time in seconds 
	// Grab current ticks 
	int mTime = SDL_GetTicks();
	// Get the time since the last update 
	int diff = mTime - lastTime;
	deltaTime = (float)diff / 1000.0f;
	// Set this time as the last time 
	lastTime = mTime;

	// Do main updates if window is visible 
	if (WINDOW_VISIBLE){
		// Update input 
		// Note: this does not actually grab the input, but
		// runs helper code nessesary for it to work correctly. 
		mMouseH.update();
		mKeyH.update(deltaTime);


		sprite.setRotation(sprite.getRotation() + 1.0f);
		cube.setRotationX(cube.getRotationX() + 1.0f);
		cube.setRotationY(cube.getRotationY() + 1.0f);
	}
}

/*
* Render game to screen 
*/
void onDraw()
{
	// Clear screen
	glClearColor(0.25f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	mgl.setProjectionMatrix(mgl.orthoMatrix);

	sprite.draw(mgl);

	mgl.setProjectionMatrix(mgl.camera3DMatrix);

	cube.draw(mgl);
}
 
/** Game loop to update game state **/
int gameLoop(void *ptr){
	int beginTime; 		// the time when the cycle begun
	int timeDiff = 0; 	// the time it took for the cycle to execute
	int sleepTime; 		// ms to sleep ( < 0 if we're behind)
	int framesSkipped;  // number of frames being skipped
	sleepTime = 0;

	// Main update loop for the game 
	while(running){
		// Get the current system time in miliseconds 
		beginTime = SDL_GetTicks(); 
					
		// Update Game 
		onUpdate();
					
		// Draws Game
		if (!render)
			render = true;
					
		// calculate how long the cycle took in miliseconds 
		timeDiff = SDL_GetTicks() - beginTime;
		// calculate sleep time
		sleepTime = FRAME_PERIOD - timeDiff;
		// If sleepTime > 0 we're OK			
		if (sleepTime > 0)
			SDL_Delay(sleepTime);
		
		// Update if behind 
		framesSkipped = 0; // reset the frames skipped
		while (sleepTime < 0 && framesSkipped < MAX_FRAME_SKIPS){
			printf("Skipped Frame: \n");
			// We need to catch up, update without rendering
			onUpdate();
			sleepTime += FRAME_PERIOD;
			framesSkipped++;
		}
	}

	return 0;
}

/**
* Updates window events and renders screen. 
*/
void eventAndRenderLoop(){
	SDL_Event windowEvent;
	while (running)
	{
		// Check events 
        while( SDL_PollEvent( &windowEvent ) ){
			if (windowEvent.type == SDL_QUIT) running = false;

			if (windowEvent.type == SDL_WINDOWEVENT) {
				switch (windowEvent.window.event) {
				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					WINDOW_VISIBLE = true;
					break;
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_FOCUS_LOST:
					WINDOW_VISIBLE = false;
					break;
				case SDL_WINDOWEVENT_RESIZED:
					break;
				default:
					break;
				}
			}

			// Update IO handler 
			mKeyH.updateState(windowEvent);
			mMouseH.updateState(windowEvent);
        }

		// Render if requested 
		if (render && WINDOW_VISIBLE){
			// Call main drawing function 
			onDraw();
			
			// check OpenGL error
			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				printf("OpenGL error: %d\n", err);
			}

			// Swap buffers 
			SDL_GL_SwapWindow(window);
			render = false;
		}
	}
}

int main(int argc, char* argv[])
{
	createGame();

	// Exit  
    exit(EXIT_SUCCESS);
}

// Game a new game 
void createGame(){
	// ======= Setup ======= //
	// Setup SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Get display settings 
	SDL_DisplayMode current;
    if(SDL_GetDesktopDisplayMode(0, &current) == 0)
        printf("Display #%d: current display mode is %dx%dpx @ %dhz. \n", 0, current.w, current.h, current.refresh_rate);
	else 
	    cout << "ERROR: " << SDL_GetError() << "\n";

	// Create Window 
	window = SDL_CreateWindow("GLSL Example", 40, 40, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	// Create the window context 
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// OpenGL Extension wrangler initialising  
	glewExperimental = GL_TRUE; 
	GLenum glew_status = glewInit();
	// Close if glew could not be set up 
	if (glew_status != GLEW_OK){
		fprintf(stderr, "Error Setting up GLEW: %s\n", glewGetErrorString(glew_status));
		exit(EXIT_FAILURE);
	}

	// GLEW Debug information
	cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << "\n";
	if (GLEW_VERSION_4_0) cout << "Core extensions of OpenGL 1.1 to 4.0 are available.\n";
	else if (GLEW_VERSION_3_0) cout << "Core extensions of OpenGL 1.1 to 3.0 are available.\n";
	else if (GLEW_VERSION_2_1) cout << "Core extensions of OpenGL 1.1 to 2.1 are available.\n";
	else if (GLEW_VERSION_2_0) cout << "Core extensions of OpenGL 1.1 to 2.0 are available.\n";
	else if (GLEW_VERSION_1_5) cout << "Core extensions of OpenGL 1.1 to 1.5 are available.\n";
	// Opengl Debug Information
	cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
	cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	cout << "GL Version: " << glGetString(GL_VERSION) << "\n";
	cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	
	// Load resources 
	if (init_resources() == 1){
		// ======= Run ======= //

		// Create game loop thread 
		running = true;
		thread = SDL_CreateThread( gameLoop, "gameLoop", (void *)NULL);

		// Run Event and render loop 
		eventAndRenderLoop();
	}
	
	// ======= Exit ======= //

	// Free resoruces 
	free_resources();
	// Delete the window context
	SDL_GL_DeleteContext(context);
	// Destroy sdl window 
	SDL_DestroyWindow(window);

	// Unload SDL
	SDL_Quit();
}


