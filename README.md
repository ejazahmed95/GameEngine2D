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
- JobSystem: A library for launching tasks/jobs

#### Basic Flow {#basic-flow}
- `Raven>src>Raven`: Source Directory for the game engine (Raven). Let's call this `[EngineSrc]`
- `MonsterChase>src>MonsterChase.cpp`: This is the entry file for the game. It extends the `Raven::Application`.
- `Raven>src>Raven>EntryPoint.h`: This is the application's entry point
- `[EngineSrc]>Application`: This is the base game application.
- `RavenStd>src>RavenStd`: Standard/Common library for Raven and Game. Let's call this `[StdSrc]`

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

#### Final Project
This is a gameplay of player vs monsters. Player can shoot the enemies using `SPACE`.

Stats:
- Player Health = 10
- Normal Enemy Health = 1
- Damage on Hit = 3

Controls:
- `WASD`: Moving the character around
- `E`: Rotate Left
- `R`: Rotate Right
- `SPACE`: Attack with an electro ball
- `Q`: Quit the game

#### 2.02 Numerial Integration
- Physics and Input Component located in `[EngineSrc]>Components`
- Physics and Input Systems are located in `[EngineSrc]>Systems`
- Timing located in `[EngineSrc]>Timing`

#### 2.03/2.04 Strong and Weak Pointers
- `[StdSrc]>memory` contains the implementation for strong and weak pointers
- Strong/Weak pointers are used in the application for storing references of game systems

#### 2.05 JSON Loader
- `MonsterChase>assets>data>scene.json`: This contains the scene heirarchy and a list of game objects to be loaded
- `[EngineSrc]>Editor>Editor.cpp`: This file contains the implementation for loading game objects using the json file

#### 2.06 Job System
The Job System is added as an additional dependency to the project.
`[EngineSrc]\Editor\Editor.cpp` contains a static method `LoadGameObjectsFromFile` that launches 2 Jobs in the ==JobSystem's Default Queue==.
1. First Job loads the `scene.json` file
2. Second Job loads the game objects from the filled json

The components are also added to the Entities(GameObject) in the job itself.

#### 2.07 Vector4 and Matrices
- `[StdSrc]>LinearAlgebra` contains both the vector4 and matrix classes
- `[StdSrc]>test` contains the MatrixTest function to test the basic functionality of a matrix.

#### 2.08 Collision
- `[EngineSrc]>Systems\CollisionSystem2D`: This system handles the collision detection for objects that have a transform and collision component
- `[EngineSrc]>Components\Collider2D`: This is the collision component that contains both the bounding box and a callback on collision detection
- Collider component also contains a variable `Continuous`. Enabling this will update the collision system to perform a Swept-Separating Axis check on those objects

---

## Raven
The game engine is structured using the ECS Model

### Entities
Basic form of a game object. Every entity is unique, and has a list of components that can be added to it.

### Components
Components are basic data structs that contain information. These can be accessed by the systems that act upon it.

### Systems
#### Rendering System
Sprites are rendered using the GLib library

#### Editor
The Editor namespace contains the logic for engine initialization using json files. The editor supports the following functionalities
- Loads the game objects from a given Json file (`scene.json`)


---

## RavenStd
Standard Library used by the Game Engine.

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
