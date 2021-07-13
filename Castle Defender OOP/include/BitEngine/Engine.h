#ifndef __BE_CORE_H__
#define __BE_CORE_H__

namespace BE
{

class Engine
{
public:
	Engine() = default;	// Use default constructor
	virtual ~Engine() = default;	// Use default destructor

	void run();		// Runs the game
protected:
	virtual void initialize() = 0;	// Abstract initializer method
	virtual void shutdown() = 0;	// Abstract shutdown method for cleanup
private:
	void init();	// Makes all engine initialization
	void loop();	// Main loop
	void quit();	// Makes all engine cleanup
};

}

#endif // !__BE_CORE_H__
