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
#ifndef CEFENGINE_H_
#define CEFENGINE_H_

#include <map>

#include <simplicity/engine/Engine.h>

#include "CEFEngineState.h"

namespace simplicity
{
	namespace simcef
	{
		/**
		 * <p>
		 * An engine that renders HTML to a texture using the Chromium Embedded Framework.
		 * </p>
		 */
		class CEFEngine : public Engine
		{
			public:
				void advance(Scene& scene) override;

				void onBeforeOpenScene(Scene& scene) override;

				void onCloseScene(Scene& scene) override;

				void onPlay() override;

				void onStop() override;

			private:
				std::map<Scene*, CEFEngineState*> state;
		};
	}
}

#endif /* CEFENGINE_H_ */
