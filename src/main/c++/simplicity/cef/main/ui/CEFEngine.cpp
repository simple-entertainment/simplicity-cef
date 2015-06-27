/*
 * Copyright © 2015 Simple Entertainment Limited
 *
 * This file is part of The Simplicity Engine.
 *
 * The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <cef_app.h>

#include "../../common/SimpleApp.h"
#include "CEFEngine.h"

using namespace std;

namespace simplicity
{
	namespace simcef
	{
		void CEFEngine::advance()
		{
			CefDoMessageLoopWork();
		}

		void CEFEngine::onPlay()
		{
			int argc = 1;
			unique_ptr<char> argv(new char);
			char* rawArgv = argv.get();

			CefMainArgs args(argc, &rawArgv);
			CefRefPtr<CefApp> app(new SimpleApp);

			CefSettings settings;
			CefString(&settings.browser_subprocess_path).FromASCII("simplicity-cef-subprocess");
			settings.multi_threaded_message_loop = 0;
			//settings.single_process = 1;
			//settings.windowless_rendering_enabled = 1;

			CefInitialize(args, settings, app.get(), nullptr);
		}

		void CEFEngine::onStop()
		{
			CefShutdown();
		}
	}
}
