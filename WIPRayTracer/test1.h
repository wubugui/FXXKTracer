#pragma once 
#include <iostream>
#include "BaseGeometryObject.h"
#include "TraceData.h"
#include "Ray.h"
#include "ViewPanel.h"
#include "World.h"
#include <windows.h>

int main()
{
	World w;
	w.build(10);
	w.render();
	w.out_put();
	std::cout << "Done!" << std::endl;
	//system("pause");
	return 0;
}
