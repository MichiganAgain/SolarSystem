#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glm/glm.hpp>
#include <vector>

#include "shader.hpp"

/*
	The ShapeVertexModel class is used to store all the vertex information for a specific shape.
	This avoids duplication of vertex data for each shape created.  For example, if multiple spheres
	were created, it would cause unnecessary duplication of vertices, wasting space.  So for each unique
	shape created, it has its own respective vertex model which generates the vertices, and if any needed,
	the indices too.  This data and its layout are shared between all instances of that shape and is stored
	in the respective gl buffer object so it can be set when rendering.  aka the flyweight design.

	To achieve this, and make sure each shape object (ie sphere) doesn't contain it own unique sphere vertex model
	(which would defeat the purpose of having a vertex model in the first place), a shape requests an instance of
	its respective shape vertex model via a static instance function implemented in its shape vertex model class,
	which creates a static instance of the vertex and returns a pointer to this object.  Making it static ensures it
	is only created once.  This same vertex model object is then shared between all instances of that same shape.
	aka the singleton design. (apparently controversial to use but seemingly useful in this case as the gl objects
	still need to be initialized).
*/
class ShapeVertexModel {
    public:
        unsigned int getVertexArrayID();
        unsigned int getVertexBufferID();
        unsigned int getElementBufferID();
        const std::vector<float>& getVertices();
        const std::vector<unsigned int>& getIndices();
        
    protected:
        virtual void initVertices() = 0;
        virtual void initIndices() = 0;
        virtual void initGlObjects() = 0;

        unsigned int vertexArrayObjectID;
        unsigned int vertexBufferObjectID;
        unsigned int elementBufferObjectID;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
};

/*
	When updating the shape's positions with, for example gravity in the physics class.  If there are three shapes
	identical in mass: shape 1, 2 and 3 with the respective positions of (-100, 0, 0), (0, 0, 0) and (100, 0, 0).
	In the loop to make each shape feel the gravitational force of the others, if shapes 1 and 2 affect each others
	position with their gravitational fields, and their new positions are (-90, 0, 0) and (-10, 0, 0) respectively,
	by the time shape 1 or 2 with shape 3 affect each others positions with gravity, shape 1 would be 10 units closer
	to shape 3, and shape 2 10 units further away from shape 3, causing an innacurate calculation with the gravitational
	forces in other shapes in that same frame. Basically the problem is that the shapes will not be updated fairly and
	their previous interactions with shapes will have an innacurate impact on their next interactions with shapes in the
	same frame, especially in the case of gravity.

	To solve this a sort of double buffer design is used, where each shape stores its next state.  When updating each
	shape in the physics functions, the shapes next state object is updated instead of the actual shape itself.  This
	ensures the shape maintains its state for the next shapes so each other shape is fairly affected by it.  When it comes
	to calling the shapes update member function, the shapes variables are set to its next state variables, and the next
	state pointer is reset.
*/
struct ShapeState {
    glm::vec3 velocity;
    float SIZE;
    float mass;
};

class Shape {
    public:
        void update();
        virtual void render(Shader* shader) = 0;

        ShapeState* nextState = nullptr;
        glm::mat4 modelMatrix;
        glm::vec3 worldCoord;
        glm::vec3 velocity;
        float mass;
        bool lightSource = false;

    protected:
        void initializeNextState();
        
        ShapeVertexModel* model;
        unsigned int textureID;
        float SIZE;        
};

#endif
