### Folder Structure

RenderEngine: Classes related to rendering.
GameEngine: Classes related to game logic.
PhysicsEngine: Classes related to physics simulation.
UI: Classes related to user interface.
Content: Files that are used for the program. E.g: Models, Textures, Levels.

### Class Naming

RenderEngine: PS_{ClassName} - PS_Pipeline, PS_ModelLoader etc.
GameEngine: PS_Game{ClassName} - PS_GameObject, PS_GameLevel etc.
PhysicsEngine: PS_Physics{ClassName} - PS_PhysicsObject etc.
UI: PS_{ClassName} - PS_UserInterface, PS_StartMenu

Classes must be named in PascalCase. First letter of every word capitalized. E.g: PhysicsObject, GameObject. 

### Function Naming

Functions must be named in camelCase. First letter of every word other than first capitalized. E.g: drawFrame, createGraphicsPipeline. 

### Structures & Global Functions

Include Structures & Global Functions in the respective Generic header. E.g: PS_GameGeneric.hpp, PS_RenderGeneric.hpp

### Headers and Source

When creating a new folder, create a folder for Headers (.hpp / .h) and Source (.cpp / .c). Add the Headers folder in the Project additional include directories.

Add class, variable and function declarations in .hpp file and implementations in .cpp file. **Getters and Setters must be in .hpp file.**

### Notes
- Put everything in "namespace ps" for easier classification.
- Put external libraries in the /Libraries folder. Must download zip and extract in folder if downloading from Github.
