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

#include "QmlUiManager.h"
#include "InputManager.h"
#include "Constants.h"
#include "TextureMath.h"
#include "Exception.h"

#include <OGRE/RenderSystems/GL/OgreGLTextureCommon.h>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtQuick/QQuickGraphicsDevice>
#include <QtQuick/QQuickRenderTarget>
#endif

using namespace Cutexture::Utility;

namespace Cutexture
{
	
    QmlUiManager::QmlUiManager() :
        mRenderControl(nullptr),
        mUiDirty(false),
        mInputManager(NULL)
	{
        mRenderControl = new QQuickRenderControl(this);
        mQuickWindow = new QQuickWindow(mRenderControl);

//        connect(mRenderControl, &QQuickRenderControl::renderRequested, this, &QmlUiManager::setUiDirty);
	}

    QmlUiManager::~QmlUiManager()
	{
	}
	
    void QmlUiManager::loadQml(const QUrl& url)
    {
	}
	
    void QmlUiManager::setInputManager(InputManager *aInputManager)
	{
		if (mInputManager && aInputManager != mInputManager)
		{
			disconnect(mInputManager, 0, this, 0);
		}
		
		if (aInputManager == 0 || !aInputManager->isInitialized())
		{
            EXCEPTION("InputManager not initialized.", "QmlUiManager::setInputManager(InputManager *)");
		}
		
		mInputManager = aInputManager;
		
		if (mInputManager)
		{
			connect(mInputManager, SIGNAL(mousePressEvent(QMouseEvent*)), this, SLOT(mousePressEvent(QMouseEvent*)));
			connect(mInputManager, SIGNAL(mouseReleaseEvent(QMouseEvent*)), this, SLOT(mouseReleaseEvent(QMouseEvent*)));
			connect(mInputManager, SIGNAL(mouseMoveEvent(QMouseEvent*)), this, SLOT(mouseMoveEvent(QMouseEvent*)));

			connect(mInputManager, SIGNAL(keyPressEvent(QKeyEvent*)), this, SLOT(keyPressEvent(QKeyEvent*)));
			connect(mInputManager, SIGNAL(keyReleaseEvent(QKeyEvent*)), this, SLOT(keyReleaseEvent(QKeyEvent*)));			
		}
	}
	
    void QmlUiManager::resizeTexture(const QSize &aSize, const Ogre::MaterialPtr &aMaterial, const Ogre::TexturePtr &aTexture)
	{
        assert(aMaterial != nullptr);
        assert(aTexture != nullptr);
		
		// get the smallest power of two dimension that is at least as large as the new UI size
		Ogre::uint newTexWidth = nextHigherPowerOfTwo(aSize.width());
		Ogre::uint newTexHeight = nextHigherPowerOfTwo(aSize.height());
	
        if (aTexture != nullptr)
		{
			std::string txtrName = aTexture->getName();
			
			// remove the old texture
			aTexture->unload();
			aMaterial->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
			Ogre::TextureManager::getSingleton().remove(aTexture->getHandle());
	
			Ogre::TexturePtr newTxtr = Ogre::TextureManager::getSingleton().createManual(
					txtrName, "General", Ogre::TEX_TYPE_2D, newTexWidth, newTexHeight, 0, Ogre::PF_A8R8G8B8,
					Ogre::TU_DYNAMIC_WRITE_ONLY);
	
			// add the new texture
			Ogre::TextureUnitState* txtrUstate = aMaterial->getTechnique(0)->getPass(0)->createTextureUnitState(txtrName);
	
			// adjust it to stay aligned and scaled to the window
			Ogre::Real txtrUScale = (Ogre::Real)newTexWidth / aSize.width();
			Ogre::Real txtrVScale = (Ogre::Real)newTexHeight / aSize.height();
			txtrUstate->setTextureScale(txtrUScale, txtrVScale);
			txtrUstate->setTextureScroll((1 / txtrUScale) / 2 - 0.5, (1 / txtrVScale) / 2 - 0.5);
		}
	}
	
    void QmlUiManager::resizeUi(QResizeEvent *aEvent)
	{
        mQuickWindow->resize(aEvent->size());
	}
	
    void QmlUiManager::mousePressEvent(QMouseEvent *event)
	{
//		QWidget *pressedWidget = NULL;
	
//		// get the clicked item through the view (respects view and item transformations)
//		QGraphicsItem* itemAt = mWidgetView->itemAt(event->pos());
//		if ((itemAt) && (itemAt->isWidget()))
//		{
//			QGraphicsProxyWidget *proxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget *>(itemAt);
//			if (proxyWidget)
//			{
//				QWidget *embeddedWidget = proxyWidget->widget();
	
//				// if the widget has children, use them, otherwise use the widget directly
//				if (embeddedWidget->children().size() > 0)
//				{
//					QPoint widgetPoint = proxyWidget->mapFromScene(mWidgetView->mapToScene(event->pos())).toPoint();
//					pressedWidget = embeddedWidget->childAt(widgetPoint);
//				}
//				else
//				{
//					pressedWidget = embeddedWidget;
//				}
//			}
//		}
	
//		// if there was a focused widget and there is none or a different one now, defocus
//		if (mFocusedWidget && (!pressedWidget || pressedWidget != mFocusedWidget))
//		{
//			QEvent foe(QEvent::FocusOut);
//			QApplication::sendEvent(mFocusedWidget, &foe);
//			mFocusedWidget = NULL;
//			mTopLevelWidget->setFocus();
//		}
	
//		// set the new focus
//		if (pressedWidget)
//		{
//			QEvent fie(QEvent::FocusIn);
//			QApplication::sendEvent(pressedWidget, &fie);
//			pressedWidget->setFocus(Qt::MouseFocusReason);
//			mFocusedWidget = pressedWidget;
//		}
	
//		QApplication::sendEvent(mWidgetView->viewport(), event);
	}
	
    void QmlUiManager::mouseReleaseEvent(QMouseEvent *event)
	{
//		QApplication::sendEvent(mWidgetView->viewport(), event);
	}
	
    void QmlUiManager::mouseMoveEvent(QMouseEvent *event)
	{
//		QApplication::sendEvent(mWidgetView->viewport(), event);
	}
	
    void QmlUiManager::keyPressEvent(QKeyEvent *event)
	{
//		QApplication::sendEvent(mWidgetView->viewport(), event);
	}
	
    void QmlUiManager::keyReleaseEvent(QKeyEvent *event)
	{
//		QApplication::sendEvent(mWidgetView->viewport(), event);
	}
	
    void QmlUiManager::setUiDirty(bool aDirty)
	{
		mUiDirty = aDirty;
	}
	
    bool QmlUiManager::isViewSizeMatching(const Ogre::TexturePtr &aTexture) const
	{
        assert(aTexture != nullptr);
		
        return (aTexture->getWidth() == mQuickWindow->width() && aTexture->getHeight() == mQuickWindow->height());
	}
	
    void QmlUiManager::setViewSize(const Ogre::TexturePtr &aTexture)
	{
		// make sure that the view size matches the texture size
        if (aTexture != nullptr && !isViewSizeMatching(aTexture))
		{
            mQuickWindow->setGeometry(QRect(0, 0, aTexture->getWidth(), aTexture->getHeight()));
		}
	}

    void QmlUiManager::initialize(const Ogre::TexturePtr &aTexture)
    {
        mOgreTexture = aTexture;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        if (!mRenderControl->initialize())
        {
            qWarning("Failed to initialize redirected Qt Quick rendering");
        }
#else
        //        if (!mRenderControl->initialize())
        //        {
        //            qWarning("Failed to initialize redirected Qt Quick rendering");
        //        }
#endif

        auto glTexture = std::static_pointer_cast<Ogre::GLTextureCommon>(aTexture);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        mQuickWindow->setRenderTarget(
            QQuickRenderTarget::fromOpenGLTexture(glTexture->getGLID(),
                                                  QSize(glTexture->getWidth(), glTexture->getHeight()),
                                                  glTexture->getFSAA()));
#else
        mQuickWindow->setRenderTarget(glTexture->getGLID(), QSize(glTexture->getWidth(), glTexture->getHeight()));
#endif

        mInitialized = true;
    }

    void QmlUiManager::renderIntoTexture()
	{
        assert(mOgreTexture != nullptr);
        assert(isViewSizeMatching(mOgreTexture));
		
        Ogre::HardwarePixelBufferSharedPtr hwBuffer = mOgreTexture->getBuffer(0, 0);
		hwBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
		
		const Ogre::PixelBox &pb = hwBuffer->getCurrentLock();

        if (!mInitialized) {
            // TODO: Throw
        }

        mRenderControl->polishItems();

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        mRenderControl->beginFrame();
#endif

        mRenderControl->sync();
        mRenderControl->render();

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        mRenderControl->endFrame(); // Qt Quick's rendering commands are submitted to the device context here
#endif

		// render into texture buffer		
		hwBuffer->unlock();
	}
}
