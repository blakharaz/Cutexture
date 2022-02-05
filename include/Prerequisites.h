/** This file is part of Cutexture.
 
 Copyright (c) 2010 Markus Weiland, Kevin Lang

 Portions of this code may be under copyright of authors listed in AUTHORS.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#pragma once

// Shut up 3rd-party warnings
#if OGRE_COMPILER == OGRE_COMPILER_MSVC
#pragma warning(push, 0)
#endif

#include <OGRE/OgreAxisAlignedBox.h>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreCommon.h>
#include <OGRE/OgreCompositorManager.h>
#include <OGRE/OgreConfigFile.h>
#include <OGRE/OgreConfigOptionMap.h>
#include <OGRE/OgreDataStream.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreException.h>
#include <OGRE/OgreHardwareBuffer.h>
#include <OGRE/OgreHardwarePixelBuffer.h>
#include <OGRE/OgreImage.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreMaterial.h>
#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreMatrix3.h>
#include <OGRE/OgreMeshManager.h>
#include <OGRE/OgreMovableObject.h>
#include <OGRE/OgrePixelFormat.h>
#include <OGRE/OgreQuaternion.h>
#include <OGRE/OgreRectangle2D.h>
#include <OGRE/OgreRenderable.h>
#include <OGRE/OgreRenderOperation.h>
#include <OGRE/OgreRenderQueue.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSharedPtr.h>
#include <OGRE/OgreSingleton.h>
#include <OGRE/OgreSphere.h>
#include <OGRE/OgreString.h>
#include <OGRE/OgreStringConverter.h>
#include <OGRE/OgreTechnique.h>
#include <OGRE/OgreTexture.h>
#include <OGRE/OgreTextureManager.h>
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/Bites/OgreWindowEventUtilities.h>

/*#include <FreeImage.h>*/

#include <OIS/OISInputManager.h>
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

#include <QtCore/QtCore>
#include <QtGui/QtGui>

#include <QtUiTools/QtUiTools>

#if OGRE_COMPILER == OGRE_COMPILER_MSVC
#pragma warning(pop)
#endif

// Disable warning about "assignment operator could not be generated."
#if OGRE_COMPILER == OGRE_COMPILER_MSVC
#pragma warning(disable: 4512)
#endif

namespace Cutexture
{
	class Core;
	class Exception;
	class InputManager;
	class OgreCore;
	class SceneManager;
	class SleepThread;
	class ViewManager;
	class Game;
	class Settings;
}

