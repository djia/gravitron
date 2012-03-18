
#include "InstructionManager.h"
#include "ObjectManager.h"
#include <iostream>


void CInstructionManager::ProcessInput(KeyState & rKeyState, MouseState & rMouseState) {

	//if (rKeyState.rgKeys[VK_F1]) 
	//	PostQuitMessage(0);

	for(int i = 0; i < m_pObjManager->m_Objs.size(); i++) {
		m_pObjManager->m_Objs[i]->ProcessUserInput(rKeyState, rMouseState);
	}

}