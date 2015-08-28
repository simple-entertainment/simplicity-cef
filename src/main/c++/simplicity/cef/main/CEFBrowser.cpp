/*
 * simple entertainment presents
 *      _                 _ _      _ _
 *     (_)               | (_)    (_) |
 *  ___ _ _ __ ___  _ __ | |_  ___ _| |_ _   _
 * / __| | '_ ` _ \| '_ \| | |/ __| | __| | | |
 * \__ \ | | | | | | |_) | | | (__| | |_| |_| |
 * |___/_|_| |_| |_| .__/|_|_|\___|_|\__|\__, |
 *                 | |                    __/ |
 *                 |_|                   |___/
 *
 * This file is part of simplicity.
 * See the LICENSE file for the full license governing this code.
 */
#include <cef_app.h>

#include <simplicity/input/KeyboardButtonEvent.h>
#include <simplicity/input/MouseButtonEvent.h>
#include <simplicity/input/MouseMoveEvent.h>
#include <simplicity/messaging/Messages.h>
#include <simplicity/messaging/Subject.h>

#include "CEFBrowser.h"
#include "SimpleClient.h"

using namespace std;

namespace simplicity
{
	namespace simcef
	{
		CEFBrowser::CEFBrowser(const Resource& initialPage, weak_ptr<Texture> texture) :
				browser(nullptr),
				entity(nullptr),
				initialPage(initialPage),
				texture(texture)
		{
		}

		void CEFBrowser::executeJavaScript(const std::string& code)
		{
			browser->GetMainFrame()->ExecuteJavaScript(code, browser->GetMainFrame()->GetURL(), 0);
		}

		void CEFBrowser::load(const Entity& entity)
		{
			this->entity = &entity;

			CefWindowInfo windowInfo;

			// We are supposed to pass a handle to our window here but CEF never actually needs it on Linux.
			// TODO Fix this because it is needed on other platforms.
			windowInfo.SetAsWindowless(0, true);

			CefRefPtr<SimpleClient> client(new SimpleClient(texture));
			browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), initialPage.getUri().c_str(),
											  CefBrowserSettings(), nullptr);

			Messages::registerRecipient(Subject::KEYBOARD_BUTTON,
										bind(&CEFBrowser::onKeyboardButton, this, placeholders::_1));
			Messages::registerRecipient(Subject::MOUSE_BUTTON,
										bind(&CEFBrowser::onMouseButton, this, placeholders::_1));
			Messages::registerRecipient(Subject::MOUSE_MOVE,
										bind(&CEFBrowser::onMouseMove, this, placeholders::_1));
		}

		bool CEFBrowser::onKeyboardButton(const Message& message)
		{
			const KeyboardButtonEvent* event = static_cast<const KeyboardButtonEvent*>(message.body);

			CefKeyEvent cefEvent;
			cefEvent.character = event->character;
			// TODO ...

			browser->GetHost()->SendKeyEvent(cefEvent);

			return false;
		}

		bool CEFBrowser::onMouseButton(const Message& message)
		{
			const MouseButtonEvent* event = static_cast<const MouseButtonEvent*>(message.body);

			CefMouseEvent cefEvent;
			//cefEvent.modifiers = ???; TODO
			cefEvent.x = event->x;
			cefEvent.y = event->y;

			CefBrowserHost::MouseButtonType button;
			if (event->button == Mouse::Button::LEFT)
			{
				button = CefBrowserHost::MouseButtonType::MBT_LEFT;
			}
			else if (event->button == Mouse::Button::MIDDLE)
			{
				button = CefBrowserHost::MouseButtonType::MBT_MIDDLE;
			}
			else if (event->button == Mouse::Button::RIGHT)
			{
				button = CefBrowserHost::MouseButtonType::MBT_RIGHT;
			}

			browser->GetHost()->SendMouseClickEvent(cefEvent, button, event->buttonState == Button::State::UP, 1);

			return false;
		}

		bool CEFBrowser::onMouseMove(const Message& message)
		{
			const MouseMoveEvent* event = static_cast<const MouseMoveEvent*>(message.body);

			CefMouseEvent cefEvent;
			//cefEvent.modifiers = ???; TODO
			cefEvent.x = event->x;
			cefEvent.y = event->y;

			browser->GetHost()->SendMouseMoveEvent(cefEvent, false); // TODO improve mouseleave

			return false;
		}

		void CEFBrowser::unload()
		{
			Messages::deregisterRecipient(Subject::KEYBOARD_BUTTON,
										bind(&CEFBrowser::onKeyboardButton, this, placeholders::_1));
			Messages::deregisterRecipient(Subject::MOUSE_BUTTON,
										bind(&CEFBrowser::onMouseButton, this, placeholders::_1));
			Messages::deregisterRecipient(Subject::MOUSE_MOVE,
										bind(&CEFBrowser::onMouseMove, this, placeholders::_1));
		}
	}
}
