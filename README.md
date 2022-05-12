# Monster Chase
This is a game engine development project. 

#### Projects
Following are the core projects used in the 
- RavenStd: Standard library with common functionality
- Raven: Core Game Engine
- MonsterChase: A sample game developed using Raven

#### Dependencies
Apart from the above, a few dependencies are added to the project
- GLib: A 2D rendering library

#### Basic Flow {#basic-flow}
- `Raven>src>Raven`: Source Directory for the game engine (Raven). Let's call this `[EngineSrc]`
- `MonsterChase>src>MonsterChase.cpp`: This is the entry file for the game. It extends the `Raven::Application`.
- `Raven>src>Raven>EntryPoint.h`: This is the application's entry point
- `[EngineSrc]>Application`: This is the base game application.

This is the basic flow of the game, once the application starts
```
void Application::App_StartGame() {
	if (m_GameStarted) return;

	// Initialization
	App_InitialiseSystems();
	GameStart(); // Virtual function available for override in Game App.

	while(!m_GameEnded) {
		// Get the frame time
		float delta = m_Timing->GetFrameTime();
		
		// Logs the frame time in trace mode
		SLib::Log::T("Last Frame Time = " + std::to_string(static_cast<int>(delta*1000)) + "ms");
		
		// Runs the Update
		App_UpdateSystems(delta);
		Update(delta);
	}

	// Destruction
	GameEnd(); //  Virtual function available for override in Game App.
	App_DestroySystems();
}
```

---

## EAE - 6310 Assignments
Check [Basic Flow](#basic-flow) section for an overview of the code design
#### 2.02 Numerial Integration
- Physics and Input Component located in `[EngineSrc]>Components`
- Physics and Input Systems are located in `[EngineSrc]>Systems`
- Timing located in `[EngineSrc]>Timing`

## Raven
The game engine is structured using the ECS Model

### Systems
#### Rendering System
Sprites are rendered using the GLib library

---

# EAE 6300 Assignments

## Final Exam

### Instructions
- Please enable the folder view in Project Explorer
- Ignore the README section of projects below for the final exam

### Test Case Files
Multiple test case files are used. Test cases are added for both the FSA and BitArray
- `TestBitArray.cpp` : Tests the working of a single bit array
- `TestFSA.cpp`: Tests the working of a single Fixed Size Allocator
- `CustomTests.cpp` contains smaller tests for bit manipulation, memset, and more


## Projects
The solution contains the following projects
### 1. Monster Chase
This is the main game project

### 2. MindPalace
This is the heap manager

### 3. MiscAssignments
All the miscellaneous assignments that do not belong to any particular project
1. Assignment 5 = Make Sentence
2. Assignment 6 = Flaws in Inheritance
3. Assignment 7 = Interview Questions

### 4. Raven
Raven is the name of the game engine. It is a static library of all the game engine code

### 5. RavenStd
RavenStd contains all the custom functionalities used in other projects for convenience
