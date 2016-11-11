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

#include "CEFEngine.h"

using namespace std;

namespace simplicity
{
	namespace simcef
	{
		void CEFEngine::advance(Scene& scene)
		{
			CefDoMessageLoopWork();
		}

		void CEFEngine::onPlay()
		{
			CefSettings settings;
			CefString(&settings.browser_subprocess_path).FromASCII("lib/simplicity-cef-subprocess");
			CefString(&settings.locales_dir_path).FromASCII("assets/cef/locales");
			CefString(&settings.resources_dir_path).FromASCII("assets/cef");

			CefInitialize(CefMainArgs(0, nullptr), settings, nullptr, nullptr);
		}

		void CEFEngine::onBeforeOpenScene(Scene& scene)
		{
			unique_ptr<CEFEngineState> state(new CEFEngineState);

			this->state[&scene] = state.get();
			scene.addState(move(state));
		}

		void CEFEngine::onCloseScene(Scene& scene)
		{
			CEFEngineState* state = this->state[&scene];
			this->state.erase(&scene);
			scene.removeState(*state);
		}

		void CEFEngine::onStop()
		{
			CefShutdown();
		}
	}
}
